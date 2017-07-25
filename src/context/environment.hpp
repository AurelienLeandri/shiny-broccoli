//
// Created by leo on 7/14/17.
//

#pragma once

#include <scheduler/data-manager.hpp>
#include <scheduler/data-update.hpp>

namespace broccoli {

  class Environment {
    public:
      Environment() {}
      virtual ~Environment() {};

    public:
      template <typename T>
      void modify(T &data, void (*operation)(T &)) const;
      template <typename T1, typename T2>
      void modify(T1 &data1, T2 data2, void (*operation)(T1 &, T2)) const;
      void set_data_manager(DataManager *data_manager) { _data_manager = data_manager; }


    private:
      DataManager *_data_manager;
      bool threaded;
  };

  template<typename T>
  void Environment::modify(T &data, void (*operation)(T &)) const {
    _data_manager->add_action(new DataUpdate<T>(data, operation, *_data_manager));
  }

  template<typename T1, typename T2>
  void Environment::modify(T1 &data1, T2 data2, void (*operation)(T1 &, T2)) const {
    _data_manager->add_action(new DataUpdate<T1, T2>(data1, data2, operation, *_data_manager));
  }

}

