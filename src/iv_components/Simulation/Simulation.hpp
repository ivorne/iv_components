#pragma once

#include "SimulationState.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Simulation
*/
class Simulation : private iv::FixedUpdateClient
{
public:
iv::ClientMarker cm;

                        Simulation( iv::Instance * inst, SimulationState * state, iv::TimeId time_id );
    
    virtual void        simulation_reset() = 0;                 ///< Called before first simulation_step, so we do not need to initialize members in the constructor as well.
    virtual void        simulation_step( int step_ms ) = 0;     ///< Not called when the simulation is paused.
    
private:
    virtual void        fixed_update( iv::TimeId time, int time_step, int steps ) override;
    
private:
    SimulationState * state;
    iv::FunctorActivatorField on_restart;
    iv::FunctorActivatorField on_end;
    iv::FunctorField< bool > on_pause;
    bool needs_reset;
};

}
