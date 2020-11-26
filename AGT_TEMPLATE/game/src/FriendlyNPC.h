#pragma once
#include <engine.h>
#include "AnimationHandler.h"
#include "player.h"

class FriendlyNPC {
public:
    FriendlyNPC();
    ~FriendlyNPC();

    // Initialise the NPC
    void initialise();
    void talk();

    void onUpdate(const engine::timestep& timestep, Player& player);

    void playDialogue() const;


    float dialogueTimer1() const { return mDialogueTimer; }
    void setMDialogueTimer(float mDialogueTimer) { this->mDialogueTimer = mDialogueTimer; }
    void progress();

    //getters/setters
    engine::ref<engine::game_object> object() { return mObject; }
    // void setMObject(const engine::ref<engine::game_object>& mObject) { this->mObject = mObject; }


private:
    engine::ref<engine::game_object> mObject;
    engine::ref<engine::audio_manager> mAudioManager {};
	engine::ref<engine::skinned_mesh>	npcMesh;

    bool isYes = true;
    bool isNo = false;
    bool isBossBeaten = false;
    bool toPLayDialogue = false;
    
    float mDialogueTimer = 0.f;
    std::string dialoguePath = "greeting";
    int         dialogueNumber = 1;

};