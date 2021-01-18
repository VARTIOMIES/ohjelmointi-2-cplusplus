#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    double temperature;
    cin >> temperature;
    double temp_cels_to_fahren = 1.8*temperature + 32;
    double temp_fahren_to_cels = (temperature-32)/1.8;
    cout << temperature << " degrees Celsius is " << temp_cels_to_fahren
         << " degrees Fahrenheit " << endl;
    cout << temperature << " degrees Fahrenheit is " << temp_fahren_to_cels
         << " degrees Celsius " << endl;

    // Write your code here

    return 0;
}
