#pragma once

#include "Store.h"

unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max);
bool firstMenu();
bool clientsInformationMenu(Store &store);
bool transactionsInformationMenu(Store &store);
bool informationMenu(Store &store);
bool modifyClientsMenu(Store &store);
bool modifyProductsMenu(Store &store);
bool clientsMenu(Store &store);
bool productsMenu(Store &store);
bool transactionsMenu(Store &store);
bool sortClientOptions(Store &store);
bool sortProductsOptions(Store &store);
bool sortTransactionsOptions(Store &store);
bool optionsMenu(Store &store);
bool mainMenu(Store &store);