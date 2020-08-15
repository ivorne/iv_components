#include "Defs.hpp"

namespace comp
{

namespace Defs
{

namespace Log
{
    const iv::LogId Simulation = iv::LogId::create( "Simulation" );
    const iv::LogId Sectors = iv::LogId::create( "Sectors" );

}

namespace Input
{
    const iv::InputId GameStateButtonTrigger = iv::InputId::create( "GameStateButtonTrigger" );
}

namespace Time
{
    const iv::TimeId Physics = iv::TimeId::create( "Physics" );
}

}

}
