Bank Management System - C++ Project
This project is a Bank Management System implemented in C++ using object-oriented programming principles. It supports account creation, transactions, and account merging, with a custom-built doubly linked list data structure to manage accounts and transactions efficiently.

Features
Account Management
Create New Accounts: Add new accounts with a unique account number, account title, and initial balance.
Remove Accounts: Delete an account from the system based on the account number.
Display Account Details: Show all account holders' details, including their account balance and transaction history.
Transactions
Credit Transactions: Add funds to an account with a complete transaction record.
Debit Transactions: Deduct funds from an account while ensuring sufficient balance is available.
Transaction History: Each account maintains a transaction log using a custom LinkedList implementation.
Account Merging
Merge two accounts into a new account:
Combine the balances of both accounts.
Merge their transaction histories in ascending order of transaction IDs.
Delete the old accounts after merging and create a new account with a user-defined name.
Technical Details
Core Components
LinkedList Template Class:

A doubly linked list implementation with support for iteration, insertion, deletion, and search.
Used for maintaining a dynamic list of accounts and transaction histories.
Account Class:

Manages account details, including account number, title, balance, and transaction history.
Handles credit and debit operations with proper logging.
Transaction Class:

Represents individual transactions with attributes like transaction ID, type (credit or debit), date/time, amount, and account number.
Bank Class:

Acts as the central system to manage all accounts and transactions.
Facilitates account creation, deletion, and merging.
Key Algorithms
Transaction Merging:

Merges transaction logs from two accounts while maintaining sorted order based on transaction IDs.
Custom Search:

Locate accounts by account number using an iterator on the doubly linked list.
Static Data Members
Ensures globally unique account numbers and transaction IDs across all operations.
Example Usage
Add Accounts: Create multiple accounts with unique account numbers.
Credit/Debit Transactions: Perform transactions on specific accounts while maintaining a log.
Merge Accounts: Combine two accounts, creating a new account with the total balance and merged transaction history.
Display Information: View all account details and transaction logs.
How to Run
Clone the repository.
Compile and run the program using any standard C++ compiler (e.g., GCC, Visual Studio).
Follow the prompts in the console to interact with the Bank Management System.
