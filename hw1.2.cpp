//
//  main.cpp
//  HW1.2
//
//  Created by Avinash Shrivastava on 8/28/18.
//  Copyright © 2018 Avinash Shrivastava. All rights reserved.
//
// Author(s):
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ
// MSCF, Pittsburgh


#include <iostream>
#include <iomanip>
using namespace std;

struct Stock {
    char ticker[8];  // leave some extra space
    int id;          // my firm's ID for this stock
    double price;
};

struct Portfolio {
    Stock *stocks;   // the "array" of Stocks
    int *num_owned;  // can sell short, so int
    size_t nstocks;  // number of stocks, >= 0
};

void put_Stock(Stock *ps) {
    cout << setw(8) << ps->ticker << setw(4) << (*ps).id
    << setw(10) << ps[0].price;
}

void put_portfolio_and_value(Portfolio *p1) {
    double port_value = 0;
    for (int i(0); i < (*p1).nstocks; ++i) {
        put_Stock((*p1).stocks + i);
        cout << setw(6) << (*p1).num_owned[i];

        double value = (((*p1).stocks + i)->price*((*p1).num_owned[i]));
        port_value += value;
        cout << setw(10) << value <<endl;
    }
    cout << setw(20) << "Portfolio Value" << setw(10) << port_value <<endl;
}

int main()
{
    Stock apple{ "AAPL", 0, 162.45 },
    vmware{ "VMW", 1, 120.08 },
    ibm{ "IBM", 2, 153.72 },
    alcoa{ "AA", 3, 47.71 },
    ford{ "F", 4, 12.07 },
    samsung{ "SAMS", 5, 141.9 },//Added 3 extra stock objects
    Exxon{ "XOM", 6, 241.2  },
    Tesla{ "TSL", 7, 120.7 };

    Portfolio p1{ new Stock[6]{ apple, ibm, ford, samsung, Exxon, Tesla},
        new int[6]{ 20, 10, -5, 20, 13, -4 },
        6 };
    
    Portfolio *pp(&p1 + 2);
    Stock *ppf{p1.stocks + 1};
    
    cout << "Portfolio:\n";
    cout << setw(8) << "Stock" << setw(4) << "id"
    << setw(10) << "price" << setw(6) << "Position" << setw(10) << "Value" <<endl;

    for (int i(0); i < p1.nstocks; ++i) {
        put_Stock(p1.stocks + i);//passing a pointer to 'stock' object; value is address to the first element(apple object)
        cout << setw(10) << p1.num_owned[i] << '\n';
    }
    
    *(p1.num_owned + 2) -= 10;
    
    cout << "\nModified portfolio:\n";
    for (int i(0); i < p1.nstocks; ++i) {
        put_Stock(p1.stocks + i);
        cout << setw(10) << p1.num_owned[i] << '\n';
    }

    cout << "\nPrinting portfolio:\n";
    put_portfolio_and_value(&p1);
    
    //apple.ticker has value = "APPL"
    cout << "APPLE ticker: " << ((p1.stocks)[0]).ticker <<endl;//just trying
    
    //ticker is an array of char with 8 elements
    //value of apple.ticker[3] is "L" which is a char
    cout << "4th element of APPLE ticker: " << ((p1.stocks)[0]).ticker[3] <<endl;//just trying
    //p1.stocks + 2 is a pointer to "stock" object, pointing to IBM object
    
    //value of sizeof(ford.ticker), type is memory in integer bytes
    cout << "value of sizeof(ford ticker): " << sizeof(((p1.stocks)[4]).ticker) <<endl;

    //value of sizeof(vmware.ticker), type is memory in integer bytes
    cout << "value of sizeof(vmware ticker): " << sizeof(((p1.stocks)[1]).price) <<endl;

    //value of sizeof(p1.numowned), type is memory in integer bytes
    cout << "value of sizeof(p1.numowned): " << sizeof(p1.num_owned) <<endl;

    //type of *p1, not a pointer and hence should give error
//    cout << "value of *p1: " << *p1 <<endl; //doesn't compile
    
    //(p1.stocks + 1)->ticker[3] data type is char
    cout << "value of (p1.stocks + 1)->ticker[3]: " << (p1.stocks + 1)->ticker[3] <<endl;
    
    //(*p1.stocks). ticker + 3 data type is char
    cout << "value of (*p1.stocks). ticker + 3: " << ((*p1.stocks).ticker + 3) <<endl;
    
    //p1.stocks[2].id is integer type
    cout << "value of p1.stocks[2].id: " << p1.stocks[2].id <<endl;
    
    //(*&p1).num_owned[1] - 3 is integer type
    cout << "value of (*&p1).num_owned[1] - 3: " << (*&p1).num_owned[1] - 3 <<endl;
    
    cout<< "example apple price: " << pp[-2].stocks->price <<endl; //since pp[-2].stocks is a pointer, shouldn't we be using * to get the stock and then get the price?
    
    cout<< "ford id: " << ppf[1].id <<endl;
    cout<< "ford id with different expression: " << (*(ppf+1)).id <<endl;

    cout<< "IBM id: " << ppf->id <<endl;
    cout<< "IBM id with different expression: " << (*(&ppf))->id <<endl;

    char *addr = ((pp[-2].stocks)[0].ticker+2);
    cout<< "address of P in apple: " << static_cast<void*>(addr) <<endl;

    char *addr2 = (((pp-2)->stocks)[0].ticker+2);
    cout<< "address of P in apple: " << static_cast<void*>(addr2) <<endl;

    char *addr3 = ((pp[-2].stocks[0]).ticker+2);
    cout<< "address of P in apple: " << static_cast<void*>(addr3) <<endl;

    char *addr4 = ((pp[-2].stocks)->ticker+2);
    cout<< "address of P in apple: " << static_cast<void*>(addr4) <<endl;

    char *addr5 = ((pp[-2].stocks)[0].ticker);
    cout<< "address of P in apple: " << static_cast<void*>(addr5+2) <<endl;

    char *addr6 = (((pp-2)->stocks)[0].ticker+2);
    cout<< "address of P in apple: " << static_cast<void*>(addr6) <<endl;

    delete[] p1.stocks;
    delete[] p1.num_owned;
}
