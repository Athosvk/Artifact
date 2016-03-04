#include <Artifact/Game.h>
#include <Artifact/Random.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/Audio/AudioSource.h>

#include "MainWorld.h"
#include "Player/PlayerInputSystem.h"
#include "Enemy/Enemy.h"
#include "Player/WeaponSystem.h"
#include "TimerSystem.h"
#include "Enemy/FollowSystem.h"
#include "BulletSystem.h"
#include "Enemy/AttackSystem.h"
#include "Enemy/ZombieBehaviourSystem.h"
#include "HealthComponent.h"
#include "GameOverScreen.h"
#include "Player/HUDSystem.h"
#include "ScoreSystem.h"
#include "Enemy/SpawnerSystem.h"
#include "Enemy/Spawner.h"

MainWorld::MainWorld(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame)
{
    addSystem<PlayerInputSystem>();
    addSystem<WeaponSystem>();
    addSystem<TimerSystem>();
    addSystem<FollowSystem>();
    addSystem<BulletSystem>();
    addSystem<AttackSystem>();
    addSystem<HUDSystem>();
    addSystem<ZombieBehaviourSystem>();
    addSystem<ScoreSystem>();
    addSystem<SpawnerSystem>();

    auto player = m_EntitySystem.createEntity<Player>();
    player.getComponent<HealthComponent>()->OnDeath += [this](const HealthComponent*)
    { 
        loadGameoverScreen(); 
    };

    for(int i = 0; i < 6; i++)
    {
        auto spawner = m_EntitySystem.createEntity<Spawner>();
        auto spawnPosition = glm::vec2(Artifact::Random::range(-4.5f, 4.5f),
            Artifact::Random::range(-4.5f, 4.5f));
        spawner.getComponent<Artifact::Transform>()->setPosition(spawnPosition);
    }

    auto background = m_EntitySystem.createEntity().addComponent<Artifact::SpriteRenderer>();
    background->setTexture(Artifact::ResourceManager::getTexture("Textures/Background.png"));
    background->Width = 12.0f;
    background->Height = 8.0f;
    background->Depth = -20.0f;
    background->UVRectangle = Artifact::Rectangle(glm::vec2(0.0f, 0.0f), 10.0f, 10.0f);
    background->Color = Artifact::Color(0.45f, 0.45f, 0.45f);
    auto backgroundMusic = background->addComponent<Artifact::AudioSource>();
    backgroundMusic->enableLooping();
    backgroundMusic->Sound = Artifact::ResourceManager::getSound("Sounds/XYZ.ogg");
    backgroundMusic->play();
}

void MainWorld::loadGameoverScreen() const
{
    m_CurrentGame->loadWorld<GameOverScreen>();
}
