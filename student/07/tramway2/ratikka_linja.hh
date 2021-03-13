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

    bool onko_linjalla(std::string pysakin_nimi);
    bool onko_pysakki_samalla_etaisyydella(double pysakin_etaisyys);
    void tulosta_pysakit();
    std::vector<std::string> get_pysakit();
    double get_pysakin_etaisyys(std::string pysakin_nimi);
    bool poista_pysakki(std::string pysakin_nimi);
private:
    std::vector<std::pair<std::string,double>> pysakit_;
    
};

#endif // RATIKKA_LINJA_HH
