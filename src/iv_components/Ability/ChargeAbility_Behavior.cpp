#include "ChargeAbility_Behavior.hpp"

using namespace iv;

namespace comp
{

ChargeAbility_Behavior::ChargeAbility_Behavior( iv::Instance * inst, Ability * m_ability, iv::Attr< int > * m_charges ) :
    Ability_Behavior( inst, m_ability ),
    cm( inst, this, "ChargeAbility_Behavior" ),
    m_charges( m_charges ),
    field_charges( inst )
{
    this->cm.inherits( this->Ability_Behavior::cm );
    this->cm.owns( this->field_charges.cm );
    
    this->field_charges.Assign_Attribute_RW( m_charges );
    this->field_charges.OnChange(
        [ this ]( bool real )
        {
            auto charges = this->field_charges.Get();
            this->AbilityEnable( charges );
        }
    );
}

void ChargeAbility_Behavior::AbilityActivated()
{
    int charges = this->field_charges.Get();
    if( charges > 0 )
    {
        this->field_charges.Modify( charges - 1 );
        this->ChargeAbilityActivated();
    }
}

}
