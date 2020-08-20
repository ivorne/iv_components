#include "SimulationState_Button.hpp"
#include "../Defs.hpp"

using namespace iv;

namespace comp
{

SimulationState_Button::SimulationState_Button( iv::Instance * inst, SimulationState * sim, LumaStyleId style_id ) :
    LumaButton( inst, style_id ),
    cm( inst, this, "SimulationState_Button" ),
    sim( sim ),
    heap( inst, &this->cm ),
    anim( inst ),
    previous_state( SimulationState::Empty )
{
    this->cm.inherits( this->iv::LumaButton::cm );
    this->cm.owns( this->anim.cm );
    
    this->sufraceNeutralColor( float4( 0.384, 0.000, 0.933, 1 ) );
    this->attr_surface.Set( "/CoreModels/Simulation/SimulationState_Button/surface.png" );
    this->attr_hot.Set( "/CoreModels/Simulation/SimulationState_Button/hot.png" );
    
    //----------- input ---------------------------------------------------------------
    auto activation =
            this->heap.create< iv::FunctorActivatorAttribute >(
            &this->cm,
            [ this, sim ]()
            {
                SimulationState::State st = sim->state.Get();
                if( st == SimulationState::Paused )
                    sim->pause.Modify( &this->cm, false );
                else if( st == SimulationState::Running )
                    sim->pause.Modify( &this->cm, true );
                else
                    sim->restart.Modify( &this->cm, sim->restart.Get().MakeActivated() );
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
        ->filename( "/CoreModels/Simulation/SimulationState_Button/border.png" );
    
    this->icon = this->surface_slot.createChild< iv::Border >()
        ->leftRight( 10, 10 )
        ->topBottom( 10, 10 )
        ->createChild< iv::Prefsize >()
            ->prefsize( float3( 0, 0, 0 ) )
            ->createChild< iv::Image >()
                ->resizeStage( iv::FlatShader::ResizeStage::Scale );
    
    //---------------------------- animation -----------------------------------------------
    // in
    AnimNode< SimulationState::State > * in_state = this->anim.Attribute_SourceNode( &sim->state, SimulationState::Empty )
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
                case SimulationState::Empty:
                {
                    this->icon->filename( "/ivorium_UI/icons/play.png" );
                } break;
                
                case SimulationState::Paused:
                {
                    this->icon->filename( "/ivorium_UI/icons/resume.png" );
                } break;
                
                case SimulationState::Running:
                {
                    this->icon->filename( "/ivorium_UI/icons/pause.png" );
                } break;
                
                case SimulationState::Ended:
                {
                    this->icon->filename( "/ivorium_UI/icons/restart.png" );
                } break;
            }
        }
    );
    
    this->CallColorsChanged();
}

void SimulationState_Button::ColorsChanged( float4 surface, float4 on_surface )
{
    this->icon->preblend( surface );
    this->icon->colorTransform( ColorTransform::Change( float4( 0.384, 0.000, 0.933, 1 ), on_surface ) );
    this->border->preblend( surface );
    this->border->colorTransform( ColorTransform::Change( float4( 0.800, 0.800, 0.800, 1 ), on_surface ) );
}

}
