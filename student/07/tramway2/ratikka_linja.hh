#ifndef RATIKKA_LINJA_HH
#define RATIKKA_LINJA_HH

#include <vector>
#include <string>
class ratikka_linja
{
public:
    // Constructor
    ratikka_linja();
    // Lisää linjalle pysäkin oikeaan kohtaan.
    bool lisaa_pysakki(std::string nimi,double etaisyys);

    bool on_linjalla(std::string pysakin_nimi);
    bool on_pysakki_samalla_etaisyydella(double pysakin_etaisyys);
    void pysakkien_tulostus();
private:
    std::vector<std::pair<std::string,double>> pysakit;
    
};

#endif // RATIKKA_LINJA_HH
