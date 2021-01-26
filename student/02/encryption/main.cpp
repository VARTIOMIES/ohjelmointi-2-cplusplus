#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool lower_az_ASCII(string string) {
    int pituus = string.length();
    for (int i = 0; i < pituus; ++i){
        char merkki = string[i];
        int merkin_ASCII = static_cast<int>(merkki);
        if (not islower(merkki)){
            return false;
        } else if (merkin_ASCII < 97 or merkin_ASCII > 122){
            return false;
        }

    }
    return true;
}

int main()
{
    cout << "Enter the encryption key: ";
    string encryption_key = "";
    getline(cin,encryption_key);

    if (encryption_key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 0;
    } else if (lower_az_ASCII(encryption_key))

    return 0;
}
