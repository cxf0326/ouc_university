#ifndef SIMPLEMUDMODIFIED_TEXTPARSER_H
#define SIMPLEMUDMODIFIED_TEXTPARSER_H

#include <utility>

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
    [[nodiscard]] int getID() const { return m_id; }

    [[nodiscard]] std::string getName() const { return m_name; }

    [[nodiscard]] std::string getDescription() const { return m_description; }

    [[nodiscard]] int getExitNumber() const { return m_exit_number; }

    std::vector<int>& getExits() { return m_exits; }

    [[nodiscard]] const std::vector<int>& getExits() const { return m_exits; }

    [[nodiscard]] int getEnemyNumber() const { return m_enemy_number; }

    std::vector<int>& getEnemies() { return m_enemies; }

    [[nodiscard]] const std::vector<int>& getEnemies() const { return m_enemies; }

    [[nodiscard]] int getNpcNumber() const { return m_npc_number; }

    std::vector<int>& getNpcs() { return m_npcs; }

    [[nodiscard]] const std::vector<int>& getNpcs() const { return m_npcs; }

    std::vector<int>& getScripts() { return m_scripts; }

    [[nodiscard]] const std::vector<int>& getScripts() const { return m_scripts; }

    // setter
    void setID(int value) { m_id = value; }

    void setName(std::string name) { m_name = std::move(name); }

    void setDescription(std::string description) { m_description = std::move(description); }

    void setExitNumber(int value) { m_exit_number = value; }

    void setEnemyNumber(int value) { m_enemy_number = value; }

    void setNpcNumber(int value) { m_npc_number = value; }

    // other functions
    void viewAround(int id) const;

};

class TextParser {
public:
    static std::vector<Spot> loadSpotDat(const std::string& filename);

    static std::vector<std::string> loadScriptDat(const std::string& filename);

    static std::vector<Enemy> loadEnemiesDat(const std::string& filename);

    static std::vector<Item> loadItemDat(const std::string& filename);

    static std::vector<Quest> loadQuestDat(const std::string& filename);

    static std::vector<Npc> loadNpcDat(const std::string& filename);
};


#endif