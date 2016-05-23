#include "Transaction.h"

Transaction::Transaction(unsigned int &ID, vector<Product> &productsBought)
{
	this->ID = ID;
	this->productsBought = productsBought;
	purchaseDate = Date::Date();
}
Transaction::Transaction(unsigned int &ID, Date &purchaseDate, vector<Product> &productsBought)
{
	this->ID = ID;
	this->productsBought = productsBought;
	this->purchaseDate = purchaseDate;
}
unsigned int Transaction::getID() const
{
	return ID;
}
Date Transaction::getPurchaseDate() const
{
	return purchaseDate;
}
vector<Product> Transaction::getProductsBought() const
{
	return productsBought;
}
double Transaction::getTransactionValue() const
{
	double value = 0;
	for (unsigned int i = 0; i < productsBought.size(); i++)
		value = value + productsBought[i].getPrice();
	return value;
}
vector<string> Transaction::getProducts() const
{
	vector<string> products;
	for (unsigned int i = 0; i < productsBought.size(); i++)
		products.push_back(productsBought[i].getName());
	return products;
}
ofstream& operator<<(ofstream &file, const Transaction &transaction)
{
	file << transaction.getID() << " ; " << transaction.getPurchaseDate().getDateString() << " ; ";
	for (unsigned int p = 0; p < transaction.getProducts().size(); p++)
	{
		if (p != (transaction.getProducts().size()) - 1)
			file << transaction.getProducts()[p] << ", ";
		else file << transaction.getProducts()[p] << endl;
	}
	return file;
}
void Transaction::show() const
{
	cout << right << setw(CONSOLE_WIDTH/ 6) << ID
		<< setw(CONSOLE_WIDTH / 6 + 8) << purchaseDate.getDateString()
		<< left << setw(CONSOLE_WIDTH / 10) << ' ';
	for (unsigned int p = 0; p < getProducts().size(); p++)
	{
		if (p != (getProducts().size()) - 1)
			cout << getProducts()[p] << ", ";
		else cout << getProducts()[p] << right << endl;
	}
	cout << right;
}
Transaction::~Transaction()
{

}
bool operator==(const Transaction &LHS, const Transaction &RHS)
{
	return (LHS.getPurchaseDate() == RHS.getPurchaseDate());
}
bool operator<(const Transaction &LHS, const Transaction &RHS)
{
	return (LHS.getPurchaseDate() < RHS.getPurchaseDate());
}
bool operator>(const Transaction &LHS, const Transaction &RHS)
{
	return (LHS.getPurchaseDate() > RHS.getPurchaseDate());
}
bool operator<=(const Transaction &LHS, const Transaction &RHS)
{
	return (LHS < RHS || LHS == RHS);
}
bool operator>=(const Transaction &LHS, const Transaction &RHS)
{
	return (LHS > RHS || LHS == RHS);
}
bool compareTransactionByID(const Transaction &LHS, const Transaction &RHS)
{
	return (LHS.getID() < RHS.getID());
}