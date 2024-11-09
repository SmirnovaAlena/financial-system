#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class CFundsStorage {
public:
	int amount;
	int cvv;
	CFundsStorage(int initialAmount, int initcvv) : amount(initialAmount), cvv(initcvv) {}
	friend void transfer(CFundsStorage& from, CFundsStorage& to) {
		int transferAmount;
		cout << "Enter amount for transfer\n";
		cin >> transferAmount;
		/*if (from.amount >= transferAmount) {*/
		from.amount -= transferAmount;
		to.amount += transferAmount;
		cout << "././././././..." << "\n";
		cout << "the transfer was completed successfully" << "\n" << " - " << transferAmount << "\n" << "money on the first account: \n " << from.amount << "\nmoney on the second account: \n " << to.amount << "\n";
		/*}
		else {
			cout << "insufficient funds for the transfer" << endl;
		}*/
	}
	friend void NotFromMyAccount(CFundsStorage& to) {
		int transferAmount;
		cout << "Enter amount for transfer\n";
		cin >> transferAmount;
		to.amount += transferAmount;
	}
	friend void expenses(CFundsStorage& from) {
		int transferAmount;
		cout << "Enter amount for transfer\n";
		cin >> transferAmount;
		cout << "enter direction of transfer\n ----------------------- \n 1-transport \n 2-communal services \n 3-food \n --------------------------\n";
		int direction;
		cin >> direction;
		if (direction == 1) {
			ofstream file("transport.txt",ios::app);
			file << transferAmount<<endl;
			file.close();
			ofstream file2("otchet.txt",ios::app);
			file2 << transferAmount<<"  "<<"transport"<<endl;
			file2.close();
		}
		else if (direction == 2) {
			ofstream file("communal.txt",ios::app);
			file << transferAmount<<endl;
			file.close();
			ofstream file2("otchet.txt",ios::app);
			file2 << transferAmount<<"  "<<"communal services"<<endl;
			file2.close();
		}
		else if (direction == 3) {
			ofstream file("food.txt",ios::app);
			file << transferAmount<<endl;
			file.close();
			ofstream file2("otchet.txt",ios::app);
			file2 << transferAmount<<"  "<<"food"<<endl;
			file2.close();
		}
		from.amount -= transferAmount;
		cout << "on your account: " << from.amount<<"\n";
	}
	CFundsStorage() {};
	~CFundsStorage() {};
};
class CCard : public CFundsStorage {
public:
	CCard(int initialAmount, int initcvv) : CFundsStorage(initialAmount, initcvv) {};
	CCard() {};
	~CCard() {};
};
void PrintMenu() {
	cout << "-----------------------------\n";
	cout << " 1-insert a new debit card \n 2-insert a new credit card \n 3-insert a new wallet \n 4-add a card \n 5-add expense \n 6-report \n 7-top-3 of expenses \n 8-top-3 of direction \n 9-goodbye" << "\n";
	cout << "-----------------------------" << "\n";
}
CCard depositDebit() {
	cout << "pleas enter number of cards,date, cvv code,current account " << "\n";
	int date, cvv, acount;
	long long number;
	cin >> number >> date >> cvv >> acount;
	CCard nd{ acount, cvv };
	return nd;
}
CCard depositCredit() {
	cout << "pleas enter number of cards,date, cvv code,current account without limit,limit " << "\n";
	int date, cvv, acount, limit;
	long long number;
	cin >> number >> date >> cvv >> acount >> limit;
	int sum = acount + limit;
	CCard nc{ sum, cvv };
	return nc;
}
CFundsStorage depositWallet() {
	cout << "pleas current account and come up with a wallet number " << "\n";
	int account, number;
	cin >> account >> number;
	CFundsStorage nw{ account,number };
	return nw;
}
int FindCard(CFundsStorage a[], int cincvv) {
	int count = 0;
	while (a[count].cvv != cincvv) {
		count++;
	}
	return count;
}

