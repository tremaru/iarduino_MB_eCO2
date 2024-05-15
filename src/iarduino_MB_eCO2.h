//	Библиотека для работы с датчиком углекислого газа по шине Modbus: https://iarduino.ru
//  Версия: 1.0.2
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru
//  Подробное описание функции бибилиотеки доступно по ссылке: https://wiki.iarduino.ru
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_MB_eCO2_h
#define iarduino_MB_eCO2_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <iarduino_Modbus.h>														//	Подключаем файл iarduino_Modbus.h - для работы по протоколу Modbus.
																					//
	#define DEF_MODEL_eCO2				11											//	Идентификатор модели eCO2 - константа.
																					//
//	#define ERROR_SHT_INIT				0b00000001									//	Ошибка возвращаемая функцией checkSensor() - ошибка инициализации датчика влажности и температуры SHT20.
//	#define ERROR_SHT_DATA				0b00000010									//	Ошибка возвращаемая функцией checkSensor() - ошибка чтения данных датчика влажности и температуры SHT20.
	#define ERROR_SGP_INIT				0b00000100									//	Ошибка возвращаемая функцией checkSensor() - ошибка инициализации датчика углекислого газа SGP30.
	#define ERROR_SGP_DATA				0b00001000									//	Ошибка возвращаемая функцией checkSensor() - ошибка чтения данных датчика углекислого газа SGP30.
//	#define ERROR_LTR_INIT				0b00010000									//	Ошибка возвращаемая функцией checkSensor() - ошибка инициализации датчика освещенности и приближения LTR-553ALS-01.
//	#define ERROR_LTR_DATA				0b00100000									//	Ошибка возвращаемая функцией checkSensor() - ошибка чтения данных датчика освещенности и приближения LTR-553ALS-01.
																					//
