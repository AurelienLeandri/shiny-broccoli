#include <agent/agent.hpp>
#include "thread_pool.hpp"

namespace broccoli
{


    class thread_pool_agent : public thread_pool
    {

        private:

          std::vector<std::pair<unsigned int, Agent *>> &_agents;

          thread_pool_agent(const thread_pool_agent &)= delete;
          thread_pool_agent(thread_pool_agent &&) = delete;
          thread_pool_agent & operator=(const thread_pool_agent &) = delete;
          thread_pool_agent & operator=(thread_pool_agent &&) = delete;

        public:


          thread_pool_agent(std::vector<std::pair<unsigned int, Agent *>> &agents, int nThreads);
          virtual ~thread_pool_agent() override {}
          void step();

    };

}