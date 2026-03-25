#include "Item.h"

Item::Item(string item_name, int atk, int def, int hp)
{
    name           = item_name;
    attack_bonus   = atk;
    defense_bonus  = def;
    health_bonus   = hp;
}
