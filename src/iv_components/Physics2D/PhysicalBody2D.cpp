#include "PhysicalBody2D.hpp"

namespace comp
{

//--------------------- Physical2D -------------------------------------------------
Physical2D::Physical2D( iv::ClientMarker * owner ) :
    entity( nullptr ),
    body( nullptr ),
    cm( owner ),
    _world( nullptr )
{
}

void Physical2D::Register( Physical2D_World * world, playrho::d2::BodyConf const & conf )
{
    if( this->_world )
    {
        this->cm->warning( SRC_INFO, "This Physical2D is already registered to a world." );
        return;
    }
    
    this->_world = world;
    this->body = this->_world->CreateBody( this, conf );
    this->_world->Register( this );
}

void Physical2D::Unregister()
{
    if( !this->_world )
        return;
    
    this->_world->Unregister( this );
    this->_world->DestroyBody( this->body );
    this->body = nullptr;
    this->_world = nullptr;
}

iv::ClientMarker * Physical2D::owner()
{
    return this->cm;
}

bool Physical2D::registered()
{
    return this->_world;
}

Physical2D_World * Physical2D::world()
{
    return this->_world;
}

//--------------------- Physical2D_Listener -------------------------------------------------
Physical2D_Listener::Physical2D_Listener( iv::Instance * inst, Physical2D_World * world ) :
    GenericListener< Physical2D_Listener >( inst, world ),
    cm( inst, this, "Physical2D_Listener" )
{
    this->cm.inherits( this->GenericListener< Physical2D_Listener >::cm );
}

//--------------------- Physical2D_World -------------------------------------------------
Physical2D_World::Physical2D_World( iv::Instance * inst ) :
    World< Physical2D >( inst ),
    GenericListener_Index< Physical2D_Listener >( inst ),
    playrho::d2::ContactListener(),
    cm( inst, this, "Physical2D_World" ),
    world()
{
    this->cm.inherits( this->World< Physical2D >::cm, this->GenericListener_Index< Physical2D_Listener >::cm );
    this->world.SetContactListener( this );
}

void Physical2D_World::Step( float timeStep )
{
    playrho::StepConf conf;
    conf.SetTime( timeStep );
    this->world.Step( conf );
}

playrho::d2::Body * Physical2D_World::CreateBody( Physical2D * component, playrho::d2::BodyConf const & conf )
{
    auto body = this->world.CreateBody( conf );
    body->SetUserData( reinterpret_cast< void * >( component ) );
    return body;
}

void Physical2D_World::DestroyBody( playrho::d2::Body * body )
{
    this->world.Destroy( body );
}

void Physical2D_World::Component_Registered( Physical2D * component )
{
}

void Physical2D_World::Component_Unregistered( Physical2D * component )
{
}

void Physical2D_World::BeginContact( playrho::d2::Contact & contact )
{
    playrho::d2::Body * bodyA = contact.GetFixtureA()->GetBody();
    playrho::d2::Body * bodyB = contact.GetFixtureB()->GetBody();
    Physical2D * phyA = reinterpret_cast< Physical2D * >( bodyA->GetUserData() );
    Physical2D * phyB = reinterpret_cast< Physical2D * >( bodyB->GetUserData() );
    
    this->InvokeListeners( &Physical2D_Listener::PhysicalBody2D_BeginContact, phyA, phyB );
}

void Physical2D_World::EndContact( playrho::d2::Contact & contact )
{
    playrho::d2::Body * bodyA = contact.GetFixtureA()->GetBody();
    playrho::d2::Body * bodyB = contact.GetFixtureB()->GetBody();
    Physical2D * phyA = reinterpret_cast< Physical2D * >( bodyA->GetUserData() );
    Physical2D * phyB = reinterpret_cast< Physical2D * >( bodyB->GetUserData() );
    
    this->InvokeListeners( &Physical2D_Listener::PhysicalBody2D_EndContact, phyA, phyB );
}

}
