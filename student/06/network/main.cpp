#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_web(const std::string& id,
               const std::map<std::string,std::vector<std::string>>& data,
               int depth)
{
    for (std::string connection : data.at(id))
    {
        std::string dots;
        for (int i=0;i<depth;i++)
        {
            dots += "..";
        }
        std::cout<<dots;
        std::cout << connection << std::endl;

        if (data.find(connection)!=data.end())
        {

            print_web(connection,data,depth+1);
        }
    }
}

int count_web(const std::string& id,
              const std::map<std::string,std::vector<std::string>>& data)
{
    int amount=0;
    if (data.find(id)==data.end())
    {
        return 0;
    }
    for (std::string connection : data.at(id))
    {
        if (data.find(connection)!=data.end())
        {
            amount += count_web(connection,data);
        }
        amount++;
        //amount+=data.at(id).size();

    }
    return amount;
}

int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string,std::vector<std::string>> data;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // Lisätään tieto rakenteeseen
            if (data.find(id1) == data.end())
            {
                data.insert({id1,{id2}});
            }
            else
            {
                data.at(id1).push_back(id2);
            }
            std::cout << data.at(id1).at(0) << std::endl;


            // TODO: Implement the command here!

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            std::cout<<id<<std::endl;
            int depth = 1;
            print_web(id,data,depth);
            // TODO: Implement the command here!

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            std::cout<<count_web(id,data)<<std::endl;
            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
