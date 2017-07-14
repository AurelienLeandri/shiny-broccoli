//
// Created by leo on 7/14/17.
//

#include "data-update.hpp"

namespace broccoli {

  template <typename T>
  void DataUpdate<T>::execute() {
    auto &mutex = _data_manager.getMutex((uintptr_t) &_data);
    mutex.lock();
    _operation(_data);
    mutex.unlock();
  }

}