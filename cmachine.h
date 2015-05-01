#ifndef CMACHINE_H
#define CMACHINE_H
#include <vector>
#include <QString>

class CMachine
{
private:
    CMachine();
    std::vector<QString> m_tape;
    unsigned int m_currentState;
    std::size_t m_currentPosition;
public:
    CMachine(const std::vector<QString>& input);
    void set_state(const unsigned int state);
    bool move_left();
    bool move_right();
    void write(const QString& str);
    void remove();
};

#endif // CMACHINE_H
