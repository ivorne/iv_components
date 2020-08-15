#pragma once

#include <ivorium.hpp>

namespace comp
{

/**
    \ingroup Ability
    We can add various more attributes to the ability:
        - autocast
        - continuous cast enable / disable
        - channeling indication
        - charges indicator
    Has identity that informs view on what graphics and descriptions to use when displaying it.
        Behavioral identity is handled outside of this model - typically depends on behavior implementation and configuration.
    Constraints are not handled here - they are specified and checked in ability behavior.
*/
class Ability
{
public:
iv::ClientMarker cm;
                            Ability( iv::Instance * inst );
    iv::Instance *          instance() const;

    iv::SharedAttr< uint64_t >          cooldown;       ///< Absolute time of when the ability cools down.
    iv::SharedAttr< iv::Activator >     activator;      ///< Controls activation of the main functionality of the ability.
};

}