class iarduino_MB_eCO2{																//
	public:																			//
	/**	Конструктор класса **/														//
		iarduino_MB_eCO2				(ModbusClient&	);							//	Объявляем конструктор класса.											Параметры: ссылка на объект работы по протоколу Modbus.
	/**	Пользовательские функции **/												//
		bool			begin			(uint8_t id=0	);							//	Объявляем  функцию инициализации модуля датчиков.						Параметры функции: ID модуля датчиков. Функция возвращает результат инициализации: true-успех / false-провал.
		bool			reset			(void			);							//	Объявляем  функцию перезагрузки модуля датчиков.						Параметры функции: нет. Функция возвращает результат перезагрузки: true-успех / false-провал.
		bool			changeID		(uint8_t new_id	);							//	Объявляем  функцию смены ID модуля датчиков (выполняется >120мс).		Параметры функции: новый ID. Функция возвращает результат смены ID: true-успех / false-провал.
		bool			setSpeedMB		(uint32_t speed	);							//	Объявляем  функцию смены скорости передачи данных.						Параметры функции: новая скорость. Функция возвращает результат смены скорости: true-успех / false-провал. Скорость необходимо подтвердить в течении 2 секунд.
		bool			ackSpeedMB		(void			);							//	Объявляем  функцию подтверждения скорости (выполняется >50мс).			Параметры функции: нет. Функция возвращает результат подтверждения скорости: true-успех / false-провал. 
		bool			setTypeMB		(uint8_t type	);							//	Объявляем  функцию смены типа протокола Modbus.							Параметры функции: MODBUS_RTU/MODBUS_ASCII. Функция возвращает результат смены типа протокола Modbus: true-успех / false-провал. Тип необходимо подтвердить в течении 2 секунд.
		bool			ackTypeMB		(void			);							//	Объявляем  функцию подтверждения типа протокола (выполняется >50мс).	Параметры функции: нет. Функция возвращает результат подтверждения типа протокола Modbus: true-успех / false-провал. 
		bool			writeFlash		(uint16_t data	);							//	Объявляем  функцию записи пользовательского значения в Flash память.	Параметры функции: целое беззнаковое число от 0 до 65535. Функция возвращает результат записи: true-успех / false-провал. 
		int32_t			readFlash		(void			);							//	Объявляем  функцию чтения пользовательского значения из Flash памяти.	Параметры функции: нет. Функция возвращает прочитанное значение, или -1 при провале чтения.
		uint8_t			getID			(void			){ return valID;	}		//	Определяем функцию получения текущего ID (адрес модуля на шине).		Параметры функции: нет. Функция возвращает текущий ID модуля датчиков, или 0 если модуль не определён.
		uint8_t			getVersion		(void			){ return valVers;	}		//	Определяем функцию получения текущей версии прошивки модуля датчиков.	Параметры функции: нет. Функция возвращает версию прошивки модуля датчиков, или 0 если модуль не определён.
		float			getPWR			(void			);							//	Объявляем  функцию получения напряжения питания.						Параметры функции: нет. Функция возвращает напряжение питания в Вольтах, или -1 при провале чтения.
		bool			setIDLED		(bool on		);							//	Объявляем  функцию смены состояния светодиода обнаружения устройства.	Параметры функции: состояние светодиода true/false. Функция возвращает результат изменения состояния: true-успех / false-провал.
		int32_t			getErr			(void			);							//	Объявляем  функцию получения флагов ошибок из регистра диагностики.		Параметры функции: нет. Функция возвращает значение регистра диагностики, каждый из 16 бит которого является флагом ошибки, или -1 при провале чтения.
		int8_t			checkSensor		(void			);							//	Объявляем  функцию проверки датчика модуля.								Параметры функции: нет. Функция возвращает ERROR_SGP_INIT/ERROR_SGP_DATA, 0 если ошибок нет, или -1 при провале чтения.
		bool			setHeating		(bool on		);							//	Объявляем  функцию управления нагревательным элементом датчика.			Параметры функции: состояние нагревательного элемента.
		int8_t			getHeating		(void			);							//	Объявляем  функцию получения состояния нагревательного элемента.		Параметры функции: нет. Функция возвращает состояние нагревательного элемента true/false, или -1 при провале чтения.
		float			getCO2			(void			);							//	Объявляем  функцию получения количества эквивалента СО2.				Параметры функции: нет. Функция возвращает количество частей на миллион ( 400ppm ... 60'000ppm ), или -1 при провале чтения.
		float			getTVOC			(void			);							//	Объявляем  функцию получения общего кол-ва летучих органич. соединений.	Параметры функции: нет. Функция возвращает количество частей на миллиард ( 0ppb ... 60'000ppb ), или -1 при провале чтения.
		bool			setPeriod		(float sec		);							//	Объявляем  функцию смены периода опроса датчика.						Параметры функции: период опроса в секундах ( 0,1...6553,5с ). Функция возвращает результат изменения периода опроса: true-успех / false-провал.
		float			getPeriod		(void			);							//	Объявляем  функцию получения периода опроса датчика.					Параметры функции: нет. Функция возвращает период опроса в секундах ( 0,1...6553,5с ), или -1 при провале чтения.
																					//	
	private:																		//	
	/**	Внутренние переменные **/													//
		ModbusClient*	objModbus;													//	Объявляем  указатель на объект работы по протоколу Modbus.				Указатель получит адрес объекта в конструкторе класса.
		uint8_t			valID			= 0;										//	Определяем переменную для хранения ID модуля который был проверен.
		uint8_t			valVers			= 0;										//	Определяем переменную для хранения версии прошивки модуля.
		uint8_t			maxRW			= 5;										//	Определяем максимальное количество попыток чтения/записи.
	/**	Внутренние функции **/														//
		int8_t			MB_readDO		(uint16_t reg							);	//	Дублер функции objModbus.coilRead();             Чтение одного регистра DO, из  модуля valID, maxRW попыток. Параметры функции: адрес регистра. Функция возвращает прочитанное значение (0/1), или -1 при неудаче.
		int8_t			MB_readDI		(uint16_t reg							);	//	Дублер функции objModbus.discreteInputRead();    Чтение одного регистра DI, из  модуля valID, maxRW попыток. Параметры функции: адрес регистра. Функция возвращает прочитанное значение (0/1), или -1 при неудаче.
		int32_t			MB_readAO		(uint16_t reg							);	//	Дублер функции objModbus.holdingRegisterRead();  Чтение одного регистра AO, из  модуля valID, maxRW попыток. Параметры функции: адрес регистра. Функция возвращает прочитанное значение (0...65535), или -1 при неудаче.
		int32_t			MB_readAI		(uint16_t reg							);	//	Дублер функции objModbus.inputRegisterRead();    Чтение одного регистра AI, из  модуля valID, maxRW попыток. Параметры функции: адрес регистра. Функция возвращает прочитанное значение (0...65535), или -1 при неудаче.
		uint16_t		MB_requestFrom	(uint8_t  type, uint16_t reg, uint16_t n);	//	Дублер функции objModbus.requestFrom();          Чтение нескольк регистров, из  модуля valID, maxRW попыток. Параметры функции: тип регистра (COILS/DISCRETE_INPUTS/HOLDING_REGISTERS/INPUT_REGISTERS), адрес первого регистра, количество регистров. Функция возвращает количество прочитанных значений, или 0 при неудаче.
		uint8_t			MB_getInfo		(uint8_t  id							);	//	Дублер функции objModbus.getInfo();              Чтение информации о устройстве модуля id   , maxRW попыток. Параметры функции: id модуля. Функция возвращает количество байт данных об устройстве, доступных для чтения функцией read() и available().
		int32_t			MB_diagnostic	(uint16_t func, uint16_t data=0			);	//	Дублер функции objModbus.diagnostic();           Выполнение команды диагностики модуля valID, maxRW попыток. Параметры функции: номер функции диагностики, данные. Функция возвращает данные результата выполнения функции диагностики, или -1 при неудаче.
		bool			MB_changeID		(uint8_t  newID							);	//	Дублер функции objModbus.changeID();             Сохранение нового ID     , для модуля valID, maxRW попыток. Параметры функции: новый id модуля. Функция возвращает результат сохранения адреса (0/1).
		bool			MB_writeDO		(uint16_t reg, bool val					);	//	Дублер функции objModbus.coilWrite();            Запись в один регистр  DO, для модуля valID, maxRW попыток. Параметры функции: адрес регистра, значение (0/1). Функция возвращает 1 при успехе, 0 при неудаче.
		bool			MB_writeAO		(uint16_t reg, uint16_t val				);	//	Дублер функции objModbus.holdingRegisterWrite(); Запись в один регистр  AO, для модуля valID, maxRW попыток. Параметры функции: адрес регистра, значение (0...65535). Функция возвращает 1 при успехе, 0 при неудаче.
};

#endif