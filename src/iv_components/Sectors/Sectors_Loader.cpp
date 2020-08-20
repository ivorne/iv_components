#include "Sectors_Loader.hpp"
#include "../Defs.hpp"

using namespace iv;

namespace comp
{

Sectors_Loader::Sectors_Loader( iv::Instance * inst, Sectors * sectors, iv::Attr< iv::float2 > * position, float load_range, int sector_size ) :
    cm( inst, this, "Sectors_Loader" ),
    sectors( sectors ),
    position( position ),
    load_range( load_range ),
    sector_size( sector_size ),
    current_begin( 0, 0 ),
    current_end( 0, 0 )
{
}

iv::Instance * Sectors_Loader::instance()
{
    return this->cm.instance();
}

void Sectors_Loader::Load( iv::int2 block )
{
    this->cm.log( SRC_INFO, ::comp::Defs::Log::Sectors, "Load block ", block, "." );
    this->sectors->Load( &this->cm, block );
}

void Sectors_Loader::Unload( iv::int2 block )
{
    this->cm.log( SRC_INFO, ::comp::Defs::Log::Sectors, "Unload block ", block, "." );
    this->sectors->Unload( &this->cm, block );
}

void Sectors_Loader::update()
{
    //--------------------- compute block ranges --------------------------------
    auto center_position = this->position->Get();
    
    int2 current_begin = this->current_begin;
    int2 current_end = this->current_end;
    int2 target_begin = sig_div( int2( center_position - float2( this->load_range, this->load_range ) ), this->sector_size );
    int2 target_end = sig_div( int2( center_position + float2( this->load_range, this->load_range ) ), this->sector_size );
    
    int max_begin_x = std::max( current_begin.x, target_begin.x );
    int min_end_x = std::min( current_end.x, target_end.x );
    
    //--------------------- unload blocks -------------------
    // left unload
    for( int x = current_begin.x; x < std::min( current_end.x, target_begin.x ); x++ )
        for( int y = current_begin.y; y < current_end.y; y++ )
            this->Unload( int2( x, y ) );
    
    // right unload
    for( int x = std::max( target_end.x, current_begin.x ); x < current_end.x; x++ )
        for( int y = current_begin.y; y < current_end.y; y++ )
            this->Unload( int2( x, y ) );
    
    // top unload
    for( int y = current_begin.y; y < std::min( current_end.y, target_begin.y ); y++ )
        for( int x = max_begin_x; x < min_end_x; x++ )
            this->Unload( int2( x, y ) );
    
    // bottom unload
    for( int y = std::max( target_end.y, current_begin.y ); y < current_end.y; y++ )
        for( int x = max_begin_x; x < min_end_x; x++ )
            this->Unload( int2( x, y ) );
    
    //------------------ load blocks -----------------------
    // left load
    for( int x = target_begin.x; x < std::min( target_end.x, current_begin.x ); x++ )
        for( int y = target_begin.y; y < target_end.y; y++ )
            this->Load( int2( x, y ) );
    
    // right load
    for( int x = std::max( current_end.x, target_begin.x ); x < target_end.x; x++ )
        for( int y = target_begin.y; y < target_end.y; y++ )
            this->Load( int2( x, y ) );
    
    // top load
    for( int y = target_begin.y; y < std::min( target_end.y, current_begin.y ); y++ )
        for( int x = max_begin_x; x < min_end_x; x++ )
            this->Load( int2( x, y ) );
    
    // bottom load
    for( int y = std::max( current_end.y, target_begin.y ); y < target_end.y; y++ )
        for( int x = max_begin_x; x < min_end_x; x++ )
            this->Load( int2( x, y ) );
    
    //------------------ store new state ----------------
    this->current_begin = target_begin;
    this->current_end = target_end;
}

}
