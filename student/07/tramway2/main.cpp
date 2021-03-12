#include "ratikka_linja.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>


const std::string TULOSTUS_INPUT_FILENAME = "Give a name for input file: ";
const std::string TULOSTUS_LINJAT = "All tramlines in alphabetical order:";
const std::string TULOSTUS_LINJAN_PYSAKIT = " goes through these stops in the"
                                            " order they are listed:";
const std::string TULOSTUS_KAIKKI_PYSAKIT = "All stops in alphabetical order:";
const std::string TULOSTUS_PYSAKIN_LINJAT = " can be found on the following"
                                            " lines:";

const std::string QUIT_COMMAND = "QUIT";
const std::string LINES_COMMAND = "LINES";
const std::string LINE_COMMAND = "LINE";
const std::string STOPS_COMMAND = "STOPS";
const std::string STOP_COMMAND = "STOP";
const std::string DISTANCE_COMMAND = "DISTANCE";

const std::string ERR_MSG_FILE_NOT_READ = "Error: File could not be read.";
const std::string ERR_MSG_BAD_FILE_FORMAT = "Error: Invalid format in file.";
const std::string ERR_MSG_ALREADY_EXIST = "Error: Stop/line already exists.";
const std::string ERR_MSG_LINE_NOT_FOUND = "Error: Line could not be found.";
const std::string ERR_MSG_STOP_NOT_FOUND = "Error: Stop could not be found.";

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
    return true;
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
    linjan_lisays(linjan_nimi,ratikkalinjat);
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

void linja_tulostus(const std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::vector<std::string> tulostus_vektori = {};

    // Täytetään tulostusvektori linjan tiedoilla
    for (auto linja : ratikkalinjat)
    {
        tulostus_vektori.push_back(linja.first);
    }

    // Tulostetaan vektori. Map -tietorakenteen ansiosta alkiot ovat valmiiksi
    // aakkosjärjestyksessä.
    for (std::string linja : tulostus_vektori)
    {
        std::cout<< linja << std::endl;
    }
}

void tulosta_linjan_pysakit(std::string linjan_nimi,
                            std::map<std::string,ratikka_linja>& ratikka_linjat)
{
    if (ratikka_linjat.find(linjan_nimi)==ratikka_linjat.end())
    {
        std::cout << ERR_MSG_LINE_NOT_FOUND<<std::endl;
        return;
    }
    std::cout<<"Line "<<linjan_nimi<<TULOSTUS_LINJAN_PYSAKIT<<std::endl;
    ratikka_linjat.at(linjan_nimi).pysakkien_tulostus();

}

void tulosta_kaikki_pysakit(std::map<std::string,ratikka_linja>& ratikka_linjat)
{
    std::set<std::string> tulostus_set = {};
    for (auto ratikka_linja : ratikka_linjat)
    {
        std::vector<std::string> linjan_pysakit =
                ratikka_linja.second.get_pysakit();
        for (auto pysakin_nimi : linjan_pysakit)
        {
            tulostus_set.insert(pysakin_nimi);
        }
    }
    // Tulostetaan linjojen pysäkit
    std::cout << TULOSTUS_KAIKKI_PYSAKIT<<std::endl;
    for (auto pysakin_nimi : tulostus_set)
    {
        std::cout<<pysakin_nimi<<std::endl;
    }

}
void tulosta_pysakin_linjat(std::string pysakin_nimi,
                            std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::set<std::string> tulostus_set = {};
    // Tutkitaan, onko pysäkin nimeä linjalla.
    for (auto linja : ratikkalinjat)
    {
        if (linja.second.on_linjalla(pysakin_nimi))
        {
            tulostus_set.insert(linja.first);
        }
    }
    // Jos pysäkkiä ei löydy linjoilta, tulostus_set suuruun on 0
    if (tulostus_set.size()==0)
    {
        std::cout<<ERR_MSG_STOP_NOT_FOUND<<std::endl;
        return;
    }

    // Tulostetaan linjat, joilta pysäkki löytyy.
    std::cout << "Stop "<<pysakin_nimi<<TULOSTUS_PYSAKIN_LINJAT<<std::endl;
    for (auto linjan_nimi : tulostus_set)
    {
        std::cout<<" - "<<linjan_nimi<<std::endl;
    }
}
void tulosta_pysakkien_etaisyys(std::string linjan_nimi, std::string pysakki1,
                                std::string pysakki2,std::map<std::string,
                                ratikka_linja>& ratikkalinjat)
{
    // Lasketaan pysäkkien etäisyys
    if (ratikkalinjat.find(linjan_nimi)==ratikkalinjat.end())
    {
        std::cout << ERR_MSG_LINE_NOT_FOUND << std::endl;
        return;
    }
    ratikka_linja linja = ratikkalinjat.at(linjan_nimi);
    if (not (linja.on_linjalla(pysakki1) or linja.on_linjalla(pysakki2)))
    {
        std::cout << ERR_MSG_STOP_NOT_FOUND<< std::endl;
        return;
    }
    double etaisyys1 = linja.get_pysakin_etaisyys(pysakki1);
    double etaisyys2 = linja.get_pysakin_etaisyys(pysakki2);
    double pysakkien_valinen_etaisyys = std::fabs(etaisyys1-etaisyys2);
    std::cout << "Distance between " <<pysakki1<<" and "<<pysakki2<< " is "<<
                 pysakkien_valinen_etaisyys << std::endl;

}

// Short and sweet main.
int main()
{
    // Tietorakenteena vektori, jossa ratikka_linja olioita
    std::map<std::string,ratikka_linja> ratikka_linjat = {};
    print_rasse();
    // Ensin tiedoston luku ja tallennus tietorakenteeseen
    if (not tiedoston_luku(ratikka_linjat))
    {
        return EXIT_FAILURE;
    }
    // Komentojen kysyminen
    while(true)
    {
        std::string syote = "";
        std::cout<<"tramway> ";
        getline(std::cin,syote);
        std::vector<std::string> komennot = split(syote,' ');
        std::string komento = komennot.at(0);
        for (char& character : komento)
        {
            character = toupper(character);
        }
        if (komento==QUIT_COMMAND)
        {
            return EXIT_SUCCESS;
        }
        else if (komento==LINES_COMMAND)
        {
            linja_tulostus(ratikka_linjat);
        }
        else if (komento==LINE_COMMAND and komennot.size()>= 2)
        {
            tulosta_linjan_pysakit(komennot.at(1),ratikka_linjat);
        }
        else if (komento==STOPS_COMMAND)
        {
            tulosta_kaikki_pysakit(ratikka_linjat);
        }
        else if (komento==STOP_COMMAND)
        {
            tulosta_pysakin_linjat(komennot.at(1),ratikka_linjat);
        }
        else if (komento==DISTANCE_COMMAND and komennot.size()>=3)
        {
            std::string linjan_nimi = komennot.at(1);
            std::string pysakki1 = komennot.at(2);
            std::string pysakki2 = komennot.at(3);
            tulosta_pysakkien_etaisyys(linjan_nimi,pysakki1,pysakki2,
                                       ratikka_linjat);
        }
    }

    
    
    return EXIT_SUCCESS;
}
