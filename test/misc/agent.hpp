#pragma once

#include <agent/agent.hpp>
#include <chrono>
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


class DummyMaki : public broccoli::Agent
{

    private:
        int myValue = 0;
        int id;

    public:
        DummyMaki(int id) : id(id) {};
        void step() {
         using namespace std::chrono_literals;
         myValue++; };
        int getValue()
        {
           return myValue;
        }
};

