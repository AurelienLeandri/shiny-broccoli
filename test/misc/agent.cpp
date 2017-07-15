#include "agent.hpp"


void DummyWazabi::step()
{
    if (!env.obstacle(Direction::RIGHT), *this)
        ++x;
    else if (!env.obstacle(Direction::DOWN), *this)
        ++y;
    else if (!env.obstacle(Direction::LEFT), *this)
        --x;
    else
        --y;
}
