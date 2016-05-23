#include "Menus.h"

unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max)
{
	unsigned int option;
	do
	{
		option = validInput<unsigned int>(badInput, normalInput, tryAgain);
		if (option < min || option > max)
		{
			system("cls");
			cout << badInput;
		}
		else break;
	} while (true);
	return option;
}
bool firstMenu()
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "==============================", "Files' Names Menu", "", "1 - Introduce files' names", "2 - Exit                  ", "==============================" }, 1, 2);
		switch (option)
		{
		case 1:
			return true;
		case 2:
		{
			cout << "\nAre you sure you want to exit? (Y/N)\n";
			if (yesNoAnswer())
				return false;
		}
		}
	}
}
bool clientsInformationMenu(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{ "-------------------------------------",
		"Read Clients File", "",
		"1 - Read all clients' information",
		"2 - Read a client's information  ", "",
		"3 - Back                         ",
		"-------------------------------------" }, 1, 3);
	switch (option)
	{
	case 1:
		store.displayAllClients();
		system("pause");
		return true;
	case 2:
		store.displayClient();
		system("pause");
		return true;
	case 3:
		return false;
	}
}
bool transactionsInformationMenu(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{ "---------------------------------------",
		"Read Transactions File", "",
		"1 - Read all transactions          ",
		"2 - Read a client's transactions   ",
		"3 - Read transactions by day       ",
		"4 - Read transactions between dates", "",
		"5 - Back                           ",
		"---------------------------------------" }, 1, 5);

	switch (option)
	{
	case 1:
		store.displayAllTransactions();
		system("pause");
		return true;
	case 2:
		store.displayTransactionsByClient();
		system("pause");
		return true;
	case 3:
		store.displayTransactionsByDay();
		system("pause");
		return true;
	case 4:
		store.displayTransactionsBetweenDates();
		system("pause");
		return true;
	case 5:
		return false;
	}
}
bool informationMenu(Store &store)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-----------------------------------",
			"Which file do you wish to read?", "",
			"1 - Clients File     ",
			"2 - Products File    ",
			"3 - Transactions File", "",
			"4 - Back             ",
			"-----------------------------------" }, 1, 4);

		switch (option)
		{
		case 1:
		{
			if (clientsInformationMenu(store))
				return true;
			break;
		}
		case 2:
		{
			store.displayProducts();
			system("pause");
			return true;
		}
		case 3:
		{
			if (transactionsInformationMenu(store))
				return true;
			break;
		}
		case 4:
			return false;
		}
	}
}
bool modifyClientsMenu(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{
		"-------------------------------",
		"What do you want to modify?", "",
		"1 - Name  ",
		"2 - Amount", "",
		"3 - Back  ",
		"-------------------------------" }, 1, 3);

	switch (option)
	{
	case 1:
		store.setClientsChanged(store.correctClientName());
		system("pause");
		return true;
	case 2:
		store.setClientsChanged(store.modifyClientAmount());
		system("pause");
		return true;
	case 3:
		return false;
	}
}
bool modifyProductsMenu(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{
		"-------------------------------",
		"What do you want to modify?", "",
		"1 - Name ",
		"2 - Price", "",
		"3 - Back ",
		"-------------------------------" }, 1, 3);

	switch (option)
	{
	case 1:
		store.setProductsChanged(store.changeProductName());
		system("pause");
		return true;
	case 2:
		store.setProductsChanged(store.changeProductPrice());
		system("pause");
		return true;
	case 3:
		return false;
	}
}
bool clientsMenu(Store &store)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "----------------------",
			"Clients Management", "",
			"1 - Add Clients   ",
			"2 - Remove Clients",
			"3 - Modify Clients", "",
			"4 - Back          ",
			"----------------------" }, 1, 4);

		switch (option)
		{
		case 1:
		{
			store.setClientsChanged(store.addClient());
			system("pause");
			return true;
		}
		case 2:
		{
			store.setClientsChanged(store.removeClient());
			system("pause");
			return true;
		}
		case 3:
		{
			if (modifyClientsMenu(store))
				return true;
			break;
		}
		case 4:
			return false;
		}
	}
}
bool productsMenu(Store &store)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-----------------------",
			"Products Management", "",
			"1 - Add Products   ",
			"2 - Remove Products",
			"3 - Modify Products", "",
			"4 - Back           ",
			"-----------------------" }, 1, 4);

		switch (option)
		{
		case 1:
		{
			store.setProductsChanged(store.addProduct());
			system("pause");
			return true;
		}
		case 2:
		{
			store.setProductsChanged(store.removeProduct());
			system("pause");
			return true;
		}
		case 3:
		{
			if (modifyProductsMenu(store))
				return true;
			break;
		}
		case 4:
			return false;
		}
	}
}
bool transactionsMenu(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{ "---------------------------",
		"Transactions Management", "",
		"1 - Add Transactions   ",
		"2 - Cancel Transactions", "",
		"3 - Back               ",
		"---------------------------" }, 1, 3);

	switch (option)
	{
	case 1:
	{
		store.setTransactionsChanged(store.addTransaction());
		system("pause");
		return true;
	}
	case 2:
	{
		store.setTransactionsChanged(store.cancelTransaction());
		system("pause");
		return true;
	}
	case 3:
		return false;
	}
}
bool sortClientOptions(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{ "------------------------------",
		"Client Sorting Options", "",
		"1 - Sort by ID            ",
		"2 - Sort by Names         ",
		"3 - Sort by Subscribe Date",
		"4 - Sort by Sum           ", "",
		"5 - Back                  ",
		"------------------------------", }, 1, 5);
	switch (option)
	{
	case 1:
		store.sortStore(store.getClientsVector());
		return true;
	case 2:
		store.sortStore(store.getClientsVector(), compareClientByName);
		return true;
	case 3:
		store.sortStore(store.getClientsVector(), compareClientBySubscribeDate);
		return true;
	case 4:
		store.sortStore(store.getClientsVector(), compareClientBySum);
		return true;
	case 5:
		return false;
	}
}
bool sortProductsOptions(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{ "---------------------------",
		"Product Sorting Options", "",
		"1 - Sort by Names",
		"2 - Sort by Price", "",
		"3 - Back         ",
		"---------------------------", }, 1, 3);
	switch (option)
	{
	case 1:
		store.sortStore(store.getProductsVector());
		return true;
	case 2:
		store.sortStore(store.getProductsVector(), compareProductByPrice);
		return true;
	case 3:
		return false;
	}
}
bool sortTransactionsOptions(Store &store)
{
	system("cls");
	unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
	{ "-------------------------------",
		"Transaction Sorting Options", "",
		"1 - Sort by ID  ",
		"2 - Sort by Date", "",
		"3 - Back        ",
		"-------------------------------", }, 1, 3);
	switch (option)
	{
	case 1:
		store.sortStore(store.getTransactionsVector(), compareTransactionByID);
		return true;
	case 2:
		store.sortStore(store.getTransactionsVector());
		return true;
	case 3:
		return false;
	}
}
bool optionsMenu(Store &store)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "------------------------------------------",
			"Options", "",
			"1 - Change client sorting options     ",
			"2 - Change product sorting options    ",
			"3 - Change transaction sorting options", "",
			"4 - Back                              ",
			"------------------------------------------", }, 1, 4);
		switch (option)
		{
		case 1:
		{
			if (sortClientOptions(store))
			{
				store.makeMapClientsName();
				store.makeMapClientsID();
				return true;
			}
			break;
		}
		case 2:
		{
			if (sortProductsOptions(store))
			{
				store.makeMapProducts();
				return true;
			}
			break;
		}
		case 3:
		{
			if (sortTransactionsOptions(store))
			{
				store.makeMapTransactions();
				return true;
			}
			break;
		}
		case 4:
			return false;
		}
	}
}
bool mainMenu(Store &store)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "=======================================",
			"Main Menu", "",
			"1 - Information                    ",
			"2 - Clients Management             ",
			"3 - Products Management            ",
			"4 - Transactions Management        ",
			"5 - Recommend Products to Client   ",
			"6 - Recommend Products to BottomTen", "",
			"7 - Options                        ",
			"8 - Return to Files' Names Menu    ",
			"9 - Exit App                       ",
			"=======================================" }, 1, 9);

		switch (option)
		{
		case 1:
		{
			informationMenu(store);
			break;
		}
		case 2:
		{
			clientsMenu(store);
			break;
		}
		case 3:
		{
			productsMenu(store);
			break;
		}
		case 4:
		{
			transactionsMenu(store);
			break;
		}
		case 5:
		{
			store.advertising();
			system("pause");
			break;
		}
		case 6:
		{
			store.makeBottomTenVectors();
			store.advertisingBottomTen();
			system("pause");
			break;
		}
		case 7:
			optionsMenu(store);
			break;
		case 8:
		{
			if (store.getClientChanged() || store.getProductsChanged() || store.getTransactionsChanged())
			{
				cout << "\nDo you want to save your changes? (Y/N)\n";
				if (yesNoAnswer())
				{
					cout << "\n\nSaving. Don't turn off the power!";
					store.saveChanges();
					cout << "\n\nSaving complete!\n\n";
					return false;
				}
				return false;
			}
			return false;
		}
		case 9:
		{
			cout << "\nAre you sure you want to exit? (Y/N)\n";
			if (yesNoAnswer())
			{
				if (store.getClientChanged() || store.getProductsChanged() || store.getTransactionsChanged())
				{
					cout << "\nDo you want to save your changes? (Y/N)\n";
					if (yesNoAnswer())
					{
						cout << "\n\nSaving. Don't turn off the power!";
						store.saveChanges();
						cout << "\n\nSaving complete!\n\n";
						return true;
					}
					return true;
				}
				return true;
			}
			else break;
		}
		}
	}
}