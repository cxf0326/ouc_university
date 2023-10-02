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
        std::cout << "��ɹ������˵��˵Ĺ���." << std::endl;
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
        std::cout << "���Ѿ������˵ȼ����ޣ��޷��ٴ�����." << std::endl;
    }
    else if (player.getEXP() >= EXPGOAL) {
        player.setLevel(1);
        player.setEXP(-EXPGOAL);
        player.addHealth(2);
        player.addStrength(5);
        player.setWisdom(4);
        std::cout << "��ո�����һ���������ڵĵȼ���" << player.getLevel()
            << ", ��������������� " << player.getHealth() << ", ��Ĺ����������� "
            << player.getStrength() << ", ��ķ����������� " << player.getWisdom() << std::endl;
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
        std::cout << "����ֵ������" << getHealthGain();
        player.addHealth(getHealthGain());
    }
    if (getWisdomGain() > 0) {
        std::cout << "����ֵ������" << getWisdomGain();
        player.addWisdom(getWisdomGain());
    }
    if (getDefensiveGain() > 0) {
        std::cout << "����ֵ������" << getDefensiveGain();
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