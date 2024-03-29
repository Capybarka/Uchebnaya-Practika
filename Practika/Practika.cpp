﻿#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <intrin.h>
#include <set>
using namespace std;

int count_words(string text);
bool check(char x);
vector <string> split(string text);
vector <string> clear(vector <string> words);
vector <string> sort(vector <string> words);


int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введитe путь файла с текстом: ";
	string pathText;
	cin >> pathText;

	ifstream fileWithText;  // прочитать из файла
	fileWithText.open(pathText);

	if (!fileWithText.is_open())
	{
		cout << "ERROR" << endl << "Не удалось открыть файл" << endl << "Повторите попытку\n";
		exit(0);
		cout << endl;
	}


	if (fileWithText.is_open() and (fileWithText.peek() == EOF))  // если файл открылся и первый символ это конец файла
	{
		cout << "Файл пустой\n" << "Повторите попытку\n";
		exit(0);
		cout << endl;
	}


	string str;
	string text = "";

	while (getline(fileWithText, str)) // считываем строку из файла и прибавляем ее к тексту
	{
		text = text + str;
	}

	// ПОДСЧЕТ ВРЕМЕНИ СОРТИРОВКИ //

	clock_t begin = clock();
	vector <string> final = sort(clear(split(text)));
	clock_t end = clock();

	float time = float(end - begin) / CLOCKS_PER_SEC;

	// ВЫВОД ОТСОРТИРОВАННОГО ВЕКТОРА В ФАЙЛ //

	ofstream fileResult;  // запись в файл
	fileResult.open("Result.txt");

	vector<string>::iterator i_word;

	for (i_word = final.begin(); i_word < final.end(); i_word++)  // от начала до конца вектора
	{
		fileResult << *i_word << endl;
	}

	fileResult.close();

	cout << "\nТекст:\n" << endl << text << endl;

	cout << "\nВариант 19: латиница, по кол-ву символов в слове, по убыванию, игнорировать числа, сортировка пузырьком\n"
		<< "\nКоличество слов в тексте: " << count_words(text) << endl << "\nВремя сортировки: " << time << " секунд\n"
		<< "\nСтатистика (количество слов каждой длины): \n";

	ofstream fileAnalisys;
	fileAnalisys.open("Analisys.txt");

	fileAnalisys << "Текст:\n" << endl << text << endl;

	fileAnalisys << "\nВариант 19: латиница, по кол-ву символов в слове, по убыванию, игнорировать числа, сортировка пузырьком\n"
		<< "\nКоличество слов в тексте: " << count_words(text) << endl << "\nВремя сортировки: " << time << " секунд\n"
		<< "\nСтатистика (количество слов каждой длины): \n";


	// ВЫВОД В КОНСОЛЬ И В ФАЙЛ CТАТИСТИКИ //

	vector <string> words = sort(clear(split(text)));  // вектор содержит уже отсортированные слова
	vector <int> count_len;  // вектор длин каждого слова

	for (string str : words)  // для каждой строки из вектора words
	{
		count_len.push_back(str.size());  // добавляет в вектор длинy словa
	}

	set <int> uniq_set_len;
	uniq_set_len.insert(count_len.begin(), count_len.end());  // добавляет в uniq_set уникальные элементы из вектора count_len

	vector <int > uniq_elem;
	copy(uniq_set_len.begin(), uniq_set_len.end(), back_inserter(uniq_elem));  // переход от set в vector


	for (int i = 0; i < uniq_elem.size(); i++)
	{
		cout << "Количество слов длины " << uniq_elem[i] << " - " << count(count_len.begin(), count_len.end(), uniq_elem[i]) << endl;
		fileAnalisys << "Количество слов длины " << uniq_elem[i] << " - " << count(count_len.begin(), count_len.end(), uniq_elem[i]) << endl;
	}

	fileAnalisys.close();
	fileWithText.close();
}


bool check(char x) // функция проверяет, является ли символ буквой или цифрой
{
	if (((x <= '9') and (x >= '1')) or ((x >= 'A' and x <= 'Z') or (x >= 'a' and x <= 'z')))
	{
		return true;
	}

	else
	{
		return false;
	}
}


int count_words(string text)  // функция считает количество слов, не учитывая числа и лишние символы
{
	int begin = 0;
	int end = 0;
	int count = 0;

	while (begin != text.size())  // проверяем все символы от начала до конца строки
	{
		while ((begin != text.size()) and (text[begin] == ' ' or check(text[begin]) == false))
			// пока символ не пробел и это не конец строки и символ не является буквой или цифрой 
		{
			begin++;  // передвигаем начало на единицу
		}

		end = begin;  // позицию первой буквы записываем в end


		while ((end != text.size() and text[end] != ' ') and (check(text[begin]) == true))
			// пока символ не пробел и это не конец строки и символ является буквой или цифрой 
		{
			end++;  // сдвигаемся вперед
		}

		if (begin != end)  // если позиция последней буквы равна позиции первой буквы, то это значит, что мы нашли словo
		{
			count++;  // увеличиваем счетчик слов
			begin = end;  // начало равно позиции последней буквы найденного слова
		}
	}
	return count;
}


vector <string> split(string text)
{
	string probel = " ";
	text.append(probel);

	vector <string> words;
	vector <char> symbol_of_word;

	for (char symbol : text)
	{
		if (symbol != ' ')
		{
			symbol_of_word.push_back(symbol);
		}

		else
		{
			string word(symbol_of_word.begin(), symbol_of_word.end());
			words.push_back(word);
			symbol_of_word.clear();
		}

	}
	return words;
}


vector <string> clear(vector <string> words)   // функция удаляет лишние символы
{
	vector <string> newWords;
	vector <char> symbol_newWords;

	for (string str : words)  // для каждой строки из вектора words
	{
		for (char symbol : str)  // для каждого символа из строки str
		{
			if ((symbol >= 'a' and symbol <= 'z') or (symbol >= 'A' and symbol <= 'Z'))
			{
				symbol_newWords.push_back(symbol);  // добавляем символ во временный вектор symbol_newWords
			}
		}

		string new_word(symbol_newWords.begin(), symbol_newWords.end());  //от начала до конца слова

		if (new_word.size() != 0)   // если длина слова не равна 0
		{
			newWords.push_back(new_word);  // добавляем это слово в массив всех слов
		}
		symbol_newWords.clear();  // очищаем временную переменную 
	}
	return newWords;
}


vector <string> sort(vector <string> words)  // функция сортирует слова пузырьком по убыванию
{
	string str;

	for (unsigned int i = 0; i < words.size(); i++)
	{
		for (unsigned int j = 0; j < words.size() - 1; j++)
		{
			if (words[j].size() < words[j + 1].size())  // если длина слова меньше чем длина следующего слова
			{
				str = words[j];
				words[j] = words[j + 1];
				words[j + 1] = str;
			}
		}
	}
	return words;
}

