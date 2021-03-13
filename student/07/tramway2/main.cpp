/* Ratikkalinjat
 *
 * Kuvaus:
 *  Ohjelma toteuttaa ratikkalinojen ja niiden pysäkkien tietojen hallinnointiin,
 * lisäämiseen ja tarkasteluun tarkoitetun järjestelmän. Ohjelman alussa
 * kysytään tiedoston nimeä, johon on tallennettu linjojen pysäkkejä ja niiden
 * etäisyyksiä linjan lähtöpysäkistä.
 *  Käyttäjä voi antaa ohjelmalle komentoja, joiden mukaan ohjelma tulostaa
 * tietoja linjoista ja niden pysäkeistä. Käyttäjä voi myös lisätä uusia linjoja
 * ja pysäkeitä tai poistaa olemassa olevia pysäkeitä. Käyttäjä voi myös poistua
 * ohjelmasta antamalla poistumiskomennon.
 * Komennot:
 * - Quit : Poistutaan ohjelmasta.
 * - Lines : Tulostaa kaikki järjestelmään kirjattujen ratikkalinjojen
 * nimet aakkosjärjestyksessä.
 * - Line <linjan_nimi> : Tulostaa <linjan_nimi> -linjan tiedot, eli pysäkit
 * ja niiden etäisyydet lähtöpysäkistä.
 * - Stops : Tulostaa kaikkien järjestelmässä olevien linjojen pysäkkien nimet
 * aakkosjärjestyksessä.
 * - Stop <pysäkin_nimi> : Tulostaa niiden linjojen nimet, joilta <pysäkin_nimi>
 * pysäkki löytyy.
 * - Distance <linjan_nimi> <pysäkin_1_nimi> <pysakin_2_nimi>: Tulostaa kahden
 * samalla linjalla <linjan_nimi> olevan pysäkin välisen etäisyyden toisistaan.
 * - Addline <linjan_nimi> : Lisää järjestelmään uuden linjan, jolla ei ole
 * pysäkeitä.
 * - Addstop <linjan_nimi> <pysäkin_nimi> <pysäkin_etäisyys> : Lisää linjalle
 * uuden pysäkin
 * - Remove <pysäkin_nimi> :
 *
 * Ohjelman kirjoittaja
 * Nimi: Onni Merilä
 * Opiskelijanumero: H299725
 * Käyttäjätunnus: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * - Tietorakenteena käytetään STL:n map säiliötä, jossa avainsana on string ja
 *   ja sisältönä on ratikka_linja olio, jonka toteutus on tiedostossa
 *   'ratikka_linja.cpp'.
 *
 * */
#include "ratikka_linja.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cmath>


const std::string TULOSTUS_TIEDOSTON_NIMI = "Give a name for input file: ";
const std::string TULOSTUS_LINJAT = "All tramlines in alphabetical order:";
const std::string TULOSTUS_LINJAN_PYSAKIT = " goes through these stops in the"
                                            " order they are listed:";
const std::string TULOSTUS_KAIKKI_PYSAKIT = "All stops in alphabetical order:";
const std::string TULOSTUS_PYSAKIN_LINJAT = " can be found on the following"
                                            " lines:";
const std::string TULOSTUS_LINJAN_LISAYS = "Line was added.";
const std::string TULOSTUS_PYSAKIN_LISAYS = "Stop was added.";
const std::string TULOSTUS_PYSAKKI_POISTETTU="Stop was removed from all lines.";

const std::string QUIT_COMMAND = "QUIT";
const std::string LINES_COMMAND = "LINES";
const std::string LINE_COMMAND = "LINE";
const std::string STOPS_COMMAND = "STOPS";
const std::string STOP_COMMAND = "STOP";
const std::string DISTANCE_COMMAND = "DISTANCE";
const std::string ADDLINE_COMMAND = "ADDLINE";
const std::string ADDSTOP_COMMAND = "ADDSTOP";
const std::string REMOVE_COMMAND = "REMOVE";

const std::string ERR_MSG_FILE_NOT_READ = "Error: File could not be read.";
const std::string ERR_MSG_BAD_FILE_FORMAT = "Error: Invalid format in file.";
const std::string ERR_MSG_ALREADY_EXIST = "Error: Stop/line already exists.";
const std::string ERR_MSG_LINE_NOT_FOUND = "Error: Line could not be found.";
const std::string ERR_MSG_STOP_NOT_FOUND = "Error: Stop could not be found.";
const std::string ERR_MSG_BAD_INPUT = "Error: Invalid input.";

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

