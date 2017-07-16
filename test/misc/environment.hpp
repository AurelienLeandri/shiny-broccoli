
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
        void setValue()
        {
            this->modify<int>(
                    value, [] (int &i) { std::cout << i << std::endl; return i + 1; });
        };

        //bool obstacle(int direction, const DummyWazabi dummie);
        //void setPos(DummyWazabi &dummie);
};
