#include <agent/agent.hpp>
#include "thread_pool_lock_free.hpp"

namespace broccoli
{


    class thread_pool_agent_free : public thread_pool_lock_free
    {

        private:

          std::weak_ptr<std::vector<std::pair<unsigned int, Agent *>>> _agents;

          thread_pool_agent_free(const thread_pool_agent_free &)= delete;
          thread_pool_agent_free(thread_pool_agent_free &&) = delete;
          thread_pool_agent_free & operator=(const thread_pool_agent_free &) = delete;
          thread_pool_agent_free & operator=(thread_pool_agent_free &&) = delete;

        public:

          thread_pool_agent_free(std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents, int nThreads);
          virtual ~thread_pool_agent_free() override {}
          void step();

    };

}