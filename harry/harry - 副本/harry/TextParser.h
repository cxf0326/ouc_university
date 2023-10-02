//
// Created by MarvinHereFound on 2023/9/6.
//

#ifndef SIMPLEMUDMODIFIED_TEXTPARSER_H
#define SIMPLEMUDMODIFIED_TEXTPARSER_H

#include "GameSetting.h"
#include "fstream"
#include "sstream"
#include "vector"

class Spot {
private:
    int m_id;
    std::string m_name;
    std::string m_description;
    int m_exit_number;
    std::vector<int> m_exits;
    int m_npc_number;
    std::vector<int> m_npcs;
    int m_enemy_number;
    std::vector<int> m_enemies;
    std::vector<int> m_scripts;
public:
    // getter
    int getID() const { return m_id; }

    std::string getName() const { return m_name; }

    std::string getDescription() const { return m_description; }

    int getExitNumber() const { return m_exit_number; }

    std::vector<int>& getExits() { return m_exits; }

    const std::vector<int>& getExits() const { return m_exits; }

    int getEnemyNumber() const { return m_enemy_number; }

    std::vector<int>& getEnemies() { return m_enemies; }

    const std::vector<int>& getEnemies() const { return m_enemies; }

    int getNpcNumber() const { return m_npc_number; }

    std::vector<int>& getNpcs() { return m_npcs; }

    const std::vector<int>& getNpcs() const { return m_npcs; }

    std::vector<int>& getScripts() { return m_scripts; }

    const std::vector<int>& getScripts() const { return m_scripts; }

    // setter
    void setID(int value) { m_id = value; }

    void setName(std::string name) { m_name = name; }

    void setDescription(std::string description) { m_description = description; }

    void setExitNumber(int value) { m_exit_number = value; }

    void setEnemyNumber(int value) { m_enemy_number = value; }

    void setNpcNumber(int value) { m_npc_number = value; }

    // other functions
    void viewAround(int id);

    void enterSpot();

    void leaveSpot();

};

class TextParser {
public:
    std::vector<Spot> loadSpotDat(const std::string filename);

    std::vector<std::string> loadScriptDat(const std::string filename);

    std::vector<Enemy> loadEnemiesDat(const std::string filename);

    std::vector<Item> loadItemDat(const std::string filename);

    std::vector<Quest> loadQuestDat(const std::string filename);

    std::vector<Npc> loadNpcDat(const std::string filename);

    void saveArchive(const std::string filename, const Player& player);
};


#endif //SIMPLEMUDMODIFIED_TEXTPARSER_H