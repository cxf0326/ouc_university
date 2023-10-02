#ifndef SIMPLEMUDMODIFIED_GAMESETTING_H
#define SIMPLEMUDMODIFIED_GAMESETTING_H

#include <utility>
#include "string"
#include "iostream"
#include "random"
#include "fstream"

#define MAXLEVEL 25
#define EXPGOAL 20

class Enemy;

class Player;

class Item {
private:
    std::string m_name;
    std::string m_description;
    int m_id;
    int m_health_gain;
    int m_wisdom_gain;
    int m_defensive_gain;
    int m_number = 0;
public:
    // Getter
    [[nodiscard]] std::string getName() const { return m_name; }

    std::string getDescription() { return m_description; }

    int getHealthGain() const { return m_health_gain; }

    int getWisdomGain() const { return m_wisdom_gain; }

    int getDefensiveGain() const { return m_defensive_gain; }

    [[nodiscard]] int getNumber() const { return m_number; }

    [[nodiscard]] int getID() const { return m_id; }

    // Setter
    void setName(std::string name) { m_name = std::move(name); }

    void setDescription(std::string description) { m_description = std::move(description); }

    void setID(int value) { m_id = value; }

    void setHealthGain(int value) { m_health_gain = value; }

    void setWisdomGain(int value) { m_wisdom_gain = value; }

    void setDefensiveGain(int value) { m_defensive_gain = value; }

    void useItem(Player& player);

    void setNumber(int value) { m_number = value; }

    void addNumber(int value) { m_number += value; }
};


struct SKILL {
    std::string skill_name;
    int skill_power;
    int wisdom_need;
    int skill_id;
};

class Player {
private:
    std::string m_name;
    int m_health{};
    int m_defensive{};
    int m_strength{};
    int m_wisdom{};
    int m_cur_wisdom{};
    float m_critical_rate{};
    float m_critical_power{};
    float m_agility{};
    int m_exp{};
    int m_level{};
    int m_id{};
    std::vector<SKILL> m_skill_list;
    std::vector<Item> m_item_list;
    int m_cur_spot_id{};
    int m_ongoing_quest_id{};
    int m_ongoing_progress{};
public:
    // 构造函数
    Player() = default;

    Player(std::string name, int health, int defensive, int strength, int wisdom, float critical_rate, float
        critical_power, float agility, int spotID) : m_name(std::move(name)), m_health(health), m_defensive(defensive),
        m_strength(strength), m_wisdom(wisdom), m_cur_wisdom(wisdom),
        m_cur_spot_id(spotID), m_agility(agility), m_exp(0), m_level(1),
        m_critical_rate(critical_rate), m_critical_power(critical_power),
        m_ongoing_quest_id(-1), m_ongoing_progress(0), m_id(0) {
        m_skill_list = { {"基础技能",    10, 20},
                        {"进阶技能", 20, 40},
                        {"终极技能", 30, 60} };
    }

    Player(const Player& other)
        : m_id(other.m_id),
        m_name(other.m_name),
        m_health(other.m_health),
        m_defensive(other.m_defensive),
        m_strength(other.m_strength),
        m_wisdom(other.m_wisdom),
        m_cur_wisdom(other.m_cur_wisdom),
        m_critical_rate(other.m_critical_rate),
        m_critical_power(other.m_critical_power),
        m_agility(other.m_agility),
        m_exp(other.m_exp),
        m_level(other.m_level),
        m_skill_list(other.m_skill_list),
        m_item_list(other.m_item_list),
        m_cur_spot_id(other.m_cur_spot_id),
        m_ongoing_quest_id(other.m_ongoing_quest_id) {
    }

    // Getter
    [[nodiscard]] std::string getName() const { return m_name; }

    [[nodiscard]] int getHealth() const { return m_health; }

    [[nodiscard]] int getDefensive() const { return m_defensive; }

    [[nodiscard]] int getStrength() const { return m_strength; }

    [[nodiscard]] int getID() const { return m_id; }

    [[nodiscard]] int getWisdom() const { return m_wisdom; }

    [[nodiscard]] int getCurWisdom() const { return m_cur_wisdom; }

    [[nodiscard]] float getCriticalRate() const { return m_critical_rate; }

    [[nodiscard]] float getCriticalPower() const { return m_critical_power; }

    [[nodiscard]] float getAgility() const { return m_agility; }

    [[nodiscard]] int getEXP() const { return m_exp; }

    [[nodiscard]] int getLevel() const { return m_level; }

    [[nodiscard]] int getCurSpotID() const { return m_cur_spot_id; }

    [[nodiscard]] std::vector<SKILL> getSkillList() const { return m_skill_list; }

    std::vector<Item>& getItemList() { return m_item_list; }

    [[nodiscard]] const std::vector<Item>& getItemList() const { return m_item_list; }


    [[nodiscard]] int getQuestID() const { return m_ongoing_quest_id; }

    [[nodiscard]] int getProgress() const { return m_ongoing_progress; }

