#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    cout<<"Input file: ";
    string input_filename = "";
    getline(cin,input_filename);
    ifstream input_file(input_filename);
    if (not input_file)
    {
        cout<< "Error! The file " <<input_filename<< " cannot be opened."<<endl;
        return EXIT_FAILURE;
    }
    map<string,int> pelaajien_pisteet;
    string line = "";
    while(getline(input_file,line))
    {
        int separator_index = line.find(':');
        string name = "";
        for (int i=0;i<separator_index;i++)
        {
            name.push_back(line.at(i));
        }
        string pisteet_str = "";
        for (int i = separator_index+1 ; i < int(line.length()) ;i++)
        {
            pisteet_str.push_back(line.at(i));
        }
        int pisteet = stoi(pisteet_str);

        if (pelaajien_pisteet.find(name)!=pelaajien_pisteet.end())
        {
            // Pelaaja on jo rakenteessa. Lisätään hänen pisteitä
            pelaajien_pisteet.at(name) += pisteet;
        }
        else
        {
            // Lisätään pelaaja tietorakenteeseen
            pelaajien_pisteet.insert({name,pisteet});
        }
    }
    // Pelaajien kokonaispisteet on nyt tietorakenteessa. Tulostetaan
    cout << "Final scores:" << endl;
    for (auto pelaaja:pelaajien_pisteet)
    {
        cout << pelaaja.first << ": " << pelaaja.second << endl;
    }

}
