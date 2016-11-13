#include "main.h"

GLfloat side_vertex[6][12] = {
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	},
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f	
	},
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	},
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f	
	},
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	},
	{
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f
	}
};

void Quad::setPos(int x, int y, int z)
{
    m_x = x;
    m_y = y;
    m_z = z;
    _setVertex();
}

int Quad::getX() {
    return m_x;
}
int Quad::getY() {
    return m_y;
}
int Quad::getZ() {
    return m_z;
}

int Quad::mooveX(int move){
    m_x = m_x + move;
    this->_setVertex();
	return m_x;
}
int Quad::mooveY(int move){
    m_y = m_y + move;
    this->_setVertex();
	return m_y;
}
int Quad::mooveZ(int move){
    m_z = m_z + move;
    this->_setVertex();
    return m_z;
}

void Quad::setSide(side side) {
  	m_side = side;
    this->_setVertex();
}

void Quad::_setDefaultVertex() {
  	std::copy(std::begin(side_vertex[m_side]), std::end(side_vertex[m_side]), std::begin(m_vertex));
}

void Quad::_addPosVertex() {
	for (int i = 0; i < 12; i++) {
		if (i % 3 == X) {
			m_vertex[i] += m_x;
		} else if (i % 3 == Y) {
			m_vertex[i] += m_y;
		} else if (i % 3 == Z) {
			m_vertex[i] += m_z;
		}
	}
}

void Quad::_setVertex() {
	this->_setDefaultVertex();
	this->_addPosVertex();
}

void Quad::display(){	
    GLuint vertextId = createAtributeBuffer(0, m_vertex, sizeof(m_vertex), 3);
    glEnableVertexAttribArray(vertextId);
	
    glDrawArrays(GL_QUADS, 0, 12);
    glDisableVertexAttribArray(vertextId);
}

Quad::Quad() {
  	this->setPos(0, 0, 0);
  	this->setSide(FRONT);
  	this->_setDefaultVertex();
}

Quad::Quad(int x = 0, int y = 0, int z = 0, side sides = TOP){
  	this->setPos(x, y, z);
  	this->setSide(sides);
  	this->_setVertex();
}
