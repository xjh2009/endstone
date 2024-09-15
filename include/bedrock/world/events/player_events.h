// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "bedrock/deps/json/value.h"
#include "bedrock/entity/gamerefs_entity/gamerefs_entity.h"
#include "bedrock/gameplayhandlers/coordinator_result.h"
#include "bedrock/gamerefs/weak_ref.h"
#include "bedrock/world/events/event_variant.h"

template <std::size_t N>
struct PlayerEventPlaceHolder {  // To ensure our variant is initialised with correct storage size
    char pad[N];
};

struct PlayerSkinLoadedClientEvent {};
struct PlayerAddEvent {};
struct PlayerAddExpEvent {};
struct PlayerAddLevelEvent {};
struct PlayerArmorExchangeEvent {};
struct PlayerDestroyBlockEvent {};
struct PlayerUseNameTagEvent {};
struct PlayerDropItemEvent {};
struct PlayerEatFoodEvent {};
struct PlayerDamageEvent {};
struct PlayerDisconnectEvent {};

enum class PlayerFormCloseReason : int {
    UserClosed = 0,
    UserBusy = 1
};

struct PlayerFormCloseEvent {
    WeakRef<EntityContext> player;
    int form_id;
    PlayerFormCloseReason form_close_reason;
};

struct PlayerFormResponseEvent {
    WeakRef<EntityContext> player;
    int form_id;
    Json::Value form_response;
};

struct PlayerInitialSpawnEvent {};
struct PlayerOpenContainerEvent {};
struct PlayerShootArrowEvent {};
struct PlayerRespawnEvent {};
struct PlayerStopLoadingEvent {};
struct PlayerUpdateInteractionEvent {};
struct PlayerSelectedItemChangedEvent {};
struct PlayerDimensionChangeBeforeEvent {};
struct PlayerDimensionChangeAfterEvent {};
struct PlayerInteractWithEntityAfterEvent {};
struct PlayerInteractWithBlockAfterEvent {};
struct PlayerInputPermissionCategoryChangeEvent {};

struct PlayerSayCommandEvent {};
struct PlayerGetExperienceOrbEvent {};
struct PlayerInteractEvent {};
struct PlayerInteractWithEntityBeforeEvent {};
struct PlayerInteractWithBlockBeforeEvent {};

template <typename Return>
struct PlayerGameplayEvent;

template <>
struct PlayerGameplayEvent<void>
    : ConstEventVariant<
          PlayerSkinLoadedClientEvent, PlayerAddEvent, PlayerAddExpEvent, PlayerAddLevelEvent, PlayerArmorExchangeEvent,
          PlayerDestroyBlockEvent, PlayerUseNameTagEvent, PlayerDropItemEvent, PlayerEatFoodEvent, PlayerDamageEvent,
          PlayerDisconnectEvent, PlayerFormCloseEvent, PlayerFormResponseEvent, PlayerInitialSpawnEvent,
          PlayerOpenContainerEvent, PlayerShootArrowEvent, PlayerRespawnEvent, PlayerStopLoadingEvent,
          PlayerUpdateInteractionEvent, PlayerSelectedItemChangedEvent, PlayerDimensionChangeBeforeEvent,
          PlayerDimensionChangeAfterEvent, PlayerInteractWithEntityAfterEvent, PlayerInteractWithBlockAfterEvent,
          PlayerInputPermissionCategoryChangeEvent, PlayerEventPlaceHolder<352>> {};

template <>
struct PlayerGameplayEvent<CoordinatorResult>
    : ConstEventVariant<PlayerSayCommandEvent, PlayerGetExperienceOrbEvent, PlayerInteractEvent,
                        PlayerInteractWithEntityBeforeEvent, PlayerInteractWithBlockBeforeEvent,
                        PlayerEventPlaceHolder<208>> {};

struct PlayerGameModeChangeEvent {};

template <typename Return>
struct MutablePlayerGameplayEvent;
template <>
struct MutablePlayerGameplayEvent<CoordinatorResult>
    : MutableEventVariant<PlayerGameModeChangeEvent, PlayerEventPlaceHolder<32>> {};
