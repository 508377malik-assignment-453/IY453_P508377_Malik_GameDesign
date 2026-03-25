#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item
{
public:
    string name;
    int    attack_bonus;
    int    defense_bonus;
    int    health_bonus;

    Item(string item_name, int atk, int def, int hp);
};

#endif
