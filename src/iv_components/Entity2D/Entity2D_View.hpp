#pragma once

#include "Entity2D.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    Not yet implemented.
*/
class Entity2D_View : public iv::SlotChild
{
public:
iv::ClientMarker cm;
    
    /**
    */
    Entity2D_View( iv::Instance * inst );
    
    /**
        View type requirements:
            class View : public iv::SlotChild
            {
            public:
                View( Entity2D * m_entity );
            };
    */
    template< class View >
    void register_view( Entity2D_TypeId );
    
};

}
