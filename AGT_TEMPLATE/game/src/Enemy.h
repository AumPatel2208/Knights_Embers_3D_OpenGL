#pragma once
#include <engine.h>

#include "player.h"
#include "glm/gtx/rotate_vector.hpp"

class Enemy {

public:
	Enemy();
	~Enemy();

	void initialise();
    void setRandomPosition() const;
    void setRandomScale();
    void setEnemyType();
    void setEnemyType(int type);
    void onUpdate(const engine::timestep& timestep, const Player& player);
    void animationHandler();
    engine::ref<engine::game_object> object() const { return mObject; }

	void turn(float angle);

	void idle();
	void attack();
    void die(const bool& isHitLight);
    void walk(engine::timestep timestep, const Player& player);
    float calculateSpeed(bool isWalking);
    void run();

	void shout();
    void agro(const engine::timestep& timestep);


    //Static references to animations to make it easier to point to the index
	static const int ANIM_IDLE = 0;
	static const int ANIM_WALK = 1;
	static const int ANIM_RUN = 2;
	static const int ANIM_ATTACK = 3;
	static const int ANIM_DEATH1 = 4;
	static const int ANIM_DEATH2 = 5;
	static const int ANIM_GET_HIT = 6;
	static const int ANIM_SHOUT = 7;


	// Enemy Types based on integer
	static const int TYPE_WALKER = 1;
	static const int TYPE_SHOUTER = 2;
	static const int TYPE_TRACKER = 3;
	static const int TYPE_JUMPER = 5;

private:
	engine::ref<engine::game_object>	mObject;
	engine::ref<engine::skinned_mesh>	enemyMesh;
	int									enemyType = 0;
	float angleFromPlayer;
	float mSpeed{ 1.f };
	float mShoutTimer = 0;
	bool toAttack = false;
	bool isAgro = false; // amount of times been agroed
	float maxSize = 0.f;
	int currentAnimation = ANIM_IDLE;
	int nextAnimation = ANIM_IDLE;
	

	// Trigger animation when first executing the action
	bool toTriggerAnimation = true;

};

