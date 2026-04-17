#include <iostream>
#include<fstream>
#include<vector>

using namespace std;
class Transaction{
    public:
    int id;
    string type;
    string category;
    string date;
    double amount;

    void input(){
            cout<<"Enter you trasaction Id:";
            cin>>id;
            cout<<"Enter Type (Expence OR Income): ";
            cin>>type;
            cout<<"Enter Amount: ";
            cin>>amount;
            if(type=="Expence"||type=="expence"){
                 cout<<"Enter Category: ";
                   cin>>category;
            }
            cout<<"Enter Date: ";
            cin>>date;
    }
};

int main()
{
    vector<Transaction>Trs;
    Transaction t1;
    t1.input();

    // write your code here...
    Trs.push_back(t1);
    for(auto a:Trs){
        ofstream Myfile("transaction.txt");
        Myfile<<"ID: "<<t1.id<<endl<<"Type: "<<t1.type<<endl<<"Category: "<<t1.category<<
        endl<<"Amount: "<<t1.amount<<endl<<"Date: "<<t1.date<<endl<<
        "-------------------------"<<endl;
        Myfile.close();
    }
    
    
    return 0;
}
