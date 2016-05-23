#include "Product.h"

Product::Product(string name, double price)
{
	this->name = name;
	this->price = price;
}
Product::~Product()
{

}
void Product::setName(string &name)
{
	this->name = name;
}
void Product::setPrice(double &price)
{
	this->price = price;
}
string Product::getName() const
{
	return name;
}
double Product::getPrice() const
{
	return price;
}
ofstream& operator<<(ofstream &file, const Product &product)
{
	file << product.getName() << " ; " << product.getPrice() << endl;
	return file;
}
void Product::show() const
{
	cout << name
		<< setw(CONSOLE_WIDTH - name.length());
	if(price != 0.0)
		cout << setprecision(2) << fixed << price << '$' << endl;
	else cout << "Not Available" << endl;
}
bool operator==(const Product &LHS, const Product &RHS)
{
	return (LHS.getName() == RHS.getName());
}
bool operator<(const Product &LHS, const Product &RHS)
{
	locale loc1, loc2;
	for (unsigned int i = 0; i < LHS.getName().size() || i < RHS.getName().size(); i++)
	{
		if (tolower(LHS.getName()[i], loc1) < tolower(RHS.getName()[i], loc2))
			return true;
		else if (tolower(LHS.getName()[i], loc1) > tolower(RHS.getName()[i], loc2))
			return false;
	}
	return (LHS.getPrice() < RHS.getPrice());
}
bool operator>(const Product &LHS, const Product &RHS)
{
	locale loc1, loc2;
	for (unsigned int i = 0; i < LHS.getName().size() || i < RHS.getName().size(); i++)
	{
		if (tolower(LHS.getName()[i], loc1) > tolower(RHS.getName()[i], loc2))
			return true;
		else if (tolower(LHS.getName()[i], loc1) < tolower(RHS.getName()[i], loc2))
			return false;
	}
	return (LHS.getPrice() > RHS.getPrice());
}
bool compareProductByPrice(const Product &LHS, const Product &RHS)
{
	return (LHS.getPrice() < RHS.getPrice());
}