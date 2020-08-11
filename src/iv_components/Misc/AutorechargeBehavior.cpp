#include "AutorechargeBehavior.hpp"

namespace comp
{

AutorechargeBehavior::AutorechargeBehavior( iv::Instance * inst, iv::TimeId time, iv::Attr< int > * m_charges, uint64_t recharge_ms, int max ) :
    iv::FixedUpdateClient( inst, time ),
    cm( inst, this, "AutorechargeBehavior" ),
    m_charges( m_charges ),
    recharge_ms( recharge_ms ),
    max( max ),
    cooldown_ms( 0 )
{
    this->cm.inherits( this->iv::FixedUpdateClient::cm );
    m_charges->Modify( &this->cm, max );
}

void AutorechargeBehavior::fixed_update( iv::TimeId time, int time_step, int steps )
{
    for( size_t i = 0; i < steps; i++ )
    {
        if( this->cooldown_ms > 0 )
        {
            if( this->cooldown_ms > time_step )
            {
                this->cooldown_ms -= time_step;
            }
            else
            {
                this->cooldown_ms = 0;
                if( this->m_charges->Get() < this->max )
                    this->m_charges->Modify( &this->cm, this->m_charges->Get() + 1 );
            }
        }
        
        if( this->cooldown_ms == 0 && this->m_charges->Get() < this->max )
            this->cooldown_ms = this->recharge_ms;
    }
}

}
