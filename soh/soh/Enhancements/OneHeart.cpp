#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "z64save.h"

extern "C" SaveContext gSaveContext;

#define CVAR_ONE_HEART_NAME CVAR_ENHANCEMENT("OneHeartChallenge")
#define CVAR_ONE_HEART_DEFAULT 0
#define CVAR_ONE_HEART_VALUE CVarGetInteger(CVAR_ONE_HEART_NAME, CVAR_ONE_HEART_DEFAULT)

void OnGameFrameUpdateOneHeart() {
    if (!GameInteractor::IsSaveLoaded(true)) {
        return;
    }

    if (gSaveContext.health > FULL_HEART_HEALTH) {
        gSaveContext.health = FULL_HEART_HEALTH;
    }

    if (gSaveContext.healthCapacity > FULL_HEART_HEALTH) {
        gSaveContext.healthCapacity = FULL_HEART_HEALTH;
    }
}

void RegisterOneHeart() {
    COND_HOOK(OnGameFrameUpdate, CVAR_ONE_HEART_VALUE, OnGameFrameUpdateOneHeart);
}

static RegisterShipInitFunc initFunc(RegisterOneHeart, { CVAR_ONE_HEART_NAME });
