#include <iostream>

using namespace std;

class GasStation{
    public:
        int gasAmount;
        double pricePerLiter;

        GasStation(int gasAmt, double price){
            gasAmount = gasAmt;
            pricePerLiter = price;
        }

        int pumpGas(int pumpFromCustomer){
            gasAmount -= pumpFromCustomer;        
            return gasAmount;
        }

        double totalPrice(int pumpFromCustomer){
            double total = pricePerLiter * pumpFromCustomer;
            return total;
        }

};


int main(){
    system("cls");

    GasStation petron(500, 50.0);//!500 liters & 50 pesos per litter
    cout << "The Gas Station's gas limit is: " << petron.gasAmount << " Liters"<< endl;
    cout << "Price Per Gallon is: " << petron.pricePerLiter << "PHP" << endl << endl;

    int getPump;
    cout << "Enter pump amount in liters: ";
    cin >> getPump;

    cout << "The remaining gas: "<< petron.pumpGas(getPump) << endl;
    cout << "The total price is: " << petron.totalPrice(getPump) << "PHP";

    
    string user;
    cout << endl << "Do you want to trancsact again? ENTER(Y/N)";
    cin >> user;

    while(user == "y" || user == "Y"){
        system("cls");
        
        cout << "The Gas Station's gas limit is: " << petron.gasAmount << " Liters"<< endl;
        cout << "Price Per Gallon is: " << petron.pricePerLiter << "PHP" << endl << endl;

        int getPump;
        cout << "Enter pump amount in liters: ";
        cin >> getPump;


        cout << "NO GAS AVAILABLE!" << endl;
        cout << "The remaining gas: "<< petron.pumpGas(getPump) << endl;

        
        cout << "The total price is: " << petron.totalPrice(getPump) << "PHP";

        cout << endl << "Do you want to trancsact again? ENTER(Y/N)";
        cin >> user;
        

        if(user == "N" || user == "n"){
            break;
        }
    }


}