#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //Kysytään tiedostojen nimet, joita käsitellään
    cout<<"Input file: ";
    string input_filename = "";
    getline(cin,input_filename);
    cout << "Output file: ";
    string output_filename = "";
    getline(cin,output_filename);

    // Yritetään avata tiedostot
    ifstream input_file(input_filename);
    if (not input_file)
    {
        cout<< "Error! The file " <<input_filename<< " cannot be opened."<<endl;
        return EXIT_FAILURE;
    }
    ofstream output_file(output_filename);

    // Luetaan tiedostot ja kirjoitetaan
    string line = "";
    int i = 1;
    while(getline(input_file,line))
    {
        output_file << i << " "<< line << endl;
        i++;
    }
    // Suljetaan tiedostot
    input_file.close();
    output_file.close();

    return EXIT_SUCCESS;
}
