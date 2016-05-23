#pragma once

/*
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <numeric> 
#include <functional>
#include <iterator>
#include <locale>
#include <map>
#define NOMINMAX
#include <windows.h>*/
#include "Date.h"
#include "Client.h"
#include "Product.h"
#include "Transaction.h"
#include "Store.h"
#include "Menus.h"
#include "Tools.h"

/*
vector<string> CheckClientProducts(vector<Transaction> transactionsVector, vector<Client> clientsVector, unsigned int id)
{
	vector<string> productslist;
	bool alreadyexist = false;
	for (unsigned int i = 0; i < transactionsVector.size(); i++)
	{
		if (transactionsVector[i].getID() == id)
		{
			for (unsigned int ii = 0; ii < transactionsVector[i].getProducts().size(); ii++)
			{
				for (unsigned int iii = 0; iii < productslist.size(); iii++)
				{

					if (productslist[iii] == transactionsVector[i].getProducts()[ii])
					{
						alreadyexist = true;
						break;
					}
				}
				if (alreadyexist == false)
					productslist.push_back(transactionsVector[i].getProducts()[ii]);
				else
					alreadyexist = false;
			}
		}
	}
	return productslist;
}
struct clientprod {
	unsigned int nummatches;
	unsigned int index;
	unsigned int total;
};
struct productpublicity {
	unsigned int index;
	unsigned int total;
};
bool ComparebyTotal(const productpublicity &a, const productpublicity &b)
{
	return a.total > b.total;
}
void advertisingSeixas(vector<Transaction> transactionsVector, vector<Client> clientsVector, vector<Product> productsVector)
{
	system("cls");
	cout << "-----------\n"
		<< "Advertising\n"
		<< "-----------\n\n";

	//GET THE CLIENT ID
	unsigned int client_ID;
	unsigned int index;
	while (true)
	{
		bool IDFound = false;

		client_ID = validInput<unsigned int>("Invalid ID!\n\n", "\nInsert the client's ID: ", "-----------\nAdvertising\n-----------\n\n");
		for (unsigned int i = 0; i < clientsVector.size(); i++)
		{
			if (client_ID == clientsVector[i].getID())
			{
				index = i;
				IDFound = true;
				break;
			}
		}
		if (IDFound)
			break;
		else cout << "\nThe ID entered is not associated to any client!\n";
	}

	//BUILD PRODUCTS VECTOR OUT OF THE TRANSACTIONS VECTOR
	if (transactionsVector.size() != 0)
	{
		vector<string> products_in_Transactions_Vector;
		bool alreadyexist = false;
		for (unsigned int i = 0; i < transactionsVector.size(); i++)
		{
			for (unsigned int ii = 0; ii < transactionsVector[i].getProducts().size(); ii++)
			{
				for (unsigned int iii = 0; iii < products_in_Transactions_Vector.size(); iii++)
				{

					if (products_in_Transactions_Vector[iii] == transactionsVector[i].getProducts()[ii])
					{
						alreadyexist = true;
						break;
					}
				}
				if (alreadyexist == false)
					products_in_Transactions_Vector.push_back(transactionsVector[i].getProducts()[ii]);
				else  alreadyexist = false;
			}
		}

		typedef vector<bool> matrixLine;
		vector<matrixLine> matrixPublicity;
		matrixPublicity.resize(clientsVector.size());

		for (unsigned int i = 0; i < matrixPublicity.size(); i++)
			matrixPublicity[i].resize(products_in_Transactions_Vector.size());

		for (unsigned int i = 0; i < clientsVector.size(); i++)
		{
			vector<string> clientproducts = CheckClientProducts(transactionsVector, clientsVector, clientsVector[i].getID());
			for (unsigned int ii = 0; ii < products_in_Transactions_Vector.size(); ii++)
			{
				for (unsigned int iii = 0; iii < clientproducts.size(); iii++)
				{
					if (clientproducts[iii] == products_in_Transactions_Vector[ii])
						matrixPublicity[i][ii] = true;
				}
			}
		}

		bool breakwhile = false;
		vector<clientprod> vecsimilarclients;
		for (unsigned int i = 0; i < clientsVector.size(); i++)
		{
			vecsimilarclients.push_back(clientprod());
			vecsimilarclients[i].index = i;
			vecsimilarclients[i].nummatches = 0;
			vecsimilarclients[i].total = 0;
			if (i != index)
			{
				for (unsigned int ii = 0; ii < products_in_Transactions_Vector.size(); ii++)
				{
					if (matrixPublicity[i][ii] && matrixPublicity[index][ii])
						vecsimilarclients[i].nummatches++;
					if (matrixPublicity[i][ii])
						vecsimilarclients[i].total++;
				}
			}
		}

		vector<unsigned int> indexallsimilar;
		unsigned int max = 0;
		for (unsigned int i = 0; i < vecsimilarclients.size(); i++)
		{
			if (indexallsimilar.size() >= 1)
			{
				if ((vecsimilarclients[i].nummatches == vecsimilarclients[indexallsimilar[0]].nummatches && vecsimilarclients[i].nummatches >= max) && vecsimilarclients[i].total > vecsimilarclients[i].nummatches)
				{
					max = vecsimilarclients[i].nummatches;
					indexallsimilar.push_back(i);

				}
				else if (vecsimilarclients[i].nummatches > vecsimilarclients[indexallsimilar[0]].nummatches && vecsimilarclients[i].nummatches >= max && vecsimilarclients[i].total > vecsimilarclients[i].nummatches)
				{
					max = vecsimilarclients[i].nummatches;
					indexallsimilar.clear();
					indexallsimilar.push_back(i);
				}
			}
			else
			{
				if (vecsimilarclients[i].nummatches >= max && vecsimilarclients[i].total > vecsimilarclients[i].nummatches)
				{
					max = vecsimilarclients[i].nummatches;
					indexallsimilar.push_back(i);

				}
				else if (vecsimilarclients[i].nummatches >= max && vecsimilarclients[i].total > vecsimilarclients[i].nummatches)
				{
					max = vecsimilarclients[i].nummatches;
					indexallsimilar.resize(0);
					indexallsimilar.push_back(i);
				}
			}

		}
		vector<bool> indexbool;
		for (unsigned int i = 0; i < products_in_Transactions_Vector.size(); i++)
			indexbool.push_back(matrixPublicity[index][i]);

		if (indexallsimilar.size() == 1)
		{
			for (unsigned int i = 0; i < products_in_Transactions_Vector.size(); i++)
			{
				if (matrixPublicity[indexallsimilar[0]][i] == 1 && matrixPublicity[index][i] == 0)
				{
					cout << endl << "Maybe you want some " << products_in_Transactions_Vector[i] << "?";
					break;
				}
			}
		}
		else if (indexallsimilar.size() > 1)
		{
			for (unsigned int i = 0; i < matrixPublicity.size(); i++)
			{
				bool exist = false;
				for (unsigned int ii = 0; ii < indexallsimilar.size(); ii++)
				{

					if (i == indexallsimilar[ii])
					{
						exist = true;
						break;
					}
				}
				if (!exist || i == index)
				{
					for (unsigned int j = 0; j < products_in_Transactions_Vector.size(); j++)
						matrixPublicity[i][j] = false;
				}
			}

			for (unsigned int i = 0; i < products_in_Transactions_Vector.size(); i++)
			{
				if (indexbool[i])
				{
					for (unsigned int ii = 0; ii < matrixPublicity.size(); ii++)
						matrixPublicity[ii][i] = false;
				}
			}

			vector<productpublicity> prodpublicityvec;
			for (unsigned int i = 0; i < products_in_Transactions_Vector.size(); i++)
			{
				prodpublicityvec.push_back(productpublicity());
				prodpublicityvec[i].index = i;
				prodpublicityvec[i].total = 0;
				for (unsigned int ii = 0; ii < indexallsimilar.size(); ii++)
					if (matrixPublicity[indexallsimilar[ii]][i] == 1)
						prodpublicityvec[i].total++;

			}

			sort(prodpublicityvec.begin(), prodpublicityvec.end(), ComparebyTotal);
			cout << "Maybe you want some " << products_in_Transactions_Vector[prodpublicityvec[0].index] << "?";

		}
		else
			cout << "Falta fazer aqui de maneira a verificar se existe algum produto da lista de produtos que o cliente nao comprou, uma vez que se esta neste caso, e pq nas transacoes tem os produtos todos de la";
	}
	else if (transactionsVector.size() == 0 || productsVector.size() != 0)
		cout << "No related products for this person.. Maybe you want to try " << productsVector[1].getName() << "?";
	else if (transactionsVector.size() == 0 || productsVector.size() == 0)
		cout << "Publicity is not available for this person right now.. ";
}
*/

int main()
{
	cout << endl;
	c("______ __ __ ______   _____ _______    __      __  ");
	c("/  ___/|  |  |\\     \\ / ___ \\\\_  __ \\ _|  |__ _|  |__");
	c("\\___ \\ |  |  ||  |\\  \\\\  ___/ |  | \\/|_    _/|_    _/");
	c("/_____\\|_____||  |/  / \\____/ |__|     |__|    |__|  ");
	c("|   __/                  ");
	c("|  |                     ");
	c("|__|                     ");
	cout << endl << endl << endl;
	c("Welcome!");
	cout << endl << endl << endl;
	system("pause");
	system("cls");

	while (firstMenu())
	{
		Store store;
		if (mainMenu(store))
			break;
	}
	
	return 0;
}