#include "Ability_View.hpp"

using namespace iv;

namespace comp
{

Ability_View::Ability_View( iv::Instance * inst, Ability * m_ability, AbilityInfo info ) :
    iv::LumaButton( inst, iv::LumaStyleId() ),
    cm( inst, this, "Ability_View" ),
    m_ability( m_ability )
{
    this->cm.inherits( iv::LumaButton::cm );
    
    this->resizeStage( iv::FlatShader::ResizeStage::Scale );
    this->surface( ResourcePath( "/CoreModels/Ability/Ability_View/surface.png" ) );
    this->hot( ResourcePath( "/CoreModels/Ability/Ability_View/hot.png" ) );
    this->overlay( info.overlay );
    this->translucent( true );
    
    this->input.field_release.Assign_Attribute_RW( &m_ability->activator );
}

}
