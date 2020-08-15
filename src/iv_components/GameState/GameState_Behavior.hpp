#pragma once

#include "GameState.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup GameState
*/
class GameState_Behavior
{
public:
iv::ClientMarker cm;
    GameState_Behavior( iv::Instance * inst, GameState * m_game );
    
private:
    GameState * m_game;
    iv::FunctorActivatorField on_restart;
    iv::FunctorActivatorField on_end;
    iv::FunctorField< bool > on_pause;
};

}
