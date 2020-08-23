#pragma once

#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Misc
*/
class AutorechargeBehavior
{
public:
iv::ClientMarker cm;
    
                            AutorechargeBehavior( iv::Instance * inst, iv::TimeId time, iv::Attr< int > * m_charges, uint64_t recharge_ms, int max );
    
    void                    reset();
    void                    step( int step_ms );
    
private:
    iv::Attr< int > *       m_charges;
    uint64_t                recharge_ms;
    int                     max;

    int                     cooldown_ms;
};

}
