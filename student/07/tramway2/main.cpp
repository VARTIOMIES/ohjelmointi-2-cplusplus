#include "ratikka_linja.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


const std::string TULOSTUS_INPUT_FILENAME = "Give a name for input file: ";

const std::string ERR_MSG_FILE_NOT_READ = "Error: File could not be read.";
const std::string ERR_MSG_BAD_FILE_FORMAT = "Error: Invalid format in file.";
const std::string ERR_MSG_ALREADY_EXIST = "Error: Stop/line already exists.";

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}
// Edellisissä tehtävissä käytetty split funktio
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
// Muuttaa rivin rivivektoriksi, eli jakaa merkkijonon useampaan merkkijonoon.
std::vector<std::string> tiedoston_rivi_vektorina(const std::string& rivi)
{
    std::vector<std::string> rivi_vektori = split(rivi,';');
    // Käsitellään rivivektoia niin,että viimeinen merkkijono ymmärretään oikein
    if (rivi_vektori.size()==2)
    {
        rivi_vektori.push_back("0");
    }
    else if (rivi_vektori.at(2)=="")
    {
        rivi_vektori.at(2)="0";
    }
    return rivi_vektori;
}

// Funktio lisää uuden linjan, jos samalla nimellä ei ole jo aikaisempaa linjaa.
bool linjan_lisays(std::string linjan_nimi,
                   std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    if (ratikkalinjat.find(linjan_nimi)==ratikkalinjat.end())
    {
        ratikkalinjat.insert({linjan_nimi,ratikka_linja()});
        return true;
    }
    else
    {
        std::cout<<ERR_MSG_ALREADY_EXIST<<std::endl;
        return false;
    }
}

// Funktio lisää pysäkin halutulle linjalle, jos mahdollista.
bool pysakin_lisays(std::string linjan_nimi,
                    std::string pysakin_nimi,
                    double pysakin_etaisyys,
                    std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    if (not ratikkalinjat.at(linjan_nimi).lisaa_pysakki(pysakin_nimi,
                                                        pysakin_etaisyys))
    {
        std::cout<<ERR_MSG_ALREADY_EXIST<<std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool rivin_kasittely(const std::string& rivi,
                     std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::vector<std::string> rivi_vektori = tiedoston_rivi_vektorina(rivi);
    // Tarkistetaan, että tiedot ovat halutussa formaatissa.
    if (rivi_vektori.size()!=3
            or rivi_vektori.at(0)==""
            or rivi_vektori.at(1)=="")
    {
        std::cout<<ERR_MSG_BAD_FILE_FORMAT<<std::endl;
        return false;
    }

    std::string linjan_nimi = rivi_vektori.at(0);
    std::string pysakin_nimi = rivi_vektori.at(1);
    double pysakin_etaisyys = stod(rivi_vektori.at(2));
    // Jos linjaa ei ole vielä tietorakenteessa, lisätään se sinne.
    if (not linjan_lisays(linjan_nimi,ratikkalinjat))
    {
        return false;
    }
    // Lisätään pysäkki. Jos se ei onnistu, tulostetaan virheilmoitus
    if (not pysakin_lisays(linjan_nimi,pysakin_nimi,pysakin_etaisyys,
                           ratikkalinjat))
    {
        return false;
    }
    return true;
}


bool tiedoston_luku(std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::string tiedoston_nimi = "";
    std::cout << TULOSTUS_INPUT_FILENAME;
    getline(std::cin,tiedoston_nimi);
    std::ifstream syote_tiedosto(tiedoston_nimi);
    if (not syote_tiedosto)
    {
        std::cout<<ERR_MSG_FILE_NOT_READ<<std::endl;
        return false;
    }
    std::string rivi = "";
    // Käydään tiedoston jokainen rivi läpi vuorotellen.
    while( getline(syote_tiedosto,rivi))
    {
        if (not rivin_kasittely(rivi,ratikkalinjat))
        {
            syote_tiedosto.close();
            return false;
        }
    }
    syote_tiedosto.close();
    return true;
}



// Short and sweet main.
int main()
{
    // Tietorakenteena vektori, jossa ratikka_linja olioita
    std::map<std::string,ratikka_linja> ratikka_linjat = {};
    print_rasse();
    // Ensin tiedoston luku
    if (not tiedoston_luku(ratikka_linjat))
    {
        return EXIT_FAILURE;
    }
    //Tiedoston tallennus tietorakenteeseen
    
    // Komentojen kysyminen


    
    
    return EXIT_SUCCESS;
}
