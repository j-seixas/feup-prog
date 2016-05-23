#pragma once

#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

unsigned int getConsoleWidth(); 
extern const unsigned int CONSOLE_WIDTH;
void c(const string s);
template<typename T>
T validInput(string badInput, string normalInput, string tryAgain)
{
	string line;
	T input;
	cout << normalInput;
	while (getline(cin, line))
	{
		istringstream iss(line);
		iss >> ws >> input >> ws;
		if (iss.fail() || !iss.eof())
		{
			cin.clear();
			system("cls");
			cerr << badInput;
			cout << endl << endl << tryAgain << normalInput;
		}
		else return input;
	}
	cin.clear();
	return NULL;
}
template<typename T>
T validInput(string &badInput, string &normalInput, vector<string> &tryAgain)
{
	string line;
	T input;
	cout << endl << endl;
	for (unsigned int i = 0; i < tryAgain.size(); i++)
		c(tryAgain[i]);
	cout << normalInput;
	while (getline(cin, line))
	{
		istringstream iss(line);
		iss >> ws >> input >> ws;
		if (iss.fail() || !iss.eof())
		{
			cin.clear();
			system("cls");
			cerr << badInput;
			cout << endl << endl;
			for (unsigned int i = 0; i < tryAgain.size(); i++)
				c(tryAgain[i]);
			cout << normalInput;
		}
		else return input;
	}
	cin.clear();
	return NULL;
}
string validFile(string fileType);
bool yesNoAnswer();