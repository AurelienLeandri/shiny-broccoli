#include <iostream>
#include <random>
#include <vector>
#include <context/context.hpp>
#include "environment.hpp"
#include "agent.hpp"

int main() {
    srand (time(NULL));
    int nb_agents = 10;
    broccoli::Context context;
    MyEnvironment env;
    context.add_environment(&env);
    std::vector<DummyWazabi*> agents;
    for (int i = 0; i < nb_agents; ++i)
    {
        agents.push_back(new DummyWazabi(env, rand() % 100000));
        context.add_agent(agents[agents.size() - 1]);
    }
    context.start();
    return 0;
}
