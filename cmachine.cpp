#include "cmachine.h"
#include <assert.h>

CMachine::CMachine(const std::vector<QString>& input)
{
    m_currentState = 0;
    m_currentPosition = 0;
    m_tape = input;
}

bool CMachine::move_left()
{
    if(m_currentPosition != 0)
    {
        --m_currentPosition;
        return true;
    }
    else
        return false;
}

bool CMachine::move_right()
{
    if(m_currentPosition != m_tape.size() - 1)
    {
        ++m_currentPosition;
        return true;
    }
    else
    {
        //TODO: space realloc for m_tape
        return false;
    }
}

void CMachine::remove()
{
    assert(m_currentPosition < m_tape.size());
    m_tape[m_currentPosition] = "#";
}

void CMachine::set_state(const unsigned int state)
{
    m_currentState = state;
}

void CMachine::write(const QString& str)
{
    assert(m_currentPosition < m_tape.size());
    m_tape[m_currentPosition] = str;
}
