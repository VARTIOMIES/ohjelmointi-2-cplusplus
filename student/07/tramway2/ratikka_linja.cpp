#include "ratikka_linja.hh"
#include <iostream>

ratikka_linja::ratikka_linja()
{
    ratikka_linja::pysakit = {};

}

bool ratikka_linja::lisaa_pysakki(std::string nimi, double etaisyys)
{
    // Tarkistetaan, onko samanniminen pysäkki jo linjalla tai onko samalla
    //etäisyydellä jo toinen pysäkki.
    if (on_linjalla(nimi) or on_pysakki_samalla_etaisyydella(etaisyys))
    {
        return false;
    }

    // etsitään iteraattorin kohta, johon pysäkki sijoitetaan
    std::vector<std::pair<std::string,double>>::iterator paikka = pysakit.begin();
    for (std::pair<std::string,double> pysakki : pysakit)
    {
        if (pysakki.second > etaisyys)
        {
            break;
        }
        paikka++;
    }
    // Sijoitetaan pysäkki selvitettyyn kohtaan it
    std::pair<std::string,double> uusi_pysakki = {nimi,etaisyys};

    pysakit.insert(paikka,uusi_pysakki);

    return true;
}

bool ratikka_linja::on_linjalla(std::string pysakin_nimi)
{
    for (std::pair<std::string,double> pysakki : pysakit)
    {
        if (pysakki.first==pysakin_nimi)
        {
            return true;
        }
    }
    return false;
}

bool ratikka_linja::on_pysakki_samalla_etaisyydella(double pysakin_etaisyys)
{
    for (std::pair<std::string,double> pysakki : pysakit)
    {
        if (pysakki.second==pysakin_etaisyys)
        {

            return true;
        }
    }
    return false;
}

void ratikka_linja::pysakkien_tulostus()
{
    for (auto pysakki : ratikka_linja::pysakit)
    {
        std::cout<<" - "<<pysakki.first<<" : "<< pysakki.second<<std::endl;
    }
}

std::vector<std::string> ratikka_linja::get_pysakit()
{
    std::vector<std::string> pysakkien_nimet = {};
    for (auto pysakki : pysakit)
    {
        pysakkien_nimet.push_back(pysakki.first);
    }
    return pysakkien_nimet;
}
