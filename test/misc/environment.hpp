#include <context/environment>
#pragma once

enum Direction
{
    RIGHT = 0,
    LEFT,
    UP,
    DOWN
};

class MyEnvironment(broccoli.environment) {
    private:
        int[10][10] map;
        const int nb_agents = 5;
        DummyWazabi* dummies;

    public:
        MyEnvironment() {};
        ~MyEnvironment() = 0;
        bool obstacle(int direction, const DummyWazabi dummie);
        void setPos(DummyWazabi &dummie)
};
