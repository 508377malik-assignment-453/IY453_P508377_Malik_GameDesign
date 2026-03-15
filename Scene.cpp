#include "Scene.h"
#include <cstdlib>


extern int GetChoice();

Scene::Scene(string t, string desc, string opt1, string opt2)
    : title(t), description(desc), option1(opt1), option2(opt2) {}

void Scene::PrintScene() const
{
    cout << "\n----------------------------------------\n";
    cout << "SCENE: " << title << "\n";
    cout << "----------------------------------------\n";
    cout << description << "\n\n";
    cout << "1. " << option1 << "\n";
    cout << "2. " << option2 << "\n";
}


ItemScene::ItemScene(string title, string description,
                     string opt1, string opt2,
                     Outcome o1, Outcome o2)
    : Scene(title, description, opt1, opt2),
      outcome1(o1), outcome2(o2) {}

bool ItemScene::Run(Player &player)
{
    PrintScene();

    int choice = GetChoice();
    Outcome &chosen = (choice == 1) ? outcome1 : outcome2;

    cout << "\n" << chosen.message << "\n";

    if (chosen.hasItem)
    {
        player.AddItem(chosen.item);
    }

    player.score += chosen.scoreDelta;
    if (player.score < 0) player.score = 0;

    if (chosen.hpPenalty > 0)
    {
        player.health -= chosen.hpPenalty;
        if (player.IsDead())
        {
            player.LoseLife();
            if (player.GameOver())
            {
                return false;
            }
        }
    }

    return true;
}


PuzzleScene::PuzzleScene(string title, string description,
                         string opt1, string opt2,
                         int correct, int reward, int penalty,
                         bool giveItem, Item item)
    : Scene(title, description, opt1, opt2),
      correctOption(correct), scoreReward(reward), hpPenalty(penalty),
      hasItem(giveItem), rewardItem(item) {}

bool PuzzleScene::Run(Player &player)
{
    PrintScene();

    int choice = GetChoice();

    if (choice == correctOption)
    {
        cout << "\nCorrect! ";
        if (hasItem)
        {
            player.AddItem(rewardItem);
        }
        player.score += scoreReward;
        cout << "+" << scoreReward << " score!\n";
    }
    else
    {
        cout << "\nWrong! You take " << hpPenalty << " damage.\n";
        player.health -= hpPenalty;
        if (player.IsDead())
        {
            player.LoseLife();
            if (player.GameOver())
            {
                return false;
            }
        }
    }

    return true;
}


CombatScene::CombatScene(string title, string description,
                         string fightOpt, string avoidOpt,
                         string enemy, int eAtk, int eDef, int eHp,
                         int reward, bool giveWinItem, Item wItem,
                         string avoidMsg, int avoidLoss,
                         bool giveAvoidItem, Item aItem)
    : Scene(title, description, fightOpt, avoidOpt),
      enemyName(enemy), enemyAttack(eAtk), enemyDefense(eDef), enemyHealth(eHp),
      scoreReward(reward), hasWinItem(giveWinItem), winItem(wItem),
      avoidMessage(avoidMsg), avoidHpLoss(avoidLoss),
      hasAvoidItem(giveAvoidItem), avoidItem(aItem) {}

int CombatScene::RandomNumber(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

bool CombatScene::RunCombat(Player &player)
{
    cout << "\n========================================\n";
    cout << "  COMBAT: " << player.name << " vs " << enemyName << "\n";
    cout << "========================================\n";
    cout << "Your Attack: "  << player.attack  << "  |  Your Defense: " << player.defense << "\n";
    cout << enemyName << " Attack: " << enemyAttack << "  |  Defense: " << enemyDefense << "\n\n";

    int enemy_hp = enemyHealth;

    while (true)
    {
        int player_roll  = RandomNumber(1, 10);
        int player_score = player.attack + player_roll;

        int enemy_roll   = RandomNumber(1, 10);
        int enemy_score  = enemyAttack + enemy_roll;

        cout << player.name << " rolls " << player_roll
             << " (total: " << player_score << ")"
             << "  vs  " << enemyName << " rolls " << enemy_roll
             << " (total: " << enemy_score << ")\n";

        if (player_score > enemy_score)
        {
            int damage = player.attack - enemyDefense;
            if (damage < 1) damage = 1;
            enemy_hp -= damage;
            cout << "  >> You hit " << enemyName << " for " << damage
                 << " damage! (Enemy HP: " << enemy_hp << ")\n";
        }
        else
        {
            int damage = enemyAttack - player.defense;
            if (damage < 1) damage = 1;
            player.health -= damage;
            cout << "  >> " << enemyName << " hits you for " << damage
                 << " damage! (Your HP: " << player.health << ")\n";
        }

        if (enemy_hp <= 0)
        {
            cout << "\n*** You defeated the " << enemyName << "! ***\n";
            return true;
        }

        if (player.health <= 0)
        {
            player.health = 0;
            cout << "\n*** You were defeated by the " << enemyName << "! ***\n";
            player.LoseLife();
            return false;
        }
    }
}

bool CombatScene::Run(Player &player)
{
    PrintScene();

    int choice = GetChoice();

    if (choice == 1)
    {
        // Fight path
        bool won = RunCombat(player);

        if (!won && player.GameOver())
        {
            return false;
        }

        if (won)
        {
            player.score += scoreReward;
            if (hasWinItem)
            {
                player.AddItem(winItem);
            }
        }
    }
    else
    {
        cout << "\n" << avoidMessage << "\n";

        if (avoidHpLoss > 0)
        {
            player.health -= avoidHpLoss;
            if (player.IsDead())
            {
                player.LoseLife();
                if (player.GameOver())
                {
                    return false;
                }
            }
        }

        if (hasAvoidItem)
        {
            player.AddItem(avoidItem);
        }
    }

    return true;
}
