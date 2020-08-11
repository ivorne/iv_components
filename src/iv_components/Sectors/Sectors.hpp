#pragma once

#include <ivorium.hpp>
#include <unordered_set>

namespace comp
{

class Sectors
{
public:
    class Listener
    {
    public:
    iv::ClientMarker cm;
                                Listener( iv::Instance * inst, Sectors * sectors );
                                ~Listener();
        iv::Instance *          instance() const;
        
        virtual void            Sector_Load( iv::int2 block ) = 0;
        virtual void            Sector_Unload( iv::int2 block ) = 0;
        
    private:
        iv::Instance * inst;
        Sectors * sectors;
    };
    
public:
    void            AddListener( Listener * );
    void            RemoveListener( Listener * );
    
    void            Load( iv::ClientMarker * behavior, iv::int2 );
    void            Unload( iv::ClientMarker * behavior, iv::int2 );
    
private:
    std::unordered_set< Listener * > listeners;
};

}
