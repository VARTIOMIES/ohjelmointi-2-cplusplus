/* Ohjelman kirjoittaja
 * Nimi: Onni Merilä
 * Opiskelijanumero: H299725
 * Käyttäjätunnus: bvonme
 * E-Mail: onni.merila@tuni.fi
 * */
#include "ratikka_linja.hh"
#include <iostream>

ratikka_linja::ratikka_linja()
{
    ratikka_linja::pysakit_ = {};

}

bool ratikka_linja::lisaa_pysakki(std::string nimi, double etaisyys)
{
    // Tarkistetaan, onko samanniminen pysäkki jo linjalla tai onko samalla
    //etäisyydellä jo toinen pysäkki.
    if (onko_linjalla(nimi) or onko_pysakki_samalla_etaisyydella(etaisyys))
    {
        return false;
    }

    // etsitään iteraattorin kohta, johon pysäkki sijoitetaan
    std::vector<std::pair<std::string,double>>::iterator paikka = pysakit_.begin();
    for (std::pair<std::string,double> pysakki : pysakit_)
    {
        if (pysakki.second > etaisyys)
        {
            break;
        }
        paikka++;
    }
    // Sijoitetaan pysäkki selvitettyyn kohtaan it
    std::pair<std::string,double> uusi_pysakki = {nimi,etaisyys};

    pysakit_.insert(paikka,uusi_pysakki);

    return true;
}

bool ratikka_linja::onko_linjalla(std::string pysakin_nimi)
{
    for (std::pair<std::string,double> pysakki : pysakit_)
    {
        if (pysakki.first==pysakin_nimi)
        {
            return true;
        }
    }
    return false;
}

bool ratikka_linja::onko_pysakki_samalla_etaisyydella(double pysakin_etaisyys)
{
    for (std::pair<std::string,double> pysakki : pysakit_)
    {
        if (pysakki.second==pysakin_etaisyys)
        {

            return true;
        }
    }
    return false;
}

void ratikka_linja::tulosta_pysakit()
{
    for (auto pysakki : ratikka_linja::pysakit_)
    {
        std::cout<<" - "<<pysakki.first<<" : "<< pysakki.second<<std::endl;
    }
}

std::vector<std::string> ratikka_linja::get_pysakit()
{
    std::vector<std::string> pysakkien_nimet = {};
    for (auto pysakki : pysakit_)
    {
        pysakkien_nimet.push_back(pysakki.first);
    }
    return pysakkien_nimet;
}

double ratikka_linja::get_pysakin_etaisyys(std::string pysakin_nimi)
{
    for (auto pysakki : pysakit_)
    {
        if (pysakki.first == pysakin_nimi)
        {
            return pysakki.second;
        }
    }
    return 0.0;
}

bool ratikka_linja::poista_pysakki(std::string pysakin_nimi)
{
    if (onko_linjalla(pysakin_nimi))
    {
        // etsitään iteraattorin kohta, josta pysäkkki poistetaan
        std::vector<std::pair<std::string,double>>::iterator paikka = pysakit_.begin();
        for (std::pair<std::string,double> pysakki : pysakit_)
        {
            if (pysakki.first == pysakin_nimi)
            {
                break;
            }
            paikka++;
        }
        // Poistetaan pysäkki
        pysakit_.erase(paikka);
        return true;
    }
    return false;
}
