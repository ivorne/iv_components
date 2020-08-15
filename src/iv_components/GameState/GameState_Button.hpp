#pragma once

#include "GameState.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup GameState
*/
class GameState_Button : public iv::LumaButton
{
public:
iv::ClientMarker cm;
using iv::LumaButton::instance;
    
                        GameState_Button( iv::Instance * inst, GameState * m_game, iv::LumaStyleId style_id = iv::LumaStyleId() );
    virtual void        ColorsChanged( iv::float4 surface, iv::float4 on_surface ) override;
    
public:
    GameState * m_game;
    iv::Heap heap;
    iv::AnimHeap anim;
    GameState::State previous_state;
    
    iv::Image * icon;
    iv::Image * border;
};

}
