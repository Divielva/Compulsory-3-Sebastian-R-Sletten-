#include "Header.h"

int main() {
    std::vector<std::vector<char>> list2;

    //pushing the neccesarry table into list2
    //we then draw the table further down in the code
    list2.push_back({ 'A', 'B', 'C', 'D' });
    list2.push_back({ 'E', 'F', 'G', 'H' });
    list2.push_back({ 'I', 'J', 'K', 'L' });
    list2.push_back({ 'M', 'N', 'O', 'P' });

    //pushing back into the empty table used for battleship later
    board.push_back({ ' ', ' ', ' ', ' ', ' ', ' ' });
    board.push_back({ ' ', ' ', ' ', ' ', ' ', ' ' });
    board.push_back({ ' ', ' ', ' ', ' ', ' ', ' ' });
    board.push_back({ ' ', ' ', ' ', ' ', ' ', ' ' });
    board.push_back({ ' ', ' ', ' ', ' ', ' ', ' ' });
    board.push_back({ ' ', ' ', ' ', ' ', ' ', ' ' });

    //the vector holds the numbers, then we transfer them to a string
    std::vector<char> pass = readPassword("pass.txt");

    for (char a : pass)
        std::cout << a;
    std::cout << std::endl;

    bool unlocked = false;
    position pos{ 0, 0 };

    //here is where we store the current position on the table
    //later we use this vector to determine if we have gotten the correct password
    std::vector<char> stored{ list2[pos.y][pos.x] };

    //this while loop is the login page, it updates the position and draws it again after every pos change
    while (!unlocked) {
        system("CLS");
        std::cout << "|---|---|---|---|" << std::endl;
        draw(list2, pos);
        std::cout << "|---|---|---|---|" << std::endl;
        std::cout << std::endl;
        std::cout << "Use the arrow buttons or WASD to type in the password " << std::endl;
        pos = move(pos, _getch());
        char pos_char = list2[pos.y][pos.x];
        if (pos_char != stored.back())
            stored.push_back(pos_char);

        if (stored == pass) {
            unlocked = true;
            stored.empty();
            break;
        }
    }

    if (unlocked) {
        bool MenuOption = false;

        while (MenuOption == false) {

            //a simple yet effective main menu
            system("CLS");
            std::cout << "                          " << std::endl;
            std::cout << "|------------------------|" << std::endl;
            std::cout << "|    MAIN MENU           |" << std::endl;
            std::cout << "| 1. Change Password     |" << std::endl;
            std::cout << "| 2. Play Battleship     |" << std::endl;
            std::cout << "| 3. Quit                |" << std::endl;
            std::cout << "|------------------------|" << std::endl;
            std::cout << "Select and option 1-3 : ";
            std::cin >> menuAnswer;
            std::cout << std::endl;

            if (menuAnswer == 1) {
                pos = { 0, 0 };
                stored.push_back('A');
                while (true) {
                    system("CLS");
                    draw(list2, pos);
                    std::cout << "|---|---|---|---|" << std::endl;
                    std::cout << std::endl;
                    std::cout << "Use the arrow buttons or WASD to type in the new password " << std::endl;
                    char in = _getch();
                    if (in == 'r' || in == 'R')
                        break;
                    pos = move(pos, in);
                    char pos_char = list2[pos.y][pos.x];
                    if (pos_char != stored.back())
                        stored.push_back(pos_char);
                }

                savePassword(stored, "pass.txt");


                MenuOption = false;
                continue;
            }
            else if (menuAnswer == 2) {
                system("CLS");
                MenuOption = true;
                char temp;
                std::cout << "  ____    _  _____ _____ _     _____ ____  _   _ ___ ____  " << std::endl;
                std::cout << " | __ )  / \\\|_   _|_   _| |   | ____/ ___|| | | |_ _|  _ \\\ " << std::endl;
                std::cout << " |  _ \\\ / _ \\\ | |   | | | |   |  _| \\\___ \\\| |_| || || |_) | " << std::endl;
                std::cout << " | |_) / ___ \\\| |   | | | |___| |___ ___) |  _  || ||  __/  " << std::endl;
                std::cout << " |____/_/   \\\_\\\_|   |_| |_____|_____|____/|_| |_|___|_|    " << std::endl;
                std::cout << "                                                           " << std::endl;
                std::cout << std::endl;
                std::cout << "Welcome to battleship, ready to play? y/n : ";
                std::cin >> temp;
                std::cout << std::endl;
                if (temp == 'y' || temp == 'Y') {
                    //setting srand and set for ship vector and guess vector
                    srand(time(0));

                    int hits = 0;
                    int numberOfShots = 13;

                    //here the program draws and places 11 ships into the map
                    //using SET, it places within the 6 columns in widht and height
                    ship_vec.empty();
                    guessed_vec.empty();
                    while (ship_vec.size() < 11)
                        ship_vec.insert(rand() % 36);


                    while (true) {
                        system("CLS");
                        std::string boardNumber;

                        PlayerBoard(board, ship_vec, guessed_vec);
                        std::cout << "You have " << numberOfShots << " left";

                        std::cout << std::endl;
                        std::cout << "[Example: A2, B6, E4]" << std::endl;
                        std::cout << "Input location in format letternumber : ";

                        std::cin >> boardNumber;
                        numberOfShots--;

                        while (boardNumber.length() != 2) {
                            std::cout << "That is not a valid input! Please try again" << std::endl;
                            std::cout << "[Example: A2, B6, E4]" << std::endl;
                            std::cout << "Input location in format letternumber : ";

                            std::cin >> boardNumber;
                        }

                        //gets my inputs and compares them with the x and y positions

                        int x_dir = boardNumber.at(0) - 'A';
                        int y_dir = boardNumber.at(1) - '1';

                        while ((x_dir < 0 || x_dir > 5) || (y_dir < 0 || y_dir > 5)) {
                            std::cout << "That is not a valid input! Please try again" << std::endl;
                            std::cout << "[Example: A2, B6, E4]" << std::endl;
                            std::cout << "Input location in format letternumber : ";

                            std::cin >> boardNumber;

                            x_dir = boardNumber.at(0) - 'A';
                            y_dir = boardNumber.at(1) - '1';
                        }

                        std::cout << x_dir << " " << y_dir << std::endl;
                        guessed_vec.insert(y_dir * 6 + x_dir);

                        if (ship_vec.find(y_dir * 6 + x_dir) != ship_vec.end() && guessed_vec.find(y_dir * 6 + x_dir) == guessed_vec.end())
                            hits++;

                        if (numberOfShots <= 0) {
                            std::cout << "You have run out of tries, do you want to play again? y/n : ";
                            std::cin >> temp;
                            if (temp == 'y' || temp == 'Y') {
                                continue;
                            }
                            else if (temp == 'n' || temp == 'N') {
                                std::cout << "See you later";
                                MenuOption = false;
                                break;
                            }
                        }
                        else if ((unsigned int)(hits) >= ship_vec.size()) {
                            std::cout << "Congratulations! you have won battleship" << std::endl;
                            std::cout << "Would you like to play again? : ";
                            std::cin >> temp;
                            if (temp == 'y' || temp == 'Y') {
                                numberOfShots = 13;
                                continue;
                            }
                            else if (temp == 'n' || temp == 'N') {
                                std::cout << "See you later";
                                MenuOption = false;
                                break;
                            }
                        }

                    }
                    if (MenuOption)
                        continue;
                }
                else if (temp == 'n' || temp == 'N') {
                    MenuOption = false;
                    continue;
                }

            }
            else if (menuAnswer == 3) {
                std::cout << "Ending program, see you later";
                return 0;
            }
            else {
                std::cout << "That is not a valid answer, try again" << std::endl;
                std::cout << "   " << std::endl;
                continue;
            }
        }
    }
}