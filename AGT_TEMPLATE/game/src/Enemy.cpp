#include "Enemy.h"


Enemy::Enemy() {
    // Initialise the animated mesh
    enemyMesh = engine::skinned_mesh::create("assets/models/animated/minotaur/Mesh.FBX");
    enemyMesh->LoadAnimationFile("assets/models/animated/minotaur/Minotaur@Idle.FBX");
    enemyMesh->LoadAnimationFile("assets/models/animated/minotaur/Minotaur@Walk.FBX");
    enemyMesh->LoadAnimationFile("assets/models/animated/minotaur/Minotaur@Attack.FBX");
    // enemyMesh->LoadAnimationFile("assets/models/animated/minotaur/Minotaur@Death1.FBX");
    // enemyMesh->LoadAnimationFile("assets/models/animated/minotaur/Minotaur@Get_Hit.FBX");
    enemyMesh->LoadAnimationFile("assets/models/animated/minotaur/Minotaur@Shout.FBX");
}


Enemy::~Enemy() = default;

void Enemy::initialise() {
    engine::game_object_properties enemyProps;
    enemyProps.animated_mesh = enemyMesh;
    enemyProps.textures = {engine::texture_2d::create("assets/models/animated/minotaur/Minotaur_diffuse.tga", false)};
    enemyProps.type = 0;
    enemyProps.bounding_shape = glm::vec3(.5f);
    mObject = engine::game_object::create(enemyProps);
    mObject->set_scale(glm::vec3(3.f));
    // mObject->set_offset(enemyMesh->offset());
    mObject->setName("enemy");
    // Set the positions of the animations based on the order they are loaded into the mesh
    animationHandler = AnimationHandler(mObject);
    animationHandler.setIdleAnim(0);
    animationHandler.setAnimWalk(1);
    animationHandler.setAnimAttack(2);
    // animationHandler.setAnimDeath(3);
    // animationHandler.setAnimGetHit(4);
    animationHandler.setAnimShout(3);
}

void Enemy::setRandomPosition() const {
    const float x = (rand() % 100) / 10;
    // const float y = (rand() % 100)/10;
    const float z = (rand() % 100) / 10;

    mObject->set_position(glm::vec3(x, 0.5f, z));
}


void Enemy::setRandomScale() {
    const float scale = (rand() % 30 + 10) / 10;
    mObject->set_scale(glm::vec3(scale));
    maxSize = 2.f * scale;
}

void Enemy::setFixedScale() {
    const float scale = 1.f;
    mObject->set_scale(glm::vec3(scale));
    maxSize = 1.5f * scale;
}

void Enemy::setEnemyType() {
    const int randNum = rand() % 100 + 1;
    if (randNum % TYPE_SHOUTER == 0) {
        enemyType = TYPE_SHOUTER;
    }
    if (randNum % TYPE_TRACKER == 0) {
        enemyType = TYPE_TRACKER;
    }
    if (randNum % TYPE_JUMPER == 0) {
        enemyType = TYPE_JUMPER;
    }

    if (enemyType != 0)
        enemyType = TYPE_WALKER;
}

void Enemy::setEnemyType(const int type) {
    enemyType = type;
}

