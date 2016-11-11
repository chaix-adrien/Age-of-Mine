#include "main.h"

  void Cube::setPos(int x = 0, int y = 0 , int z = 0)
  {
    m_x = x;
    m_y = y;
    m_z = z;
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
    return m_x;
  }
  int Cube::mooveY(int move){
    m_y = m_y + move;
    return m_y;
  }
  int Cube::mooveZ(int move){
    m_z = m_z + move;
    return m_z;
  }

  void Cube::display(){
    GLfloat vertex_data[12] = {
      -1 + m_x, -1 + m_y, 0 + m_z,
      -1 + m_x, 1 + m_y, 0 + m_z,
      1 + m_x, 1 + m_y, 0 + m_z,
      1 + m_x, -1 + m_y, 0 + m_z
    };
    GLfloat color_data[12] = {
      0.123, 1, 0,
      -1, 0.12, 0,
      1, 1, 0,
      1, -1, 0
    };
    GLuint vertextId = createAtributeBuffer(0, vertex_data, sizeof(vertex_data));
    glEnableVertexAttribArray(vertextId);
    GLuint colorId = createAtributeBuffer(1, color_data, sizeof(color_data));
    glEnableVertexAttribArray(colorId);
    glDrawArrays(GL_QUADS, 0, 3 * 4); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
    glDisableVertexAttribArray(vertextId);
    glDisableVertexAttribArray(colorId);

  }

  Cube::Cube(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
  }
