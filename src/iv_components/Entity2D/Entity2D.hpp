#pragma once

#include <ivorium.hpp>
#include <unordered_set>

namespace comp
{

class Entity2D_World;

//------------- Entity2D_TypeId -------------------------------------------------
/**
    \ingroup Entity2D
*/
class Entity2D_TypeId final : public iv::RuntimeId< Entity2D_TypeId >
{
public:
    static constexpr char TypeName[] = "Entity2D_TypeId";
    static iv::RuntimeIdDictionary Dictionary;
    using iv::RuntimeId< Entity2D_TypeId >::RuntimeId;
};

//------------- Entity2D -------------------------------------------------
/**
    \ingroup Entity2D
*/
class Entity2D
{
public:
                                        Entity2D( iv::ClientMarker * owner );
                                        ~Entity2D();
                                        
    void                                Register( Entity2D_World * world );
    void                                Unregister();
    
    iv::ClientMarker *                  owner();
    bool                                registered();
    Entity2D_World *                    world();
    
    // identity - do not change on registered entity
    Entity2D_TypeId                     type;
    iv::VLink                           v_entity;
    
    // state
    iv::ComponentAttr< Entity2D, iv::float2 > position;
    
private:
    iv::ClientMarker * cm;
    Entity2D_World * _world;
};

//------------- Entity2D_Listener -------------------------------------------------
/**
    \ingroup Entity2D
    Do not forget to call this->Entity2D_Listener::Initialize(), it will call Entity2D_Registered for all existing entities.
*/
class Entity2D_Listener : public iv::GenericListener< Entity2D_Listener >
{
public:
iv::ClientMarker cm;
    
                            Entity2D_Listener( iv::Instance * inst, Entity2D_World * world );

    virtual void            Entity2D_Registered( Entity2D * ){}
    virtual void            Entity2D_Unregistered( Entity2D * ){}
    virtual void            Entity2D_Moved( Entity2D * ){}
    
private:
    iv::Instance * inst;
    Entity2D_World * world;
};

//------------- Entity2D_World -------------------------------------------------
/**
    \ingroup Entity2D
*/
class Entity2D_World : public iv::World< Entity2D >, public iv::GenericListener_Index< Entity2D_Listener >, public iv::ComponentAttr_Index< Entity2D >
{
public:
iv::ClientMarker cm;
using iv::World< Entity2D >::instance;
    
                            Entity2D_World( iv::Instance * inst );
    
protected:
    // iv::GenericListener_Index< Entity2D_Listener >
    virtual void Listener_Initialize( Entity2D_Listener * ) override;
    
    // iv::World< Entity2D >
    virtual void Component_Registered( Entity2D * entity ) override;
    virtual void Component_Unregistered( Entity2D * entity ) override;
    
    // iv::ComponentAttr_Index< Entity2D >
    virtual void Component_AttrChanged( Entity2D * entity, iv::Attribute * attr ) override;
};

}

namespace std
{
template<> struct hash< comp::Entity2D_TypeId > : public iv::hash< comp::Entity2D_TypeId >{};
}
