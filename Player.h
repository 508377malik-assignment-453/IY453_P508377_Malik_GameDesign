#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
using namespace std;


class Player
{
public:
    string       name;
    int          health;
    int          max_health;
    int          attack;
    int          defense;
    int          score;
    vector<Item> inventory;

    Player(string player_name);

    void AddItem(Item item);

    void ShowStats();

    void ShowInventory();

    bool IsDead();
};

#endif 
