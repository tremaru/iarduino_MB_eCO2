// ПРИМЕР УПРАВЛЕНИЯ НАГРЕВАТЕЛЬНЫМ ЭЛЕМЕНТОМ ДАТЧИКА:                             //
// По умолчанию, нагревательный элемент включается при подачи питания на модуль.   //
// Модуль отвечает: CO2=400ppm, TVOC=0ppb, если нагрев отключён setHeating(false), //
// или с момента включения нагревательного элемента прошло менее 15 секунд.        //
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
     Serial.begin(9600); while(!Serial);                                           //   Инициируем передачу данных в монитор последовательного порта, указав его скорость.
     rs485.begin(9600); while(!rs485);                                             //   Инициируем работу с программной шиной UART-RS485 указав её скорость.
     modbus.begin();                                                               //   Инициируем работу по протоколу Modbus.
//   modbus.setTimeout(10);                                                        //   Указываем максимальное время ожидания ответа по протоколу Modbus.
//   modbus.setDelay(4);                                                           //   Указываем минимальный интервал между отправляемыми сообщениями по протоколу Modbus.
//   modbus.setTypeMB( MODBUS_RTU );                                               //   Указываем тип протокола Modbus: MODBUS_RTU (по умолчанию), или MODBUS_ASCII.
     sensor.begin(6);                                                              //   Инициируем работу с модулем углекислого газа, указав его адрес. Если адрес не указан sensor.begin(), то он будет найден, но это займёт некоторое время.
//   sensor.setPeriod( 1.0f );                                                     //   Указываем модулю обновлять данные датчика углекислого газа каждую секунду.
}                                                                                  //
                                                                                   //
uint8_t t=0;                                                                       //
                                                                                   //
void loop(){                                                                       //
//   На первой секунде работы цикла loop():                                        //
     if( t==0 ){                                                                   //
     //  Включаем нагревательный элемент датчика углекислого газа:                 //
         sensor.setHeating( true );                                                //
     //  Информируем о состоянии нагревательного элемента:                         //
         Serial.print(F("Нагревательный элемент "));                               //
         switch( sensor.getHeating() ){                                            //   Читаем состояние нагревательного элемента.
             case -1:    Serial.println(F("не удалось прочитать.")); break;        //   Если -1, значит функция sensor.getHeating() не смогла прочитать данные.
             case true:  Serial.println(F("включён." )); break;                    //   Если true,  значит нагревательный элемент включён.
             case false: Serial.println(F("отключён.")); break;                    //   Если false, значит нагревательный элемент отключён.
         }                                                                         //
     }                                                                             //
//   На 30 секунде работы цикла loop():                                            //
     if( t==30 ){                                                                  //
     //  Отключаем нагревательный элемент датчика углекислого газа:                //
         sensor.setHeating( false );                                               //
     //  Информируем о состоянии нагревательного элемента:                         //
         Serial.print(F("Нагревательный элемент "));                               //
         switch( sensor.getHeating() ){                                            //   Читаем состояние нагревательного элемента.
             case -1:    Serial.println(F("не удалось прочитать.")); break;        //   Если -1, значит функция sensor.getHeating() не смогла прочитать данные.
             case true:  Serial.println(F("включён." )); break;                    //   Если true,  значит нагревательный элемент включён.
             case false: Serial.println(F("отключён.")); break;                    //   Если false, значит нагревательный элемент отключён.
         }                                                                         //
     }                                                                             //
//   На 35 секунде работы цикла loop():                                            //
     t++; if( t==35 ){ t=0; }                                                      //
                                                                                   //
//   Выводим показания модуля независимо от состояния нагревательного элемента:    //
     delay(1000);                                                                  //
     Serial.print( (String) "CO2="  + sensor.getCO2()  + "ppm, "    );             //   Выводим количество эквивалента СО2 (углекислого газа).
     Serial.print( (String) "TVOC=" + sensor.getTVOC() + "ppb.\r\n" );             //   Выводим общее количество летучих органических соединений.
}                                                                                  //