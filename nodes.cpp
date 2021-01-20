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

node* AddNode(node* head, char _symbol, int _amount);
node* MoveNode(node* head, int _amount);
node* SearchNodeAddress(node* head, int _amount);
void PrintNode(node* head);


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

		char* buffer = new char[fileSize];

		file.read(buffer, fileSize);

		if (file)
		{
			std::cout << "Все символы были прочитаны!" << std::endl;
			std::map<char, int> m;
			for (size_t i = 0; i < std::string(buffer).size(); i++)
				if (std::string(buffer)[i] != ' ') m[std::string(buffer)[i]]++;

			for (auto i = m.begin(); i != m.end(); i++)
				std::cout << i->first << "->" << i->second << std::endl;

			std::cout << "==========================" << std::endl;

			node* head = NULL;
			for (auto i = m.begin(); i != m.end(); i++)
			{
				head = AddNode(head, i->first, i->second);
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


node* AddNode(node* head, char _symbol, int _amount)
{
	node* temp;
	if (head == NULL)
	{
		head = new node;
		head->symbol = _symbol;
		head->amount = _amount;
		head->next = NULL;
	}
	else
	{
		head = MoveNode(head, _amount);
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
		temp->amount = _amount;
		newNode->next = temp;
		temp->next = NULL;
	}
	return head;
}

node* MoveNode(node* head, int _amount)
{
	if (head == NULL) return NULL;
	node* temp = head, * tempPrev = head;
	node* requiredNode = SearchNodeAddress(head, _amount);
	if (requiredNode == head) requiredNode = SearchNodeAddress(head->next, _amount);
	if(requiredNode!= NULL && head->next == requiredNode && head->amount == requiredNode->amount) requiredNode = SearchNodeAddress(requiredNode->next, _amount);
	if (requiredNode != NULL)
	{
		while (temp->next != requiredNode)
		{
			tempPrev = temp;
			temp = temp->next;
		}
		tempPrev->next = requiredNode;
		temp->next = requiredNode->next;
		requiredNode->next = temp;
	}
	return head;
}

node* SearchNodeAddress(node* head, int _amount)
{
	if (head == NULL) return NULL;
	if (head->amount == _amount) return head;
	return SearchNodeAddress(head->next, _amount);
}

void PrintNode(node* head)
{
	node* current = head;
	while (current != NULL)
	{
		std::cout << current->symbol << "->" << current->amount << ";" << std::endl;
		current = current->next;
	}
}