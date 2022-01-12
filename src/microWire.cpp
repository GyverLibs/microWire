#include "microWire.h"

void TwoWire::begin() 
{	  												// Инициализация шины в роли master
    pinMode(SDA, INPUT_PULLUP); 					// Подтяжка шины 
    pinMode(SCL, INPUT_PULLUP);						// Подтяжка шины 
    TWBR = 72;										// Стандартная скорость - 100kHz
    TWSR = 0;										// Делитель - /1 , статус - 0;
}

void TwoWire::setClock(uint32_t clock) 
{ 													// Функция установки частоты шины 31-900 kHz (в герцах)
    TWBR = (((long)F_CPU / clock) - 16) / 2; 		// Расчет baudrate - регистра
}

void TwoWire::beginTransmission(uint8_t address) 
{ 													// Начать передачу (для записи данных)
    TwoWire::start();                        		// Старт
    TwoWire::write(address << 1);            		// Отправка slave - устройству адреса с битом "write"
}

uint8_t TwoWire::endTransmission(void)
{ 													// Завершить передачу и отпустить шину
    return TwoWire::endTransmission(true);
}

uint8_t TwoWire::endTransmission(bool stop) 
{													// Завершить передачу (после записи данных)
    if (stop) TwoWire::stop();                    	// Если задано stop или аргумент пуст - отпустить шину
    else TwoWire::start();                      		// Иначе - restart (другой master на шине не сможет влезть между сообщениями)
    if (_address_nack) {               				// Если нет ответа при передаче адреса
        _address_nack = false;            				// Обнуляем оба флага
        _data_nack = false;               				// Обнуляем оба флага
        return 2;                   					// Возвращаем '2'
    } if (_data_nack) {               				// Если нет ответа при передаче данных
        _address_nack = false;             				// Обнуляем оба флага
        _data_nack = false;              				// Обнуляем оба флага
        return 3;                   					// Возвращаем '2'
    } return 0;										// Если все ОК - возвращаем '0'
}

size_t TwoWire::write(uint8_t data)
{													// Прямая отправка байта на шину
    TWDR = data;									// Записать данные в data - регистр
    TWCR = _BV(TWEN) | _BV(TWINT);				    // Запустить передачу
    while (!(TWCR & _BV(TWINT)));					// Дождаться окончания
    uint8_t _bus_status = TWSR & 0xF8;				// Чтение статуса шины
    if(_bus_status == 0x20) _address_nack = true;	// SLA + W + NACK ? - нет ответа при передаче адреса
    if(_bus_status == 0x30) _data_nack = true;		// BYTE + NACK ? - нет ответа при передаче данных
	return 1;                                       // для совместимости с Wire API
}

uint8_t TwoWire::available() 
{													// Вернуть оставшееся количество запрошенных для чтения байт
    return _requested_bytes;						// Это содержимое этой переменной
}

uint8_t TwoWire::read()
{						  							// Прямое чтение байта из шины после запроса
    if (--_requested_bytes) {					    // Если байт не последний 						
        TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);	// Запустить чтение шины (с подтверждением "ACK")
        while (!(TWCR & _BV(TWINT)));				// Дождаться окончания приема данных
        return TWDR;								// Вернуть принятые данные , это содержимое data - регистра 
    }
    _requested_bytes = 0; 							// Если читаем последний байт
    TWCR = _BV(TWEN) | _BV(TWINT);					// Запустить чтение шины (БЕЗ подтверждения "NACK")
    while (!(TWCR & _BV(TWINT)));					// Дождаться окончания приема данных
    if (_stop_after_request) TwoWire::stop();  		// Если в requestFrom не задан аргумент stop , или stop задан как true - отпустить шину
    else TwoWire::start();							// Иначе - restart (другой master на шине не сможет влезть между сообщениями)
    return TWDR;									// Вернуть принятый ранее байт из data - регистра
}

uint8_t TwoWire::requestFrom(uint8_t address , uint8_t length) 
{  													// Запрос n-го кол-ва байт от ведомого устройства и отпускание шины
    return TwoWire::requestFrom(address , length , true); 
}

uint8_t TwoWire::requestFrom(uint8_t address , uint8_t length , bool stop) 
{  													// Запрос n-го кол-ва байт от ведомого устройства (Читайте все байты сразу!!!)
    _stop_after_request = stop; 					// stop или restart после чтения последнего байта
    _requested_bytes = length;						// Записать в переменную количество запрошенных байт
    TwoWire::start();								// Начать работу на шине
    TwoWire::write((address << 1) | 0x1);			// Отправить устройству адрес + бит "read" 
	return length;									// вернуть длину сообщения для совместимости с оригинальной Wire API
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop){
	return requestFrom(address , quantity , sendStop!=0);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop){
	if (isize > 0) {
	  // send internal address; this mode allows sending a repeated start to access
	  // some devices' internal registers. This function is executed by the hardware
	  // TWI module on other processors (for example Due's TWI_IADR and TWI_MMR registers)

	  beginTransmission(address);

	  // the maximum size of internal address is 4 bytes
	  // не понятно почему ограничение размерности регистра в оригинальной Wire API в 3 байта
	  if (isize > 4){
		isize = 4;
	  }

	  // write internal register address - most significant byte first
	  while (isize-- > 0)
		write((uint8_t)(iaddress >> (isize*8)));
	  endTransmission(false);
    }

   return requestFrom(address, quantity, sendStop);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

size_t TwoWire::write(const uint8_t *buffer, size_t size){
	for (size_t i = 0 ; i < size; ++i)
		write(buffer[i]);
	return size;
}

void TwoWire::start()
{													// сервисная функция с нее начинается любая работа с шиной
    TWCR = _BV(TWSTA) | _BV(TWEN) | _BV(TWINT); 	// start + TwoWire enable + установка флага "выполнить задачу"
    while (!(TWCR & _BV(TWINT)));					// Ожидание завершения 
}

void TwoWire::stop() 
{													// сервисная функция ей заканчивается работа с шиной
    TWCR = _BV(TWSTO) | _BV(TWEN) | _BV(TWINT);		// stop + TwoWire enable + установка флага "выполнить задачу"
}

TwoWire Wire = TwoWire();