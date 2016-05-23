#pragma once

#include <map>
#include <algorithm>
#include <numeric>
#include "Date.h"
#include "Client.h"
#include "Product.h"
#include "Transaction.h"
#include "Tools.h"

struct row
{
	unsigned int ID;
	vector <Product> prod_bought;
	vector<bool> prod_bool;
};
bool operator==(const row &LHS, const row &RHS);
class Store
{
public:
	Store();
	void readClients();
	void readProducts();
	double productPrice(string &productName);
	void readTransactions();
	void makeMapClientsName();
	void makeMapClientsID();
	void makeMapProducts();
	void makeMapTransactions();
	vector<Client>& getClientsVector();
	vector<Product>& getProductsVector();
	vector<Transaction>& getTransactionsVector();
	map<string, unsigned int>& getClientsNameToIndex();
	map<unsigned int, unsigned int>& getClientsIDToIndex();
	map<string, unsigned int>& getProductsNameToIndex();
	multimap<unsigned int, unsigned int>& getClientsTransactions();
	bool getClientChanged() const;
	bool getProductsChanged() const;
	bool getTransactionsChanged() const;
	void setClientsChanged(bool newBool);
	void setProductsChanged(bool newBool);
	void setTransactionsChanged(bool newBool);
	bool displayAllClients() const;
	bool displayClient() const;
	bool displayProducts() const;
	bool displayAllTransactions() const;
	bool displayTransactionsByDay() const;
	bool displayTransactionsByClient() const;
	bool displayTransactionsBetweenDates() const;
	bool addClient();
	bool correctClientName();
	bool modifyClientAmount();
	bool removeClient();
	bool addProduct();
	bool changeProductName();
	bool changeProductPrice();
	bool removeProduct();
	bool addTransaction();
	bool cancelTransaction();
	template<typename T, typename compare>
	void sortStore(vector<T> &vector, compare &predicate)
	{
		sort(vector.begin(), vector.end(), predicate);
	}
	template<typename T>
	void sortStore(vector<T> &vector)
	{
		sort(vector.begin(), vector.end());
	}
	template<typename T>
	void saveToFiles(vector<T> &vector, string &fileName)
	{
		ofstream file;
		file.open(fileName);
		file << vector.size() << endl;
		for (unsigned int i = 0; i < vector.size(); i++)
			file << vector[i];
		file.close();
	}
	void saveChanges();
	void makeRowsVectors(vector<row> &rowsVector, vector<Product> &productsInRow, vector<unsigned int> &numberOfPurchases, vector<Client> &typeOfClients);
	void makeBottomTenVectors();
	void advertising();
	void advertisingBottomTen();
	~Store();
private:
	string customersFileName, productsFileName, transactionsFileName;
	bool clientsChanged, productsChanged, transactionsChanged;
	vector<Client> clientsVector, bottomTenClientsVector, interestingClientsVector;
	vector<Product> productsVector;
	vector<Transaction> transactionsVector;
	map<string, unsigned int> ClientsNameToIndex;
	map<string, unsigned int> ProductsNameToIndex;
	multimap<unsigned int, unsigned int> ClientsTransactions;
	map<unsigned int, unsigned int> ClientsIDToIndex;
};