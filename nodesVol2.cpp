#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <fstream>

struct node {
	char symbol;
	int amount;
	struct node* next;
};

node* AddNode(node* head, char _symbol);
node* MoveNode(node* head, node* requiredNode);
node* SearchNode(node* head, char _symbol);
//node* SearchAddress(node* head, node* tmp);
void PrintNode(node* head);



/*
20.	Описать односвязный линейный список, тип значения элемента которого — запись из двух полей : 
символ и количество его повторений в тексте.Сформировать список из заданного текста. Реализовать метод вставки, 
выполняющий вставку отсутствующего в списке символа в его конец и перемещение на один элемент к началу списка элемента с 
присутствующим в списке значением.
*/


// Вот с этим у меня как раз и были проблемы, я написал какую-то функцию, но она по другому работает, если находится символ, у которого количество вхождений как у передаваемого, то он передвигается на один
//вперед
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	/*std::string s;
	std::cout << "Введите строку: " << std::endl;
	getline(std::cin, s);*/

	std::string filename;
	std::cout << "Введите имя файла: ";
	std::cin >> filename;
	int fileSize;
	std::ifstream file;
	file.open(filename, std::ifstream::binary);
	if (file.is_open())
	{
		file.seekg(0, file.end);
		fileSize = file.tellg();
		file.seekg(0, file.beg);

		char* buffer = new char[fileSize+1];

		file.read(buffer, fileSize);
		buffer[fileSize] = '\0';

		if (file)
		{
			/*std::cout << "Все символы были прочитаны!" << std::endl;
			std::map<char, int> m;
			for (size_t i = 0; i < std::string(buffer).size(); i++)
				if (std::string(buffer)[i] != ' ') m[std::string(buffer)[i]]++;

			for (auto i = m.begin(); i != m.end(); i++)
				std::cout << i->first << "->" << i->second << std::endl;

			std::cout << "==========================" << std::endl;*/

			node* head = NULL;
		/*	for (auto i = m.begin(); i != m.end(); i++)
			{
				head = AddNode(head, i->first, i->second);
			}*/


			for (size_t i = 0; i < std::string(buffer).size(); i++)
			{
				head = AddNode(head, buffer[i]);
			}

			PrintNode(head);
		}
		else
		{
			std::cout << "Ошибка! Было прочитано только " << file.gcount() << " символов!";
		}
	}
	else std::cout << "Файл не найден!" << std::endl;
	file.close();
	return 0;
}


node* AddNode(node* head, char _symbol)
{
	node* temp;
	if (head == NULL)
	{
		head = new node;
		head->symbol = _symbol;
		head->amount = 1;
		head->next = NULL;
	}
	else
	{
		int count = 0;
		node* t = SearchNode(head, _symbol);
		if (t && t!=head) head = MoveNode(head, t);
		else
		{
			node* newNode = head;
			if (newNode->next != NULL)
			{
				while (newNode->next != NULL)
				{
					newNode = newNode->next;
				}
			}

			temp = new node;
			temp->symbol = _symbol;
			temp->amount = 1;
			newNode->next = temp;
			temp->next = NULL;
		}
	}
	return head;
}

node* MoveNode(node* head, node* requiredNode)
{
	if (head == NULL) return NULL;
	node* temp = head, * tempPrev = head;
	if (requiredNode != NULL)
	{
		requiredNode->amount++;
		while (temp->next != requiredNode)
		{
			tempPrev = temp;
			temp = temp->next;
		}
		if (tempPrev == temp)
		{
			head->next = requiredNode->next;
			requiredNode->next = head;
			head = requiredNode;
		}
		else
		{
			tempPrev->next = requiredNode;
			temp->next = requiredNode->next;
			requiredNode->next = temp;
		}
	}
	return head;
}

node* SearchNode(node* head, char _symbol)
{
	if (head == NULL) return NULL;
	if (head->symbol == _symbol) return head;
	return SearchNode(head->next, _symbol);
}

//node* SearchAddress(node* head, node* tmp) //Поиск родителя искомого узла(передаем указатель на начало дерева, и адрес дочернего узла)
//{
//	if (tmp == head) return NULL;
//	if (tmp == head->next) return head;
//	return SearchAddress(head->next, tmp);
//}

void PrintNode(node* head)
{
	node* current = head;
	while (current != NULL)
	{
		std::cout << current->symbol << "->" << current->amount << ";" << std::endl;
		current = current->next;
	}
}

//void Equals(node* head, int& count, char _symbol)
//{
//	if (head)
//	{
//		if (head->amount == _amount) count++;
//		Equals(head->next, count, _amount);
//	}
//}