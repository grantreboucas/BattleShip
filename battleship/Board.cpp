//#include "Board.h"
#ifndef SHIP_H
#define SHIP_H
#include "Ship.cpp"
#endif // SHIP_H

#include <iomanip>
#include <iostream>
#include <iostream>
#include<fstream>
#include<string>
class Board
{
public:
    /*Board();
    bool placeShip(int x, int y, int dir, int length);
    void fire(int x, int y, Board enemy);
    bool checkShip(int shipNum);
    void printBoard();*/

    Ship* shipList[5];
    int shipGrid[10][10];
    char shipGridPrint[10][10];
    char shotsFired[10][10];
    int shots[10][10];
    int shipCount;
    int boardLength;

    Board()
    {
        for(int i = 0; i<10; i++)
        {
            for(int j = 0; j<10; j++)
            {
                shipGrid[i][j] = 0;
                shipGridPrint[i][j] = '-';
                shotsFired[i][j] = '-';
                shots[i][j] = 0;
            }
        }
        shipCount = 0;
        boardLength = 10;
    }

    bool placeShip(int x, int y, int dir, int length)
    {
        shipList[shipCount] = new Ship(x,y,length,dir,false);
        if(dir == 0)
        {
            for(int i = 0; i < length; i++)
            {
                if(shipGrid[x][y-i] != 0 || y-i == -1)
                {
                    return false;
                }
            }
            for(int i = 0; i < length; i++)
            {
                shipGrid[x][y-i] = 1;
                shipGridPrint[x][y-i] = shipCount+1+'0';
            }
        }
        else if(dir == 1)
        {
            for(int i = 0; i < length; i++)
            {
                if(shipGrid[x+i][y] != 0 || x+i == 10)
                {
                    return false;
                }
            }
            for(int i = 0; i < length; i++)
            {
                shipGrid[x+i][y] = 1;
                shipGridPrint[x+i][y] = shipCount+1+'0';
            }
        }
        else if(dir == 2)
        {
            for(int i = 0; i < length; i++)
            {
                if(shipGrid[x][y+i] != 0 || y+1 == 10)
                {
                    return false;
                }
            }
            for(int i = 0; i < length; i++)
            {
                shipGrid[x][y+i] = 1;
                shipGridPrint[x][y+i] = shipCount+1+'0';
            }
        }
        else
        {
            for(int i = 0; i < length; i++)
            {
                if(shipGrid[x-i][y] != 0 || x-i == -1)
                {
                    return false;
                }
            }
            for(int i = 0; i < length; i++)
            {
                shipGrid[x-i][y] = 1;
                shipGridPrint[x-i][y] = shipCount+1+'0';
            }
        }
        shipCount++;
        return true;
    }

    bool checkHit(int x, int y)
    {
        if(shipGrid[x][y] == 0 || shipGrid[x][y] == 2)
        {
            shipGrid[x][y] = 2;
            shipGridPrint[x][y] = 'o';
            return false;
        }
        else
        {
            shipGrid[x][y] = 3;
            shipGridPrint[x][y] = 'x';
            return true;
        }

    }

    bool fire(int x, int y, Board* enemy)
    {
        if(enemy->checkHit(x,y))
        {
            shotsFired[x][y] = 'x';
            shots[x][y] = 1;
            return true;
        }
        else
        {
            shotsFired[x][y] = 'o';
            shots[x][y] = 1;
            return false;
        }
    };

    bool checkShip(int shipNum)
    {
        for(int i = 0; i < boardLength; i++)
        {
            for(int j = 0; j < boardLength; j++)
            {
                if(shipGridPrint[i][j] == shipNum+'0')
                {
                    return false;
                }
            }
        }
        return true;
    }

    void printBoard()
    {
        for(int i = 0; i < 2*boardLength; i++)
        {
            cout << '-';
        }
        cout << endl;
        for(int i = 0; i < boardLength; i++)
        {
            for(int j = 0; j < boardLength; j++)
            {
                cout << shotsFired[j][i] << " ";
            }
            cout << endl;
        }
        for(int i = 0; i < 2*boardLength; i++)
        {
            cout << '-';
        }
        cout << endl;
        for(int i = 0; i < boardLength; i++)
        {
            for(int j = 0; j < boardLength; j++)
            {
                cout << shipGridPrint[j][i] << " ";
            }
            cout << endl;
        }
        for(int i = 0; i < 2*boardLength; i++)
        {
            cout << '-';
        }
        cout << endl;
    }

    void save(string textFile)
    {
        const char *temp = textFile.c_str();
        std::ofstream file (temp);
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                file.put(shipGrid[i][j]);
            }
        }
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                file.put(shipGridPrint[i][j]);
            }
        }
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                file.put(shotsFired[i][j]);
            }
        }
        file.close();
    }
    bool load(string textFile)
    {
        const char *temp = textFile.c_str();
        std::ifstream file (temp,std::ifstream::in);
        char character;
        if(file.is_open())
        {
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    file.get(character);
                    shipGrid[i][j] = character;
                }
            }
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    file.get(character);
                    shipGridPrint[i][j] = character;
                }
            }
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    file.get(character);
                    shotsFired[i][j] = character;
                }
            }
            return true;
        }
        else
        {
            return false;

        }
    }
};