    // Setter
    void addHealth(int value) { m_health += value; }

    void addDefensive(int value) { m_defensive += value; }

    void addStrength(int value) { m_strength += value; }

    void addWisdom(int value) { m_wisdom += value; }

    void setLevel(int value) { m_level = value; }

    void setEXP(int value) { m_exp = value; }

    void setWisdom(int value) { m_wisdom = value; }

    void setCurWisdom(int value) { m_cur_wisdom = value; }

    void setSpotID(int value) { m_cur_spot_id = value; }

    void setQuestID(int value) { m_ongoing_quest_id = value; }

    void setProgress(int value) { m_ongoing_progress = value; }

    void addProgress(int value) { m_ongoing_progress += value; }

    void setHealth(int value) { m_health = value; }

    void setDefensive(int value) { m_defensive = value; }

    void setStrength(int value) { m_strength = value; }

    void setCriticalRate(float value) { m_critical_rate = value; }

    void setCriticalPower(float value) { m_critical_power = value; }

    void setAgility(float value) { m_agility = value; }

    void setID(int value) { m_id = value; }

    void setItemList(std::vector<Item> list) { m_item_list = std::move(list); }

    void setName(std::string name) { m_name = std::move(name); }

    //
    static int getHit(Player& player, const Enemy& enemy);

    static void levelUp(Player& player);

    void addItem(Item item, int number);

    void rmItem(const Item& item);

    //static Player load(std::string filename);

    //void save(std::string filename) const;
};

class Enemy {
private:
    std::string m_name;
    int m_health;
    int m_defensive;
    int m_strength;
    int m_exp;
    std::string m_description;
    int m_id;
    int m_drop_item_id;
    int m_drop_item_num;
    int m_skill_id;
public:
    // Getter
    [[nodiscard]] std::string getName() const { return m_name; }

    [[nodiscard]] int getHealth() const { return m_health; }

    [[nodiscard]] int getDefensive() const { return m_defensive; }

    [[nodiscard]] int getStrength() const { return m_strength; }

    [[nodiscard]] int getID() const { return m_id; }

    [[nodiscard]] int getDropItemID() const { return m_drop_item_id; }

    [[nodiscard]] int getDropItemNum() const { return m_drop_item_num; }

    [[nodiscard]] int getEXP() const { return m_exp; }

    [[nodiscard]] int getSkillID() const { return m_skill_id; }

    [[nodiscard]] std::string getDescription() const { return m_description; }

    // Setter
    void setName(std::string name) { m_name = std::move(name); }

    void setID(int value) { m_id = value; }

    void addHealth(int value) { m_health += value; }

    void addDefensive(int value) { m_defensive += value; }

    void addStrength(int value) { m_strength += value; }

    void setDescription(std::string description) { m_description = std::move(description); }

    void setHealth(int value) { m_health = value; }

    void setDefensive(int value) { m_defensive = value; }

    void setStrength(int value) { m_strength = value; }

    void setEXP(int value) { m_exp = value; }

    void setDropItemID(int value) { m_drop_item_id = value; }

    void setDropItemNum(int value) { m_drop_item_num = value; }

    void setSkillID(int value) { m_drop_item_id = value; }

    // 其他方法
    static int getHit(const Player& player, Enemy& enemy);

    static int getSkillHit(const Player& player, Enemy& enemy, int choice);
};

class Npc {
private:
    int m_id;
    std::string m_name;
    std::string m_description;
    int m_quest_id;
public:
    Npc() {}

    // getter
    int getID() { return m_id; }

    std::string getName() { return m_name; }

    std::string getDescription() { return m_description; }

    int getQuestID() { return m_quest_id; }

    //set
    void setName(std::string name) { m_name = name; }

    void setID(int value) { m_id = value; }

    void setDescription(std::string description) { m_description = description; }

    void setQuestID(int value) { m_quest_id = value; }


};

class Quest {
private:
    int m_id;
    std::string m_name;
    std::string m_todo_description;
    std::string m_done_description;
    int m_enemy_id;
    int m_item_id;
    int m_enemy_number;
    bool quest_done = false;
public:
    // getter
    int getID() { return m_id; }

    std::string getName() { return m_name; }

    std::string getDescription0() { return m_todo_description; }

    std::string getDescription1() { return m_done_description; }

    int getEnemyID() { return m_enemy_id; }

    int getItemID() { return m_item_id; }

    int getEnemyNumber() { return m_enemy_number; }

    bool getQuestDone() { return quest_done; }

    // setter
    void setID(int value) { m_id = value; }

    void setName(std::string name) { m_name = name; }

    void setDescription0(std::string description) { m_todo_description = description; }

    void setDescription1(std::string description) { m_done_description = description; }

    void setEnemyID(int value) { m_enemy_id = value; }

    void setItemID(int value) { m_item_id = value; }

    void setEnemyNumber(int value) { m_enemy_number = value; }

    void setQuestDone(bool value) { quest_done = value; }

    //

    void start(Player& player);

    void check(Player& player);
};

#endif