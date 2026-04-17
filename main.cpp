#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Transaction {
public:
    int id;
    string type; // income / expense
    string category;
    double amount;
    string date;

    void display();
};
class User {
public:
    string name;
    double balance;
    double monthlyBudget;

    void updateBalance(double amount, string type);
};
class ExpenseManager {
private:
    vector<Transaction> transactions;

public:
    void addTransaction();
    void viewTransactions();
    void saveToFile();
    void loadFromFile();
    void showSummary();
};

int main()
{
    ExpenseManager Manager;
   do {
    cout << "\n1. Add Transaction\n";
    cout << "2. View Transactions\n";
    cout << "3. Show Summary\n";
    cout << "4. Set Budget\n";
    cout << "5. Exit\n";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: Manager.addTransaction(); break;
        case 2: Manager.viewTransactions(); break;
        case 3: Manager.showSummary(); break;
        case 4: // set budget
        case 5: cout<<"Exit Succesfully"<<endl;
        default: cout << "Invalid choice!";
    }
}while(!5);
    
    return 0;
}
