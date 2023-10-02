#ifndef SIMPLEMUDMODIFIED_GAMECONTROLLER_H
#define SIMPLEMUDMODIFIED_GAMECONTROLLER_H

#include "TextParser.h"
#include "iostream"
#include<fstream>
#include<string>
#include "cstdlib"

class GameController {
public:
    GameController() {}

    void RunGame();

private:
    // Display Information or Menu
    void showStartMenu();

    void showArchiveMenu();

    static void showCombatMenu();

    static void showSkillMenu(const Player& player);

    void showItemMenu(Player player);

    void showEscape();

    void showPlayerHurt(Player& player, int damage);

    void showEnemyHurt(Enemy& enemy, int damage);

    void showEnemyAttack(Enemy enemy);

    void showChoiceError();

    void showItemDrop(Enemy enemy);

    void showNormalDiscoverMenu();

    void showPlayerState(Player player);

    void displayLogo(const std::string filename);// Display Logo

    void displayMap(const std::string filename);

    void displayAllData();

    // Turn-based Combat System
    bool PlayerTurn(Player& player, Enemy& enemy);

    void EnemyTurn(Player& player, Enemy& enemy);

    void Combat(Player& player);

    //
    void Discover(Player& player);

    void Interactive(Player& player);

    // Archive-about Operation
    Player initializeArchive();

    static Player loadArchive(const std::string& filename);

    void loadAllData();

    // Used for Test
    void Test();
};

#endif //SIMPLEMUDMODIFIED_GAMECONTROLLER_H