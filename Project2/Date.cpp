#include "Date.h"

bool leapYear(unsigned int &year)
{
	if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0))
		return true;
	else return false;
}
unsigned int numDays(unsigned int &year, unsigned int &month)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		if (leapYear(year))
			return 29;
		else return 28;
	default:
		return 0;
	}
}
Date::Date()
{
	time_t now = time(0);
	tm timeinfo;
	localtime_s(&timeinfo, &now);
	year = 1900 + timeinfo.tm_year;
	month = 1 + timeinfo.tm_mon;
	day = timeinfo.tm_mday;
	valid = true;
}
Date::Date(unsigned int &day, unsigned int &month, unsigned int &year)
{
	this->year = year;
	this->month = month;
	this->day = day;
	if (month > 12 || month < 1 || day > numDays(year, month) || day < 1)
		valid = false;
	else valid = true;
}
Date::Date(string &dayMonthYear)
{
	istringstream iss(dayMonthYear);
	char delimiter;
	iss >> day >> ws >> delimiter >> month >> ws >> delimiter >> year >> ws;
	if (iss.fail() || !iss.eof() || month > 12 || month < 1 || day > numDays(year, month) || day < 1)
		valid = false;
	else valid = true;
}
void Date::setYear(unsigned int &year)
{
	this->year = year;
}
void Date::setMonth(unsigned int &month)
{
	this->month = month;
	if (month > 12 || month < 1)
		valid = false;
}
void Date::setDay(unsigned int &day)
{
	this->day = day;
	if (day > numDays(year, month) || day < 1)
		valid = false;
}
void Date::setDate(unsigned int &year, unsigned int &month, unsigned int &day)
{
	this->year = year;
	this->month = month;
	this->day = day;
	if (month > 12 || month < 1 || day > numDays(year, month) || day < 1)
		valid = false;
	else valid = true;
}
void Date::setDate(string &dayMonthYear)
{
	istringstream iss(dayMonthYear);
	char delimiter;
	iss >> ws >> day >> ws >> delimiter >> ws >> month >> ws >> delimiter >> ws >> year >> ws;
	if (iss.fail() || !iss.eof() || month > 12 || month < 1 || day > numDays(year, month) || day < 1)
		valid = false;
	else valid = true;
}
unsigned int Date::getYear() const
{
	return year;
}
unsigned int Date::getMonth() const
{
	return month;
}
unsigned int Date::getDay() const
{
	return day;
}
string Date::getDateString() const
{
	string dateString;
	if (day < 10)
		dateString = dateString + to_string(0);
	dateString = dateString + to_string(day) + '/';
	if (month < 10)
		dateString = dateString + to_string(0);
	dateString = dateString + to_string(month) + '/' + to_string(year);
	return dateString;
}
bool Date::getValidBool() const
{
	return valid;
}
void Date::show() const
{
	cout << getDateString();
}
istream& operator >> (istream &is, Date &date)
{
	string dateString;
	getline(is, dateString);
	date.setDate(dateString);
	is.clear();
	return is;
}
Date::~Date()
{
}
bool operator==(const Date &LHS, const Date &RHS)
{
	return (10000 * LHS.getYear() + 100 * LHS.getMonth() + LHS.getDay()
		== 10000 * RHS.getYear() + 100 * RHS.getMonth() + RHS.getDay());
}
bool operator<(const Date &LHS, const Date &RHS)
{
	return (10000 * LHS.getYear() + 100 * LHS.getMonth() + LHS.getDay()
		< 10000 * RHS.getYear() + 100 * RHS.getMonth() + RHS.getDay());
}
bool operator>(const Date &LHS, const Date &RHS)
{
	return (10000 * LHS.getYear() + 100 * LHS.getMonth() + LHS.getDay()
> 10000 * RHS.getYear() + 100 * RHS.getMonth() + RHS.getDay());
}
bool operator<=(const Date &LHS, const Date &RHS)
{
	return (LHS < RHS || LHS == RHS);
}
bool operator>=(const Date &LHS, const Date &RHS)
{
	return (LHS > RHS || LHS == RHS);
}