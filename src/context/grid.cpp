//
// Created by leo on 7/16/17.
//

#include <algorithm>
#include "grid.hpp"

namespace broccoli {

  std::vector<GridElement *> &Grid::getElementsAt(GridPoint position) {
    return _grid_elements.at(position._y * _rows + position._x);
  }

  void Grid::addElementAt(GridElement *element, GridPoint position) {
    std::vector<GridElement *> &s = this->_grid_elements[position._y * _rows + position._x];
    this->modify<std::vector<GridElement *>, GridElement *&>(
        s,
        element,
       [] (std::vector<GridElement *> &st, GridElement *&e) {
          st.push_back(e);
        }
    );
  }

  void Grid::moveElementTo(GridElement *element, GridPoint from, GridPoint to) {
    if (removeElement(element, from) != nullptr)
      addElementAt(element, to);
  }

  GridElement *Grid::removeElement(GridElement *element, GridPoint position) {
    auto &s = this->_grid_elements[position._y * _rows + position._x];
    auto it = std::find(s.begin(), s.end(), element);
    if (it == s.end())
      return nullptr;
    this->modify<std::vector<GridElement *>, GridElement *&>(
        this->_grid_elements[position._y * _rows + position._x],
        element,
        [] (std::vector<GridElement *> &st, GridElement *&e) {
          auto i = std::find(st.begin(), st.end(), e);
          if (i != st.end())
            st.erase(i);
        }
    );
    return element;
  }

  bool Grid::hasElement(GridElement *element, GridPoint position) {
    auto s = this->_grid_elements[position._y * _rows + position._x];
    auto it = std::find(s.begin(), s.end(), element);
    return it != s.end();
  }

  const std::vector<GridElement *> &Grid::getStackAt(GridPoint position) {
    return this->_grid_elements[position._y * _rows + position._x];
  }

  void Grid::clearStackAt(GridPoint position) {
    this->modify<std::vector<GridElement *>>(
        this->_grid_elements[position._y * _rows + position._x],
        [] (std::vector<GridElement *> &s) {
          s.clear();
        }
    );
  }
}
