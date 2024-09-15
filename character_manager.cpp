#include "enemy.h"
#include "player.h"
#include "character_manager.h"
#include "bullet_time_manager.h"

CharacterManager* CharacterManager::manager = nullptr;

CharacterManager* CharacterManager::Instance()
{
    if(!manager)
        manager = new CharacterManager();
    return manager;
}

void CharacterManager::on_input(const ExMessage& msg)
{
    player->on_input(msg);
}

void CharacterManager::on_update(float delta)
{
    enemy->on_update(delta);
    player->on_update(delta);
}

void CharacterManager::on_render()
{
    //printf("CharacterManager::on_render\n");
    enemy->on_render();
    BulletTimeManager::Instance()->post_process();
    player->on_render();
}

CharacterManager::CharacterManager()
{
    enemy = new Enemy();
    player = new Player();
}

CharacterManager::~CharacterManager()
{
    delete player;
    player = nullptr;
    delete enemy;
    enemy = nullptr;
}
