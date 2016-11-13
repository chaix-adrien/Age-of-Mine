#include "main.h"

  void Cube::setPos(int x, int y, int z)
  {
    m_x = x;
    m_y = y;
    m_z = z;
    _setQuadsPos();
  }

  void Cube::_setQuadsPos() {
    for (int i = 0; i < 6; i++) {
      m_quads[i].setPos(m_x, m_y, m_z);
    }
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
    _setQuadsPos();
    return m_x;
  }
  int Cube::mooveY(int move){
    m_y = m_y + move;
    _setQuadsPos();
    return m_y;
  }
  int Cube::mooveZ(int move){
    m_z = m_z + move;
    _setQuadsPos();
    return m_z;
  }

  void Cube::display(){
    for (int i = 0; i < 6; i++) {
      m_quads[i].display();
    }
    // GLfloat vertex_data[12] = {
    //   -1 + m_x, -1 + m_y, 0 + m_z,
    //   -1 + m_x, 1 + m_y, 0 + m_z,
    //   1 + m_x, 1 + m_y, 0 + m_z,
    //   1 + m_x, -1 + m_y, 0 + m_z
    // };
    // GLfloat color_data[12] = {
    //   0.123, 1, 0,
    //   -1, 0.12, 0,
    //   1, 1, 0,
    //   1, -1, 0
    // };
    // GLuint vertextId = createAtributeBuffer(0, vertex_data, sizeof(vertex_data));
    // glEnableVertexAttribArray(vertextId);
    // GLuint colorId = createAtributeBuffer(1, color_data, sizeof(color_data));
    // glEnableVertexAttribArray(colorId);
    // glDrawArrays(GL_QUADS, 0, 3 * 4); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
    // glDisableVertexAttribArray(vertextId);
    // glDisableVertexAttribArray(colorId);

  }

  void Cube::_setQuadsSide() {
    for (int i = 0; i < 6; i++) {
      m_quads[i].setSide(static_cast<side>(i));
    }
  }

  Cube::Cube() {
    setPos(0, 0, 0);
    _setQuadsSide();
    _setQuadsPos();

  }

  Cube::Cube(int x = 0, int y = 0, int z = 0){
    setPos(x, y, z);
    _setQuadsSide();
    _setQuadsPos();
  }
