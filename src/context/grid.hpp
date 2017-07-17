//
// Created by leo on 7/16/17.
//

#pragma once

#include <stack>
#include "environment.hpp"
#include "grid-element.hpp"

namespace broccoli {

  class Grid : public Environment {
    public:
      Grid(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols) {}
      virtual std::vector<GridElement *> &getElementsAt(GridPoint position);
      virtual void addElementAt(GridElement *element, GridPoint position);
      virtual GridElement *removeElement(GridElement *element, GridPoint position);
      virtual void moveElementTo(GridElement *element, GridPoint from, GridPoint to);
      virtual bool hasElement(GridElement *element, GridPoint position);
      virtual const std::vector<GridElement *> &getStackAt(GridPoint position);
      virtual void clearStackAt(GridPoint position);

    public:
      const std::vector<std::vector<GridElement *>> &get_grid_elements() const { return _grid_elements; }
      const unsigned int &get_rows() { return _rows; }
      const unsigned int &get_cols() { return _cols; }

    private:
      std::vector<std::vector<GridElement *>> _grid_elements;
      unsigned int _rows;
      unsigned int _cols;
  };


}
