#include "thread_pool_agent.hpp"
#include <iostream>


namespace broccoli
{



   thread_pool_agent::thread_pool_agent(std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents, int nThreads)
           :  _agents(agents), thread_pool(nThreads, true)
          {
            std::cout << "constructing thread_pool agent" << std::endl;
          }

   void thread_pool_agent::step()
          {
            stopped_.store(true);

            std::unique_lock< std::mutex > lock( mutex_);
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

                                    tasks_.push(_f);
                                    tasks_running_++;
                                    elt.first = elt.second->get_ticks_between_updates();
                               }
                            }
                         }


             stopped_.store(false);
             lock.unlock();
             condition_.notify_all();

             while(!waiting())
                continue;

            stopped_.store(true);

          }



}