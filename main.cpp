#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
using namespace std;

class Transaction {
public:
    int id;
    string type;      // income or expense
    string category;
    double amount;
    string date;      // simple format: YYYY-MM-DD

    Transaction() {
        id = 0;
        amount = 0;
    }

    Transaction(int i, string t, string c, double a, string d) {
        id = i;
        type = t;
        category = c;
        amount = a;
        date = d;
    }

    void display() const {
        cout << id << " | "
             << type << " | "
             << category << " | "
             << amount << " | "
             << date << endl;
    }
};

class User {
public:
    string name;
    double balance;
    double monthlyBudget;

    User() {
        name = "Default";
        balance = 0;
        monthlyBudget = 0;
    }
};

class ExpenseManager {
private:
    vector<Transaction> transactions;
    User user;

public:
    ExpenseManager() {
        loadFromFile();
        recomputeBalance();
    }

    void setUserName() {
        cout << "Enter user name: ";
        cin >> user.name;
    }

    void setBudget() {
        try {
            double b;
            cout << "Enter monthly budget: ";
            cin >> b;

            if(cin.fail()) {
                throw runtime_error("Invalid numeric input.");
            }

            if(b < 0) {
                throw invalid_argument("Budget cannot be negative.");
            }

            user.monthlyBudget = b;
            cout << "Budget updated successfully.\n";
        }
        catch(exception &e) {
            cout << "Error: " << e.what() << endl;
            clearInput();
        }
    }

    void addTransaction() {
        try {
            int id;
            string type;
            string category;
            double amount;
            string date;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter type (income/expense): ";
            cin >> type;

            if(type != "income" && type != "expense") {
                throw invalid_argument("Type must be income or expense.");
            }

            cout << "Enter category: ";
            cin >> category;

            cout << "Enter amount: ";
            cin >> amount;

            if(cin.fail()) {
                throw runtime_error("Invalid amount input.");
            }

            if(amount <= 0) {
                throw invalid_argument("Amount must be positive.");
            }

            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;

            Transaction t(id, type, category, amount, date);
            transactions.push_back(t);

            if(type == "income") {
                user.balance += amount;
            }
            else {
                user.balance -= amount;
            }

            cout << "Transaction added successfully.\n";
            checkBudgetWarning();
        }
        catch(exception &e) {
            cout << "Error: " << e.what() << endl;
            clearInput();
        }
    }

    void viewTransactions() const {
        if(transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }

        cout << "\nID | TYPE | CATEGORY | AMOUNT | DATE\n";
        cout << "------------------------------------\n";

        for(const auto &t : transactions) {
            t.display();
        }
    }

    void showSummary() const {
        double income = 0;
        double expense = 0;

        for(const auto &t : transactions) {
            if(t.type == "income") {
                income += t.amount;
            }
            else {
                expense += t.amount;
            }
        }

        cout << "\n----- SUMMARY -----\n";
        cout << "User: " << user.name << endl;
        cout << "Total Income: " << income << endl;
        cout << "Total Expense: " << expense << endl;
        cout << "Balance: " << user.balance << endl;
        cout << "Budget: " << user.monthlyBudget << endl;
    }

    void searchByCategory() const {
        string cat;
        cout << "Enter category to search: ";
        cin >> cat;

        bool found = false;
        for(const auto &t : transactions) {
            if(t.category == cat) {
                t.display();
                found = true;
            }
        }

        if(!found) {
            cout << "No matching transactions.\n";
        }
    }

    void saveToFile() {
        ofstream file("transactions.txt");

        if(!file) {
            cout << "Could not open file for writing.\n";
            return;
        }

        for(const auto &t : transactions) {
            file << t.id << ' '
                 << t.type << ' '
                 << t.category << ' '
                 << t.amount << ' '
                 << t.date << '\n';
        }

        file.close();
        cout << "Data saved successfully.\n";
    }

    void loadFromFile() {
        ifstream file("transactions.txt");

        if(!file) {
            return;
        }

        transactions.clear();

        Transaction t;
        while(file >> t.id >> t.type >> t.category >> t.amount >> t.date) {
            transactions.push_back(t);
        }

        file.close();
    }

private:
    void recomputeBalance() {
        user.balance = 0;

        for(const auto &t : transactions) {
            if(t.type == "income") {
                user.balance += t.amount;
            }
            else {
                user.balance -= t.amount;
            }
        }
    }

    void checkBudgetWarning() const {
        if(user.monthlyBudget <= 0) {
            return;
        }

        double expense = 0;

        for(const auto &t : transactions) {
            if(t.type == "expense") {
                expense += t.amount;
            }
        }

        if(expense >= user.monthlyBudget) {
            cout << "WARNING: Budget exceeded!\n";
        }
        else if(expense >= user.monthlyBudget * 0.8) {
            cout << "WARNING: You have used 80% of budget.\n";
        }
    }

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

int main() {
    ExpenseManager manager;

    int choice;

    do {
        cout << "\n===== SMART EXPENSE TRACKER =====\n";
        cout << "1. Set User Name\n";
        cout << "2. Add Transaction\n";
        cout << "3. View Transactions\n";
        cout << "4. Show Summary\n";
        cout << "5. Set Budget\n";
        cout << "6. Search by Category\n";
        cout << "7. Save Data\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                manager.setUserName();
                break;
            case 2:
                manager.addTransaction();
                break;
            case 3:
                manager.viewTransactions();
                break;
            case 4:
                manager.showSummary();
                break;
            case 5:
                manager.setBudget();
                break;
            case 6:
                manager.searchByCategory();
                break;
            case 7:
                manager.saveToFile();
                break;
            case 8:
                manager.saveToFile();
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while(choice != 8);

    return 0;
}
