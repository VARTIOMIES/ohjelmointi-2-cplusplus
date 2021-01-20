#include <iostream>

using namespace std;

int kertoma(int luku){
    int luvun_kertoma = 0;
    for (int i = 1; i <= luku;i++){
        luvun_kertoma *= i;
    }
    return luvun_kertoma;
}
int lottorivien_maara(int kaikki_pallot, int arvotut_pallot){
    int osoittaja = kertoma(kaikki_pallot);
    int nimittaja = kertoma(kaikki_pallot - arvotut_pallot) * kertoma(arvotut_pallot);
    return osoittaja / nimittaja;

}
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
