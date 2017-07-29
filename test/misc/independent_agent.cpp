#include <iostream>
#include <random>
#include <context/context.hpp>
#include "environment.hpp"
#include "agent.hpp"
#include <cstring>
#include <cassert>

int main(int argc, char *argv[]) {
     broccoli::ThreadingPolicy policy = broccoli::ThreadingPolicy::ALL;
        broccoli::LockPolicy lock_policy = broccoli::LockPolicy::LOCK_FREE;
        if (argc >= 2 && !strcmp(argv[1], "DATA_ONLY"))
            policy = broccoli::ThreadingPolicy::DATA_ONLY;
        else if (argc >= 2 && !strcmp(argv[1], "AGENTS_ONLY"))
            policy = broccoli::ThreadingPolicy::AGENTS_ONLY;
        else if (argc >= 2 && !strcmp(argv[1], "NONE"))
            policy = broccoli::ThreadingPolicy::NONE;


         if (argc == 3 && !strcmp(argv[2], "LOCK_FREE"))
                lock_policy = broccoli::LockPolicy::LOCK_FREE;
         else if (argc == 3 && !strcmp(argv[2], "USE_LOCK"))
                lock_policy = broccoli::LockPolicy::USE_LOCK;


    srand (time(NULL));
    int nb_agents = 10000;
    broccoli::Context context(policy, lock_policy);
    MyEnvironment* env = new MyEnvironment();
    context.add_environment(env);
    std::vector<DummyMaki*> agents;

    for (int i = 0; i < nb_agents; ++i)
    {
        agents.push_back(new DummyMaki(rand() % 100000));
        context.add_agent(agents.back());
    }
    int nbtick = 1000;
    for (int i = 0; i < nbtick; ++i)
      context.update();

    std::cout << "value : " << agents.front()->getValue() << std::endl;
    for (int i = 0; i < nb_agents; ++i)
        assert(agents[i]->getValue() == nbtick);
    return 0;
}
