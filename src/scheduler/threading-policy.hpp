//
// Created by leo on 7/15/17.
//

#ifndef SHINYBROCCOLI_THREADING_POLICY_HPP
#define SHINYBROCCOLI_THREADING_POLICY_HPP

namespace broccoli {

  enum class ThreadingPolicy {
    ALL,
    DATA_ONLY,
    AGENTS_ONLY,
    NONE
  };

  enum class LockPolicy {
    USE_LOCK,
    LOCK_FREE
  };

}

#endif //SHINYBROCCOLI_THREADING_POLICY_HPP
