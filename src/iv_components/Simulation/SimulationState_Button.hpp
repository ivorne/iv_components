#pragma once

#include "SimulationState.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Simulation
*/
class SimulationState_Button : public iv::LumaButton
{
public:
iv::ClientMarker cm;
using iv::LumaButton::instance;
    
                        SimulationState_Button( iv::Instance * inst, SimulationState * sim, iv::LumaStyleId style_id = iv::LumaStyleId() );
    virtual void        ColorsChanged( iv::float4 surface, iv::float4 on_surface ) override;
    
public:
    SimulationState * sim;
    iv::Heap heap;
    iv::AnimHeap anim;
    SimulationState::State previous_state;
    
    iv::Image * icon;
    iv::Image * border;
};

}
