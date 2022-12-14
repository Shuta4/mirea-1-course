# Тема 1. Информация и информатика
## Информация
В XX веке было совершено множество попыток дать определение информации. Некоторые варианты опрееделений:
- Информация - набор статистических данных (Фишер 1921)
- Информация - матпеременная, принимающая одно из значений с одинаковой вероятностью (Хартли 1928)
- Информация - сигналы, полезные для получателя, в результате получения которых уменьшается неопределенность знаний (Шеннон 1948)
- Информация - знания, которые используются для управления системой (Винер 1948)
- Информация - это информация, а не материя или энергия (Винер 1948)
- Информация - совокупность сведений, которые циркулируют в природе, обществе и в техсистемах (Глушков)
- Информация - характеристика не самого сообщения, а результат взаимодействия между сообщением и его потребителем (Колмогоров)
- Информация - сведения (сообщения, данные) независимо от формы их представления (по 149-ФЗ):
	- Сведения - известия, сообщения о чем-либо данные, характеризующие что-либо, а также знания в какой-либо области (Малый академсловарь)
	- Сведения - знания, критерий истинности которых не одинаков у различных участников познавательного процесса, иначе говоря, это знания, в истинности которых можно сомневаться (толковый словарь по информатике 2008 г)
	- Знания - проверенный практикой результат познания действительности, т.е. ее верное отражение в сознании человека (Малый академсловарь)
	- Знания - выяленные закономерности предметной области, описывающие действующие в ней принципы, наблюдаемые в ней связи, протекающие в ней процессы. Знаниня позволяют решать задачи в рассматриваемой области (толковый словарь по информатике)
- Информация - знания относительно фактов, событий, вещей, идей и понятий, которые в определенном контексте имеют конкретный смысла (перевод ISO)

Информация:
- с учетом смысловой составляющей:
	- с учетом новизны сведений
	- без учета новизны сведений

Информация - новые сведения (об объектах, процессах, явлениях), полученные методом интерпретации данных на материальном носителе.

## Данные
1. Данные - сигналы, зарегистрированные на материальном носителе.
2. Сигнал - изменяющийся во времени физический процесс, обладающий различными характеристиками. Виды сигналов:
	1. Аналоговый
	2. Цифровой
	3. Двоичный сигнал - частный случай цифрового:
		1. Нижний и верхний уровень
		2. Передний и задний фронт

		```
		              Структура
		           Верхний уровень
		                  |
		                  V
		Передний фронт -> 01 <- Задний фронт
		                  ^
		                  |
		            Нижний уровень
		ДДР

		Сведения -Сигналы-> Данные -Сигналы-> Новый сведения
		```

## Метод интерпретации
1. Из одних и тех же данных можно извлечь разные сведения при помощи разных методов интерпретации.
2. Если неизвестен метод, при помощи которого источник сведений записал данные, то невознможно применить адекватный метод интерпретации данных, чтобы получить исходные данные.

Метод интерпретации - алгоритм получения информации из данных.

## Свойства информации
1. Объективность
2. Точность
3. Достоверность (объективная информация всегда достоверна, субъективная информация не всегда достоверна)
4. Полнота
5. Актуальность (наличие нужной информации в момент принятия решения)
6. Полезность (применимость для решения задач)
7. Синтаксическая адекватность (соответствие потребностям получателя):
	- Тип носителя
	- Скорость передачи
	- Способ кодирования
	- Точность представления
8. Связность (с носителем)
9. Осмысленность
10. Неисчерпаемость (неподверженность физическому старению, накопляемость, тиражируемость)
11. Количество (кол-во состояний информационной системы):
	1. Количество (по Хартли):
		- Состояния системы равновероятны.
		- Предложил меру колва инф, основанную на двоичной системе счисления.
		- 1 бит - колво инф, приобритаемой приобретаемое получателем одного из двух равновероятных сообщений о состоянии некоторой системы.
	2. Количество (по Шеннону):
		- Расширение формулы Хартли для случая получения одного из N не равновероятных сообщений.
		- Усредненное количество информации при получении какого-либо сообщения о состоянии системы.
12. Объем - размер памяти, необходимый для хранения текста сообщения (зависит от используемой кодировки).

## Информатика
Концепции информатики:
1. Информатика - междисциплинарное научное направление, изучающее вопросы производства, хранения, накопления, передачи, обработки и использования информации при помощи ЭВМ.
2. Информатика - методология работы с информацией, определяющая информационную культуру личности человека (Глушков).
