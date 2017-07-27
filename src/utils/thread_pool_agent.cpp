#include "thread_pool_agent.hpp"

namespace broccoli
{



          thread_pool_agent::thread_pool_agent(std::vector<std::pair<unsigned int, Agent *>> &agents, int nThreads)
           :  _agents(agents), thread_pool(nThreads, true)
          {
          }

          void thread_pool_agent::step()
          {
            stopped_ = true;
            std::vector<std::future<void>> results;
            std::unique_lock< std::mutex > lock( mutex_);
            for (unsigned int i = 0; i < _agents.size(); ++i) {
                    if (_agents[i].second) {
                      _agents[i].first--;
                      if (!_agents[i].first && _agents[i].second->is_step_enabled()) {

                        auto pck = std::make_shared<std::packaged_task<void()>>(
                                            [this, i]() { _agents[i].second->step(); }
                                            );
                        auto _f = new std::function<void()>([pck]() {
                                               (*pck)();
                                           });

                        results.push_back(pck->get_future());
                        tasks_.push(_f);
                        _agents[i].first = _agents[i].second->get_ticks_between_updates();
                   }
                }
             }

             stopped_ = false;
             lock.unlock();
             condition_.notify_all();

            for (unsigned int i = 0; i < results.size(); ++i)
                 if (results[i].valid())
                     results[i].get();

            stopped_ = true;

          }



}