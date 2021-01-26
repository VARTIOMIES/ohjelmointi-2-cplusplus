#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool only_az_ASCII(string string) {
    int pituus = string.length();
    for (int i = 0; i < pituus; ++i){
        int merkin_ASCII = static_cast<int>(string[i]);
        if (merkin_ASCII < 97 or merkin_ASCII > 122){
            return false;
        }
    }
    return true;
}

bool all_az_ASCII(string string) {
    int pituus = string.length();
    // Käydään läpi aakkoset
    for (int j = 97; j <= 122; ++j){
        bool kirjain_sanassa = false;
        // Käydään läpi string
        for (int i = 0; i < pituus; ++i){
            char merkki = string[i];
            int merkin_ASCII = static_cast<int>(merkki);
            // Tarkastetaan, onko merkki ja tämän hetkinen aakkonen samat
            if (merkin_ASCII == j){
                // Jos on, niin poistutaan sanan läpikäymisestä, koska tämä aakkonen
                //on ainakin sanassa
                kirjain_sanassa = true;
                break;
            }
        }
        // Jos sana on käyty kokonaan läpi, ja kirjainta ei ole sanassa
        // niin kirjain_sanassa muuttuja on false, jolloin tässä vaiheessa voidaan
        // todeta, että kaikki aakkoset eivät ole sanassa.
        if (not kirjain_sanassa){
            return false;
        }
        // Siirrytään seuraavaan aakkoseen, mikäli edellinen aakkonen ainakin oli sanassa
    }
    // Kaikki aakkoset on käyty läpi, ja funktiosta ei olla poistuttu, joten kaikki
    // aakkoset ovat sanassa. Palautetaan totuusarvo true
    return true;

}
string encrypt(string text, string key) {
    int tekstin_pituus = text.length();
    // Käydään teksti läpi
    for(int i=0;i<tekstin_pituus;++i){
        char kirjain = text[i];
        int kirjaimen_ASCII = static_cast<int>(kirjain);
        int kohta_keyssa = kirjaimen_ASCII-97;
        text[i] = key[kohta_keyssa];
    }
    return text;
}

int main()
{
    cout << "Enter the encryption key: ";
    string encryption_key = "";
    getline(cin,encryption_key);

    if (encryption_key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 1;
    } else if (not only_az_ASCII(encryption_key)){
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return 1;
    } else if (not all_az_ASCII(encryption_key)){
        cout << "Error! The encryption key must contain all alphabets a-z" << endl;
        return 1;
    }
    // Salausavain on siis halutunlainen. Kysytään nyt salattavaa tekstiä
    cout << "Enter the text to be encrypted: ";
    string text = "";
    getline(cin,text);

    if (not only_az_ASCII(text)){
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return 1;
    }

    // Aloitetaan salaaminen
    string encypted_text = encrypt(text, encryption_key);
    cout << "Encrypted text: " << encypted_text << endl;

    return 0;
}
