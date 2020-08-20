#pragma once

#include "Sectors.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Sectors
    \brief Keeps sectors in range loaded. Needs to be updated from a simulaiton (Sectors_Loader::update).
*/
class Sectors_Loader
{
public:
iv::ClientMarker cm;

                                            Sectors_Loader( iv::Instance * inst, Sectors * sectors, iv::Attr< iv::float2 > * position, float load_range, int sector_size );
    iv::Instance *                          instance();
    
    /**
        Polls current position, unloads out of reach sectors and loads sectors that are now in reach.
    */
    void                                    update();
    
private:
    void                                    Load( iv::int2 block );
    void                                    Unload( iv::int2 block );
    
private:
    Sectors * sectors;
    iv::Attr< iv::float2 > * position;
    float load_range;
    int sector_size;
    
    iv::int2 current_begin;
    iv::int2 current_end;
};

}
