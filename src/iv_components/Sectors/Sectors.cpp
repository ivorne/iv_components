#include "Sectors.hpp"

namespace comp
{

Sectors::Listener::Listener( iv::Instance * inst, Sectors * sectors ) :
    cm( inst, this, "Blocks::Listener" ),
    inst( inst ),
    sectors( sectors )
{
    this->sectors->AddListener( this );
}

Sectors::Listener::~Listener()
{
    this->sectors->RemoveListener( this );
}

iv::Instance * Sectors::Listener::instance() const
{
    return this->inst;
}

void Sectors::Load( iv::ClientMarker * modifier, iv::int2 block )
{
    for( Listener * listener : this->listeners )
        listener->Sector_Load( block );
}

void Sectors::Unload( iv::ClientMarker * modifier, iv::int2 block )
{
    for( Listener * listener : this->listeners )
        listener->Sector_Unload( block );
}

void Sectors::AddListener( Listener * listener )
{
    this->listeners.insert( listener );
}

void Sectors::RemoveListener( Listener * listener )
{
    this->listeners.erase( listener );
}

}
