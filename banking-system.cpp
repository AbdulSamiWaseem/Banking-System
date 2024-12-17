#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;
class Transaction;
class Account;
template<typename T>
class LinkedList {
private:
	class Node {
	public:

		T data;
		Node(T d, Node* n, Node* p) {
			data = d;
			next = n;
			prev = p;
		}
		Node(Node* n = nullptr, Node* p = nullptr) {
			next = n;
			prev = p;
		}
		~Node() {

		}
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	int count;
public:
	LinkedList() {
		Node* h = new Node();
		Node* t = new Node();
		head = h;
		tail = t;
		head->next = tail;
		tail->prev = head;
		count = 0;
	}

	class Iterator {
		friend class LinkedList;
	private:
		Node* curr;
	public:
		Iterator(Node* temp = nullptr) {
			curr = temp;
		}
		Iterator(const Iterator& rhs) {
			curr = rhs.curr;
		}
		Iterator& operator++() {
			curr = curr->next;
			return *this;
		}
		Iterator& operator--() {
			curr = curr->prev;
			return *this;
		}
		bool operator==(const Iterator& rhs) {
			if (curr == rhs.curr)
				return true;
			return false;
		}
		bool operator!=(const Iterator& rhs) {
			if (curr != rhs.curr)
				return true;
			return false;
		}
		T& operator*() {
			return curr->data;
		}
		T GetData()
		{
			return this->curr->data;
		}


	};
	Iterator Begin() const {
		Iterator itr(head->next);
		return itr;
	}
	Iterator End() const {
		Iterator itr(tail);
		return itr;
	}
	Iterator Insert(Iterator it, T d)
	{
		Node* c = it.curr;
		Node* temp = new Node;
		temp->data = d;
		temp->prev = c->prev;
		temp->next = c;
		c->prev->next = temp;
		c->prev = temp;
		Iterator itr(temp);
		count++;
		return itr;
	}
	void InsertAtStart(T d) {
		Iterator itr(head->next);
		Insert(itr, d);
	}
	void InsertAtEnd(T d) {
		Iterator itr(tail);
		Insert(itr, d);
	}
	void RemoveValue(T const V) {
		Account temp;
		Account t = V;

		for (Iterator itr = Begin(); itr != End(); ++itr) {
			temp = itr.curr->data;
			if (temp.GetAccNum() == t.GetAccNum()) {
				itr.curr->next->prev = itr.curr->prev;
				itr.curr->prev->next = itr.curr->next;
				Node* n = itr.curr;
				itr.curr = itr.curr->next;
				delete n;
				count--;
				break;
			}


		}
	}
	void print() {
		Iterator itr;
		Account temp;
		for (itr = Begin(); itr != End(); ++itr) {
			temp = itr.curr->data;
			cout << endl;
			temp.display();
			cout << endl;
		}
		cout << endl << endl;

	}
	Iterator search(int num) {
		Iterator itr;
		T temp;
		for (itr = Begin(); itr != End(); ++itr) {
			temp = itr.curr->data;
			if (temp.GetAccNum() == num) {
				return itr;
			}
		}
	}
	void DeleteAll()
	{
		while (head->next != tail)
		{
			Node* temp = head->next;
			head->next = temp->next;
			temp->next->prev = head;
			delete temp;
			count--;
		}
	}
	LinkedList(const LinkedList& other)
	{
		head = new Node;
		tail = new Node;
		head->next = tail;
		head->prev = nullptr;
		tail->next = nullptr;
		tail->prev = head;
		count = 0;

		for (Iterator itr = other.Begin(); itr != other.End(); ++itr)
		{
			InsertAtEnd(itr.GetData());
		}
	}
	LinkedList& operator=(const LinkedList& other)
	{
		if (this == &other) {
			return *this;
		}
		DeleteAll();
		for (Iterator itr = other.Begin(); itr != other.End(); ++itr)
		{
			InsertAtEnd(itr.GetData());
		}

		return *this;
	}
	
