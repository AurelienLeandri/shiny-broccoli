//
// Created by leo on 7/14/17.
//

#ifndef SHINYBROCCOLI_ACTIONRESULT_HPP
#define SHINYBROCCOLI_ACTIONRESULT_HPP

namespace broccoli {

  enum ActionResult {
    SUCCESS = 0,
    FAILURE = 1,
    CONCURRENT_ACCESS = 2
  };

}

#endif //SHINYBROCCOLI_ACTIONRESULT_HPP
