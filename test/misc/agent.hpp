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
         myValue++;int i = 0; for (int j = 0; j < 500; ++j)
          {
             i += j *j - sqrt(54 * j);
          }};
        int getValue()
        {
           return myValue;
        }
};