	~LinkedList()
	{
		DeleteAll();
		delete head;
		delete tail;
	}
};

class Transaction {
private:
	int transId;
	string transDate_Time;
	string transType;
	int transAmount;
	int AccNumOfSender;
public:

	Transaction(string  type = " ", int const amount = 0, int const accNum = 0,int const id=0) {
		time_t now = time(0);
		char* dt = ctime(&now);
		transDate_Time = dt;
		transId = id;
		transType = type;
		transAmount = amount;
		AccNumOfSender = accNum;
	}
	Transaction(const Transaction& c) {
		transId = c.transId;
		transDate_Time = c.transDate_Time;
		transType = c.transType;
		transAmount = c.transAmount;
		AccNumOfSender = c.AccNumOfSender;
	}
	Transaction& operator=(const Transaction& c) {
		if (this == &c) {
			return *this;
		}
		else {
			transId = c.transId;
			transDate_Time = c.transDate_Time;
			transType = c.transType;
			transAmount = c.transAmount;
			AccNumOfSender = c.AccNumOfSender;

			return *this;
		}

	}
	void print() {
		cout << "\nTransaction Id : " << transId;
		cout << "\nTransaction Date and Time : " << transDate_Time;
		cout << "\nTransaction Amount : " << transAmount;
		cout << "\n Sender Account Number : " << AccNumOfSender;

	}
	int GetTransId() {
		return transId;
	}

};
class Account {
private:
	int accNum;
	string accTitle;
	int accBalance;
	LinkedList<Transaction> history;
	static int AccountNumbers;
	
	int TransactionNumber;
public:

