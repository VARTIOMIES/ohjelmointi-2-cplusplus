#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int number = 0;
    cin >> number;
    if (number <= 0){
        cout << "Only positive numbers accepted" << endl;
    } else {
        int jako = 1;
        int tekija1 = number;
        int tekija2 = 1;
        for (int i = 1; i <= number; ++i){
            // Tarkistetaan onko luku jaollinen i:llä
            if (number % i == 0){
                jako = number/i;
                if (abs(jako-i) < abs(tekija1-tekija2)){
                    tekija1 = i;
                    tekija2 = jako;
                }
            }
        }
        cout << number << " = " << tekija1 << " * " << tekija2 << endl;
    }
    return 0;
}
