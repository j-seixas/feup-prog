#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Product.h"
#include "Date.h"
#include "Tools.h"
using namespace std;

class Transaction
{
private:
	unsigned int ID;
	Date purchaseDate;
	vector<Product> productsBought;
public:
	Transaction(unsigned int &ID, vector<Product> &productsBought);
	Transaction(unsigned int &ID, Date &purchaseDate, vector<Product> &productsBought);
	unsigned int getID() const;
	Date getPurchaseDate() const;
	vector<Product> getProductsBought() const;
	double getTransactionValue() const;
	vector<string> getProducts() const;
	friend ofstream& operator<<(ofstream &file, const Transaction &transaction);
	void show() const;
	friend bool operator==(const Transaction &LHS, const Transaction &RHS);
	friend bool operator<(const Transaction &LHS, const Transaction &RHS);
	friend bool operator>(const Transaction &LHS, const Transaction &RHS);
	friend bool operator<=(const Transaction &LHS, const Transaction &RHS);
	friend bool operator>=(const Transaction &LHS, const Transaction &RHS);
	friend bool compareTransactionByID(const Transaction &LHS, const Transaction &RHS);
	~Transaction();
};