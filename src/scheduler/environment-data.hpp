//
// Created by leo on 7/14/17.
//

#pragma once


template <typename T>
class EnvironmentData<T> {
  public:
    EnvironmentData(const T &data_address);

  private:
    T &data_adress;
};