	Account(const string title = "", int balance = 0) {
		accNum = ++AccountNumbers;
		accTitle = title;
		accBalance = balance;

	}
	Account(const Account& other) {
		accNum = other.accNum;
		accTitle = other.accTitle;
		accBalance = other.accBalance;
		history = other.history;
		TransactionNumber = other.TransactionNumber;
	}
	Account& operator=(const Account& other) {
		if (this == &other) {
			return *this;
		}
		accNum = other.accNum;
		accTitle = other.accTitle;
		accBalance = other.accBalance;
		history = other.history;
		TransactionNumber = other.TransactionNumber;
		return *this;
	}
	void creditTransaction(int amount, Transaction t) {
		accBalance = accBalance + amount;
		history.InsertAtEnd(t);
		cout << "Welcome " << accTitle << " to our Bank" << endl;
		cout << "Your Account Number : " << accNum << endl;
		cout << "The amount of " << amount << " has been successfully credited to your Bank account." << endl;
		cout << "Your current Balance is : " << accBalance << endl;
		cout << "Thank You !" << endl;
		cout << "\n\t\t\t***Transaction History***\n\n";
		t.print();
	}
	void debitTransaction(int amount, Transaction t) {
		if (accBalance >= amount) {
			accBalance = accBalance - amount;
			history.InsertAtEnd(t);
			cout << "Welcome " << accTitle << " to our Bank" << endl;
			cout << "Your Account Number : " << accNum << endl;
			cout << "The amount of " << amount << " has been successfully debited to your Bank account." << endl;
			cout << "Your remaining Balance is : " << accBalance << endl;
			cout << "Thank You !" << endl;
			cout << "\n\t\t\t***Transaction History***\n\n";
			t.print();
		}
		else {
			cout << "Insufficient Balance" << endl;
			cout << "You have " << amount << " in you account\n";
			cout << "Kindly perform Valid Transaction\n";
		}
	}
	void display() {
		cout << "Account Holder : " << accTitle << endl;
		cout << "Account Number : " << accNum << endl;
		cout << "Account Balance : " << accBalance << endl;
	}
	int GetAccNum() {
		return accNum;
	}
	int GetAccBalance() {
		return accBalance;
	}
	void MergeLists(Account* a1, Account* a2) {

		LinkedList<Transaction>::Iterator itr1(a1->history.Begin());
		LinkedList<Transaction>::Iterator itr2(a2->history.Begin());

		while (itr1 != a1->history.End() && itr2 != a2->history.End())
		{
			Transaction* t1 = &(*itr1);
			Transaction* t2 = &(*itr2);

			if (t1->GetTransId() < t2->GetTransId())
			{
				this->history.InsertAtEnd(*itr1);
				++itr1;
			}
			else if (t2->GetTransId() < t1->GetTransId())
			{
				this->history.InsertAtEnd(*itr2);
				++itr2;
			}

		}
	}
};
class Bank {
private:
	LinkedList<Account> accList;
	int TotalAccounts = 0;
	int TransIds = 0;
public:
	Bank() {}
	void addNewAccount(Account newAcc) {
		accList.InsertAtEnd(newAcc);
		cout << "\nAccount Number " << newAcc.GetAccNum() << " has been added in bank" << endl;
		TotalAccounts++;
	}
	void remExistingAccount(Account acc) {
		accList.RemoveValue(acc);
		cout << "\nAccount Number " << acc.GetAccNum() << " has been removed from bank" << endl;
		TotalAccounts--;
	}
	void display() {
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		cout << "\t\t\t\t\t\tWelcome to our Bank\n ";
		cout << "Accounts List :\n";
		accList.print();
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";

	}
	void Trans(string type, int accNum, int amount) {
		LinkedList<Account>::Iterator itr(accList.Begin());
		bool flag = true;
		while (itr != nullptr)
		{
			Account* temp = &(*itr);
			if (temp->GetAccNum() == accNum)
			{
				if (type == "credit") {
					TransIds++;
					Transaction t(type, amount, accNum, TransIds);
					temp->creditTransaction(amount, t);
					flag = false;
					break;
				}
				else if (type == "debit") {
					TransIds++;
					Transaction t(type, amount, accNum, TransIds);
					temp->debitTransaction(amount, t);
					flag = false;
					break;
				}
				else {
					cout << "Transaction Failed Due to Wrong Type " << endl;
				}
			}
			++itr;
		}
		if (flag)
			cout << "Account doesnot Exist";
	}
	void MergeAccounts(int accNum1, int accNum2)
	{
		LinkedList<Account>::Iterator itr(accList.Begin());
		Account* acc1 = nullptr;
		Account* acc2 = nullptr;
		bool f1 = false, f2 = false;
		while (itr != accList.End())
		{
			Account* current = &(*itr);
			if (current->GetAccNum() == accNum1)
			{
				acc1 = current;
				f1 = true;
			}
			else if (current->GetAccNum() == accNum2)
			{
				acc2 = current;
				f2 = true;
			}
			if (f1 == true && f2 == true) {
				break;
			}
			++itr;
		}
		TotalAccounts++;
		char name[100];
		cout << "Enter New Name for the Merged Account : ";
		cin.getline(name, 100);
		int balance = acc1->GetAccBalance() + acc2->GetAccBalance();

		Account MergedAccount(name, balance);
		MergedAccount.MergeLists(acc1, acc2);
		addNewAccount(MergedAccount);
		cout << "\nCongrats! New Merged Account is created!" << endl;
		remExistingAccount(*acc1);
		remExistingAccount(*acc2);

	}
};
int Account::AccountNumbers = 0;
int main() {
	Account a1("Hassan", 10000);
	Account a2("Ali ", -1000);
	Account a3("Abdul Sami", 1000);
	Account a4("Mamoon", 15000);
	Account a5("Ahmad", 5400);

	Bank Meezan;
	Meezan.addNewAccount(a1);
	Meezan.addNewAccount(a2);
	Meezan.addNewAccount(a3);
	Meezan.addNewAccount(a4);
	Meezan.addNewAccount(a5);

	Meezan.display();
	Meezan.remExistingAccount(a1);
	cout << endl;
	Meezan.display();
	cout << endl << endl;

	Meezan.Trans("credit", 3, -500);
	Meezan.display();
	cout << endl << endl;

	Meezan.Trans("debit", 2, 50000);
	Meezan.display();

	Meezan.Trans("debit", 2, 2000);
	Meezan.display();

	Meezan.MergeAccounts(3, 2);
	Meezan.display();

	Meezan.Trans("cre", 19, 2000);
	Meezan.display();

	return 0;
}