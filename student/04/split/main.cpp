#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector<std::string> split(const std::string& line, const char& separator, bool skip_empty=false){
    std::string::size_type index_of_first_char = 0;
    std::string::size_type size = line.size();
    std::vector<std::string> result;

    for (std::string::size_type index = 1; index < size; index++){
        char character = line.at(index);
        if (character == separator){
            std::string osa_teksti;
            // Peräkkäisten välimerkkien tunnistaminen.
            if (index == index_of_first_char){
                osa_teksti = "";
            }
            else {
                for (std::string::size_type i = index_of_first_char; i < index; i++){
                    osa_teksti.push_back(line.at(i));
                }
            }

            if (!(osa_teksti == "" and skip_empty)){
                result.push_back(osa_teksti);
            }
            index_of_first_char = index + 1;
        }
    }
    if (line.at(size-1) == separator and !skip_empty){
        result.push_back("");
    }
    return result;



    /*
    if (line.at(0)==separator){
        result.push_back("");
    }
    for (std::string::size_type index = 1; index < size; index++){
        char character = line.at(index);
        if (character == separator){
            std::string osa_teksti = "";
            for (std::string::size_type i = index_of_separator; i < index-1; i++){
                osa_teksti.push_back(line.at(i+1));
            }
            if (!(skip_empty and osa_teksti == "")){
                result.push_back(osa_teksti);
            }
            index_of_separator = index;
            if (index + 1 == size and !skip_empty){
                result.push_back("");
            }
        }

    }
    return result;
    */
}
int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
