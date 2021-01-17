#include<cstdlib>
#include<iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <Windows.h>
using namespace std;


int wordCounter(string* _str, string _word);
void printFile(char* _str, int _size, string _word);
void printFile(string _str, int _size, string _word);
string* splitString(string _tmp);
int wordCounter(string* _str, string _word);

void printFile(char* _str, int _size, string _word)
{
	string str = string(_str);
	printFile(str, _size, _word);
}

void printFile(string _str, int _size, string _word) {
	int count = 0;
	string tmp = "";
	for (int i = 0; i < _size; i++)
	{
		if (i == 0 && _str[i] == ' ') continue;
		if (_str[i] == '.' || _str[i] == '!' || _str[i] == '?')
		{
			if (_str[i + 1] == ' ') i++;
			tmp += '\0';
			cout << tmp << endl;
			count = wordCounter(splitString(tmp), _word);
			if (count != 0) cout << "Слово <" << _word << "> встречается в предложении " << count << " раз!" << endl;
			tmp = "";
		}
		else
		{
			tmp += _str[i];
		}
	}
}

string* splitString(string _tmp)
{
	int i = 0, size = 0;
	while (_tmp[i] != 0)
	{
		if (_tmp[i] == ' ') size++;
		i++;
	}
	size++;
	string* str = new string[size];
	string razdelitel = " ";
	size_t pos = 0;
	int wordCounter = 0;
	i = 0;
	while ((pos = _tmp.find(razdelitel)) != string::npos)
	{
		str[i] = _tmp.substr(0, pos);
		_tmp.erase(0, pos + razdelitel.length());
		i++;
	}
	return str;
}

int wordCounter(string* _str, string _word) {
	int i = 0, wordCount = 0;
	while (_str[i] != "")
	{
		if (_str[i] == _word) wordCount++;
		i++;
	}
	return wordCount;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	char filename[25];
	cout << "File name? ";
	cin >> filename;

#pragma region fstream
	cout << "FSTREAM" << endl;
	int wordCount = 0, fileSize = 0;
	ifstream file;
	file.open(filename, ifstream::binary);
	if(file.is_open())
	{
		//Размер файла
		file.seekg(0, file.end); //Переходим в конец файла
		fileSize = file.tellg(); //Смотрим сколько байт прочитано
		file.seekg(0, file.beg); //Переходим в начало файла

		char* buffer = new char[fileSize];

		file.read(buffer, fileSize);

		if (file)
		{
			cout << "Все символы были прочитаны!" << endl;
			string word;
			cout << "Введите искомое слово: "; cin >> word;
			printFile(buffer, fileSize, word);
		}
		else
		{
			cout << "Ошибка: только " << file.gcount() << " символов было прочитано!";
		}
	}
	else cout << "File not found!" << endl;
	file.close();
#pragma endregion fstream

	cout << "\n=========================================================================\n\n";

#pragma region file
	cout << "FILE*" << endl;
	FILE* file_1;
	char buffer[255];
	string fstr, temp;
	fopen_s(&file_1, filename, "rb");
	if (file_1 != NULL)
	{
		while (fgets(buffer, 255, file_1))
		{
			fstr += buffer;
		}
		wordCount = 0;
		string word;
		cout << "Введите искомое слово: "; cin >> word;
		printFile(fstr, fstr.length(), word);
	}
	else cout << "File not found!" << endl;
	fclose(file_1);
#pragma endregion file

	system("pause");
	return 0;
}