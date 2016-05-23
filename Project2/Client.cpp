#include "Client.h"

Client::Client(unsigned int ID, string name)
{
	this->ID = ID;
	this->name = name;
	sum = 0;
	subscribe_Date = Date::Date();
}
Client::Client(unsigned int &ID, string &name, Date &subscribe_Date, double &sum)
{
	this->ID = ID;
	this->name = name;
	this->sum = sum;
	this->subscribe_Date = subscribe_Date;
}
void Client::setName(string &name)
{
	this->name = name;
}
void Client::setSubscribeDate(Date &subscribe_Date)
{
	this->subscribe_Date = subscribe_Date;
}
void Client::setSum(double sum)
{
	this->sum = sum;
}
unsigned int Client::getID() const
{
	return ID;
}
string Client::getName() const
{
	return name;
}
Date Client::getSubscribeDate() const
{
	return subscribe_Date;
}
double Client::getSum() const
{
	return sum;
}
void Client::show() const
{
	cout << setw(CONSOLE_WIDTH / 6) << ID
		<< setw(CONSOLE_WIDTH / 5 + 8) << subscribe_Date.getDateString()
		<< setw(CONSOLE_WIDTH / 1.5 + name.length() / 2) << name
		<< setw(CONSOLE_WIDTH / 1.25 - (name.length() / 2))
		<< setprecision(2) << fixed << sum << endl;
}
ofstream& operator<<(ofstream &file, const Client &client)
{
	file << client.getID() << " ; " << client.getName() << " ; " << client.getSubscribeDate().getDateString() << " ; " << client.getSum() << endl;
	return file;
}
Client::~Client()
{
}
bool operator==(const Client &LHS, const Client &RHS)
{
	return (LHS.getID() == RHS.getID());
}
bool operator<(const Client &LHS, const Client &RHS)
{
	return (LHS.getID() < RHS.getID());
}
bool operator>(const Client &LHS, const Client &RHS)
{
	return (LHS.getID() > RHS.getID());
}
bool compareClientBySum(const Client &LHS, const Client &RHS)
{
	return (LHS.getSum() < RHS.getSum());
}
bool compareClientByName(const Client &LHS, const Client &RHS)
{
	locale loc1, loc2;
	for (unsigned int i = 0; i < LHS.getName().size() || i < RHS.getName().size(); i++)
	{
		if (tolower(LHS.getName()[i], loc1) < tolower(RHS.getName()[i], loc2))
			return true;
		else if (tolower(LHS.getName()[i], loc1) > tolower(RHS.getName()[i], loc2))
			return false;
	}
	return (LHS.getID() < RHS.getID());
}
bool compareClientBySubscribeDate(const Client &LHS, const Client &RHS)
{
	return (LHS.getSubscribeDate() < RHS.getSubscribeDate());
}