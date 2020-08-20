#pragma once

#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Simulation
*/
class SimulationState
{
public:
    enum State
    {
        Empty,      ///< No game was run before.
        Running,    ///< Game is actively running.
        Paused,     ///< Game was started and then paused.
        Ended       ///< Existing game ended.
    };
    
public:
iv::ClientMarker cm;
                                        SimulationState( iv::Instance * inst );
    iv::Instance *                      instance();

    // write
    iv::SharedAttr< iv::Activator >     restart;
    iv::SharedAttr< iv::Activator >     end;
    iv::SharedAttr< bool >              pause;
    
    // read
    iv::SharedAttr< State >             state;
    
    //
    iv::SharedAttr< long >              time_ms;
};

}

//------------------- StringIO --------------------
namespace iv
{
template<>
struct StringIO< comp::SimulationState::State > : public StringIO_Table< comp::SimulationState::State >
{
    static const ValuesType Values;
};
}
