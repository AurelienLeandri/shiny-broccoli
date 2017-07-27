//
// Created by leo on 7/16/17.
//

#include <algorithm>
#include <iostream>
#include "grid.hpp"

namespace broccoli {

  std::vector<GridElement *> &Grid::getElementsAt(GridPoint position) {
    return _grid_elements.at(position._y * _cols + position._x);
  }

  void Grid::addElementAt(GridElement *element, GridPoint position) {
    MoveElement *move = new MoveElement();
    move->previous = this->_grid_elements[element->get_position()._x, element->get_position()._y];
    move->next = this->_grid_elements[position._x, position._y];
    move->new_position = position;
    move->element = element;
    this->modify<GridElement, MoveElement*>(
        *element,
        move,
       [] (GridElement &elt, MoveElement *m) {
         auto i = std::remove(m->previous.begin(), m->previous.end(), m->element);
         m->previous.erase(i, m->previous.end());
         m->previous.shrink_to_fit();
         m->element->set_position(m->new_position);
         m->next.push_back(m->element);
         delete m;
        }
    );
  }

  void Grid::moveElementTo(GridElement *element, GridPoint position) {
    MoveElement *move = new MoveElement();
    move->previous = this->_grid_elements[element->get_position()._y * _cols + element->get_position()._x];
    move->next = this->_grid_elements[position._y * _cols + position._x];
    move->new_position = position;
    move->element = element;
    this->modify<GridElement, MoveElement*>(
        *element,
        move,
        [] (GridElement &elt, MoveElement *m) {
          auto i = std::remove(m->previous.begin(), m->previous.end(), m->element);
          m->previous.erase(i, m->previous.end());
          m->previous.shrink_to_fit();
          m->element->set_position(m->new_position);
          m->next.push_back(m->element);
          delete m;
        }
    );
  }

  GridElement *Grid::removeElement(GridElement *element, GridPoint position) {
    auto &s = this->_grid_elements[position._y * _cols + position._x];
    auto it = std::find(s.begin(), s.end(), element);
    if (it == s.end())
      return nullptr;
    this->modify<std::vector<GridElement *>&, GridElement *>(
        s,
        element,
        [] (std::vector<GridElement *> &st, GridElement *e) {
          // Use the erase-remove idiom in combination with a lambda expression
          auto i = std::remove(st.begin(), st.end(), e);
          st.erase(i, st.end());
          st.shrink_to_fit();
        }
    );
    return element;
  }

  bool Grid::hasElement(GridElement *element, GridPoint position) {
    auto s = this->_grid_elements[position._y * _cols + position._x];
    auto it = std::find(s.begin(), s.end(), element);
    return it != s.end();
  }

  const std::vector<GridElement *> &Grid::getStackAt(GridPoint position) {
    return this->_grid_elements[position._y * _cols + position._x];
  }

  void Grid::clearStackAt(GridPoint position) {
    this->modify<std::vector<GridElement *>>(
        this->_grid_elements[position._y * _cols + position._x],
        [] (std::vector<GridElement *> &s) {
          s.clear();
        }
    );
  }
}
