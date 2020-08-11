#pragma once

#include <PlayRho/PlayRho.hpp>
#include "../Link.hpp"
#include "../Entity2D/Entity2D.hpp"

namespace comp
{

class Physical2D_World;

/**
    Whole PhysicalBody2D module was not yet tested.
*/
class Physical2D
{
public:
                            Physical2D( iv::ClientMarker * owner );
    
    void                    Register( Physical2D_World * world, playrho::d2::BodyConf const & conf );
    void                    Unregister();
    
    iv::ClientMarker *      owner();
    bool                    registered();
    Physical2D_World *      world();
    
    //-------------------------------------------
    /**
    */
    Link< Entity2D >        entity;
    
    /**
        Instantiated during registration to Physical2D_World, deinstantiated during unregistration from Physical2D_World.
    */
    playrho::d2::Body *     body;
    
private:
    iv::ClientMarker * cm;
    Physical2D_World * _world;
};

/**
    Do not forget to call this->comp::Physical2D_Listener::Initialize(), it will suppress warning about missing initialization (but it does nothing else in this case :-) ).
*/
class Physical2D_Listener : public GenericListener< Physical2D_Listener >
{
public:
iv::ClientMarker cm;
                        Physical2D_Listener( iv::Instance * inst, Physical2D_World * world );
    
    // PhysicalBody2D_Listener
    virtual void        PhysicalBody2D_BeginContact( Physical2D * a, Physical2D * b ) = 0;
    virtual void        PhysicalBody2D_EndContact( Physical2D * a, Physical2D * b ) = 0;
};

/**
*/
class Physical2D_World : public World< Physical2D >, public GenericListener_Index< Physical2D_Listener >, protected playrho::d2::ContactListener
{
public:
iv::ClientMarker cm;
    
                        Physical2D_World( iv::Instance * inst );
    
    void                Step( float timeStep );
    
    /**
        \p component Component that will be notified when contacts happen.
    */
    playrho::d2::Body * CreateBody( Physical2D * component, playrho::d2::BodyConf const & conf );
    void                DestroyBody( playrho::d2::Body * );
    
protected:
    // core::World< Entity2D >
    virtual void        Component_Registered( Physical2D * component ) override;
    virtual void        Component_Unregistered( Physical2D * component ) override;
    
    // playrho::d2::ContactListener
    virtual void        BeginContact( playrho::d2::Contact & contact ) override;
    virtual void        EndContact( playrho::d2::Contact & contact ) override;
    
private:
    playrho::d2::World world;
};

}
