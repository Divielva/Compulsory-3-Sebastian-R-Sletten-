#ifndef Compulsory_Header
#define Compulsory_Header
#pragma once

#include <fstream>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <sstream>
#include <iterator>

int menuAnswer;


//struct for the x and y position for pos
struct position {
    unsigned int x;
    unsigned int y;

    bool operator<(const position& a) const {
        return a.x + a.y < x + y;
    };

    void toString() {
        std::cout << x << " " << y << std::endl;

    }
};

//the function that draws the table, we can call this table whenever we want in the main
void draw(std::vector<std::vector<char>> list, position pos) {
    char drawable;
    for (unsigned int i = 0; i < list.size(); i++) {
        for (unsigned int j = 0; j < list[i].size(); j++) {
            drawable = pos.x == j && pos.y == i ? '*' : list[i][j];
            std::cout << "| " << drawable << " ";
        }
        std::cout << "|" << std::endl;
    }
}

void savePassword(std::vector<char> pass, std::string filename) {
    std::ofstream ow(filename, std::ios_base::out | std::ios_base::trunc);

    for (auto it = pass.begin(); it != pass.end() - 1; it++)
        ow << *it;
    ow.close();
}

std::vector<char> readPassword(std::string filename) {
    std::ifstream pw(filename);
    std::vector<char> pass;
    while (pw) {
        char a;
        pw >> a;
        pass.push_back(a);
    }
    pw.close();

    return { pass.begin(), pass.end() - 1 };
}

//this function checks the asterisks position on the loginpage
//it also checks to make sure you cant move the asterisk outside the board
position move(position current, int direction) {
    position new_pos;
    if (direction == 'a')
        new_pos = { current.x - 1, current.y };
    else if (direction == 'w')
        new_pos = { current.x, current.y - 1 };
    else if (direction == 'd')
        new_pos = { current.x + 1, current.y };
    else if (direction == 's')
        new_pos = { current.x, current.y + 1 };

    //this if statement makes sure the '*' doesnt go outside its board
    if (new_pos.x > 3 || new_pos.y > 3)
        new_pos = current;

    return new_pos;
}

int numberOfShots = 13;
int gameWon;
int boardNumber;
char boardLetter;

std::vector<std::vector<char>> board;

void ShipBoard(std::vector<std::vector<char>> board, std::set<int> draws) {
    char drawable = ' ';
    for (unsigned int m = 0; m < board.size(); m++) {
        std::cout << board.size() - m;
        for (unsigned int n = 0; n < board[m].size(); n++) {
            for (auto it = draws.begin(); it != draws.end(); it++)
                if (*it == m * 6 + n) {
                    drawable = 'S';
                    break;
                }
            std::cout << "|" << drawable;
            drawable = ' ';
        }
        std::cout << "|" << std::endl;
    }

    std::cout << " -------------\n |A|B|C|D|E|F|" << std::endl;
}

std::set<int> ship_vec;
std::set<int> guessed_vec;

int placeX;
int placeY;

//the playerboard that we print and modify in the main game
void PlayerBoard(std::vector<std::vector<char>> board, std::set<int> ships, std::set<int> guesses) {

    char drawable = ' ';
    for (unsigned int m = 0; m < board.size(); m++) {
        std::cout << board.size() - m;
        for (unsigned int n = 0; n < board[m].size(); n++) {
            int pos = m * 6 + n;
            if (guesses.find(pos) != guesses.end()) {
                drawable = 'M';
                if (ships.find(pos) != ships.end()) {
                    drawable = 'H';
                }
            }
            std::cout << "|" << drawable;
            drawable = ' ';
        }
        std::cout << "|" << std::endl;
    }

    std::cout << " -------------\n |A|B|C|D|E|F|" << std::endl;
}


#endif 
