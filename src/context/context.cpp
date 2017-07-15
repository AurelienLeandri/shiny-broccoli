//
// Created by leo on 7/15/17.
//

#include "context.hpp"

namespace broccoli {

  Context::~Context() {
    for (auto e : _agents) delete e.second;
    for (auto e : _environments) delete e;
  }

  void Context::add_agent(Agent *agent) {
    _agents.push_back(std::make_pair(agent->get_ticks_between_updates(), agent));
  }

  void Context::add_environment(Environment *environment) {
    environment->set_data_manager(&_data_manager);
    _environments.push_back(environment);
  }

  void Context::start() {
    _scheduler.start();
  }

}
