#include "GameSetting.h"

bool canEvade(float rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    float rand_num = dis(gen);
    if (rand_num < rate) return true;
    else return false;
}

int calculateEnemyFinalDamage(const Player& player, const Enemy& enemy) {
    if (canEvade(player.getAgility())) {
        std::cout << "你成功闪避了敌人的攻击." << std::endl;
        return 0;
    }
    else {
        return enemy.getStrength() - player.getDefensive();
    }
}

int Player::getHit(Player& player, const Enemy& enemy) {
    int finalDamage = calculateEnemyFinalDamage(player, enemy);
    if (finalDamage == 0) {
        //print
        player.addHealth(0);
    }
    else {
        //print
        player.addHealth(-finalDamage);
    }
    return finalDamage;
}

void Player::levelUp(Player& player) {
    if (player.getLevel() > MAXLEVEL) {
        std::cout << "你已经到达了等级上限，无法再次升级." << std::endl;
    }
    else if (player.getEXP() >= EXPGOAL) {
        player.setLevel(1);
        player.setEXP(-EXPGOAL);
        player.addHealth(2);
        player.addStrength(5);
        player.setWisdom(4);
        std::cout << "你刚刚升了一级，你现在的等级是" << player.getLevel()
            << ", 你的生命提升到了 " << player.getHealth() << ", 你的攻击提升到了 "
            << player.getStrength() << ", 你的法力提升到了 " << player.getWisdom() << std::endl;
    }
    else {
        //
    }
}

bool isCritical(float rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    float rand_num = dis(gen);
    if (rand_num < rate) return true;
    else return false;
}

int calculatePlayerFinalDamage(const Player& player, const Enemy& enemy) {
    int damage = 0;
    if (isCritical(player.getCriticalRate())) {
        damage = player.getStrength() * (1 + player.getCriticalPower());
    }
    else {
        damage = player.getStrength();
    }
    int final_damage = damage - enemy.getDefensive();
    if (final_damage <= 0) {
        final_damage = 1;
    }
    return final_damage;
}


int Enemy::getHit(const Player& player, Enemy& enemy) {
    int damage = calculatePlayerFinalDamage(player, enemy);
    enemy.addHealth(-damage);
    return damage;
}

int Enemy::getSkillHit(const Player& player, Enemy& enemy, int choice) {
    int damage = player.getSkillList().at(choice - 1).skill_power;
    enemy.addHealth(-damage);
    return damage;
}

void Item::useItem(Player& player) {
    if (getHealthGain() > 0) {
        std::cout << "生命值提升：" << getHealthGain();
        player.addHealth(getHealthGain());
    }
    if (getWisdomGain() > 0) {
        std::cout << "法力值提升：" << getWisdomGain();
        player.addWisdom(getWisdomGain());
    }
    if (getDefensiveGain() > 0) {
        std::cout << "防御值提升：" << getDefensiveGain();
        player.addDefensive(getDefensiveGain());
    }
    std::cout << std::endl;
}

void Player::addItem(Item item, int number) {
    for (auto& i : m_item_list) {
        if (item.getName() == i.getName()) {
            i.addNumber(number);
            return;
        }
    }
    item.setNumber(number);
    m_item_list.push_back(item);
}

void Player::rmItem(const Item& item) {
    for (auto it = m_item_list.begin(); it != m_item_list.end();) {
        if (item.getName() == it->getName()) {
            it->addNumber(-1);
            if (it->getNumber() == 0) {
                it = m_item_list.erase(it);
                continue;
            }
        }
        ++it;
    }
}