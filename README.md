![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# microWire
Лёгкая библиотека со стандартным набором инструментов для работы с аппаратным I2C
- Облегчайте свой код простой заменой Wire.h на microWire.h
- ATmega168/328p (nano,uno,mini), ATmega32u4 (leonardo,micro) , ATmega2560 (mega)

### Совместимость
AVR ATmega168/328p (nano,uno,mini), ATmega32u4 (leonardo,micro), ATmega2560 (mega)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **microWire** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/microWire/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
Нет

<a id="usage"></a>
## Использование
```cpp
void begin(void);            				// инициализация шины
void setClock(uint32_t clock);       		// ручная установка частоты шины 31-900 kHz (в герцах)
void beginTransmission(uint8_t address); 	// открыть соединение (для записи данных)
uint8_t endTransmission(bool stop);  		// закрыть соединение , произвести stop или restart (по умолчанию - stop)
uint8_t endTransmission(void);  			// закрыть соединение , произвести stop
void write(uint8_t data);                	// отправить в шину байт данных , отправка производится сразу , формат - byte "unsigned char"
void requestFrom(uint8_t address , uint8_t length , bool stop); //открыть соединение и запросить данные от устройства, отпустить или удержать шину
void requestFrom(uint8_t address , uint8_t length);  			//открыть соединение и запросить данные от устройства, отпустить шину
uint8_t read(void);                      	// прочитать байт , БУФЕРА НЕТ!!! , читайте сразу все запрошенные байты , stop или restart после чтения последнего байта, настраивается в requestFrom
uint8_t available(void);                 	// вернет количество оставшихся для чтения байт
```

<a id="example"></a>
## Пример
```cpp
/* Пример записи и чтения данных в I2C - EEPROM "AT24C32" */

// #include <Wire.h> // заменяем Wire.h на microWire.h
#include <microWire.h>

uint8_t chipAddress = 0x57; // адрес устройства (используйте i2c scaner для определения)
uint16_t cellAddress = 3064; // адрес первой ячейки , куда будем писать и откуда читать
uint8_t data_0 = 115; // данные , которые запишем в EEPROM ( сравнивайте с этим числом при чтении )
uint8_t data_1 = 14;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  /* запись */
  Wire.beginTransmission(chipAddress);  // начинаем передачу с устройством , зовем по адресу
  Wire.write(highByte(cellAddress));    // отправляем старший байт первой адреса ячейки
  Wire.write(lowByte(cellAddress));     // отправляем младший байт первой адреса ячейки
  Wire.write(data_0);                   // отпарвляем байт данных
  Wire.write(data_1);                   // отпарвляем еще байт данных
  Wire.endTransmission();               // завершаем передачу

  delay(50);                            // подождем

  /* чтение */
  Wire.beginTransmission(chipAddress);  // начинаем передачу с устройством , зовем по адресу
  Wire.write(highByte(cellAddress));    // отправляем старший байт адреса  первой ячейки
  Wire.write(lowByte(cellAddress));     // отправляем младший байт адреса  первой ячейки
  Wire.endTransmission();               // завершаем передачу
  Wire.requestFrom(chipAddress , 2);    // запрашиваем свои 2 байта данных
  while (Wire.available()) {            // пока запрошенные данные не кончились
    Serial.println(Wire.read());        // читаем и выводим их
  }
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v2.1
- v2.2 от firexx - добавлены функции для полной совместимости с API Wire

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!