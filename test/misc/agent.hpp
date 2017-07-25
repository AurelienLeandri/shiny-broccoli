#pragma once

#include <agent/agent.hpp>
#include "environment.hpp"

class DummyWazabi : public broccoli::Agent
{
    private:
        MyEnvironment& env;
        int id;

    public:
        DummyWazabi(MyEnvironment& env, int id) : env(env), id(id) {};
        void step() { env.setValue(); };
};
