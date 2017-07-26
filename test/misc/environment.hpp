
#pragma once

#include <context/environment.hpp>

enum Direction
{
    RIGHT = 0,
    LEFT,
    UP,
    DOWN
};

class MyEnvironment : public broccoli::Environment {
    private:
        int value;

    public:
        MyEnvironment() : value(0) {};

        int getValue()
        {
        return value;
        }
        void setValue()
        {
            this->modify<int>(
                    value, [] (int &i) { i = i + 1; });
        };
};
