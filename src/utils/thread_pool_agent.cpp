#include "thread_pool_agent.hpp"
#include <iostream>
namespace broccoli
{



          thread_pool_agent::thread_pool_agent(std::vector<std::pair<unsigned int, Agent *>> &agents, int nThreads)
           :  _agents(agents), thread_pool(nThreads, true)
          {
          }

          void thread_pool_agent::step()
          {
            stopped_ = true;

            std::unique_lock< std::mutex > lock( mutex_);
            for (unsigned int i = 0; i < _agents.size(); ++i) {
                    if (_agents[i].second ) {
                      if (_agents[i].first)
                          _agents[i].first--;
                      if (!_agents[i].first && _agents[i].second->is_step_enabled()) {


                        auto _f = new std::function<void()>([this, i](){
                                    _agents[i].second->step();
                        });

                        tasks_.push(_f);
                        tasks_running_++;
                        _agents[i].first = _agents[i].second->get_ticks_between_updates();
                   }
                }
             }


             stopped_ = false;
             lock.unlock();
             condition_.notify_all();

             while(!waiting())
                continue;

            stopped_ = true;

          }



}