// Funktio lisää pysäkin halutulle linjalle, jos mahdollista. Tulostaa virheil-
// moituksen. jos pysäkin lisäys ei onnistu.
bool lisaa_pysakki(std::string linjan_nimi,
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

// Funktio käsittelee annetun merkkijonon, joka on tiedoston rivi, ja lisää sen
// sisältämän tiedon tietorakenteeseen ratikkalinjat. Jos rivin tieto on vir-
// heellinen, tulostetaan virheilmoitus ja poistutaan funktiosta totuusarvolla
// false. Rivin käsittelyn onnistuttua poistutaan totuusarvolla true.
bool kasittele_rivi(const std::string& rivi,
                     std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::vector<std::string> rivi_vektori = tiedoston_rivi_vektorina(rivi);
    // Tarkistetaan, että tiedot ovat halutussa formaatissa. Tulostetaan virhe-
    // ilmoitus ja poistutaan funktiosta, jos tietoa ei ymmärretä.
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
    // Lisätään pysäkki. Jos se ei onnistu, poistutaan funktiosta
    if (not lisaa_pysakki(linjan_nimi,pysakin_nimi,pysakin_etaisyys,
                           ratikkalinjat))
    {
        return false;
    }
    // Rivin käsittely onnistunut. Poistutaan funktiosta.
    return true;
}

// Funktio kysyy tiedoston nimeä, jonka se avaa, lukee tiedot ja tallettaa ne
// tietorakenteeseen. Jos tiedoston lukeminen ei onnistu, tulostetaan virhe-
// ilmoitus ja poistutaan funktiosta totuusarvolla false. Jos koko tiedosto
// luetaan onnistuneesti, poistutaan funktiosta totuusarvolla true.
bool lue_tiedosto(std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::string tiedoston_nimi = "";
    std::cout << TULOSTUS_TIEDOSTON_NIMI;
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
        // Jos rivin_kasittely ei onnistu, suljetaan tiedosto ja lopetetaan
        // tiedoston lukeminen.
        if (not kasittele_rivi(rivi,ratikkalinjat))
        {
            syote_tiedosto.close();
            return false;
        }
    }
    syote_tiedosto.close();
    return true;
}

// Funktio tulostaa kaikki tietorakenteessa olevien linjojen nimet.
void tulosta_linja(const std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::vector<std::string> tulostus_vektori = {};

    // Täytetään tulostusvektori linjojen nimillä.
    for (auto linja : ratikkalinjat)
    {
        tulostus_vektori.push_back(linja.first);
    }

    // Tulostetaan vektori. Map -tietorakenteen ansiosta alkiot ovat valmiiksi
    // aakkosjärjestyksessä.
    std::cout << TULOSTUS_LINJAT << std::endl;
    for (std::string linja : tulostus_vektori)
    {
        std::cout<< linja << std::endl;
    }
}

// Funktio tulostaa halutun linjan pysäkkien tiedot. Jos annetulla nimellä
// ei tietorakenteesta löydy linjaa, tulostetaan virheilmoitus ja poistutaan.
void tulosta_linjan_pysakit(std::string linjan_nimi,
                            std::map<std::string,ratikka_linja>& ratikka_linjat)
{
    if (ratikka_linjat.find(linjan_nimi)==ratikka_linjat.end())
    {
        std::cout << ERR_MSG_LINE_NOT_FOUND<<std::endl;
        return;
    }
    std::cout<<"Line "<<linjan_nimi<<TULOSTUS_LINJAN_PYSAKIT<<std::endl;
    ratikka_linjat.at(linjan_nimi).tulosta_pysakit();

}

// Funktio tulostaa kaikki tietorakenteessa olevat pysäkit aakkosjärjestyksessä.
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

