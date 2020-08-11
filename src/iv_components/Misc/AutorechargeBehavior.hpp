#pragma once

#include <ivorium.hpp>

namespace comp
{

class AutorechargeBehavior : private iv::FixedUpdateClient
{
public:
iv::ClientMarker cm;
    
                            AutorechargeBehavior( iv::Instance * inst, iv::TimeId time, iv::Attr< int > * m_charges, uint64_t recharge_ms, int max );
    
    // iv::FixedUpdateClient
    virtual void            fixed_update( iv::TimeId time, int time_step, int steps ) override final;
    
private:
    iv::Attr< int > *       m_charges;
    uint64_t                recharge_ms;
    int                     max;

    int                     cooldown_ms;
};

}