void find_max(ifstream& file) {
	string a;
	int max = 0;
	int max2 = 0;
	int max3 = 0;
	while (getline(file, a)) {
		if (stoi(a) >= max) {
			max3 = max2;
			max2 = max;
			max = stoi(a);
		}
		string b = "";
	}
	cout << max << "\n" << max2 << "\n" << max3 << "\n";
	
	/*find_digit(max);
	find_digit(max2);
	find_digit(max3);*/
}
int main() {
	int i = 0;
	int j = 0;
	int k = 0;
	CCard* DebitCardsArray = new CCard[1024];
	CCard* CreditCardsArray = new CCard[1024];
	CFundsStorage* WalletArray = new CFundsStorage[1024];
	int choose = 0;
	while (choose != 9) {
		PrintMenu();
		cin >> choose;
		if (choose == 1) {
			DebitCardsArray[i] = depositDebit();
			i++;

		}
		else if (choose == 2) {
			CreditCardsArray[j] = depositCredit();
			j++;
		}
		else if (choose == 3) {
			WalletArray[k] = depositWallet();
			k++;
		}
		else if (choose == 4) {
			cout << "select the type of card you want to sendmoney from\n 1-debit card \n 2-credit card \n 3-wallet \n 4-not from my account \n -------------------------\n";
			int choose_card;
			cin >> choose_card;
			int res1;
			if (choose_card == 1) {
				cout << "enter cvv code please\n";
				int cvv;
				cin >> cvv;
				res1 = FindCard(DebitCardsArray, cvv);
				cout << "which card is the deposit to \n 1-debit card \n 2-credit card \n 3-wallet \n";
				int choose_card2;
				cin >> choose_card2;
				int res2;
				int cvv2;
				switch (choose_card2) {
				case 1:
					cout << "enter cvv code\n";
					cin >> cvv2;
					res2 = FindCard(DebitCardsArray, cvv2);
					transfer(DebitCardsArray[res1], DebitCardsArray[res2]);
					break;
				case 2:
					cout << "enter cvv code\n";
					cin >> cvv2;
					res2 = FindCard(CreditCardsArray, cvv2);
					transfer(DebitCardsArray[res1], CreditCardsArray[res2]);
					break;
				case 3:
					cout << "enter number of wallet\n";
					int n;
					cin >> n;
					res2 = FindCard(WalletArray, n);
					transfer(DebitCardsArray[res1], WalletArray[res2]);
					break;
				}
			}
			else if (choose_card == 2) {
				cout << "enter cvv code please\n";
				int cvvc;
				cin >> cvvc;
				res1 = FindCard(CreditCardsArray, cvvc);
				cout << "which card is the deposit to \n 1-debit card \n 2-credit card \n 3-wallet \n";
				int choose_card2c;
				cin >> choose_card2c;
				int res2c;
				int cvv2c;
				switch (choose_card2c) {
				case 1:
					cout << "enter cvv code\n";
					cin >> cvv2c;
					res2c = FindCard(CreditCardsArray, cvvc);
					transfer(CreditCardsArray[res1], DebitCardsArray[res2c]);
					break;
				case 2:
					cout << "enter cvv code\n";
					cin >> cvv2c;
					res2c = FindCard(CreditCardsArray, cvv2c);
					transfer(CreditCardsArray[res1], CreditCardsArray[res2c]);
					break;
				case 3:
					cout << "enter number of wallet\n";
					int n2;
					cin >> n2;
					int res3с = FindCard(WalletArray, n2);
					transfer(CreditCardsArray[res1], WalletArray[res3с]);
					break;
				}
			}
			else if (choose_card == 3) {
				cout << "enter number of wallet please\n";
				int n;
				cin >> n;
				int res1w = FindCard(WalletArray, n);
				cout << "which card is the deposit to \n 1-debit card \n 2-credit card \n 3-wallet \n ";
				int choose_card2w;
				cin >> choose_card2w;
				int res2w;
				int cvv2w;
				switch (choose_card2w) {
				case 1:
					cout << "enter cvv code\n";
					cin >> cvv2w;
					res2w = FindCard(DebitCardsArray, cvv2w);
					transfer(WalletArray[res1w], DebitCardsArray[res2w]);
					break;
				case 2:
					cout << "enter cvv code\n";
					cin >> cvv2w;
					res2w = FindCard(CreditCardsArray, cvv2w);
					transfer(WalletArray[res1w], CreditCardsArray[res2w]);
					break;
				case 3:
					cout << "enter number of wallet\n";
					int n3;
					cin >> n3;
					int res4w = FindCard(WalletArray, n3);
					transfer(WalletArray[res1w], WalletArray[res4w]);
					break;
				}
			}
			else if (choose_card == 4) {
				cout << "which card is the deposit to \n 1-debit card \n 2-credit card \n 3-wallet \n";
				int choose_card2;
				cin >> choose_card2;
				int res4;
				int cvv4;
				switch (choose_card2) {
				case 1:
					cout << "enter cvv code\n";
					cin >> cvv4;
					res4 = FindCard(DebitCardsArray, cvv4);
					NotFromMyAccount(DebitCardsArray[res4]);
					break;
				case 2:
					cout << "enter cvv code\n";
					cin >> cvv4;
					res4 = FindCard(CreditCardsArray, cvv4);
					NotFromMyAccount(CreditCardsArray[res4]);
					break;
				case 3:
					cout << "enter number of wallet\n";
					int n;
					cin >> n;
					int res4w = FindCard(WalletArray, n);
					NotFromMyAccount(WalletArray[res4w]);
					break;
				}
			}
		}
		else if (choose == 5) {
			cout << "from which account was the cost made?\n";
			cout << "----------------------------------------\n";
			cout << "1-debit \n 2-credit \n 3-wallet \n ";
			cout << "------------------------------------------\n";
			int choose_exe_card;
			cin >> choose_exe_card;
			int cvvex;
			int resex;
			switch (choose_exe_card) {
			case 1:
				cout << "enter cvv of card\n----------------\n";
				cin >> cvvex;
				resex = FindCard(DebitCardsArray, cvvex);
				expenses(DebitCardsArray[resex]);
				break;
			case 2:
				cout << "enter cvv of card\n----------------\n";
				cin >> cvvex;
				resex = FindCard(CreditCardsArray, cvvex);
				expenses(CreditCardsArray[resex]);
				break;
			case 3:
				cout << "enter number of wallet\n----------------\n";
				int nex;
				cin >> nex;
				int resexw = FindCard(WalletArray, nex);
				expenses(WalletArray[resexw]);
				break;
			}

		}
		else if (choose == 6) {
			string a;
			ifstream file("otchet.txt");
			file.seekg(0, ios_base::beg);
			while (getline(file, a)) {
				/*file >> a;*/
				cout << a;
				cout << "\n";

			}
			file.close();
		}
		else if (choose == 7) {
			ifstream file("otchet.txt");
			find_max(file);
		}
		else if (choose == 8) {
			ifstream file("communal.txt");
			cout << "communal services: \n";
			find_max(file);
			file.close();
			cout << "\n";
			ifstream filef("food.txt");
			cout << "food: \n";
			find_max(filef);
			filef.close();
			cout << "\n";
			ifstream filea("transport.txt");
			cout << "transport: \n";
			find_max(filea);
			filea.close();

		}

	}
	return 0;
}
