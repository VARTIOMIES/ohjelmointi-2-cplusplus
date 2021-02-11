/* Muistipeli
 *
 * Kuvaus:
 * Ohjelma toteuttaa muistipelin. Pelissä on vaihteleva määrä kortteja ja pelaajia.
 * Pelin alussa käyttäjältä kysytään myös siemenluku, koska kortit arvotaan sarunnaisesti pelilaudalle.....
 *
 * Ohjelman kirjoittaja
 * Nimi: Onni Merilä
 * Opiskelijanumero: H299725
 * Käyttäjätunnus: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
//
// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
//
// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    //
    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    //
    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    //
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
//
// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    //
    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    //
    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    //
    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        //
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
//
// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
//
// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan.
//
// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Kysyy ja lukee pelaajien määrän ja nimet ja luo pelaajat
std::vector<Player> ask_player_info_and_create_players()
{
    unsigned int player_amount = 0;
    // Kysytään pelaajamäärää niin pitkään, että annetaan sallittu määrä
    while(not (player_amount > 0))
    {
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        string player_amount_str = "";
        std::getline(std::cin, player_amount_str);
        player_amount = stoi_with_check(player_amount_str);
    }
    // Kysytään pelaajien nimet ja tallennetaan ne vektoriin.
    std::cout << "List " << player_amount << " players: ";
    std::vector<Player> players_in_vector;

    for(unsigned int i = 0; i < player_amount;i++)
    {
        string player_name = "";
        std::cin >> player_name;
        players_in_vector.push_back(Player(player_name));
    }
    return players_in_vector;
}

// Kysyy käyttäjältä koordinaatteja
std::vector<string> ask_for_input(Player& player_in_turn)
{
    std::cout << player_in_turn.get_name() << ": " << INPUT_CARDS << ": ";
    std::vector<string> input_vector;
    for (int i = 0; i < 4; i++)
    {

        std::string input_str;
        std::cin >> input_str;
        input_vector.push_back(input_str);
        if (input_str == "q")
        {
            return input_vector;
        }
    }
    return input_vector;
}

// Tarkistaa annetun vektorin alkiot, että ne voidaan ilmaista numeerisesti
bool is_numeric_coordinates(std::vector<string> coordinates)
{
    for (int i = 0; i < 4;i++)
    {
        if(not stoi_with_check(coordinates.at(i)))
        {
            return false;
        }
    }
    return true;
}

// Palauttaa numeerisen vektorin annetusta string vektorista
std::vector<int> string_vector_to_integer_vector(std::vector<string>& string_vector)
{
    std::vector<int> integer_vector;
    for (string coord : string_vector)
    {
        integer_vector.push_back(stoi_with_check(coord)-1);
    }
    return integer_vector;
}

// Funktio tarkistaa, onko annetut koordinaatit sopivat
bool are_coordinates_good(const std::vector<int>& coordinates, Game_board_type& g_board)
{
    // Koordinaatteja tulee olla 4 kappaletta.
    if (coordinates.size() != 4)
    {
        return false;
    }
    int board_rows = g_board.size();
    int board_columns = g_board.at(0).size()-1;
    for (int i = 0; i < 4; i += 2){

        // Koordinaattien tulee sijaita pelilaudalla.
        if ( coordinates.at(i+1) > board_rows or coordinates.at(i) > board_columns)
        {
            return false;
        }

        // Koordinaateissa pitää olla kortti
        if(g_board.at(coordinates.at(i+1)).at(coordinates.at(i)).get_visibility() == EMPTY)
        {
            return false;
        }
    }
    // Samaa korttia ei voida kääntää samalla vuorolla.
    if (coordinates.at(0)==coordinates.at(2) and coordinates.at(1) == coordinates.at(3))
    {
        return false;
    }
    return true;
}

// Funktio tarkistaa, onko pelikenttä tyhjä vai ei.
bool is_game_board_empty(Game_board_type g_board)
{
    for (unsigned int i = 0 ; i < g_board.size();i++)
    {
        for (unsigned int j = 0 ; j < g_board.at(i).size() ; j++)
        {

            if (g_board.at(i).at(j).get_visibility()!=EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}


// Lisää funktioita
// More functions


int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // Kysytään pelaajien tiedot, tallennetaan pelaajat vektoriin.
    std::vector<Player> players = ask_player_info_and_create_players();

    // Peli alkaa.
    int turn = 0;
    bool game_is_on = true;
    int player_amount = players.size();
    while (game_is_on)
    {
        print(game_board);
        // Määritellään vuorossa oleva pelaaja, 0, 1 ,...->
        int player_index = turn % player_amount;
        Player& player_in_turn = players.at(player_index);

        // Koordinaattien kysyminen
        bool quit = false;
        std::vector<int> coordinates;    
        while(true){
            vector<string> input_vector = ask_for_input(player_in_turn);
            if (input_vector.at(0)=="q")
            {
                quit = true;
                break;
            }
            // Tarkistetaan koordinaattien numeerisuus
            if (is_numeric_coordinates(input_vector))
            {
                coordinates = string_vector_to_integer_vector(input_vector);
            }
            else
            {
                std::cout << INVALID_CARD << std::endl;
                continue;
            }
            // Tarkistetaan muut ehdot
            if (are_coordinates_good(coordinates,game_board))
            {
                break;
            }
            else
            {
                std::cout << INVALID_CARD << std::endl;
            }
        }
        // Jos pelaaja on antanut käskyn "q", niin poistutaan pelistä
        if (quit)
        {
            std::cout << GIVING_UP << std::endl;
            break;
        }

        //Käännetään kortit
        Card& card1 = game_board.at(coordinates.at(1)).at(coordinates.at(0));
        Card& card2 = game_board.at(coordinates.at(3)).at(coordinates.at(2));
        card1.turn();
        card2.turn();
        print(game_board);

        // Tarkistetaan, ovatko käännetyt kortit parit
        if (card1.get_letter() == card2.get_letter())
        {
            std::cout << FOUND << std::endl;
            player_in_turn.add_card(card1);
            card2.remove_from_game_board();

        }
        else
        {
            std::cout << NOT_FOUND << std::endl;
            card1.turn();
            card2.turn();
        }

        // Tulostetaan pistetilanne
        for (unsigned int i = 0 ; i < players.size() ; i++)
        {
            players.at(i).print();
        }

        // Lopetetaan peli, jos pöytä on tyhjä
        if (is_game_board_empty(game_board))
        {
            game_is_on = false;
            std::cout << GAME_OVER << std::endl;

            // Voittajan selvittäminen
            unsigned int most_pairs = 0;
            std::string winner_name = "";
            bool tie = false;
            int winner_amount = 1;

            for (Player& player : players)
            {
                if (player.number_of_pairs() > most_pairs and !tie)
                {
                    most_pairs = player.number_of_pairs();
                    winner_name = player.get_name();
                }
                else if (player.number_of_pairs() > most_pairs and tie)
                {
                    tie = false;
                    winner_amount = 1;
                    most_pairs = player.number_of_pairs();
                    winner_name = player.get_name();
                }
                else if (player.number_of_pairs() == most_pairs)
                {

                    tie = true;
                    winner_amount++;
                }
            }

            // Voittajan/voittajien tulostus
            if (tie)
            {
                std::cout << "Tie of " << winner_amount << " players with "
                          << most_pairs << " pairs." << std::endl;
            }
            else
            {
                std::cout << winner_name << " has won with " << most_pairs
                          << " pairs." << std::endl;
            }
        }

        // Mennään seuraavaan vuoroon
        turn++;
    }

    // Lisää koodia
    // More code

    return EXIT_SUCCESS;
}

