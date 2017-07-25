#include <iostream>
#include <random>
#include <vector>
#include <context/context.hpp>
#include "environment.hpp"
#include "agent.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
    broccoli::ThreadingPolicy policy = broccoli::ALL;
    if (argc == 2 && !strcmp(argv[1], "DATA_ONLY"))
      policy = broccoli::DATA_ONLY;
    else if (argc == 2 && !strcmp(argv[1], "AGENTS_ONLY"))
      policy = broccoli::AGENTS_ONLY;
    if (argc == 2 && !strcmp(argv[1], "NONE"))
      policy = broccoli::NONE;
    
    srand (time(NULL));
    int nb_agents = 10000;
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
