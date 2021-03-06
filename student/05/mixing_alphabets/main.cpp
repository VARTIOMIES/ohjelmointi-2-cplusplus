#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        std::string::iterator range_begin = word.begin();
        std::string::iterator range_end = word.end();
        if (word.length()>=2)
        {
            range_begin++;
            range_end--;
        }
        shuffle(range_begin,range_end,generator);

	
        std::cout << word << std::endl;
    }
}
