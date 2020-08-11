#include "Ability.hpp"

namespace comp
{

Ability::Ability( iv::Instance * inst ) :
    cm( inst, this, "Ability" ),
    cooldown( &this->cm ),
    activator( &this->cm )
{
}

iv::Instance * Ability::instance() const
{
    return this->cm.instance();
}

}
