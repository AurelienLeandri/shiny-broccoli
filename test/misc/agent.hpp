#include <agent/agent.hpp>

class DummyWazabi(broccoli.Agent)
{
    private:
        size_t x;
        size_t y;
        MyEnvironment &env;

    public:
        DummyWazabi(MyEnvironment env, size_t x, size_t y) {this->x = x; this->y = y; this->env = env;};
        void step();
    
};
