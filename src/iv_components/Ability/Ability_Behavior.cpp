#include "Ability_Behavior.hpp"

namespace comp
{

Ability_Behavior::Ability_Behavior( iv::Instance * inst, Ability * m_ability ) :
    cm( inst, this, "Ability_Behavior" ),
    inst( inst ),
    m_ability( m_ability ),
    field_activate( inst )
{
    this->cm.owns( this->field_activate.cm );
    
    this->m_ability->activator.ModifyMode( &this->cm, iv::Attribute::ValueMode::Disabled );
    
    this->field_activate.Assign_Attribute_R( &m_ability->activator );
    this->field_activate.on_activated(
        [ this ]()
        {
            this->AbilityActivated();
        }
    );
}

iv::Instance * Ability_Behavior::instance() const
{
    return this->inst;
}

Ability * Ability_Behavior::ability()
{
    return this->m_ability;
}

void Ability_Behavior::AbilityEnable( bool enabled )
{
    if( enabled )
        this->m_ability->activator.ModifyMode( &this->cm, iv::Attribute::ValueMode::ValueModify );
    else
        this->m_ability->activator.ModifyMode( &this->cm, iv::Attribute::ValueMode::Disabled );
}

}
