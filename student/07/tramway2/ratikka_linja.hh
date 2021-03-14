/* Tiedosto sisältää ratikka_linja olion rajapinnan ja metodien selitteet.
 *
 * Ohjelman kirjoittaja
 * Nimi: Onni Merilä
 * Opiskelijanumero: H299725
 * Käyttäjätunnus: bvonme
 * E-Mail: onni.merila@tuni.fi
 * */
#ifndef RATIKKA_LINJA_HH
#define RATIKKA_LINJA_HH

#include <vector>
#include <string>
class ratikka_linja
{
public:
    // Rakentaja. Alustaa linjalle tyhjän pysäkki vektorin.
    ratikka_linja();
    
    // Lisää tälle linjalle pysäkin oikeaan kohtaan.
    bool lisaa_pysakki(std::string nimi,double etaisyys);
    
    // Tarkistaa, onko annettu pysäkki jo tällä linjalla.
    bool onko_linjalla(std::string pysakin_nimi);
    
    // Tarkistaa onko linjalla jo pysäkkiä annetulla etäisyydellä.
    bool onko_pysakki_samalla_etaisyydella(double pysakin_etaisyys);
    
    // Tulostaa linjan pysäkit etäisyys järjestyksessä.
    void tulosta_pysakit();
    
    // Antaa vektorina kaikkien linjan pysäkkien nimet.
    std::vector<std::string> get_pysakit();
    
    // Antaa halutun pysäkin etäisyyden linjan alkupysäkistä.
    double get_pysakin_etaisyys(std::string pysakin_nimi);
    
    // Poistaa annetun pysäkin linjalta, jos pysäkki on linjalla. Palauttaa
    // totuusarvon false, jos pysäkkiä ei ole linjalla, ja true mikäli pysäkki
    // löytyy linjalta ja sen poistaminen onnistuu.
    bool poista_pysakki(std::string pysakin_nimi);
    
private:
    std::vector<std::pair<std::string,double>> pysakit_;
    
};

#endif // RATIKKA_LINJA_HH
