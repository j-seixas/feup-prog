#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <locale>
#include "Date.h"
#include "Tools.h"
using namespace std;

class Client
{
private:
	unsigned int ID;
	string name;
	Date subscribe_Date;
	double sum;
public:
	Client(unsigned int ID, string name);
	Client(unsigned int &ID, string &name, Date &subscribe_Date, double &sum);
	void setName(string &name);
	void setSubscribeDate(Date &subscribe_Date);
	void setSum(double sum);
	unsigned int getID() const;
	string getName() const;
	Date getSubscribeDate() const;
	double getSum() const;
	void show() const;
	friend ofstream& operator<<(ofstream &file, const Client &client);
	friend bool operator==(const Client &LHS, const Client &RHS);
	friend bool operator<(const Client &LHS, const Client &RHS);
	friend bool operator>(const Client &LHS, const Client &RHS);
	friend bool compareClientBySum(const Client &LHS, const Client &RHS);
	friend bool compareClientByName(const Client &LHS, const Client &RHS);
	friend bool compareClientBySubscribeDate(const Client &LHS, const Client &RHS);
	~Client();
};