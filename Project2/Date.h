#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

bool leapYear(unsigned int &year);
unsigned int numDays(unsigned int &year, unsigned int &month);

class Date
{
private:
	unsigned int day, month, year;
	bool valid;
public:
	Date();
	Date(unsigned int &day, unsigned int &month, unsigned int &year);
	Date(string &dayMonthYear);
	void setYear(unsigned int &year);
	void setMonth(unsigned int &month);
	void setDay(unsigned int &day);
	void setDate(unsigned int &year, unsigned int &month, unsigned int &day);
	void setDate(string &dayMonthYear);
	unsigned int getYear() const;
	unsigned int getMonth() const;
	unsigned int getDay() const;
	string getDateString() const;
	bool getValidBool() const;
	friend istream& operator >> (istream &is, Date &date);
	friend bool operator==(const Date &LHS, const Date &RHS);
	friend bool operator<(const Date &LHS, const Date &RHS);
	friend bool operator>(const Date &LHS, const Date &RHS);
	friend bool operator<=(const Date &LHS, const Date &RHS);
	friend bool operator>=(const Date &LHS, const Date &RHS);
	void show() const;
	~Date();
};