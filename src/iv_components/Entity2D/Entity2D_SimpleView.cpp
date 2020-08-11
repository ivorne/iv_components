#include "Entity2D_SimpleView.hpp"

namespace comp
{

Entity2D_SimpleView_Item::Entity2D_SimpleView_Item( iv::Instance * inst ) :
    iv::Transform( inst ),
    cm( inst, this, "Entity2D_SimpleView_Item" ),
    img( inst )
{
    this->cm.inherits( this->iv::Transform::cm );
    this->cm.owns( this->img.cm );
    
    this->setChild( &this->img );
    this->img.filename( "/CoreModels/Entity2D/SimpleView.png" );
    this->img.translucent( true );
}

Entity2D_SimpleView::Entity2D_SimpleView( iv::Instance * inst, Entity2D_World * world ) :
    iv::Slot( inst ),
    iv::FrameUpdateClient( inst ),
    Entity2D_Listener( inst, world ),
    cm( inst, this, "Entity2D_SimpleView" ),
    heap( inst, &this->cm )
{
    this->cm.inherits( this->iv::Slot::cm, this->iv::FrameUpdateClient::cm, this->Entity2D_Listener::cm );
    
    this->Entity2D_Listener::Initialize();
}

void Entity2D_SimpleView::frame_update()
{
    for( auto & [ entity, item ] : this->entities )
    {
        iv::float2 pos = entity->position.Get();
        item->position( iv::float3( pos.x, pos.y, 0.0f ) );
    }
}

void Entity2D_SimpleView::Entity2D_Registered( Entity2D * entity )
{
    if( this->entities.count( entity ) )
    {
        this->cm.warning( SRC_INFO, "Entity already registered." );
        return;
    }
    
    auto item = this->heap.createClient< Entity2D_SimpleView_Item >();
    this->pushChild( item );
    this->entities[ entity ] = item;
}

void Entity2D_SimpleView::Entity2D_Unregistered( Entity2D * entity )
{
    auto item = this->entities[ entity ];
    this->removeChild( item );
    this->heap.destroy( item );
    this->entities.erase( entity );
}

}