void Enemy::onUpdate(const engine::timestep& timestep, Player& player) {

    // turn towards the player
    const glm::vec3 v = player.object()->position() - mObject->position();
    const float theta = atan2(v.x, v.z);


    // Animation Handler handles the current animation that needs to be played
    animationHandler.onUpdate(timestep);

    //check distance from player and stop walking and shout at the player (2.f currently)
    auto d = mObject->position() - player.object()->position();
    const int randomNo = rand() % 100;


    if (glm::length(d) < 1.5f) {
        if(player.getIsSwordSwinging()) {
            die();
        }
    }

    switch (mState) {

    case State::IDLE:
        idle();
        // if in shout range
        if (glm::length(d) < 2.f) {
            // the animation duration is being returned in frames, so i divided it by 30 to get the answer in seconds as then i can accurately get the timer
            mShoutTimer = static_cast<float>(mObject->animated_mesh()->animations().at(animationHandler.animShout())->mDuration) / 30.f;
            // isInShoutRange = true;
            mState = State::SHOUT;
        }
        else if (glm::length(d) < agroRange) {
            // move the enemy
            mState = State::WALK;
        }
        mObject->set_angular_velocity(glm::vec3(0.f));
        break;

    case State::WALK:
        // if in shout range
        if (glm::length(d) < 2.f) {
            // the animation duration is being returned in frames, so i divided it by 30 to get the answer in seconds as then i can accurately get the timer
            mShoutTimer = static_cast<float>(mObject->animated_mesh()->animations().at(animationHandler.animShout())->mDuration) / 30.f;
            // isInShoutRange = true;
            mState = State::SHOUT;
        }
        else if (glm::length(d) > agroRange)
            mState = State::IDLE;

        turn(theta);
        walk(timestep, player);
        break;

    case State::SHOUT: // shout and turn
        turn(theta);
        shout();
        // state will be changed to attack after the animation for shouting has finished
        break;

    case State::ATTACK:
        turn(theta);
        attack();
        // add 5% chance of the player getting hit
        if(randomNo<=5) {
            player.getHit(5); // do 5hp damage to the player
        }

        // walk if the player is too far away to hit
        if (glm::length(d) >= 2.f) {
            mState = State::WALK;
        }
        break;
    case State::DIE: break; // unimplemented as no space to add the death animation
    default: break;
    }


    // Handling the timer for the shout/grow then attack
    if (mShoutTimer > 0.f) {
        mShoutTimer -= static_cast<float>(timestep);
        const float scale = 1.f + timestep; // scalar factor when the enemy grows
        if (!((mObject->scale() *= scale).x > maxSize))
            mObject->set_scale(mObject->scale() *= (1.f + timestep));
        if (mShoutTimer <= 0.f) {
            // toAttack = true;
            mState = State::ATTACK; // set the state to attack after shouting has finished
        }
    }

}


// calculate the speed based on the size of the enemy
float Enemy::calculateSpeed(bool isWalking) const {
    if (isWalking)
        return mSpeed / (mObject->scale().x + 2.f);
    else
        return mSpeed;
}


// Turn Enemy towards the player
void Enemy::turn(float angle) {
    // mObject->set_rotation_amount(angle);
    if (angle != 0.f) {
        mObject->set_angular_velocity(glm::vec3(0.f, 2 * angle, 0.f));
    }else {
        mObject->set_angular_velocity(glm::vec3(0.f));
    }

    angleFromPlayer = angle;
}

// play the idle animation and set the velocity to 0
void Enemy::idle() {
    animationHandler.nextAnimation(animationHandler.animIdle());
    mObject->set_velocity(glm::vec3(0.f));
}

// walk the enemy in relation to the player
void Enemy::walk(engine::timestep timestep, const Player& player) {
    // tell the animation handler that the next animation will be a walking animation
    animationHandler.nextAnimation(animationHandler.animWalk());

    // calculate the direction vector to walk towards the player
    const glm::vec3 directionVector = glm::normalize(player.object()->position() - mObject->position());

    // move the game object
    // mObject->set_position(mObject->position() += directionVector * glm::vec3(timestep) * calculateSpeed(true)); // old method of moving
    mObject->set_velocity(directionVector * 2.f*  calculateSpeed(true));
}


// play the attack animation // will be expanded to contain collisions.
void Enemy::attack() {
    animationHandler.nextAnimation(animationHandler.animAttack());
}

// play the death animation and also will handle turning into a ragdoll
void Enemy::die() {
    // animationHandler.nextAnimation(animationHandler.animDeath()); // animation for death has been removed
    isDead = true;
}

// play the shout animation
void Enemy::shout() {
    // play the shout animation
    animationHandler.nextAnimation(animationHandler.animShout());
}
