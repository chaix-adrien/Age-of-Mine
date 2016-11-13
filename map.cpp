#include "main.h"

Map::Map() {
	m_w = 10;
	m_h = 10;
	m_z = 10;
	this->_mallocData();
	this->generateRandom();
}

Map::Map(int w, int h, int z) {
	m_w = w;
	m_h = h;
	m_z = z;
	this->_mallocData();
	this->generateRandom();
}

int Map::getW() {
	return m_w;
}

Cube *Map::getCube(int x, int y, int z) {
	return &m_data[(m_w * m_h * z) + (m_h * y) + x];
}

void Map::toAllCubes(void (*func)(Map *, int, int, int)) {
	for (int x = 0; x < m_w; x++){
		for (int y = 0; y < m_h; y++){
			for (int z = 0; z < m_z; z++){
				func(this, x, y, z);
			}
		}
	}	
}

void _setCubeRandomTye(Map *mapObject, int x, int y, int z) {
	mapObject->getCube(x, y, z)->setTexture(std::rand() % 3);
}

void _setCubePos(Map *mapObject, int x, int y, int z) {
	mapObject->getCube(x, y, z)->setPos(x, y, z);
}

void Map::_mallocData() {
	m_data = new Cube[m_w * m_h * m_z];
	this->toAllCubes(_setCubePos);
}

void Map::generateRandom() {
	this->toAllCubes(_setCubeRandomTye);
}

void Map::display() {
	for (int i  = 0; i < m_w * m_h * m_z; i++) {
		m_data[i].display();
	}
}