#include "GameState_Button.hpp"
#include "../Defs.hpp"

using namespace iv;

namespace comp
{

GameState_Button::GameState_Button( iv::Instance * inst, GameState * m_game, LumaStyleId style_id ) :
    LumaButton( inst, style_id ),
    cm( inst, this, "GameState_Button" ),
    m_game( m_game ),
    heap( inst, &this->cm ),
    anim( inst ),
    previous_state( GameState::State::Empty )
{
    this->cm.inherits( this->iv::LumaButton::cm );
    this->cm.owns( this->anim.cm );
    
    this->sufraceNeutralColor( float4( 0.384, 0.000, 0.933, 1 ) );
    this->attr_surface.Set( "/CoreModels/GameState/GameState_Button/surface.png" );
    this->attr_hot.Set( "/CoreModels/GameState/GameState_Button/hot.png" );
    
    //----------- input ---------------------------------------------------------------
    auto activation =
            this->heap.create< iv::FunctorActivatorAttribute >(
            &this->cm,
            [ this, m_game ]()
            {
                GameState::State state = m_game->game_state.Get();
                if( state == GameState::State::Paused )
                    m_game->pause.Modify( &this->cm, false );
                else if( state == GameState::State::Running )
                    m_game->pause.Modify( &this->cm, true );
                else
                    m_game->restart.Modify( &this->cm, m_game->restart.Get().MakeActivated() );
            }
        );
    
    //
    this->input.field_release.Assign_Attribute_RW( activation );
    
    // 
    auto space_key = this->heap.createClient< iv::Key_InputNode >( comp::Defs::Input::GameStateButtonTrigger );
    space_key->field_press.Assign_Attribute_RW( activation );
    this->Add_InputNode( space_key );
    
    //----- visuals -------------------------------------------------------------------
    this->border = this->surface_slot.createChild< iv::Image >()
        ->filename( "/CoreModels/GameState/GameState_Button/border.png" );
    
    this->icon = this->surface_slot.createChild< iv::Border >()
        ->leftRight( 10, 10 )
        ->topBottom( 10, 10 )
        ->createChild< iv::Prefsize >()
            ->prefsize( float3( 0, 0, 0 ) )
            ->createChild< iv::Image >()
                ->resizeStage( iv::FlatShader::ResizeStage::Scale );
    
    //---------------------------- animation -----------------------------------------------
    // in
    AnimNode< GameState::State > * in_state = this->anim.Attribute_SourceNode( &m_game->game_state, GameState::State::Empty )
                                                        ->label( "in_game_state" );
    
    // lambda connector
    auto lambda = this->anim.Make_Lambda_Connector()
        ->AddParent( in_state );
    
    lambda->Retargeting(
        [ = ]( bool warping )
        {
            if( this->previous_state != in_state->Target() )
            {
                this->previous_state = in_state->Target();
                this->input.interruptActivation();
            }
            
            switch( in_state->Target() )
            {
                case GameState::State::Empty:
                {
                    this->icon->filename( "/ivorium_UI/icons/play.png" );
                } break;
                
                case GameState::State::Paused:
                {
                    this->icon->filename( "/ivorium_UI/icons/resume.png" );
                } break;
                
                case GameState::State::Running:
                {
                    this->icon->filename( "/ivorium_UI/icons/pause.png" );
                } break;
                
                case GameState::State::Ended:
                {
                    this->icon->filename( "/ivorium_UI/icons/restart.png" );
                } break;
            }
        }
    );
    
    this->CallColorsChanged();
}

void GameState_Button::ColorsChanged( float4 surface, float4 on_surface )
{
    this->icon->preblend( surface );
    this->icon->colorTransform( ColorTransform::Change( float4( 0.384, 0.000, 0.933, 1 ), on_surface ) );
    this->border->preblend( surface );
    this->border->colorTransform( ColorTransform::Change( float4( 0.800, 0.800, 0.800, 1 ), on_surface ) );
}

}
