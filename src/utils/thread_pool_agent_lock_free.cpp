#include "thread_pool_agent_lock_free.hpp"
#include <iostream>
namespace broccoli
{



          thread_pool_agent_free::thread_pool_agent_free(
          std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents, int nThreads)
           :  _agents(agents), thread_pool_lock_free(nThreads, true)
          {
            std::cout << "built !\n";

          }

          void thread_pool_agent_free::step()
          {


            auto tmp = _agents.lock();
            auto agents = *tmp;
            for (auto& elt : agents) {

                    if (elt.second ) {
                      if (elt.first)
                          elt.first--;
                      if (!elt.first && elt.second->is_step_enabled()) {


                        auto _f = new std::function<void()>([agent=elt.second](){
                                    agent->step();
                        });

                        tasks_.enqueue(_f);
                        tasks_running_++;
                        elt.first = elt.second->get_ticks_between_updates();
                   }
                }
             }



             while(!waiting())
                continue;

          }
}