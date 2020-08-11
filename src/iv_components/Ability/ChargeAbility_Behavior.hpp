#pragma once

#include "Ability_Behavior.hpp"

namespace comp
{

/**
    Each use of the ability depletes one charge from the model given in constructor.
    Ability gets disabled and can not be activated when charges are on 0.
    Does not provide any mechanism for refilling charges (that must be provided by another behavior).
*/
class ChargeAbility_Behavior : public Ability_Behavior
{
public:
iv::ClientMarker cm;
    ChargeAbility_Behavior( iv::Instance * inst, Ability * m_ability, iv::Attr< int > * m_charges );
    
protected:
    // ChargeAbility_Behavior
    virtual void ChargeAbilityActivated() = 0;
    
    // Ability_Behavior
    virtual void AbilityActivated() override;
    
private:
    iv::Attr< int > *       m_charges;
    iv::FunctorField< int > field_charges;
};

}
