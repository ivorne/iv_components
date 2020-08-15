#include "Entity2D.hpp"

namespace comp
{

//------------- Entity2D_TypeId --------------------------------------------------
iv::RuntimeIdDictionary Entity2D_TypeId::Dictionary;

//------------- Entity2D ---------------------------------------------------------
Entity2D::Entity2D( iv::ClientMarker * cm ) :
    type( Entity2D_TypeId() ),
    v_entity( iv::VLink() ),
    position( cm, iv::float2( 0, 0 ) ),
    cm( cm ),
    _world( nullptr )
{
}

Entity2D::~Entity2D()
{
    this->Unregister();
}

void Entity2D::Register( Entity2D_World * world )
{
    if( this->_world )
    {
        this->owner()->warning( SRC_INFO, "This Entity2D is already registered to a world." );
        return;
    }
    
    this->position.Index( this, world );
    
    this->_world = world;
    this->_world->Register( this );
}

void Entity2D::Unregister()
{
    if( !this->_world )
        return;
    
    this->_world->Unregister( this );
    this->_world = nullptr;
    
    this->position.Index();
}

bool Entity2D::registered()
{
    return this->_world;
}

Entity2D_World * Entity2D::world()
{
    return this->_world;
}

iv::ClientMarker * Entity2D::owner()
{
    return this->cm;
}

//------------- Entity2D_Listener -------------------------------------------------
Entity2D_Listener::Entity2D_Listener( iv::Instance * inst, Entity2D_World * world ) :
    iv::GenericListener< Entity2D_Listener >( inst, world ),
    cm( inst, this, "Entity2D_Listener" )
{
    this->cm.inherits( this->iv::GenericListener< Entity2D_Listener >::cm );
}

//------------- Entity2D_World -------------------------------------------------
Entity2D_World::Entity2D_World( iv::Instance * inst ) :
    iv::World< Entity2D >( inst ),
    iv::GenericListener_Index< Entity2D_Listener >( inst ),
    iv::ComponentAttr_Index< Entity2D >( inst ),
    cm( inst, this, "Entity2D_World" )
{
    this->cm.inherits( this->iv::GenericListener_Index< Entity2D_Listener >::cm, this->iv::World< Entity2D >::cm, this->iv::ComponentAttr_Index< Entity2D >::cm );
}

void Entity2D_World::Listener_Initialize( Entity2D_Listener * listener )
{
    for( Entity2D * component : this->components() )
        listener->Entity2D_Registered( component );
}

void Entity2D_World::Component_Registered( Entity2D * entity )
{
    this->InvokeListeners( &Entity2D_Listener::Entity2D_Registered, entity );
}

void Entity2D_World::Component_Unregistered( Entity2D * entity )
{
    this->InvokeListeners( &Entity2D_Listener::Entity2D_Unregistered, entity );
}

void Entity2D_World::Component_AttrChanged( Entity2D * entity, iv::Attribute * attr )
{
    this->InvokeListeners( &Entity2D_Listener::Entity2D_Moved, entity );
}

}
