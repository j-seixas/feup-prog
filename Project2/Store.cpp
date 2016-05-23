#include "Store.h"

bool operator==(const row &LHS, const row &RHS)
{
	return LHS.ID == RHS.ID;
}
Store::Store()
{
	customersFileName = validFile("customers");
	productsFileName = validFile("products");
	transactionsFileName = validFile("transactions");
	readClients();
	readProducts();
	readTransactions();
	makeMapClientsName();
	makeMapClientsID();
	makeMapProducts();
	makeMapTransactions();
	clientsChanged = productsChanged = transactionsChanged = false;
	sortStore(clientsVector);
	sortStore(productsVector);
	sortStore(transactionsVector);
}
void Store::readClients()
{
	string line;
	ifstream file;

	file.open(customersFileName);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			unsigned int ID;
			string name, dateStr;
			double sum;
			char delimiter;
			istringstream iss(line);

			iss >> ws >> ID >> ws >> delimiter >> ws;
			if (!iss.fail())
			{
				getline(iss, name, delimiter);
				getline(iss, dateStr, delimiter);
				iss >> ws >> sum >> ws;
				if (!iss.fail())
				{
					Date subscribe_Date(dateStr);
					if (subscribe_Date.getValidBool() && !name.empty())
					{
						size_t	i = name.length() - 1;
						while (name[i] == ' ' && i < name.length() && i >= 0)
						{
							name = name.substr(0, (name.length() - 1));
							i = name.length() - 1;
						}
						clientsVector.push_back(Client(ID, name, subscribe_Date, sum));
					}
				}
				else iss.clear();
			}
			else iss.clear();
		}
		file.close();
	}
}
void Store::readProducts()
{
	ifstream file;
	string line, productName;
	double productPrice;

	file.open(productsFileName);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);

			iss >> ws;
			getline(iss, productName, ';');
			iss >> ws >> productPrice >> ws;
			if (!iss.fail())
			{
				if (!productName.empty())
				{
					size_t	i = productName.length() - 1;
					while (productName[i] == ' ' && i < productName.length() && i >= 0)
					{
						productName = productName.substr(0, (productName.length() - 1));
						i = productName.length() - 1;
					}
					productsVector.push_back(Product(productName, productPrice));
				}
			}
			else iss.clear();
		}
		file.close();
	}
}
double Store::productPrice(string &productName)
{
	for (unsigned int i = 0; i < productsVector.size(); i++)
	{
		if (productName == productsVector[i].getName())
			return productsVector[i].getPrice();
	}
	return (double)0;
}
void Store::readTransactions()
{
	ifstream file;
	string line, products, dateStr;
	char ch;
	unsigned int ID;

	file.open(transactionsFileName);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);

			iss >> ws >> ID >> ws >> ch;
			getline(iss, dateStr, ch);
			Date transactionDate(dateStr);
			iss >> ws;
			getline(iss, products, '\n');
			if (!iss.fail() && transactionDate.getValidBool() && !products.empty())
			{
				vector<Product> transactionProductsVector;
				string productName;
				istringstream iss(products);

				while (iss)
				{
					getline(iss, productName, ',');
					while (productName[0] == ' ')
					{
						productName.erase(0, 1);
					}
					size_t i = productName.length() - 1;
					while (productName[i] == ' ')
					{
						productName = productName.substr(0, (productName.length() - 1));
						i = productName.length() - 1;
					}
					transactionProductsVector.push_back(Product(productName, productPrice(productName)));
				}
				transactionProductsVector.pop_back();
				transactionsVector.push_back(Transaction(ID, transactionDate, transactionProductsVector));
			}
		}
		file.close();
	}
}
void Store::makeMapClientsName()
{
	ClientsNameToIndex.clear();
	for (unsigned int i = 0; i < clientsVector.size(); i++)
		ClientsNameToIndex.insert(pair<string, unsigned int>(clientsVector[i].getName(), i));
}
void Store::makeMapClientsID()
{
	ClientsIDToIndex.clear();
	for (unsigned int i = 0; i < clientsVector.size(); i++)
		ClientsIDToIndex.insert(pair<unsigned int, unsigned int>(clientsVector[i].getID(), i));
}
void Store::makeMapProducts()
{
	ProductsNameToIndex.clear();
	for (unsigned int i = 0; i < productsVector.size(); i++)
		ProductsNameToIndex.insert(pair<string, unsigned int>(productsVector[i].getName(), i));
}
void Store::makeMapTransactions()
{
	ClientsTransactions.clear();
	for (unsigned int i = 0; i < clientsVector.size(); i++)
	{
		for (unsigned int ii = 0; ii < transactionsVector.size(); ii++)
		{
			if (clientsVector[i].getID() == transactionsVector[ii].getID())
				ClientsTransactions.insert(pair<unsigned int, unsigned int>(clientsVector[i].getID(), ii));
		}
	}
}
Store::~Store()
{
}
vector<Client>& Store::getClientsVector()
{
	return clientsVector;
}
vector<Product>& Store::getProductsVector()
{
	return productsVector;
}
vector<Transaction>& Store::getTransactionsVector()
{
	return transactionsVector;
}
map<string, unsigned int>& Store::getClientsNameToIndex()
{
	return ClientsNameToIndex;
}
map<unsigned, unsigned int>& Store::getClientsIDToIndex()
{
	return ClientsIDToIndex;
}
map<string, unsigned int>& Store::getProductsNameToIndex()
{
	return ProductsNameToIndex;
}
multimap<unsigned int, unsigned int>& Store::getClientsTransactions()
{
	return ClientsTransactions;
}
bool Store::getClientChanged() const
{
	return clientsChanged;
}
bool Store::getProductsChanged() const
{
	return productsChanged;
}
bool Store::getTransactionsChanged() const
{
	return transactionsChanged;
}
void Store::setClientsChanged(bool newBool)
{
	clientsChanged = newBool;
}
void Store::setProductsChanged(bool newBool)
{
	productsChanged = newBool;
}
void Store::setTransactionsChanged(bool newBool)
{
	transactionsChanged = newBool;
}
bool Store::displayAllClients() const
{
	system("cls");
	cout << "-------------------------\n"
		<< "Read Clients' Information\n"
		<< "-------------------------\n\n";

	if (clientsVector.empty())
	{
		cerr << "Clients' file is empty!\n\n";
		return false;
	}
	else
	{
		cout << setw(CONSOLE_WIDTH / 6) << "ID"
			<< setw(CONSOLE_WIDTH / 5 + 8) << "Date"
			<< setw(CONSOLE_WIDTH / 1.5 + 2) << "Name"
			<< setw(CONSOLE_WIDTH / 1.25 - 2) << "Sum"
			<< endl;
		for (unsigned int i = 0; i < clientsVector.size(); i++)
			clientsVector[i].show();
		return true;
	}
}
bool Store::displayClient() const
{
	system("cls");
	cout << "---------------------------\n"
		<< "Read a Client's Information\n"
		<< "---------------------------\n\n";

	bool clientFound = false;

	if (clientsVector.empty())
	{
		cerr << "Clients' file is empty!\n\n";
		return false;
	}
	else
	{
		cout << "Insert the name or ID of the client you wish to view information of: ";
		unsigned int ID;
		cin >> ID;
		if (cin.fail())
		{
			string clientName;
			if (cin.eof())
			{
				cin.clear();
				cout << "\nAction canceled\n";
				return false;
			}
			cin.clear();
			getline(cin, clientName);
			transform(clientName.begin(), clientName.end(), clientName.begin(), ::tolower);
			for (unsigned int i = 0; i < clientsVector.size(); i++)
			{
				string currentName = clientsVector[i].getName();
				transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
				if (currentName == clientName)
				{
					if (!clientFound)
						cout << endl << setw(CONSOLE_WIDTH / 6) << "ID"
						<< setw(CONSOLE_WIDTH / 5 + 8) << "Date"
						<< setw(CONSOLE_WIDTH / 1.5 + 2) << "Name"
						<< setw(CONSOLE_WIDTH / 1.25 - 2) << "Sum"
						<< endl;
					clientsVector[i].show();
					clientFound = true;
				}
			}
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (unsigned int i = 0; i < clientsVector.size(); i++)
			{
				if (clientsVector[i].getID() == ID)
				{
					if (!clientFound)
						cout << endl << setw(CONSOLE_WIDTH / 6) << "ID"
						<< setw(CONSOLE_WIDTH / 5 + 8) << "Date"
						<< setw(CONSOLE_WIDTH / 1.5 + 2) << "Name"
						<< setw(CONSOLE_WIDTH / 1.25 - 2) << "Sum"
						<< endl;
					clientsVector[i].show();
					clientFound = true;
				}
			}
		}
		if (!clientFound)
		{
			cout << "\nClient not found!\n\n";
			return true;
		}
		else return false;
	}
}
bool Store::displayProducts() const
{
	system("cls");
	cout << "--------------------------\n"
		<< "Read Products' Information\n"
		<< "--------------------------\n\n";

	if (productsVector.empty())
	{
		cerr << "Products file is empty !\n\n";
		return false;
	}
	else
	{
		cout << setw(CONSOLE_WIDTH / 8) << '#' << setw(CONSOLE_WIDTH / 20 + 1) << ' ' << "Name"
			<< setw(CONSOLE_WIDTH - 4) << "Price" << endl;
		for (unsigned int i = 0; i < productsVector.size(); i++)
		{
			cout << setw(CONSOLE_WIDTH / 8) << (i + 1) << '.' << setw(CONSOLE_WIDTH / 20) << ' ';
			productsVector[i].show();
		}
		return true;
	}
}
bool Store::displayAllTransactions() const
{
	system("cls");
	cout << "---------------------\n"
		<< "Read All Transactions\n"
		<< "---------------------\n\n";

	if (transactionsVector.empty())
	{
		cerr << "Transactions file is empty !\n\n";
		return false;
	}
	else
	{
		cout << setw(CONSOLE_WIDTH / 6) << "ID"
			<< setw(CONSOLE_WIDTH / 6 + 8) << "Date"
			<< left << setw(CONSOLE_WIDTH / 10) << ' ' << "Products" << right << endl;
		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			transactionsVector[i].show();
		}
		return true;
	}
}
bool Store::displayTransactionsByDay() const
{
	system("cls");
	cout << "------------------------\n"
		<< "Read Transactions by Day\n"
		<< "------------------------\n\n";

	if (transactionsVector.empty())
	{
		cerr << "Transactions file is empty !\n\n";
		return false;
	}
	else
	{
		bool transactionFound = false;
		Date transactionDate;

		while (true)
		{
			cout << "\nInsert a date you wish to view transactions for. Format: DD/MM/YYYY\n";
			string dateString;
			getline(cin, dateString);
			transactionDate.setDate(dateString);
			if (!transactionDate.getValidBool())
			{
				cin.clear();
				system("cls");
				cerr << "Invalid Date!\n\n";
				cout << "------------------------\n"
					<< "Read Transactions by Day\n"
					<< "------------------------\n\n";
			}
			else break;
		}

		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			if (transactionsVector[i].getPurchaseDate() == transactionDate)
			{
				if (!transactionFound)
					cout << endl << setw(CONSOLE_WIDTH / 6) << "ID"
					<< setw(CONSOLE_WIDTH / 6 + 8) << "Date"
					<< left << setw(CONSOLE_WIDTH / 10) << ' ' << "Products" << right << endl;
				transactionsVector[i].show();
				transactionFound = true;
			}
		}
		if (!transactionFound)
		{
			cout << "\nNo transactions found for the specified date\n\n";
			return false;
		}
		else
			return true;
	}
}
bool Store::displayTransactionsByClient() const
{
	system("cls");
	cout << "---------------------------\n"
		<< "Read Transactions by Client\n"
		<< "---------------------------\n\n";

	if (transactionsVector.empty())
	{
		cerr << "Transactions file is empty !\n\n";
		return false;
	}
	else
	{
		bool transactionFound = false;
		unsigned int ID = validInput<unsigned int>("Invalid ID!", "\nInsert an ID from a client you wish to view transactions for: ", "---------------------------\nRead Transactions by Client\n---------------------------\n\n");

		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			if (transactionsVector[i].getID() == ID)
			{
				if (!transactionFound)
					cout << endl << setw(CONSOLE_WIDTH / 6) << "ID"
					<< setw(CONSOLE_WIDTH / 6 + 8) << "Date"
					<< left << setw(CONSOLE_WIDTH / 10) << ' ' << "Products" << right << endl;
				transactionsVector[i].show();
				transactionFound = true;
			}
		}
		if (!transactionFound)
		{
			cout << "\nNo transactions found for the specified client\n\n";
			return false;
		}
		else return true;
	}
}
bool Store::displayTransactionsBetweenDates() const
{
	system("cls");
	cout << "-------------------------------\n"
		<< "Read Transactions between Dates\n"
		<< "-------------------------------\n\n";

	if (transactionsVector.empty())
	{
		cerr << "\nTransactions file is empty !\n\n";
		return false;
	}
	else
	{
		bool transactionFound = false;

		Date startDate;
		while (true)
		{
			cout << "\nInsert a date you wish to view transactions for. Format: DD/MM/YYYY\n";
			cin >> startDate;
			if (!startDate.getValidBool())
			{
				cin.clear();
				system("cls");
				cerr << "Invalid Date!\n\n";
				cout << "------------------------\n"
					<< "Read Transactions by Day\n"
					<< "------------------------\n\n";
			}
			else break;
		}

		Date endDate;
		while (true)
		{
			cout << "\nInsert a date you wish to view transactions for. Format: DD/MM/YYYY\n";
			cin >> endDate;
			if (!endDate.getValidBool())
			{
				cin.clear();
				system("cls");
				cerr << "Invalid Date!\n\n";
				cout << "------------------------\n"
					<< "Read Transactions by Day\n"
					<< "------------------------\n\n";
			}
			else break;
		}

		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			if (transactionsVector[i].getPurchaseDate() >= startDate && transactionsVector[i].getPurchaseDate() <= endDate)
			{
				if (!transactionFound)
					cout << endl << setw(CONSOLE_WIDTH / 6) << "ID"
					<< setw(CONSOLE_WIDTH / 6 + 8) << "Date"
					<< left << setw(CONSOLE_WIDTH / 10) << ' ' << "Products" << right << endl;
				transactionsVector[i].show();
				transactionFound = true;
			}
		}
		if (!transactionFound)
		{
			cout << "\nNo transactions found for the specified dates\n\n";
			return false;
		}
		else
			return true;
	}
}
bool Store::addClient()
{
	system("cls");
	cout << "----------\n"
		<< "Add Client\n"
		<< "----------\n\n";
	string name;
	cout << "\nWhat's the name of the client you wish to create? ";
	while (true)
	{
		if (getline(cin, name))
			if (!name.empty())
				break;
			else cout << "\nThe client name cannot be empty!\n";
		else
		{
			cin.clear();
			cout << "\nClient creation canceled!\n";
			return false;
		}
	}
	unsigned int ID = 1, ID2 = 0;
	if (!clientsVector.empty())
	{
		ID = clientsVector.size() - 1;
		ID = clientsVector[ID].getID() + 1;
	}
	for (unsigned int i = 0; i < transactionsVector.size(); i++)
	{
		if (ID2 < transactionsVector[i].getID())
			ID2 = transactionsVector[i].getID() + 1;
	}
	if (ID < ID2)
		ID = ID2;
	clientsVector.push_back(Client(ID, name));
	cout << "\nClient added with success! " << name << "'s ID is " << ID << '.' << endl << endl;
	makeMapClientsName();
	makeMapClientsID();
	makeMapTransactions();
	return true;
}
bool Store::correctClientName()
{
	system("cls");
	cout << "--------------------\n"
		<< "Correct Client's Name\n"
		<< "--------------------\n\n";

	unsigned int ID;
	string name;
	bool clientFound = false;

	cout << "\nInsert an ID or a name of the client you wish to modify: ";
	cin.clear();
	cin >> ID;
	if (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			cout << "\nAction canceled\n";
			return false;
		}
		cin.clear();
		getline(cin, name);
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			string currentName = clientsVector[index].getName();
			transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
			if (currentName == name)
			{
				cout << "\nIs this the client you're searching for? (Y/N) \n";
				clientsVector[index].show();
				if (yesNoAnswer())
				{
					while (true)
					{
						cout << "\nWhat's the new name? ";
						if (getline(cin, name))
							if (!name.empty())
								break;
							else cout << "\nThe client name cannot be empty!\n";
						else
						{
							cin.clear();
							cout << "\nAction canceled\n";
							return false;
						}
					}
					clientsVector[index].setName(name);
					clientFound = true;
					break;
				}
			}
		}
	}
	else
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			if (clientsVector[index].getID() == ID)
			{
				cout << "\nIs this the client you're searching for? (Y/N) \n";
				clientsVector[index].show();
				if (yesNoAnswer())
				{
					while (true)
					{
						cout << "\nWhat's the new name? ";
						if (getline(cin, name))
							if (!name.empty())
								break;
							else cout << "\nThe client name cannot be empty!\n";
						else
						{
							cin.clear();
							cout << "\nAction canceled\n";
							return false;
						}
					}
					clientsVector[index].setName(name);
					clientFound = true;
					break;
				}
			}
		}
	}
	if (clientFound)
	{
		cout << "\nClient modified!\n\n";
		makeMapClientsName();
		makeMapClientsID();
		makeMapTransactions();
		return true;
	}
	else
	{
		cout << "\nClient not found!\n\n";
		return false;
	}
}
bool Store::modifyClientAmount()
{
	system("cls");
	cout << "----------------------\n"
		<< "Modify Client's Amount\n"
		<< "----------------------\n\n";

	unsigned int ID;
	string name;
	bool clientFound = false;
	double amount;

	cout << "\nInsert an ID or a name of the client you wish to modify: ";
	cin.clear();
	cin >> ID;
	if (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			cout << "\nAction canceled\n";
			return false;
		}
		cin.clear();
		getline(cin, name);
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			string currentName = clientsVector[index].getName();
			transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
			if (currentName == name)
			{
				cout << "\nIs this the client you're searching for? (Y/N) \n";
				clientsVector[index].show();
				if (yesNoAnswer())
				{
					amount = validInput<double>("Invalid Amount!\n", "\nWhat's the new amount? ", "----------------------\nModify Client's Amount\n----------------------\n\n");
					clientsVector[index].setSum(amount);
					clientFound = true;
					break;
				}
			}
		}
	}
	else
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			if (clientsVector[index].getID() == ID)
			{
				cout << "\nIs this the client you're searching for? (Y/N) \n";
				clientsVector[index].show();
				if (yesNoAnswer())
				{
					amount = validInput<double>("Invalid Amount!\n", "\nWhat's the new amount? ", "----------------------\nModify Client's Amount\n----------------------\n\n");
					clientsVector[index].setSum(amount);
					clientFound = true;
					break;
				}
			}
		}
	}
	if (clientFound)
	{
		cout << "\nClient modified!\n\n";
		makeMapClientsName();
		makeMapClientsID();
		makeMapTransactions();
		return true;
	}
	else
	{
		cout << "\nClient not found!\n\n";
		return false;
	}
}
bool Store::removeClient()
{
	system("cls");
	cout << "-------------\n"
		<< "Remove Client\n"
		<< "-------------\n\n";

	cout << "\nInsert an ID or a name of the client you wish to remove: ";
	unsigned int ID;
	string name;
	bool clientFound = false;

	cin.clear();
	cin >> ID;
	if (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			cout << "\nAction canceled\n";
			return false;
		}
		cin.clear();
		getline(cin, name);
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			string currentName = clientsVector[index].getName();
			transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
			if (currentName == name)
			{
				cout << "\nIs this the client you're searching for? (Y/N) \n"
					<< setw(CONSOLE_WIDTH / 6) << "ID"
					<< setw(CONSOLE_WIDTH / 5 + 8) << "Date"
					<< setw(CONSOLE_WIDTH / 1.5 + 2) << "Name"
					<< setw(CONSOLE_WIDTH / 1.25 - 2) << "Sum"
					<< endl;
				clientsVector[index].show();
				if (yesNoAnswer())
				{
					clientsVector.erase(clientsVector.begin() + index);
					clientFound = true;
					break;
				}
			}
		}
	}
	else
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			if (clientsVector[index].getID() == ID)
			{
				cout << "\nIs this the client you're searching for? (Y/N) \n"
					<< setw(CONSOLE_WIDTH / 6) << "ID"
					<< setw(CONSOLE_WIDTH / 5 + 8) << "Date"
					<< setw(CONSOLE_WIDTH / 1.5 + 2) << "Name"
					<< setw(CONSOLE_WIDTH / 1.25 - 2) << "Sum"
					<< endl;
				clientsVector[index].show();
				if (yesNoAnswer())
				{
					clientsVector.erase(clientsVector.begin() + index);
					clientFound = true;
					break;
				}
			}

		}
	}

	if (clientFound)
	{
		cout << "\nClient removed!\n\n";
		makeMapClientsName();
		makeMapClientsID();
		makeMapTransactions();
		return true;
	}
	else
	{
		cout << "\nClient not found!\n\n";
		return false;
	}
}
bool Store::addProduct()
{
	system("cls");
	cout << "-----------\n"
		<< "Add Product\n"
		<< "-----------\n\n";

	string new_product;
	while (true)
	{
		cout << "\nWhat's the name of the new product? ";
		if (getline(cin, new_product))
			if (!new_product.empty())
				break;
			else cout << "\nThe product name cannot be empty!\n";
		else
		{
			cin.clear();
			cout << "\nProduct creation canceled!\n";
			return false;
		}
	}
	double amount = validInput<double>("Invalid Amount!\n\n", "\nHow much does it cost? ", "-----------\nAdd Product\n-----------\n\n");
	productsVector.push_back(Product(new_product, amount));
	cout << endl << new_product << " added with success to the products list!\n\n";
	sortStore<Product>(productsVector);
	makeMapProducts();
	return true;
}
bool Store::changeProductName()
{
	system("cls");
	cout << "-------------------\n"
		<< "Change Product Name\n"
		<< "-------------------\n\n";

	string product;
	bool productFound = false;
	while (true)
	{
		cout << "\nInsert the name of the product you wish to change the name of: ";
		if (getline(cin, product))
			if (!product.empty())
				break;
			else cout << "\nThe product name cannot be empty!\n";
		else
		{
			cin.clear();
			cout << "\nAction canceled!\n";
			return false;
		}
	}
	transform(product.begin(), product.end(), product.begin(), ::tolower);
	for (unsigned int index = 0; index < productsVector.size(); index++)
	{
		string currentProduct = productsVector[index].getName();
		transform(currentProduct.begin(), currentProduct.end(), currentProduct.begin(), ::tolower);
		if (currentProduct == product)
		{
			string newName;
			while (true)
			{
				cout << "\nWhat's the new name of the product? ";
				if (getline(cin, newName))
					if (!newName.empty())
						break;
					else "\nThe product name cannot be empty!\n";
				else
				{
					cin.clear();
					cout << "\nAction canceled\n";
					return false;
				}

			}
			productsVector[index].setName(newName);
			productFound = true;
			break;
		}
	}

	if (productFound)
	{
		cout << "\nProduct name changed!\n\n";
		sortStore<Product>(productsVector);
		makeMapProducts();
		return true;
	}
	else
	{
		cout << "\nProduct not found!\n\n";
		return false;
	}
}
bool Store::changeProductPrice()
{
	system("cls");
	cout << "--------------------\n"
		<< "Change Product Price\n"
		<< "--------------------\n\n";

	string product;
	bool productFound = false;
	while (true)
	{
		cout << "\nInsert the name of the product you wish to change the price of: ";
		if (getline(cin, product))
			if (!product.empty())
				break;
			else cout << "\nThe product name cannot be empty!\n";
		else
		{
			cin.clear();
			cout << "\nAction canceled!\n";
			return false;
		}
	}
	transform(product.begin(), product.end(), product.begin(), ::tolower);
	for (unsigned int index = 0; index < productsVector.size(); index++)
	{
		string currentProduct = productsVector[index].getName();
		transform(currentProduct.begin(), currentProduct.end(), currentProduct.begin(), ::tolower);
		if (currentProduct == product)
		{
			double newPrice = validInput<double>("\nInvalid Price!\n", "\nWhat's the new price? ", "--------------------\nChange Product Price\n--------------------\n\n");
			productsVector[index].setPrice(newPrice);
			productFound = true;
			break;
		}
	}

	if (productFound)
	{
		cout << "\nProduct price changed!\n\n";
		return true;
	}
	else
	{
		cout << "\nProduct not found!\n\n";
		return false;
	}
}
bool Store::removeProduct()
{
	system("cls");
	cout << "--------------\n"
		<< "Remove Product\n"
		<< "--------------\n\n";

	string product;
	bool productFound = false;
	while (true)
	{
		cout << "\nInsert the name of the product you wish to remove: ";
		if (getline(cin, product))
			if (!product.empty())
				break;
			else cout << "\nThe product name cannot be empty!\n";
		else
		{
			cin.clear();
			cout << "\nAction canceled!\n";
			return false;
		}
	}
	transform(product.begin(), product.end(), product.begin(), ::tolower);
	for (unsigned int index = 0; index < productsVector.size(); index++)
	{
		string currentProduct = productsVector[index].getName();
		transform(currentProduct.begin(), currentProduct.end(), currentProduct.begin(), ::tolower);
		if (currentProduct == product)
		{
			productsVector.erase(productsVector.begin() + index);
			productFound = true;
			break;
		}
	}

	if (productFound)
	{
		cout << "\nProduct Removed!\n\n";
		makeMapProducts();
		return true;
	}
	else
	{
		cout << "\nProduct not found!\n\n";
		return false;
	}
}
bool Store::addTransaction()
{
	system("cls");
	cout << "---------------\n"
		<< "Add Transaction\n"
		<< "---------------\n\n";

	unsigned int ID, index;
	bool IDFound = false;
	while (true)
	{
		ID = validInput<unsigned int>("Invalid ID!\n\n", "\nInsert the client's ID: ", "---------------\nAdd Transaction\n---------------\n\n");
		for (index = 0; index < clientsVector.size(); index++)
		{
			if (ID == clientsVector[index].getID())
			{
				IDFound = true;
				break;
			}
		}
		if (IDFound)
			break;
		else cout << "\nThe ID entered is not associated to any client!\n";
	}

	vector<Product> products_Bought;
	double sum;

	if (displayProducts())
	{
		cout << endl
			<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 1 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "End Transaction\n"
			<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 2 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Last Product\n"
			<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 3 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Transaction\n"
			<< endl << "Client ID: " << ID << endl;

		unsigned int product_ID;
		while (true)
		{
			if (products_Bought.size() != 0)
			{
				sum = 0;
				cout << "\n\nCurrent list of products:\n";
				for (unsigned int p = 0; p < products_Bought.size(); p++)
				{
					products_Bought[p].show();
					sum = sum + products_Bought[p].getPrice();
				}
				cout << endl << "Sum: " << sum << endl;
			}

			cout << "\nEnter a product bought by the client, using the product ID: ";
			string prod_ID_String;
			cin.clear();
			getline(cin, prod_ID_String);
			istringstream iss(prod_ID_String);
			iss >> ws >> product_ID >> ws;
			if (iss.fail() || !iss.eof())
			{
				cin.clear();
				system("cls");
				cerr << "Invalid Product ID!\n\n";
				displayProducts();
				cout << endl
					<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 1 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "End Transaction\n"
					<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 2 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Last Product\n"
					<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 3 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Transaction\n"
					<< endl << "Client ID: " << ID << endl;
			}
			else if (product_ID > 0 && product_ID <= productsVector.size() + 1)
			{
				if (product_ID == productsVector.size() + 1)
					break;
				else
				{
					products_Bought.push_back(productsVector[product_ID - 1]);
					system("cls");
					displayProducts();
					cout << endl
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 1 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "End Transaction\n"
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 2 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Last Product\n"
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 3 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Transaction\n"
						<< endl << "Client ID: " << ID << endl;
				}
			}
			else  if (product_ID == productsVector.size() + 2)
			{
				if (products_Bought.size() == 0)
				{
					system("cls");
					cerr << "There are no products to remove from the transaction\n";
					displayProducts();
					cout << endl
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 1 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "End Transaction\n"
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 2 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Last Product\n"
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 3 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Transaction\n"
						<< endl << "Client ID: " << ID << endl;
				}
				else
				{
					products_Bought.pop_back();
					system("cls");
					cout << "Last product removed from transaction!\n";
					displayProducts();
					cout << endl
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 1 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "End Transaction\n"
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 2 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Last Product\n"
						<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 3 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Transaction\n"
						<< endl << "Client ID: " << ID << endl;
				}
			}
			else if (product_ID == productsVector.size() + 3)
			{
				products_Bought.clear();
				break;
			}
			else
			{
				system("cls");
				cerr << "Invalid Product ID!\n\n";
				displayProducts();
				cout << endl
					<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 1 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "End Transaction\n"
					<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 2 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Last Product\n"
					<< setw(CONSOLE_WIDTH / 8) << productsVector.size() + 3 << '.' << setw(CONSOLE_WIDTH / 20) << ' ' << "Cancel Transaction\n"
					<< endl << "Client ID: " << ID << endl;
			}
		}
		if (products_Bought.size() != 0)
		{
			transactionsVector.push_back(Transaction(ID, products_Bought));
			clientsVector[index].setSum(clientsVector[index].getSum() + sum);
			cout << "\nTransaction complete with success!\n\n";
			sortStore<Transaction>(transactionsVector);
			sortStore<Client>(clientsVector);
			makeMapTransactions();
			return true;
		}
		else
		{
			cout << "\nTransaction canceled!\n\n";
			return false;
		}
	}
	return false;
}
bool Store::cancelTransaction()
{
	system("cls");
	cout << "------------------\n"
		<< "Remove Transaction\n"
		<< "------------------\n\n";

	unsigned int ID = validInput<unsigned int>("Invalid ID!\n\n", "\nInsert the client's ID: ", "------------------\nRemove Transaction\n------------------\n\n");

	Date transactionDate;
	while (true)
	{
		cout << "\nInsert a date you wish to view transactions for. Format: DD/MM/YYYY\n";
		string dateString;
		getline(cin, dateString);
		transactionDate.setDate(dateString);
		if (!transactionDate.getValidBool())
		{
			cin.clear();
			system("cls");
			cerr << "Invalid Date!\n\n";
			cout << "------------------\n"
				<< "Remove Transaction\n"
				<< "------------------\n\n";
		}
		else break;
	}

	bool transactionFound = false;
	for (unsigned int i = 0; i < transactionsVector.size(); i++)
	{
		if (transactionsVector[i].getID() == ID
			&& transactionsVector[i].getPurchaseDate() == transactionDate)
		{
			cout << "\nAre you sure you want to cancel this transaction? (Y/N)\n";
			transactionsVector[i].show();
			if (yesNoAnswer())
			{
				transactionsVector.erase(transactionsVector.begin() + i);
				for (unsigned int i = 0; i < clientsVector.size(); i++)
				{
					if (ID == clientsVector[i].getID())
					{
						clientsVector[i].setSum(clientsVector[i].getSum() - transactionsVector[i].getTransactionValue());
						break;
					}
				}
				cout << "\nTransaction canceled!\n";
				transactionFound = true;
				cout << "\nDo you want to keep looking for other transactions for the same date and client ID? (Y/N)\n";
				if (!yesNoAnswer())
					break;
			}
		}
	}

	if (transactionFound)
	{
		makeMapTransactions();
		return true;
	}
	else
		return false;
}
void Store::saveChanges()
{
	if (clientsChanged)
		saveToFiles(clientsVector, customersFileName);
	if (productsChanged)
		saveToFiles(productsVector, productsFileName);
	if (transactionsChanged)
		saveToFiles(transactionsVector, transactionsFileName);
}
void Store::makeBottomTenVectors()
{
	bottomTenClientsVector = clientsVector;
	if (clientsVector.size() > 10)
	{
		sort(bottomTenClientsVector.begin(), bottomTenClientsVector.end(), compareClientBySum);
		interestingClientsVector = bottomTenClientsVector;
		interestingClientsVector.erase(interestingClientsVector.begin(), interestingClientsVector.begin() + 10);
		bottomTenClientsVector.resize(10, Client(0, ""));
	}
}
void Store::advertising()
{
	system("cls");
	cout << "-----------\n"
		<< "Advertising\n"
		<< "-----------\n\n";

	//GET THE CLIENT ID
	unsigned int client_ID;
	while (true)
	{
		bool IDFound = false;
		client_ID = validInput<unsigned int>("Invalid ID!\n\n", "\nInsert the client's ID: ", "-----------\nAdvertising\n-----------\n\n");
		//CHECK IF INTRODUCED ID IS ASSOCIATED TO A CLIENT
		for (unsigned int index = 0; index < clientsVector.size(); index++)
		{
			if (client_ID == clientsVector[index].getID())
			{
				IDFound = true;
				break;
			}
		}
		if (IDFound)
			break;
		else
		{
			if (client_ID != NULL)
				cout << "\nThe ID entered is not associated to any client!\n";
			else return;
		}
	}

	//BUILD A PRODUCTS VECTOR AND A VECTOR WITH THE NUMBER OF PURCHASES OF A PRODUCT OUT OF THE TRANSACTIONS VECTOR
	if (transactionsVector.size() != 0)
	{
		vector<Product> products_in_Transactions_Vector;
		vector<unsigned int> number_of_Purchases;
		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			for (unsigned int i_2 = 0; i_2 < transactionsVector[i].getProductsBought().size(); i_2++)
			{
				//VERIFY IF CURRENT PRODUCT IS ALREADY IN THE NEW PRODUCTS VECTOR
				if (find(products_in_Transactions_Vector.begin(), products_in_Transactions_Vector.end(), transactionsVector[i].getProductsBought()[i_2]) == products_in_Transactions_Vector.end())
				{
					//IF NOT, ADD IT TO THE NEW PRODUCTS VECTOR AND ADDING A NEW '1' TO THE NUMBER OF PURCHASES OF THAT PRODUCT
					products_in_Transactions_Vector.push_back(transactionsVector[i].getProductsBought()[i_2]);
					number_of_Purchases.push_back(1);
				}
				else
					//IF IT IS ALREADY IN THE NEW PRODUCTS VECTOR, THEN INCREMENT THE NUMBER OF PURCHASES OF THAT PRODUCT
					number_of_Purchases[distance(products_in_Transactions_Vector.begin(), find(products_in_Transactions_Vector.begin(), products_in_Transactions_Vector.end(), transactionsVector[i].getProductsBought()[i_2]))]++;
			}
		}

		//BUILD ROWS VECTOR
		vector<row> rows;
		row new_row;
		//INITIALIZATION OF THE ROWS VECTOR
		new_row.ID = transactionsVector[0].getID();
		new_row.prod_bought = transactionsVector[0].getProductsBought();
		rows.push_back(new_row);
		for (unsigned int index = 1; index < transactionsVector.size(); index++)
		{
			bool ID_Found = false;
			//CHECK IF CURRENT ID FROM THE TRANSACTIONS VECTOR IS ALREADY IN THE ROWS VECTOR
			for (unsigned int index_2 = 0; index_2 < rows.size(); index_2++)
			{
				unsigned int currentID = transactionsVector[index].getID();
				if (currentID == rows[index_2].ID)
				{
					//IF YES, THEN JUST ADD THE PRODUCTS BOUGHT IN THAT TRANSACTION TO THE PRODUCTS VECTOR OF THAT ID
					for (unsigned int index_3 = 0; index_3 < transactionsVector[index].getProductsBought().size(); index_3++)
						rows[index_2].prod_bought.push_back(transactionsVector[index].getProductsBought()[index_3]);
					ID_Found = true;
					break;
				}
			}
			//IF NOT, THEN ADD A NEW ROW TO THE ROWS VECTOR
			if (!ID_Found)
			{
				new_row.ID = transactionsVector[index].getID();
				new_row.prod_bought = transactionsVector[index].getProductsBought();
				rows.push_back(new_row);
			}
		}

		//BUILD BOOLEANS VECTOR
		for (unsigned int j_c = 0; j_c < rows.size(); j_c++)
		{
			for (unsigned int i_p = 0; i_p < products_in_Transactions_Vector.size(); i_p++)
			{
				//IF THE CURRENT PRODUCT IS FOUND IN THE PRODUCTS VECTOR OF THE CURRENT ROW, THEN ADD A TRUE TO THE BOOL VECTOR
				if (find(rows[j_c].prod_bought.begin(), rows[j_c].prod_bought.end(), products_in_Transactions_Vector[i_p]) != rows[j_c].prod_bought.end())
					rows[j_c].prod_bool.push_back(true);
				else
					//IF NOT, THEN ADD A FALSE TO THE BOOL VECTOR
					rows[j_c].prod_bool.push_back(false);
			}
		}

		//REMOVE TARGET-CLIENT'S DATA FROM THE ROWS VECTOR
		row client_row;
		bool client_Found = false;
		for (unsigned int index = 0; index < rows.size(); index++)
		{
			if (rows[index].ID == client_ID)
			{
				client_Found = true;
				client_row = rows[index];
				rows.erase(rows.begin() + index);
				break;
			}
		}
		//NOW WE'VE GOT THE THE TARGET-CLIENT'S ROW

		if (client_Found)
		{
			//NUMBER OF PRODUCTS THAT THE CLIENT BOUGHT
			unsigned int number_Target_Client_Trues = accumulate(client_row.prod_bool.begin(), client_row.prod_bool.end(), 0);

			//NEW ROWS: CLIENTS_BOOLEANS = CLIENTS_BOOLEANS && TARGET_CLIENT_BOOLEANS
			vector<row> and_rows = rows;
			for (unsigned int i = 0; i < and_rows.size(); i++)
			{
				for (unsigned int i_2 = 0; i_2 < and_rows[i].prod_bool.size(); i_2++)
				{
					and_rows[i].prod_bool[i_2] = and_rows[i].prod_bool[i_2] && client_row.prod_bool[i_2];
				}
			}

			//BUILD A VECTOR OF PRODUCTS TO RECOMMEND
			unsigned int maximum_Equal_Products = 0;
			vector<Product> products_to_Recommend;
			//'i' IS THE LEVEL OF SIMILARITY BETWEEN THE CURRENT CLIENT AND THE TARGET-CLIENT
			//FOR MAXIMUM SIMILARITY, 'i' MUST START AT THE NUMBER OF PRODUCTS THAT THE CLIENT BOUGHT AND WILL "DECREASE IT'S QUALITY" EVERY ITERATION
			//UNTIL A GOOD ENOUGH MATCH IS FOUND
			for (unsigned int i = number_Target_Client_Trues; i > 0; i--)
			{
				for (unsigned int i_2 = 0; i_2 < and_rows.size(); i_2++)
				{
					//IF CURRENT SIMILARITY LEVEL IS THE SAME AS THE NUMBER OF BOUGHT PRODUCTS OF THE CURRENT ROW 
					//AND IF THE CURRENT ROW AS BOUGHT AT LEAST ONE MORE PRODUCT, THEN IT IS A GOOD MATCH
					//SO, THE PRODUCTS VECTOR OF THAT ROW WILL BE APPENDED TO THE PRODUCTS TO RECOMMEND VECTOR
					if (i == accumulate(and_rows[i_2].prod_bool.begin(), and_rows[i_2].prod_bool.end(), 0)
						&& accumulate(rows[i_2].prod_bool.begin(), rows[i_2].prod_bool.end(), 0) + 0.0 > i)
					{
						maximum_Equal_Products = i;
						products_to_Recommend.insert(products_to_Recommend.begin(), rows[i_2].prod_bought.begin(), rows[i_2].prod_bought.end());
					}
				}
				//ONCE THERE'S A GOOD ENOUGHT MATCH THEN THIS LOOP MUST END, BECAUSE EVERYTHING THAT WOULD FOLLOW WOULDN'T HAVE BETTER SIMILARITY
				if (maximum_Equal_Products != 0)
					break;
			}

			//ELIMINATES DUPLICATES OF THE PRODUCTS TO RECOMMEND VECTOR
			sort(products_to_Recommend.begin(), products_to_Recommend.end());
			products_to_Recommend.erase(unique(products_to_Recommend.begin(), products_to_Recommend.end()), products_to_Recommend.end());
			//ELIMINATES THE PRODUCTS THAT THE TARGET-CLIENT BOUGHT OUT OF THE PRODUCTS TO RECOMMEND VECTOR
			for (unsigned int i = 0; i < client_row.prod_bought.size(); i++)
			{
				for (unsigned int i_2 = 0; i_2 < products_to_Recommend.size(); i_2++)
				{
					if (client_row.prod_bought[i] == products_to_Recommend[i_2])
					{
						products_to_Recommend.erase(products_to_Recommend.begin() + i_2);
						i_2--;
					}
				}
			}

			//PRINT PRODUCTS
			//IF THE MAXIMUM EQUAL PRODUCTS IS ZERO, THEN THERE WAS NO GOOD MATCH
			//THEREFORE, THE TARGET-CLIENT HAS NO SPECIFIC RECOMMENDATION AND WILL BE RECOMMENDED WITH THE MOST BOUGHT PRODUCT OVERALL
			if (maximum_Equal_Products == 0)
			{
				cout << "\nThere are no specific recommendations to client number " << client_ID << endl << endl;
				vector<Product> products_to_Recommend_no_Transactions;
				//GETS THE MAXIMUM OF THE NUMBER OF PURCHASES
				unsigned int maximum = number_of_Purchases[distance(number_of_Purchases.begin(), max_element(number_of_Purchases.begin(), number_of_Purchases.end()))];
				//GETS THE INDEXES OF THE MOST BOUGHT PRODUCTS AND APPENDS THE CORRESPONDING PRODUCT TO THE 
				//PRODUCTS TO RECOMMEND WITH NO TRANSACTIONS VECTOR
				for (unsigned int i = 0; i < number_of_Purchases.size(); i++)
				{
					if (number_of_Purchases[i] == maximum)
					{
						products_to_Recommend_no_Transactions.push_back(products_in_Transactions_Vector[i]);
					}

				}
				sort(products_to_Recommend_no_Transactions.begin(), products_to_Recommend_no_Transactions.end());
				products_to_Recommend_no_Transactions.erase(unique(products_to_Recommend_no_Transactions.begin(), products_to_Recommend_no_Transactions.end()), products_to_Recommend_no_Transactions.end());
				//PRINT THE PRODUCTS TO RECOMMEND
				if (products_to_Recommend_no_Transactions.size() > 1)
				{
					cout << "\nHowever, these are the most bought products:" << endl;
					for (unsigned int i = 0; i < products_to_Recommend_no_Transactions.size(); i++)
					{
						products_to_Recommend_no_Transactions[i].show();
					}
				}
				else
				{
					cout << "\nHowever, this is the most bought product:" << endl;
					products_to_Recommend_no_Transactions[0].show();
				}
			}
			else
			{
				//THERE WAS A GOOD MATCH
				//FIND THE NUMBER OF PURCHASES OF EACH OF THE RECOMMENDED PRODUCTS
				vector<unsigned int> number_of_Purchases_of_Recommended_Products;
				number_of_Purchases_of_Recommended_Products.resize(products_to_Recommend.size());
				for (unsigned int i = 0; i < products_to_Recommend.size(); i++)
				{
					number_of_Purchases_of_Recommended_Products[i] =
						number_of_Purchases[distance(products_in_Transactions_Vector.begin(), find(products_in_Transactions_Vector.begin(), products_in_Transactions_Vector.end(), products_to_Recommend[i]))];
				}
				//FIND THE PRODUCT (OR PRODUCTS) OF THE RECOMMENDED PRODUCTS VECTOR WITH THE MOST SALES AND THEIR INDEXES
				vector<unsigned int> indexex_of_Most_Purchases;
				unsigned int most_Purchases = number_of_Purchases_of_Recommended_Products[distance(number_of_Purchases_of_Recommended_Products.begin(), max_element(number_of_Purchases_of_Recommended_Products.begin(), number_of_Purchases_of_Recommended_Products.end()))];
				for (unsigned int i = 0; i < number_of_Purchases_of_Recommended_Products.size(); i++)
				{
					if (number_of_Purchases_of_Recommended_Products[i] == most_Purchases)
						indexex_of_Most_Purchases.push_back(i);
				}
				//PRINT THE PRODUCTS TO RECOMMEND
				if (indexex_of_Most_Purchases.size() > 1)
				{
					cout << "\nThe recommendations for client number " << client_ID << " are: " << endl;
					for (unsigned int i = 0; i < indexex_of_Most_Purchases.size(); i++)
					{
						products_to_Recommend[indexex_of_Most_Purchases[i]].show();
					}
				}
				else
				{
					cout << "\nThe recommendation for client number " << client_ID << " is: " << endl;
					products_to_Recommend[indexex_of_Most_Purchases[0]].show();
				}
			}
		}
		else
		{
			//THE TARGET-CLIENT HAS NO TRANSACTIONS
			//THEREFORE, HE WILL BE RECOMMENDED WITH THE MOST BOUGHT PRODUCT OVERALL
			cout << "\nThe client number " << client_ID << " has no transactions\n";
			vector<Product> products_to_Recommend_no_Transactions;
			//GETS THE MAXIMUM OF THE NUMBER OF PURCHASES
			unsigned int maximum = number_of_Purchases[distance(number_of_Purchases.begin(), max_element(number_of_Purchases.begin(), number_of_Purchases.end()))];
			//GETS THE INDEXES OF THE MOST BOUGHT PRODUCTS AND APPENDS THE CORRESPONDING PRODUCT TO THE 
			//PRODUCTS TO RECOMMEND WITH NO TRANSACTIONS VECTOR
			for (unsigned int i = 0; i < number_of_Purchases.size(); i++)
			{
				if (number_of_Purchases[i] == maximum)
				{
					products_to_Recommend_no_Transactions.push_back(products_in_Transactions_Vector[i]);
				}
			}
			sort(products_to_Recommend_no_Transactions.begin(), products_to_Recommend_no_Transactions.end());
			products_to_Recommend_no_Transactions.erase(unique(products_to_Recommend_no_Transactions.begin(), products_to_Recommend_no_Transactions.end()), products_to_Recommend_no_Transactions.end());
			//PRINT THE PRODUCTS TO RECOMMEND
			if (products_to_Recommend_no_Transactions.size() > 1)
			{
				cout << "\nHowever, these are the most bought products:" << endl;
				for (unsigned int i = 0; i < products_to_Recommend_no_Transactions.size(); i++)
				{
					products_to_Recommend_no_Transactions[i].show();
				}
			}
			else
			{
				cout << "\nHowever, this is the most bought product:" << endl;
				products_to_Recommend_no_Transactions[0].show();
			}
		}
	}
}
void Store::makeRowsVectors(vector<row> &rowsVector, vector<Product> &productsInRow, vector<unsigned int> &numberOfPurchases, vector<Client> &typeOfClients)
{
	//THIS AUXILIAR FUNCTION BUILDS 3 VECTORS:
	//THE ROWS VECTOR, THE PRODUCTS VECTOR AND THE NUMBER OF PURCHASES OF THOSE PRODUCTS
	//ALL BASED ON THE TYPE OF CLIENTS, WHICH IS THE LAST ARGUMENT

	//BUILD THE ROWS VECTOR
	row new_row;
	for (unsigned int i = 0; i < typeOfClients.size(); i++)
	{
		for (unsigned int ii = 0; ii < transactionsVector.size(); ii++)
		{
			if (typeOfClients[i].getID() == transactionsVector[ii].getID())
			{
				bool alreadyInRows = false;
				for (unsigned int iii = 0; iii < rowsVector.size(); iii++)
				{
					alreadyInRows = false;
					if (rowsVector[iii].ID == typeOfClients[i].getID())
					{
						alreadyInRows = true;
						for (unsigned int iv = 0; iv < transactionsVector[ii].getProductsBought().size(); iv++)
							rowsVector[iii].prod_bought.push_back(transactionsVector[ii].getProductsBought()[iv]);
					}
				}
				if (!alreadyInRows)
				{
					new_row.ID = transactionsVector[ii].getID();
					new_row.prod_bought = transactionsVector[ii].getProductsBought();
					rowsVector.push_back(new_row);
				}
			}
		}
	}
	for (unsigned int i = 0; i < rowsVector.size(); i++)
	{
		for (unsigned int ii = 0; ii < rowsVector[i].prod_bought.size(); ii++)
			productsInRow.push_back(rowsVector[i].prod_bought[ii]);
	}

	vector<Product> productInRowTemp;
	for (unsigned int i = 0; i < productsInRow.size(); i++)
	{
		if (find(productInRowTemp.begin(), productInRowTemp.end(), productsInRow[i]) == productInRowTemp.end())
		{
			productInRowTemp.push_back(productsInRow[i]);
			numberOfPurchases.push_back(count(productsInRow.begin(), productsInRow.end(), productsInRow[i]));
		}
	}
	productsInRow = productInRowTemp;

	for (unsigned int i = 0; i < rowsVector.size(); i++)
	{
		sort(rowsVector[i].prod_bought.begin(), rowsVector[i].prod_bought.end());
		rowsVector[i].prod_bought.erase(unique(rowsVector[i].prod_bought.begin(), rowsVector[i].prod_bought.end()), rowsVector[i].prod_bought.end());
	}
}
void Store::advertisingBottomTen()
{
	system("cls");
	cout << "---------------------\n"
		<< "BottomTen Advertising\n"
		<< "---------------------\n\n";

	//BUILD A PRODUCTS VECTOR AND A VECTOR WITH THE NUMBER OF PURCHASES OF A PRODUCT OUT OF THE TRANSACTIONS VECTOR
	if (transactionsVector.size() != 0)
	{
		vector<Product> productsFromAllTransactions;
		vector<unsigned int> numberPurchases;
		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			for (unsigned int i_2 = 0; i_2 < transactionsVector[i].getProductsBought().size(); i_2++)
			{
				//VERIFY IF CURRENT PRODUCT IS ALREADY IN THE NEW PRODUCTS VECTOR
				if (find(productsFromAllTransactions.begin(), productsFromAllTransactions.end(), transactionsVector[i].getProductsBought()[i_2]) == productsFromAllTransactions.end())
				{
					//IF NOT, ADD IT TO THE NEW PRODUCTS VECTOR AND ADDING A NEW '1' TO THE NUMBER OF PURCHASES OF THAT PRODUCT
					productsFromAllTransactions.push_back(transactionsVector[i].getProductsBought()[i_2]);
					numberPurchases.push_back(1);
				}
				else
					//IF IT IS ALREADY IN THE NEW PRODUCTS VECTOR, THEN INCREMENT THE NUMBER OF PURCHASES OF THAT PRODUCT
					numberPurchases[distance(productsFromAllTransactions.begin(), find(productsFromAllTransactions.begin(), productsFromAllTransactions.end(), transactionsVector[i].getProductsBought()[i_2]))]++;
			}
		}

		if (bottomTenClientsVector.size() == 10 && interestingClientsVector.size() > 0)
		{
			vector<row> bottomTenRows;
			vector<Product> bottomTenProducts;
			vector<unsigned int> bottomTenProductsPurchases;
			makeRowsVectors(bottomTenRows, bottomTenProducts, bottomTenProductsPurchases, bottomTenClientsVector);
			vector<row> interestingRows;
			vector<Product> interestingProducts;
			vector<unsigned int> interestingProductsPurchases;
			makeRowsVectors(interestingRows, interestingProducts, interestingProductsPurchases, interestingClientsVector);


			if (bottomTenRows.size() > 0 && interestingRows.size() > 0)
			{
				//BUILD COMMON PRODUCTS VECTOR
				vector<Product> commonProducts;
				for (unsigned int i = 0; i < productsFromAllTransactions.size(); i < i++)
				{
					bool commonToAll = true;
					for (unsigned int ii = 0; ii < bottomTenRows.size(); ii++)
					{
						//IF THE CURRENT PRODUCT IS NOT FOUND ON THE CURRENT ROW, THEN IT'S NOT COMMON TO ALL THE BOTTOM TEN CLIENTS
						if (find(bottomTenRows[ii].prod_bought.begin(), bottomTenRows[ii].prod_bought.end(), productsFromAllTransactions[i]) == bottomTenRows[ii].prod_bought.end())
						{
							commonToAll = false;
							break;
						}
					}
					//IF IT IS, THEN ADD THAT PRODUCT TO THE COMMON PRODUCTS VECTOR
					if (commonToAll)
						commonProducts.push_back(productsFromAllTransactions[i]);
				}
				//DELETE DUPLICATES
				sort(commonProducts.begin(), commonProducts.end());
				commonProducts.erase(unique(commonProducts.begin(), commonProducts.end()), commonProducts.end());

				if (commonProducts.size() > 0)
				{
					//RE-BUILD THE INTERESTING CLIENS' ROWS VECTOR BASED ON THE COMMON PRODUCTS VECTOR
					for (unsigned int i = 0; i < interestingRows.size(); i++)
					{
						bool clientBoughtAllCommon = true;
						//IF THE CURRENT CLIENT HAS LESS OR THE SAME NUMBER OF PRODUCTS IN THE COMMON PRODUCTS VECTOR, THEN HE ISN'T A INTERESTING CLIENT
						if (interestingRows[i].prod_bought.size() <= commonProducts.size())
						{
							interestingRows.erase(interestingRows.begin() + i);
							i--;
						}

						else
						{
							for (unsigned int ii = 0; ii < commonProducts.size(); ii++)
							{
								//IF THE CURRENT CLIENT DIDN'T BUY THE CURRENT COMMON PRODUCT, THEN HE ISN'T A INTERESTING CLIENT
								if (find(interestingRows[i].prod_bought.begin(), interestingRows[i].prod_bought.end(), commonProducts[ii]) == interestingRows[i].prod_bought.end())
								{
									clientBoughtAllCommon = false;
									break;
								}
							}
							if (!clientBoughtAllCommon)
							{
								interestingRows.erase(interestingRows.begin() + i);
								i--;
							}
						}
					}

					if (interestingRows.size() > 0)
					{
						for (unsigned int i = 0; i < commonProducts.size(); i++)
						{
							//DELETES ALL THE COMMON PRODUCTS TO THE BOTTOM TEN CLIENTS FROM THE INTERESTING PRODUCTS
							if (find(interestingProducts.begin(), interestingProducts.end(), commonProducts[i]) != interestingProducts.end())
							{
								interestingProductsPurchases.erase(interestingProductsPurchases.begin() +
									distance(interestingProducts.begin(), find(interestingProducts.begin(), interestingProducts.end(), commonProducts[i])));
								interestingProducts.erase(interestingProducts.begin() +
									distance(interestingProducts.begin(), find(interestingProducts.begin(), interestingProducts.end(), commonProducts[i])));
							}
						}
						vector<Product> productsBoughtByNoneOfTheBottomTen;
						//IF A PRODUCT FROM THE INTERESTING PRODUCTS WASN'T BOUGHT BY ANY OF THE BOTTOM TEN CLIENTS, THEN ADD IT TO THE THE VECTOR
						//IF A PRODUCT FROM THE INTERESTING PRODUCTS WAS BOUGHT BY ALL OF THE BOTTOM TEN, THEN REMOVE IT FROM THE INTERESTING PRODUCTS 
						for (unsigned int i = 0; i < interestingProducts.size(); i++)
						{
							bool productFoundInAll = true, boughtByNobody = true;
							for (unsigned int ii = 0; ii < bottomTenRows.size(); ii++)
							{
								if (find(bottomTenRows[ii].prod_bought.begin(), bottomTenRows[ii].prod_bought.end(), interestingProducts[i]) == bottomTenRows[ii].prod_bought.end())
								{
									productFoundInAll = false;
								}
								else boughtByNobody = false;
							}
							if (productFoundInAll)
							{
								interestingProducts.erase(interestingProducts.begin() + i);
								i--;
							}
							else if (boughtByNobody)
								productsBoughtByNoneOfTheBottomTen.push_back(interestingProducts[i]);
						}

						if (productsBoughtByNoneOfTheBottomTen.size() > 0)
						{
							//IF THERE ARE ANY PRODUCTS IN THIS SITUATION, THEN RECOMMEND THE ONE THAT HAS MORE SALES
							unsigned int maximumSales = 0, correspondentIndex = 0;
							for (unsigned int i = 0; i < productsBoughtByNoneOfTheBottomTen.size(); i++)
							{
								if (numberPurchases[distance(productsFromAllTransactions.begin(), find(productsFromAllTransactions.begin(), productsFromAllTransactions.end(), productsBoughtByNoneOfTheBottomTen[i]))] > maximumSales)
								{
									maximumSales = numberPurchases[distance(productsFromAllTransactions.begin(), find(productsFromAllTransactions.begin(), productsFromAllTransactions.end(), productsBoughtByNoneOfTheBottomTen[i]))];
									correspondentIndex = i;
								}
							}
							cout << "The best bottom ten recommendation is:\n";
							productsBoughtByNoneOfTheBottomTen[correspondentIndex].show();
							return;
						}
						else
						{
							//FIND THE INTERESTING PRODUCT WITH MOST SALES
							unsigned int mostSales = 0, correspondentIndex = 0;
							for (unsigned int i = 0; i < interestingProductsPurchases.size(); i++)
							{
								if (interestingProductsPurchases[i] > mostSales)
								{
									mostSales = interestingProductsPurchases[i];
									correspondentIndex = i;
								}
							}
							//FIND THE BOTTOM TEN PRODUCT WITH THE LEAST SALES
							unsigned int lessSales = 0, correspondentIndex2 = 0;
							for (unsigned int i = 0; i < bottomTenProductsPurchases.size(); i++)
							{
								if (bottomTenProductsPurchases[i] < lessSales)
								{
									lessSales = bottomTenProductsPurchases[i];
									correspondentIndex2 = i;
								}
							}
							//IF THEY ARE THE SAME, RECOMMEND IT
							if (bottomTenProducts[correspondentIndex2] == interestingProducts[correspondentIndex])
							{
								cout << "The most bought product of the interesting clients matches the least bought product of the bottomTen clients!\n";
								interestingProducts[correspondentIndex].show();
								return;
							}
							else
							{
								//IF THEY AREN'T, THEN FIND THE PRODUCT WHICH HAS THE MOST DIFFERENCE IS SALE BETWEEN INTERESTING CLIENTS AND BOTTOM TEN CLIENTS
								int maximumDifference = 0, correspondentIndex3 = 0;
								for (unsigned int i = 0; i < interestingProductsPurchases.size(); i++)
								{
									vector<Product>::iterator findIterator = find(bottomTenProducts.begin(), bottomTenProducts.end(), interestingProducts[i]);
									if (findIterator != bottomTenProducts.end())
									{
										int currentDifference = interestingProductsPurchases[i] - bottomTenProductsPurchases[distance(bottomTenProducts.begin(), findIterator)];
										if (currentDifference > maximumDifference)
										{
											maximumDifference = currentDifference;
											correspondentIndex3 = i;
										}
									}
								}

								cout << "\nThe most bought product of the interesting clients doesn't match the least bought product of the bottomTen clients!\n";
								cout << "\nHowever, this is the product with the biggest difference in sales between interesting clients and bottomTen clients:\n";
								interestingProducts[correspondentIndex3].show();
								return;
							}
						}

					}
					else
					{
						//FIND THE INTERESTING PRODUCT WITH MOST SALES
						unsigned int mostSales = 0, correspondentIndex = 0;
						for (unsigned int i = 0; i < interestingProductsPurchases.size(); i++)
						{
							if (interestingProductsPurchases[i] > mostSales)
							{
								mostSales = interestingProductsPurchases[i];
								correspondentIndex = i;
							}
						}
						//FIND THE BOTTOM TEN PRODUCT WITH THE LEAST SALES
						unsigned int lessSales = 0, correspondentIndex2 = 0;
						for (unsigned int i = 0; i < bottomTenProductsPurchases.size(); i++)
						{
							if (bottomTenProductsPurchases[i] < lessSales)
							{
								lessSales = bottomTenProductsPurchases[i];
								correspondentIndex2 = i;
							}
						}
						cout << "No interesting clients bought all of the common products to all of the bottomTen clients and at least one more product!\n";
						cout << "\nMost bought by the interesting clients:\n";
						interestingProducts[correspondentIndex].show();
						cout << "\nLeast bought by the bottomTen clients:\n";
						bottomTenProducts[correspondentIndex2].show();
						return;
					}
				}
				else
				{
					//FIND THE INTERESTING PRODUCT WITH MOST SALES
					unsigned int mostSales = 0, correspondentIndex = 0;
					for (unsigned int i = 0; i < interestingProductsPurchases.size(); i++)
					{
						if (interestingProductsPurchases[i] > mostSales)
						{
							mostSales = interestingProductsPurchases[i];
							correspondentIndex = i;
						}
					}
					//FIND THE BOTTOM TEN PRODUCT WITH THE LEAST SALES
					unsigned int lessSales = 0, correspondentIndex2 = 0;
					for (unsigned int i = 0; i < bottomTenProductsPurchases.size(); i++)
					{
						if (bottomTenProductsPurchases[i] < lessSales)
						{
							lessSales = bottomTenProductsPurchases[i];
							correspondentIndex2 = i;
						}
					}
					cout << "There are no products common to all of the bottomTen clients!\n";
					cout << "\nMost bought by the interesting clients:\n";
					interestingProducts[correspondentIndex].show();
					cout << "\nLeast bought by the bottomTen clients:\n";
					bottomTenProducts[correspondentIndex2].show();
					return;
				}
			}
			else
			{
				cout << "There aren't enought clients for this action!\n";
				return;
			}
		}
		else
		{
			cout << "There aren't enough clients for this action!\n";
			return;
		}
	}
	else
		cout << "There are no transactions!\n";
}