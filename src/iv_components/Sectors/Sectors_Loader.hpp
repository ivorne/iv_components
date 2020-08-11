#pragma once

#include "Sectors.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
*/
class Sectors_Loader : public iv::FrameUpdateClient
{
public:
using iv::FrameUpdateClient::instance;
iv::ClientMarker cm;

                                            Sectors_Loader( iv::Instance * inst, Sectors * sectors, iv::Attr< iv::float2 > * position, float load_range, int sector_size );
    
protected:
    virtual void                            frame_update() override final;
    
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
