
/*#ifndef AI_H
#define AI_H
#include "Ai.h"
#endif // AI_H*/

#include "Ai.h"

#ifndef BOARD_H
#define BOARD_H
#include "Board.cpp"
#endif

#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

class Ai {

private:
	std::string difficulty;
	int* target;
	// targetStack[100][2];
	linkedList* targetStack = new linkedList();
	int stackPtr;

	//Each "Ai object" possesses the 5 standard ships
	/*Ship carrier;
	Ship battleship;
	Ship cruiser;
	Ship submarine;
	Ship destroyer;*/

	//Used in the Ai's Insane mode to calculate square probabilities
	//void enumerateTallies(int board[10][10], int shipSize);
	double probabilityBoard[10][10];

public:
	Ai(std::string difficulty)
    {
        //targetStack[0][0] = -1;
        this->difficulty = difficulty;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                probabilityBoard[i][j] = 0;
            }
        }
    };

    /*void Ai::printRadar() {

        //Calculates the average probability on the probability board
        double avProbability = 0;
        int count = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (probabilityBoard[i][j]) {
                    avProbability += probabilityBoard[i][j];
                    count++;
                }
            }
        }

        avProbability = avProbability / double(count);
        std::cout << avProbability;

        //For formatting purposes
        for (int i = 0; i < 5; i++)
            std::cout << std::endl;

        //Outputs numbers for X axis
        std::cout << "           ";
        for (int i = 0; i < 10; i++)
            std::cout << std::setw(5) << i;

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        //Outputs letters for Y axis
        for (int i = 0; i < 10; i++) {
            std::cout << "     " << char('A' + i) << "     ";

            //Outputs appropriate visual character for that square's probability compared with the average for the board
            for (int j = 0; j < 10; j++) {
                if (probabilityBoard[i][j] < avProbability / 2)
                    std::cout << std::setw(4) << char(32) << char(248);
                else if (probabilityBoard[i][j] > avProbability / 2 && probabilityBoard[i][j] < avProbability)
                    std::cout << std::setw(4) << char(176) << char(176);
                else if (probabilityBoard[i][j] > avProbability && probabilityBoard[i][j] < avProbability * 3 / 2)
                    std::cout << std::setw(4) << char(177) << char(177);
                else if (probabilityBoard[i][j] > avProbability * 3 / 2)
                    std::cout << std::setw(4) << char(178) << char(178);
                else
                    std::cout << std::setw(4) << char(219) << char(219);
            }

            std::cout << std::endl;

            std::cout << std::endl;
        }
    }*/

    //Arranges ships at the start of the game only
    void arrangeShip(Board* my)
    {
        int x;
        int y;
        int dir;
        while(1)
        {
            srand(time(NULL)*time(NULL)*time(NULL));
            x = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            y = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            dir = rand() % 4;
            if(my->placeShip(x,y,dir,2))
            {
                break;
            }
        }
        while(1)
        {
            srand(time(NULL)*time(NULL)*time(NULL));
            x = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            y = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            dir = rand() % 4;
            if(my->placeShip(x,y,dir,3))
            {
                break;
            }
        }
        while(1)
        {
            srand(time(NULL)*time(NULL)*time(NULL));
            x = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            y = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            dir = rand() % 4;
            if(my->placeShip(x,y,dir,3))
            {
                break;
            }
        }
        while(1)
        {
            srand(time(NULL)*time(NULL)*time(NULL));
            x = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            y = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            dir = rand() % 4;
            if(my->placeShip(x,y,dir,4))
            {
                break;
            }
        }
        while(1)
        {
            srand(time(NULL)*time(NULL)*time(NULL));
            x = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            y = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            dir = rand() % 4;
            if(my->placeShip(x,y,dir,5))
            {
                break;
            }
        }
    };

    //Selects the correct attack for the difficulty level
    void attack(Board* my, Board* enemy) {
        if (difficulty == "easy") {
            easyAttack(my->shots);
        }
        if (difficulty == "normal") {
            normalAttack(my->shots);
        }
        if (difficulty == "insane") {
            insaneAttack(my->shots);
        }
        //cout << "Target: "<<target[0] << " " << target [1] << endl;
        if(my->fire(target[0],target[1],enemy))
        {
            if(target[1]-1 != -1)
            {
                targetStack->push(target[0],target[1]-1);
            }
            if(target[0]+1 != 10)
            {
                targetStack->push(target[0]+1,target[1]);
            }
            if(target[1]+1 != 10)
            {
                targetStack->push(target[0],target[1]+1);
            }
            if(target[0]-1 != -1)
            {
                targetStack->push(target[0]-1,target[1]);
            }
            /*stackPtr++;
            targetStack[stackPtr][0] = target[0];
            if(target[1]-1 != -1)
            {
                targetStack[stackPtr][1] = target[1]-1;
            }
            else
            {
                targetStack[stackPtr][0] = -1;
                stackPtr--;
            }

            stackPtr++;
            if(target[0]+1 != 10)
            {
                targetStack[stackPtr][0] = target[0]+1;
            }
            else
            {
                targetStack[stackPtr][0] = -1;
                stackPtr--;
            }
            targetStack[stackPtr][1] = target[1];

            stackPtr++;
            targetStack[stackPtr][0] = target[0];
            if(target[1]+1 != 10)
            {
                targetStack[stackPtr][1] = target[1]+1;
            }
            else
            {
                targetStack[stackPtr][0] = -1;
                stackPtr--;
            }

            stackPtr++;
            if(target[0]-1 != -1)
            {
                targetStack[stackPtr][0] = target[0]-1;
            }
            else
            {
                targetStack[stackPtr][0] = -1;
                stackPtr--;
            };
            targetStack[stackPtr][1] = target[1];*/
        }
    }

    void easyAttack(int board[10][10]) {

        //int attack[3];
        int x;
        int y;

        while(1)
        {
            srand(time(NULL)*time(NULL)*time(NULL));
            x = rand() % 10 + 1;
            srand(time(NULL)*time(NULL)*time(NULL));
            y = rand() % 10 + 1;
            if(board[x][y] == 0)
            {
                break;
            }
        }
        //cout << x << " " << y << endl;
        target[0] = x;
        target[1] = y;
        //cout << attack[1] << " " << attack[2] << endl;
        //return attack;
    };

    void normalAttack(int board[10][10]) {

        int* getAddress;
        //int attack[2];

        //If target in stack, return coordinates and override search code
        if (targetStack->first != NULL) {
            target = targetStack->pop();
            while(1)
            {
                if(board[target[0]][target[1]] != 0)
                {
                    target = targetStack->pop();
                }
                else
                {
                    break;
                }
            }
            //cout << target[0] << " " << target[1] << endl;
            //return attack;
        }
        //Else, return easy attack
        else {
            //cout << "hi";
            easyAttack(board);
        }

        //std::cout << "Unknown Error.";
        //return NULL;
    }

    //Note: Each time this function is run, the probability board is reset and recalculated
    void insaneAttack(int board[10][10]) {

        //If target in stack, choose first. Else, continue with probability calculations
        int* getAddress;
        //int attack[2];

        if (targetStack->first != NULL) {
            target = targetStack->pop();
            while(1)
            {
                if(board[target[0]][target[1]] != 0)
                {
                    target = targetStack->pop();
                }
                else
                {
                    break;
                }
            }
        }
        else
        {

            //Resets the probability matrix for each calculation
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    probabilityBoard[i][j] = 0;
                }
            }

                //Calculates the tallies for all remaining ships
            if (true/*carrier*/){
                enumerateTallies(board, 5);
            }
            if (true/*battleship*/) {
                enumerateTallies(board, 4);
            }
            if (true/*cruiser*/) {
                enumerateTallies(board, 3);
            }
            if (true/*submarine*/) {
                enumerateTallies(board, 3);
            }
            if (true/*destroyer*/) {
                enumerateTallies(board, 2);
            }

            //Factors in parity for even squares, ie sets "probability" to 0
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if ((i + j) % 2 == 0) {
                        probabilityBoard[i][j] = 0;
                    }
                }
            }

            //From the remaining even squares, calculates probabilities based on tallies
            double total = 0;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    total += probabilityBoard[i][j];
                }
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    probabilityBoard[i][j] = probabilityBoard[i][j] / total;
                }
            }

            //Searches for and returns the coordinates of the square with the highest probability
            double max = 0;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (probabilityBoard[i][j] > max) {
                        max = probabilityBoard[i][j];
                        target[0] = i;
                        target[1] = j;
                    }
                }
            }
        }

        //return attack;
    }

    //This function is utilized in hardAttack to enumerate the possibilities a ship is in a certain location
    void enumerateTallies(int board[10][10], int shipSize) {

        int emptyCount = 100;	//ie the maximum empty squares on the board
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (board[i][j]) {	//This counts the squares that were fired upon, changes their probability to 0, and also decreases the square count
                    probabilityBoard[i][j] = 0;
                    emptyCount--;
                }
            }
        }

        //Counts tallies horizontally
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j <= 10 - shipSize; j++) {
                int count = 0;
                for (int k = 0; k < shipSize; k++){
                    if (!board[i][j + k]) {		//Counts number of adjacent empty squares from an empty square
                        count++;
                    }
                }
                if (count >= shipSize) {
                    for (int k = 0; k < count; k++) {
                        probabilityBoard[i][j + k]++;
                    }
                }
            }
        }

        //Counts tallies vertically
        for (int i = 0; i <= 10 - shipSize; i++) {
            for (int j = 0; j < 10; j++) {
                int count = 0;
                for (int k = 0; k < shipSize; k++) {
                    if (!board[i + k][j]) {		//Counts number of adjacent empty squares from an empty square
                        count++;
                    }
                }
                if (count >= shipSize) {
                    for (int k = 0; k < count; k++) {
                        probabilityBoard[i + k][j]++;
                    }
                }
            }
        }
    }

};
