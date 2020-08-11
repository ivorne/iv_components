#pragma once

#include "Entity2D.hpp"
#include <ivorium.hpp>
#include <unordered_map>

namespace comp
{

class Entity2D_SimpleView_Item : public iv::Transform
{
public:
iv::ClientMarker cm;
    
    Entity2D_SimpleView_Item( iv::Instance * inst );

private:
    iv::Image img;
};

class Entity2D_SimpleView : public iv::Slot, public iv::FrameUpdateClient, public Entity2D_Listener
{
public:
iv::ClientMarker cm;
using iv::SlotChild::instance;
    
                        Entity2D_SimpleView( iv::Instance * inst, Entity2D_World * world );
    
    virtual void        frame_update() override;
    
protected:
    virtual void        Entity2D_Registered( Entity2D * entity ) override;
    virtual void        Entity2D_Unregistered( Entity2D * entity ) override;
    
private:
    iv::Heap heap;
    std::unordered_map< Entity2D *, Entity2D_SimpleView_Item * > entities;
    
};

}
