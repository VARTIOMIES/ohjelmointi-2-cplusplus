#include <iostream>

using namespace std;

unsigned long int kertoma(int luku){
    unsigned long int luvun_kertoma = 1;
    for (int i = 1; i <= luku;i++){
        luvun_kertoma *= i;
    }
    return luvun_kertoma;
}
int lottorivien_maara(int kaikki_pallot, int arvotut_pallot){
    unsigned long int osoittaja = kertoma(kaikki_pallot);
    unsigned long int nimittaja = kertoma(kaikki_pallot - arvotut_pallot) * kertoma(arvotut_pallot);
    unsigned long int maara = osoittaja/nimittaja;
    return maara;
}
bool positiiviset(int luku1, int luku2){
    if (luku1 >= 0 and luku2 >=0){
        return true;
    } else {
        return false;
    }
}
int main()
{
    cout << "Enter the total number of lottery balls: ";
    int pallot = 0;
    cin >> pallot;
    cout << "Enter the number of drawn balls: ";
    int arvottavat_pallot = 0;
    cin >> arvottavat_pallot;
    if (not positiiviset(pallot, arvottavat_pallot)){
        cout << "The number of balls must be a positive number." << endl;
    } else {
        cout << "The probability of guessing all " << arvottavat_pallot << " balls correctly is 1/" << lottorivien_maara(pallot, arvottavat_pallot) << endl;
    }


    return 0;
}
