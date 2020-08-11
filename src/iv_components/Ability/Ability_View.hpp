#pragma once

#include "Ability.hpp"
#include <ivorium.hpp>

namespace comp
{

struct AbilityInfo
{
    iv::ResourcePath overlay;
};

class Ability_View : public iv::LumaButton
{
public:
iv::ClientMarker cm;
using iv::LumaButton::instance;
    
    /**
    */
    Ability_View( iv::Instance * inst, Ability * m_ability, AbilityInfo info );
    
private:
    Ability * m_ability;
};

}
