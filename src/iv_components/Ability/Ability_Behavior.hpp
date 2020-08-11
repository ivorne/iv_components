#pragma once

#include "Ability.hpp"
#include <ivorium.hpp>

namespace comp
{

/**
    Allows implementors to make the ability either enabled or disabled, depending on outside conditions.
    Method AbilityActivated is called when activation of the ability is requested by the user.
*/
class Ability_Behavior
{
public:
iv::ClientMarker cm;

                            Ability_Behavior( iv::Instance *, Ability * m_ability );
    iv::Instance *          instance() const;
    
protected:
    // Ability_Behavior
    /**
    */
    virtual void            AbilityActivated() = 0;
    
    /**
    */
    void                    AbilityEnable( bool );
    
    /**
    */
    Ability *               ability();
    
private:
    iv::Instance * inst;
    Ability * m_ability;
    iv::FunctorActivatorField field_activate;
};

}
