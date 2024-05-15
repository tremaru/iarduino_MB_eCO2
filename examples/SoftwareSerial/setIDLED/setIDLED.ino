// ПРИМЕР ВИЗУАЛЬНОГО ОБНАРУЖЕНИЯ УСТРОЙСТВА:                                      //
                                                                                   //
#include <SoftwareSerial.h>                                                        //   Подключаем библиотеку для работы с программной шиной UART.
#include <iarduino_Modbus.h>                                                       //   Подключаем библиотеку для работы по протоколу Modbus.
#include <iarduino_MB_eCO2.h>                                                      //   Подключаем библиотеку для работы с модулем углекислого газа.
                                                                                   //
SoftwareSerial   rs485(8,9);                                                       //   Создаём объект для работы с программной шиной UART-RS485 указывая выводы RX, TX.
ModbusClient     modbus(rs485, 2);                                                 //   Создаём объект для работы по протоколу Modbus указывая объект программной шины UART-RS485 и вывод DE конвертера UART-RS485.
iarduino_MB_eCO2 sensor(modbus);                                                   //   Создаём объект для работы с модулем углекислого газа указывая объект протокола Modbus.
                                                                                   //
void setup(){                                                                      //
     rs485.begin(9600); // while(!rs485);                                          //   Инициируем работу с программной шиной UART-RS485 указав её скорость.
     modbus.begin();                                                               //   Инициируем работу по протоколу Modbus.
//   modbus.setTimeout(10);                                                        //   Указываем максимальное время ожидания ответа по протоколу Modbus.
//   modbus.setDelay(4);                                                           //   Указываем минимальный интервал между отправляемыми сообщениями по протоколу Modbus.
//   modbus.setTypeMB( MODBUS_RTU );                                               //   Указываем тип протокола Modbus: MODBUS_RTU (по умолчанию), или MODBUS_ASCII.
     sensor.begin(6);                                                              //   Инициируем работу с модулем углекислого газа, указав его адрес. Если адрес не указан sensor.begin(), то он будет найден, но это займёт некоторое время.
//   sensor.setPeriod( 1.0f );                                                     //   Указываем модулю обновлять данные датчика углекислого газа каждую секунду.
}                                                                                  //
                                                                                   //
void loop(){                                                                       //
//   Мигаем светодиодом обнаружения устройства (на разъёме):                       //
     sensor.setIDLED(true ); delay(1000);                                          //   Включаем  светодиод на 1 секунду.
     sensor.setIDLED(false); delay(1000);                                          //   Отключаем светодиод на 1 секунду.
}                                                                                  //