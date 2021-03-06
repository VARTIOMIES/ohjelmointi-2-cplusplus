#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------
    unsigned int jakaja;
    if (num > 10000000)
    {
        jakaja = 10000000;
    }
    else if (num > 1000000)
    {
        jakaja = 1000000;
    }
    else if (num > 100000)
    {
        jakaja = 100000;
    }
    else if (num >10000)
    {
        jakaja = 10000;
    }
    else if(num>1000)
    {
        jakaja = 1000;
    }
    else if (num>100)
    {
        jakaja = 100;
    }
    else if (num>10)
    {
        jakaja = 10;
    }
    else
    {
        std::cout << num<< std::endl;
        return;
    }
    // Tulostetaan numero ja vähennetään siitä, jotta voidaan tulostaa seuraavat
    unsigned int eka_num = num/jakaja;
    std::cout << eka_num<< std::endl;
    //Jatketaan jakojäännöksellä
    int uusi_num  = num%jakaja;
    if (uusi_num/(jakaja/10)==0)
    {
        std::cout<<0<<std::endl;
    }
    print_vertical(num % jakaja);
    // Add your implementation here
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
