#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale>
#include "Tools.h"
using namespace std;

class Product
{
private:
	string name;
	double price;
public:
	Product(string name, double price);
	~Product();
	void setName(string &name);
	void setPrice(double &price);
	string getName() const;
	double getPrice() const;
	friend ofstream& operator<<(ofstream &file, const Product &product);
	friend bool operator==(const Product &LHS, const Product &RHS);
	friend bool operator<(const Product &LHS, const Product &RHS);
	friend bool operator>(const Product &LHS, const Product &RHS);
	friend bool compareProductByPrice(const Product &LHS, const Product &RHS);
	void show() const;
};