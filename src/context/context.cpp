//
// Created by leo on 7/15/17.
//

#include "context.hpp"

namespace broccoli {

  Context::~Context() {
    for (auto e : *_agents) delete e.second;
    for (auto* e : _environments) delete e;
  }

  void Context::add_agent(Agent *agent) {
    _agents->push_back(std::make_pair(agent->get_ticks_between_updates(), agent));
  }

  void Context::add_environment(Environment *environment) {
    environment->set_data_manager(_data_manager.get());
    _environments.push_back(environment);
  }

  void Context::start() {
    _scheduler->start();
  }

  void Context::update() {
    _scheduler->tick();
  }

  Context::Context()
    :
         _agents(std::make_shared<std::vector<std::pair<unsigned int, Agent *>>>()),
         _data_manager(std::make_shared<DataManager>())
      {
        _scheduler = std::make_shared<Scheduler>(_agents, _data_manager);
      }

  Context::Context(ThreadingPolicy threading_policy,
                   LockPolicy lock_policy)
  :
      _agents(std::make_shared<std::vector<std::pair<unsigned int, Agent *>>>())

  {
     _data_manager = std::make_shared<DataManager>((threading_policy == ThreadingPolicy::ALL) || (threading_policy == ThreadingPolicy::DATA_ONLY),
                          lock_policy);
     _scheduler = std::make_shared<Scheduler>(_agents, _data_manager,
                      (threading_policy == ThreadingPolicy::ALL) || (threading_policy == ThreadingPolicy::AGENTS_ONLY),
                       lock_policy);
  }

  DataManager &Context::get_data_manager() {
    return *_data_manager;
  }
}
