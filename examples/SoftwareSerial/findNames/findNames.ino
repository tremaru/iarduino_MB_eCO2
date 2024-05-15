// ПРИМЕР ПОЛУЧЕНИЯ СПИСКА АДРЕСОВ И НАЗВАНИЙ ВСЕХ УСТРОЙСТВ НА ШИНЕ:              //
                                                                                   //
#include <SoftwareSerial.h>                                                        //   Подключаем библиотеку для работы с программной шиной UART.
#include <iarduino_Modbus.h>                                                       //   Подключаем библиотеку для работы по протоколу Modbus.
                                                                                   //
SoftwareSerial     rs485(8,9);                                                     //   Создаём объект для работы с программной шиной UART-RS485 указывая выводы RX, TX.
ModbusClient       modbus(rs485, 2);                                               //   Создаём объект для работы по протоколу Modbus указывая объект программной шины UART-RS485 и вывод DE конвертера UART-RS485.
                                                                                   //
void setup(){                                                                      //
     Serial.begin(9600);   while(!Serial);                                         //   Инициируем передачу данных в монитор последовательного порта, указав его скорость.
     rs485.begin(9600); // while(!rs485 );                                         //   Инициируем работу с программной шиной UATR-RS485 указав её скорость.
     modbus.begin();                                                               //   Инициируем работу по протоколу Modbus.
//   modbus.setTimeout(10);                                                        //   Указываем максимальное время ожидания ответа по протоколу Modbus.
//   modbus.setDelay(4);                                                           //   Указываем минимальный интервал между отправляемыми сообщениями по протоколу Modbus.
//   modbus.setTypeMB( MODBUS_RTU );                                               //   Указываем тип протокола Modbus: MODBUS_RTU (по умолчанию), или MODBUS_ASCII.
                                                                                   //
     Serial.println(F("Поиск устройств..."));                                      //
//   Выполняем поиск всех устройств на шине (занимает несколько секунд):           //
     uint8_t sum = modbus.findID();                                                //   Функция возвращает количество найденных адресов.
     if( sum ){                                                                    //
     //  Устройства найдены:                                                       //
         Serial.print(F("Найдено устройств "));                                    //
         Serial.print(sum);                                                        //
         Serial.println(':');                                                      //
     //  Создаём массив для хранения всех найденных адресов устройств:             //
         uint8_t arrAdr[sum];                                                      //
     //  Заполняем массив адресами найденных устройств:                            //
         uint8_t i=0; while( modbus.available() ){ arrAdr[i++]=modbus.read(); }    //   Заполняем каждый элемент массива адресами, используя функции available() и read().
     //  Выполняем действия для каждого найденного устройства:                     //
         for(i=0; i<sum; i++){                                                     //
             Serial.print(F("Адрес "));                                            //
             Serial.print(arrAdr[i]  );                                            //   Выводим адрес очередного устройства
             Serial.print(F(" - ")   );                                            //
         //  Получаем название устройства с адресом arrAdr[i]:                     //
             int8_t j = modbus.getName(arrAdr[i]);                                 //   Функция возвращает длину строки с названием устройства.
         //  Выводим название устройства в монитор:                                //
             if(j>0){while(modbus.available()){Serial.print((char)modbus.read());}}//   Выводим название побайтно, используя функции available() и read().
             else   {Serial.print(F("без названия"));} Serial.println('.');        //   Если j<=0, значит модуль не поддерживает вывод названия.
         }                                                                         //
//   Если sum==0, значит устройства не найдены:                                    //
     }else{ Serial.println(F("Не найдено ни одного устройства.")); }               //
}                                                                                  //
                                                                                   //
void loop(){                                                                       //
}                                                                                  //