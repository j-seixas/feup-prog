Development state: Complete.


Structure:
- File's names menu - Menu where you can introduce the file's names of a store so that you can start the the actual programm
- Once done, you're able to move on to the main menu
- In the main menu there are 8 options:
- 1) Read Files - Here you can read all the files with all the suggested and required options of the project
- 2) Clients Management - Here you can add/remove/modify clients
- 3) Products Management - Here you can add/remove/modify products
- 4) Transactions Management - Here you can add/remove transactions
- 5) Advertising - Here, by introducing the target client's ID, you can recommend products to that client based on all transactions, "similarity with other customers" and product popularity
- 6) BottomTen Advertising - Recommends a product to the bottomTen clients, based on all the transactions, "similarity with other customers" and product popularity
- 7) Options - Let's you choose how to sort clients/products/transactions
- 8) Returns to file's names menu so that you can re-introduce them in case of typo or to access another store. If changes were made to that store, then the app will prompt you to save changes
- 9) Exit - This is will close the program, but before, if there have been changes, this will ask you if you want to maintain those changes or quit without saving - Same for the exit option in the file's names menu


Advertising:
First, finds out all the clients which have the highest similarity level to the target-client.
Then, gets together all of their products, excluding the ones the target-client bought.
Lastly, figures out which of those products has the most sales and recommends them.


BottomTen Advertising:
First, checks if there are any common products to all the bottom ten clients
If there are none, then recommends two products, the product with most sales from the interesting clients and the one with the least sales from the bottom ten clients
Then, gets together all the interesting clients that have all of those common products and at least one more
If there are none, then recommends two products, the product with most sales from the interesting clients and the one with the least sales from the bottom ten clients
Next, gathers all the products that they bought, removing the common products to the bottom ten
Afterwards, checks if any of those products wasn't bought by any of the bottom ten clients. If so, recommends the one with most sales
If there's none in that situation, it will check the product with the biggest difference in sales between interesting clients and bottom ten clients
