// Calculater.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class Osnova
{
	/*переменные*/
public:
	int countActive,			/*Количество активов*/
		countPassive,			/*количство пассивов*/
		mount,					/*выбранный № месяца*/
		countDay;				/*количество дней*/
	int sum,					/*резльтат*/
		numberMonth;			/*номер месяца*/
	bool _isStateAction,		/*Наличие дополнительной деятельности*/
		_isReady ;				/*Указан весь перечень товаров, работ и услуг*/
	string dateOperaion;
	ofstream file;
	int countOperation = 0;		/*наличае операций*/
#pragma region Основная функция прогаммы
	void MainCode()
	{
		file.open((char*)"report.txt", ios_base::out); /*открываем файл (создаем)*/
		file << "годовая бухгалтерская отчетность" << endl;
		sum = 0;
		numberMonth = 0;
		cout << "P.S. Месяцы указазны в цифрах с января по декабрь (с 1 по 12 месяцы)" << endl;
		cin >> numberMonth;
		for (mount = 1; mount <= 12; mount++)
		{
			file << "Месяц № " << numberMonth << endl;
			cout << "Наличие финансовых операций в месяце(0-нет, 1 - да): - " << mount << endl;
			cin >> countOperation;			
			if (countOperation != 0)
			{
				CountDayToMonth(numberMonth);
				moveMoney();
			}
		}
		cout << "Расчет выполнен. Рузкльтат сохранен в отдельный файл, спасибо за внимание!-)" << endl;
		file.close(); /*закрываем файл. сохранился в каталоге программы*/
	}

	/*метод описывающий действия с количеством операций в месяце*/
	void CountDayToMonth(int d)
	{
		countDay = 0;
		cout << " Месяц - " + d << endl;
		if (d == 4 or d == 6 || d == 9 || d == 11)
		{			
			countDay = 30;		
		}
		else if (d == 2)
		{
			countDay = 28;		
		}
		else
			countDay = 31;
		cout << "количество дней: " << countDay << endl;		
	}

	/*Движение денежных средств*/
	void moveMoney()
	{
		ResultToWork();
		/*Метод выручки от иных действий*/
		anotherAction();		
		/*действия с капиталом*/
		Manipalationcapital();
	}

public :
	int number,
		countCoast =0 ,   /*количество*/
		countCoastJob = 0,
		countCoastService = 0;
	string nameGoods,
		nameJob,
		nameService;

	int coast = 0,
		coastJob = 0,
		coastService = 0;

	int resultGoods = 0,    /*выручка за товары*/
		resultJob = 0,		/*выручка за работу*/
		resultService = 0;  /*выручка за услуги*/
	/*выручка за товары и работу, услуги*/
#pragma region Отчет результат работы компании
	void ResultToWork()
	{ 
		bool _loopState = false;
		/*пока не закончиться заполнение товар, работ и услуг*/
		while (_loopState == false)
		{
			/*внесение информации 1- товары, 2- работа, 3 - услуга*/			
			cout << "Выберите категорию по каторой вы хотите внести информацию по выручке(1-товар, 2 - работа, 3- услуга): " << endl;
			cin >> number;
			if (number == 1)
			{
				/*товар*/
				cout << "Введите дату операции: " << endl;
				cin >> dateOperaion;
				cout << "Введите название товара: " << endl;				
				cin >> nameGoods;
				cout << "Введите количество " << endl;
				cin >> countCoast;
				/*стоимость товара*/
				cout << "Введите стоимость товара:" << endl;				
				cin >> coast;
			}
			else if (number == 2)
			{
				/*работа*/
				cout << "Введите дату операции: " << endl;
				cin >> dateOperaion;
				cout << "Введите название работы: " << endl;
				cin >> nameJob;
				cout << "Введите стоимость работы: " << endl;
				cin >> coastJob;
			}
			else if (number == 3)
			{
				/*услуга*/
				cout << "Введите дату операции: " << endl;
				cin >> dateOperaion;
				cout << "Введите название услуги: " << endl;
				cin >> nameService;
				cout << "Введите стоимость услуги: " << endl;
				cin >> coastService;
			}
			resultGoods = countCoast * coast; /*стоимость товаров*/
			resultJob = countCoastJob * coastJob; /*стоисость работ*/
			resultService = countCoastService * coastService;  /*стоимость услуг*/
			/*Запись результатов*/
			
			file << "Дата: " << dateOperaion << endl;
			file << "товар: " << nameGoods << " стоимость: " << resultGoods << endl;
			file << "работы: " << nameJob << " стоимость: " << resultJob << endl;
			file << "услуги: " << nameService << "стоимость: " << resultService << endl;
			
			
			/*выход или продолжение*/
			cout << "Хотите продолжить заполнять?: y/n" << endl;
			char c;
			cin >> c;
			if (c == 'y' || c == 'Y')
			{
				_loopState = false;
				sum = resultGoods + resultJob + resultService + sum;
			}
			if (c == 'n' || c == 'N')
			{
				_loopState = true;
				sum = resultGoods + resultJob + resultService + sum;
				/*Расчет вырчки с учетом налогов*/
				cout << "выручка за месяц составляет: " << sum << endl;
				sum = (sum / 100) * 13;		/*подоходный*/
				file << "выручка за месяц составляет: " << sum;
				cout << "с учетом подоходного налога: " << sum << endl;
				sum = (sum / 100) * 4;		/*пенсия*/
				file << "пенсионные отчисления: " << sum;
				cout << "пенсионные отчисления: " << sum << endl;
				sum = (sum / 100) * 23;		/*страховая*/
				cout << "с учетом страховой части:" << sum << endl;
				file << "с учетом страховой части:"  << sum;
			}
		}
		
	}
#pragma endregion
#pragma region отчет по иным действиям
	public:
		string nameAction;
		int sizeMoney;
	/*Выручка от иных действий*/
	void anotherAction()
	{
		cout << "Имеется ли не учтенная деятельность? Если да, нажмите один, если нет, - нажмите 0: " << endl;
		int priznak;
		cin >> priznak;
		if (priznak == 1)
		{
			cout << "Введите назание деятельности, которую необходимо учесть: ";
			cin >> nameAction;
			cout << "Укажите размер выручки от учтенной деятельности: " << endl;
			cin >> sizeMoney;
			file << "Деятельность:" << nameAction << " Размер выручки: " << sizeMoney;
		}
		else if (priznak == 0)
		{
			file << "Дополнительной деятельности нет" << endl;
			return;
		}
	}

#pragma endregion

  public:
	  int ustavCapital,  /*устанвной капитал*/
		  sumCapital,	 /*сумма уставного капитала*/
	  kvartal;			 /*квартал*/
	  void Manipalationcapital()
	  {
		  kvartal = 1;
		  while (kvartal < 4)
		  {			  
			  cout << "Введите значине уставного капитала компании за " << kvartal << "ый квартал: " << endl;
			  cin >> ustavCapital;
			  sumCapital = ustavCapital + sumCapital;
			  file << "Уставной капитал за " << kvartal << " квартал составляет: " << sumCapital;
			  kvartal++;
		  }
	  }
#pragma endregion

};


int main()
{
	setlocale(LC_ALL, "Russian");
	/*cout << "Привет!";
    std::cout << "Hello World!\n"; */
	Osnova osn;
	osn.MainCode();
}

