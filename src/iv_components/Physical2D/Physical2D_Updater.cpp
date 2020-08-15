#include "Physical2D_Updater.hpp"
#include "../Defs.hpp"

namespace comp
{

Physical2D_Updater::Physical2D_Updater( iv::Instance * inst, Physical2D_World * world ) :
    iv::FixedUpdateClient( inst, ::comp::Defs::Time::Physics ),
    cm( inst, this, "Physical2D_Updater" ),
    world( world )
{
    this->cm.inherits( this->iv::FixedUpdateClient::cm );
}

void Physical2D_Updater::fixed_update( iv::TimeId time, int time_step, int steps ) 
{
    for( size_t i = 0; i < steps; i++ )
        this->world->Step( float( time_step ) / 1000.0f );
}


}
