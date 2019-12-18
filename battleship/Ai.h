#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#endif // AI_H_INCLUDED

class linkedList
{
    struct Node
    {
        int* coord;
        Node *next;
    };
public:
    Node *first = NULL;
    Node *last = NULL;
    Node *temp = NULL;

    linkedList()
    {
        Node *first = NULL;
        //Node *last = NULL;
        Node *temp = NULL;
    }

    void push(int x, int y)
    {
        int* data;
        data = new int[2];
        data[0] = x;
        data[1] = y;
        temp = new Node;
        temp->coord = data;
        temp->next = first;
        first = temp;
        /*if(first == NULL)
        {
            first = temp;
            last = temp;
        }
        else
        {
            last->next = temp;
            last = temp;
        }*/
    }
    int* pop()
    {
        int* data;
        if(first == NULL)
        {
            return NULL;
        }
        else
        {
            //cout << "Stored values: " << first->coord[0] << " " << first->coord[1] << endl;
            data = first->coord;
            first = first->next;
            return data;
        }
    }
};
