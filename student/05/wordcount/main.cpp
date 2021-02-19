#include <iostream>
#include <fstream>
#include <map>
#include <set>

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
    map<string, set<int>> word_count;
    string line = "";
    string word = "";
    int line_number = 1;
    while(getline(input_file,line))
    {
        // Käydään riveittäin
        for (int i = 0 ; i < int(line.size()) ; i++)
        {
            char letter = line.at(i);
            if (letter == ' ')
            {
                // Jos sanaa ei ole vielä rakenteessa, lisätään se sinne
                if (word_count.find(word)==word_count.end())
                {
                    set<int>lines;
                    lines.insert(line_number);
                    word_count.insert( {word, lines} );
                }
                // Lisätään rivinumero
                else
                {
                    word_count.at(word).insert(line_number);
                }
                word = "";
            }

            else if(i == int(line.size())-1)
            {
                word.push_back(letter);
                // Jos sanaa ei ole vielä rakenteessa, lisätään se sinne
                if (word_count.find(word)==word_count.end())
                {
                    set<int>lines;
                    lines.insert(line_number);
                    word_count.insert( {word, lines} );
                }
                // Lisätään rivinumero
                else
                {
                    word_count.at(word).insert(line_number);
                }
                word = "";

            }
            else
            {
                word.push_back(letter);
            }

            /*
            // Jaetaan rivi sanoihin
            if (letter != ' ' and i < int(line.size())-1)
            {
                word.push_back(letter);
            }
            // Lisätään ensimmäinen sana rakenteeseen
            else
            {
                // Jos sanaa ei ole vielä rakenteessa, lisätään se sinne
                if (word_count.find(word)==word_count.end())
                {
                    set<int>lines;
                    lines.insert(line_number);
                    word_count.insert( {word, lines} );
                }
                // Lisätään rivinumero
                else
                {
                    word_count.at(word).insert(line_number);
                }
                word = "";
            } */
        }
        // rivi vaihtuu
        line_number++;
    }
    // Nyt on talletettu sanat ja niiden esiintyminen tietorakenteeseen
    // Tulostetaan
    for (auto word: word_count)
    {
        // Määritellään tulostettavat rivit
        string rivit_str = "";
        set<int>::iterator iter;
        // <1,2,3>
        iter = word.second.begin();
        while(iter!=word.second.end())
        {
            int x=*iter;

            rivit_str += to_string(x);

            ++iter;
            if (iter != word.second.end())
            {
                rivit_str += ", ";
            }
        }
        cout << word.first <<" "<<word.second.size() <<": "<< rivit_str << endl;
    }

    return EXIT_SUCCESS;


}
