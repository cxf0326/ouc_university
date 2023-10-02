#include "GameSetting.h"

bool canEvade(float rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    float rand_num = dis(gen);
    if (rand_num < rate) return true;
    else return false;
}

int calculateEnemyFinalDamage(Player player, const Enemy& enemy) {
    if (canEvade(player.getAgility())) {
        std::cout <<"你成功地躲过了袭击。" << std::endl;
        return 0;
    }
    else {
        return enemy.getStrength() - player.getDefensive();
    }
}

int Player::getHit(Player& player, Enemy enemy) {
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
        std::cout << "你已经达到了最大等级，无法在提升等级。" << std::endl;
    }
    else if (player.getEXP() >= EXPGOAL) {
        player.setLevel(1);
        player.setEXP(-EXPGOAL);
        player.addHealth(2);
        player.addStrength(5);
        player.setWisdom(4);
        std::cout << "你的等级提升了一级，达到了Lv." << player.getLevel()
            << "，血量值提升到了： " << player.getHealth() << "，攻击力提升到了： "
            << player.getStrength() << "法力值提升到了：" << player.getWisdom() << std::endl;
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

int calculatePlayerFinalDamage(Player player, Enemy enemy) {
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


int Enemy::getHit(Player player, Enemy& enemy) {
    int damage = calculatePlayerFinalDamage(player, enemy);
    enemy.addHealth(-damage);
    return damage;
}

int Enemy::getSkillHit(Player player, Enemy& enemy, int choice) {
    int damage = player.getSkillList().at(choice - 1).skill_power;
    enemy.addHealth(-damage);
    return damage;
}

void Item::useItem(Player& player) {
    if (getHealthGain() > 0) {
        std::cout << "血量回复： " << getHealthGain();
        player.addHealth(getHealthGain());
    }
    if (getWisdomGain() > 0) {
        std::cout << "法力值回复： " << getWisdomGain();
        player.addWisdom(getWisdomGain());
    }
    if (getDefensiveGain() > 0) {
        std::cout << "防御值提升： " << getDefensiveGain();
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

void Player::rmItem(Item item) {
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
