#pragma once

#include "Physical2D.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Physical2D
*/
class Physical2D_Updater : public iv::FixedUpdateClient
{
public:
iv::ClientMarker cm;
using iv::FixedUpdateClient::instance;

                        Physical2D_Updater( iv::Instance * inst, Physical2D_World * world );
    
protected:
    virtual void        fixed_update( iv::TimeId time, int time_step, int steps ) override;
    
private:
    Physical2D_World * world;
};

}
