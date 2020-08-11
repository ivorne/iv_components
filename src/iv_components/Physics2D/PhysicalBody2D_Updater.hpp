#pragma once

#include "PhysicalBody2D.hpp"
#include <ivorium.hpp>

namespace comp
{


class PhysicalBody2D_Updater : public iv::FixedUpdateClient
{
public:
iv::ClientMarker cm;
using iv::FixedUpdateClient::instance;

                        PhysicalBody2D_Updater( iv::Instance * inst, Physical2D_World * world );
    
protected:
    virtual void        fixed_update( iv::TimeId time, int time_step, int steps ) override;
    
private:
    Physical2D_World * world;
};

}
