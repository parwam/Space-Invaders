﻿#include "../../Header/Enemy/EnemyService.h"
#include "../../Header/Enemy/EnemyController.h"
#include "../../Header/Global/ServiceLocator.h"

namespace Enemy
{
    EnemyService::EnemyService() { }

    EnemyService::~EnemyService() { destroy();}

    void EnemyService::initialize()
    {
        spawn_timer = spawn_interval;
    }

    void EnemyService::update()
    {
        updateSpawnTimer();
        processEnemySpawn();
        
        for (int i = 0; i < enemy_list.size(); i++)
        {
            enemy_list[i]->update();
        }
    }

    void EnemyService::render()
    {
        for (int i = 0; i < enemy_list.size(); i++)
        {
            enemy_list[i]->render();
        }
    }

    void EnemyService::updateSpawnTimer()
    {
        spawn_timer += Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
    }

    void EnemyService::processEnemySpawn()
    {
        if (spawn_timer >= spawn_interval)
        {
            spawnEnemy(); 
            spawn_timer = 0.0f;
        }
    }
    
    EnemyController* EnemyService::spawnEnemy()
    {
        EnemyController* enemy_controller = new EnemyController();
        enemy_controller->initialize();

        enemy_list.push_back(enemy_controller);
        return enemy_controller;
    }
	
    void EnemyService::destroy()
    {
        for (int i = 0; i < enemy_list.size(); i++)
        {
            delete (enemy_list[i]);
        }
    }
}