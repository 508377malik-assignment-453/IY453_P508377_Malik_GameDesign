#include "Player.h"


Player::Player(string player_name)
{
    name       = player_name;
    health     = 20;
    max_health = 20;
    attack     = 5;
    defense    = 2;
    score      = 0;
}


void Player::AddItem(Item item)
{
    inventory.push_back(item);
    attack  += item.attack_bonus;
    defense += item.defense_bonus;

    if (item.health_bonus > 0)
    {
        health += item.health_bonus;
        if (health > max_health) health = max_health;
        cout << "You feel restored! +" << item.health_bonus << " HP\n";
    }
    cout << "You picked up: " << item.name << "!\n";
}

void Player::ShowStats()
{
    cout << "\n--- " << name << "'s Stats ---\n";
    cout << "Health  : " << health << " / " << max_health << "\n";
    cout << "Attack  : " << attack << "\n";
    cout << "Defense : " << defense << "\n";
    cout << "Score   : " << score << "\n";
}

void Player::ShowInventory()
{
    cout << "\n--- Inventory ---\n";
    if (inventory.empty())
    {
        cout << "You have no items.\n";
    }
    else
    {
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << "- " << inventory[i].name << "\n";
        }
    }
}

bool Player::IsDead()
{
    return health <= 0;
}
