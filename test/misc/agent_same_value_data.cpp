#include <iostream>
#include <random>
#include <context/context.hpp>
#include "environment.hpp"
#include "agent.hpp"
#include <cstring>
#include <cassert>

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
    broccoli::Context context(policy);
    MyEnvironment* env = new MyEnvironment();
    context.add_environment(env);
    std::vector<DummyWazabi*> agents;

    for (int i = 0; i < nb_agents; ++i)
    {
        agents.push_back(new DummyWazabi(*env, rand() % 100000));
        context.add_agent(agents.back());
    }
    int nbtick = 100;
    for (int i = 0; i < nbtick; ++i)
      context.update();

    std::cout << "value : " << env->getValue() << std::endl;
    assert(env->getValue() == nbtick * nb_agents);
    return 0;
}
