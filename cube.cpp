#include "main.h"

  void Cube::_setQuadsPos() {
    for (int i = 0; i < 6; i++) {
      m_quads[i].setPos(m_x, m_y, m_z);
    }
  }

  void Cube::_setQuadsSide() {
    for (int i = 0; i < 6; i++) {
      m_quads[i].setSide(static_cast<side>(i));
    }
  }

  void Cube::setPos(int x, int y, int z)
  {
    m_x = x;
    m_y = y;
    m_z = z;
    _setQuadsPos();
  }

  int Cube::getX() {
    return m_x;
  }
  int Cube::getY() {
    return m_y;
  }
  int Cube::getZ() {
    return m_z;
  }

  int Cube::mooveX(int move){
    m_x = m_x + move;
    this->_setQuadsPos();
    return m_x;
  }
  int Cube::mooveY(int move){
    m_y = m_y + move;
    this->_setQuadsPos();
    return m_y;
  }
  int Cube::mooveZ(int move){
    m_z = m_z + move;
    this->_setQuadsPos();
    return m_z;
  }

  void Cube::display(){
    for (int i = 0; i < 6; i++) {
      m_quads[i].display();
    }
  }


  Cube::Cube() {
    this->setPos(0, 0, 0);
    this->_setQuadsSide();
    this->_setQuadsPos();

  }

  Cube::Cube(int x = 0, int y = 0, int z = 0){
    this->setPos(x, y, z);
    this->_setQuadsSide();
    this->_setQuadsPos();
  }
