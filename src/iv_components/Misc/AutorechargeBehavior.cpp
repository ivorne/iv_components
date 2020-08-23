#include "AutorechargeBehavior.hpp"

namespace comp
{

AutorechargeBehavior::AutorechargeBehavior( iv::Instance * inst, iv::TimeId time, iv::Attr< int > * m_charges, uint64_t recharge_ms, int max ) :
    cm( inst, this, "AutorechargeBehavior" ),
    m_charges( m_charges ),
    recharge_ms( recharge_ms ),
    max( max ),
    cooldown_ms( 0 )
{
    this->m_charges->Modify( &this->cm, this->max );
}

void AutorechargeBehavior::reset()
{
    this->cooldown_ms = 0;
    this->m_charges->Modify( &this->cm, this->max );
}

void AutorechargeBehavior::step( int step_ms )
{
    if( this->cooldown_ms > 0 )
    {
        if( this->cooldown_ms > step_ms )
        {
            this->cooldown_ms -= step_ms;
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
