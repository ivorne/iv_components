#pragma once

#include <ivorium.hpp>

namespace comp
{

class GameState
{
public:
    enum class State
    {
        Empty,      ///< No game was run before.
        Running,    ///< Game is actively running.
        Paused,     ///< Game was started and then paused.
        Ended       ///< Existing game ended.
    };
    
public:
iv::ClientMarker cm;
                                        GameState( iv::Instance * inst );
    iv::Instance *                      instance();

    // write
    iv::SharedAttr< iv::Activator >     restart;
    iv::SharedAttr< iv::Activator >     end;
    iv::SharedAttr< bool >              pause;
    
    // read
    iv::SharedAttr< State >             game_state;
};

}

//------------------- StringIO --------------------
namespace iv
{
template<>
struct StringIO< comp::GameState::State > : public StringIO_Table< comp::GameState::State >
{
    static const ValuesType Values;
};
}
