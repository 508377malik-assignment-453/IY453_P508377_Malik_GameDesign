#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Item
{
public:
    string name;
    int    attack_bonus;
    int    defense_bonus;
    int    health_bonus;

    Item(string item_name, int atk, int def, int hp)
    {
        name           = item_name;
        attack_bonus   = atk;
        defense_bonus  = def;
        health_bonus   = hp;
    }
};


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

    Player(string player_name)
    {
        name       = player_name;
        health     = 20;
        max_health = 20;
        attack     = 5;
        defense    = 2;
        score      = 0;
    }

    void AddItem(Item item)
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

    void ShowStats()
    {
        cout << "\n--- " << name << "'s Stats ---\n";
        cout << "Health  : " << health << " / " << max_health << "\n";
        cout << "Attack  : " << attack << "\n";
        cout << "Defense : " << defense << "\n";
        cout << "Score   : " << score << "\n";
    }

    void ShowInventory()
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

    bool IsDead()
    {
        return health <= 0;
    }
};



int GetChoice()
{
    int choice;
    while (true)
    {
        cout << "Enter choice (1 or 2): ";
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            return choice;
        }
        cout << "Invalid input. Please enter 1 or 2.\n";
    }
}


int RandomNumber(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}


bool RunCombat(Player &player, string enemy_name,int enemy_attack, int enemy_defense, int enemy_health)
{

    cout << "\n--- COMBAT: " << player.name << " vs " << enemy_name << " ---\n";

    int enemy_hp = enemy_health;

    while (true)
    {
        int player_roll  = RandomNumber(1, 10);
        int player_score = player.attack + player_roll;

        int enemy_roll   = RandomNumber(1, 10);
        int enemy_score  = enemy_attack + enemy_roll;

        cout << "\n" << player.name << " rolls " << player_roll
             << " (total: " << player_score << ")"
             << "  vs  " << enemy_name << " rolls " << enemy_roll
             << " (total: " << enemy_score << ")\n";

        if (player_score > enemy_score)
        {
            int damage = player.attack - enemy_defense;
            if (damage < 1)
            {
                damage = 1;
            }
            enemy_hp -= damage;
            cout << "You hit " << enemy_name << " for " << damage<< " damage! (Enemy HP: " << enemy_hp << ")\n";
        }
        else
        {
            int damage = enemy_attack - player.defense;
            if (damage < 1)
            {
                damage = 1;
            }
            player.health -= damage;
            cout << enemy_name << " hits you for " << damage<< " damage! (Your HP: " << player.health << ")\n";
        }

		if (enemy_hp <= 0)
		{
            cout << "\nYou defeated the " << enemy_name << "!\n";
            return true;
        }
        if (player.health <= 0)
		{
            player.health = 0;
            cout << "\nYou were defeated by the " << enemy_name << "...\n";
            return false;
        }
    }


int main() {
        cout << "================================\n";
        cout << "     THE SHATTERED REALM\n";
        cout << "================================\n\n";

        string player_name;
        cout << "Enter your name, adventurer: ";
        getline(cin, player_name);

        Player player(player_name);
        cout << "\nWelcome, " << player.name << "! Your quest begins...\n";



        // SCENE 0 — The Crossroads
        cout << "\n================================================\n";
        cout << "You stand at a crossroads outside the ruined city\n";
        cout << "of Aldenmoor. A dying soldier presses a cracked\n";
        cout << "map into your hands. Two paths stretch before you.\n";
        cout << "================================================\n";
        cout << "1. Take the forest path east\n";
        cout << "2. Take the cursed road west\n";

        int opening_choice = GetChoice();



        // BRANCH A — Forest Path
        if (opening_choice == 1)
        {
            // Scene 1A — Item Collection
            cout << "\nYou enter the Whispering Forest. A wounded fox\n";
            cout << "is caught in a trap. Nearby hangs a ranger's pack.\n";
            cout << "1. Free the wounded fox\n";
            cout << "2. Grab the ranger's pack\n";

            if (GetChoice() == 1)
            {
                cout << "\nThe grateful fox leads you to a hidden cache.\n";
                player.AddItem(Item("Elvish Boots", 0, 2, 0));
                player.score += 25;
            }
            else
            {
                cout << "\nThe pack contains useful supplies!\n";
                player.AddItem(Item("Hunting Knife", 3, 0, 0));
                player.AddItem(Item("Dried Meat", 0, 0, 2));
                player.score += 25;
            }

            // Scene 2A — Combat
            cout << "\nA goblin scout drops from the trees!\n";
            cout << "1. Fight the goblin\n";
            cout << "2. Flee into the undergrowth\n";

            if (GetChoice() == 1)
            {
                bool won = RunCombat(player, "Goblin Scout", 6, 2, 8);
                if (!won)
                {
                    cout << "\n=== GAME OVER ===\n";
                    cout << "Final Score: " << player.score << "\n";
                    return 0;
                }
                player.score += 75;
                cout << "You find a brass key on the goblin!\n";
                player.AddItem(Item("Brass Key", 0, 0, 0));
            }
            else
            {
                cout << "\nYou escape but fall and take 2 damage.\n";
                player.health -= 2;
                player.AddItem(Item("Crude Sword", 2, 0, 0));
            }
        }
    }