// Tulostaa kaikkien niiden linjojen nimet aakkosjärjetyksessä, joilta annettu
// pysäkki löytyy. Jos pysäkkiä ei löydy linjoilta, tulostuu virheilmoitus
// ja poistutaan funktiosta.
void tulosta_pysakin_linjat(std::string pysakin_nimi,
                            std::map<std::string,ratikka_linja>& ratikkalinjat)
{
    std::set<std::string> tulostus_set = {};
    // Tutkitaan, onko pysäkin nimeä linjalla.
    for (auto linja : ratikkalinjat)
    {
        if (linja.second.onko_linjalla(pysakin_nimi))
        {
            tulostus_set.insert(linja.first);
        }
    }
    // Jos pysäkkiä ei löydy linjoilta, tulostus_set suuruus on 0
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

// Laskee ja tulostaa kahden pysäkin välisen etäisyyden tietyllä linjalla.
// Jos annettua linjaa tai pysäkkejä ei löydy, tulostuu virheilmoitus ja
// poistutaan funktiosta.
void tulosta_pysakkien_etaisyys(std::string linjan_nimi, std::string pysakki1,
                                std::string pysakki2,std::map<std::string,
                                ratikka_linja>& ratikkalinjat)
{
    // Tutkitaan, löytyyko annetuua linjaa tietorakenteesta
    if (ratikkalinjat.find(linjan_nimi)==ratikkalinjat.end())
    {
        std::cout << ERR_MSG_LINE_NOT_FOUND << std::endl;
        return;
    }
    ratikka_linja linja = ratikkalinjat.at(linjan_nimi);

    // Tutkitaan löytyykö annetulta linjalta molemmat annetut pysäkit.
    if (not (linja.onko_linjalla(pysakki1) or linja.onko_linjalla(pysakki2)))
    {
        std::cout << ERR_MSG_STOP_NOT_FOUND<< std::endl;
        return;
    }
    // Lasketaan pysäkkien etäisyys
    double etaisyys1 = linja.get_pysakin_etaisyys(pysakki1);
    double etaisyys2 = linja.get_pysakin_etaisyys(pysakki2);
    double pysakkien_valinen_etaisyys = std::fabs(etaisyys1-etaisyys2);
    // Tulostus
    std::cout << "Distance between " <<pysakki1<<" and "<<pysakki2<< " is "<<
                 pysakkien_valinen_etaisyys << std::endl;

}

// Funktio poistaa pysäkin kaikilta linjoilta ja tulostaa onnistumisen viestin.
// Jos pysäkkiä ei löydy, tulostetaan virheilmoitus.
void poista_pysakki(std::string pysakin_nimi,
                    std::map<std::string,ratikka_linja>& ratikkalinjat)
{
   bool pysakki_poistettu = false;
   for (auto& linja : ratikkalinjat)
   {
       if (linja.second.poista_pysakki(pysakin_nimi))
       {
           pysakki_poistettu = true;
       }
   }
   if (pysakki_poistettu)
   {
       std::cout << TULOSTUS_PYSAKKI_POISTETTU << std::endl;
   }
   else
   {
       std::cout << ERR_MSG_STOP_NOT_FOUND << std::endl;
   }
}

// Funktio lukee syötteen ja käsittelee annetun merkkijonon komento vektoriksi
// Tämä funktio sisältää monimutkaisen algoritmin, joka käsittelee tiedon
// oikeaan muotoon
std::vector<std::string> kysy_syote()
{
    std::string syote = "";
    std::cout<<"tramway> ";
    getline(std::cin,syote);

    // Jaetaan merkkijono ensin "-merkkien suhteen, jolloin saadaan eriteltyä
    // komennoista välilyöntejä sisältävät komentojen osat.
    std::vector<std::string> erittely = split(syote,'"',false);

    std::vector<std::string> alku_osa = split(erittely.at(0),' ',true);
    std::vector<std::string> loppu_osa= {};
    if (erittely.size()>1)
    {
        loppu_osa = split(erittely.at(erittely.size()-1),' ');
    }

    std::vector<std::string> komennot = {};
    for (auto alkio:alku_osa)
    {
        komennot.push_back(alkio);
    }
    if (erittely.size()==3 or erittely.size()==4)
    {
       komennot.push_back(erittely.at(1));
    }
    else if (erittely.size()==5)
    {
        komennot.push_back(erittely.at(1));
        komennot.push_back(erittely.at(3));
    }
    for (auto loppu_alkio:loppu_osa)
    {
        if (loppu_alkio == "")
        {
            continue;
        }
        komennot.push_back(loppu_alkio);
    }

    return komennot;
}


int main()
{
    // Tietorakenteena map, jossa avainsanana linjan nimi ja tietona on
    //ratikka_linja olioita
    std::map<std::string,ratikka_linja> ratikka_linjat = {};
    print_rasse();
    // Ensin tiedoston luku ja tallennus tietorakenteeseen
    if (not lue_tiedosto(ratikka_linjat))
    {
        return EXIT_FAILURE;
    }
    // Komentojen kysyminen
    while(true)
    {
        std::vector<std::string> komennot = kysy_syote();
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
            tulosta_linja(ratikka_linjat);
        }
        else if (komento==LINE_COMMAND and komennot.size()>= 2)
        {
            tulosta_linjan_pysakit(komennot.at(1),ratikka_linjat);
        }
        else if (komento==STOPS_COMMAND)
        {
            tulosta_kaikki_pysakit(ratikka_linjat);
        }
        else if (komento==STOP_COMMAND and komennot.size()>=2)
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
        else if (komento==ADDLINE_COMMAND and komennot.size()>=2)
        {
            if (linjan_lisays(komennot.at(1),ratikka_linjat))
            {
                std::cout << TULOSTUS_LINJAN_LISAYS << std::endl;
            }
            else
            {
                std::cout << ERR_MSG_ALREADY_EXIST << std::endl;
            }
        }
        else if (komento==ADDSTOP_COMMAND and komennot.size()>=4)
        {
            if (lisaa_pysakki(komennot.at(1),komennot.at(2),
                               stod(komennot.at(3)),ratikka_linjat))
            {
                std::cout << TULOSTUS_PYSAKIN_LISAYS << std::endl;
            }
        }
        else if (komento==REMOVE_COMMAND and komennot.size()>=2)
        {
            poista_pysakki(komennot.at(1),ratikka_linjat);
        }
        else
        {
            std::cout << ERR_MSG_BAD_INPUT << std::endl;
        }

    }
    return EXIT_SUCCESS;
}
