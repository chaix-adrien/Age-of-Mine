#ifndef MAIN_H_
#define MAIN_H_

#include "opengl.h"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
int createAtributeBuffer(int attributeId, const GLfloat *data, unsigned long size);
class Cube {
	public:
		Cube();
		void display();
		void setPos(int x, int y, int z);
		int mooveX(int move);
		int mooveY(int move);
		int mooveZ(int move);
		int  getX();
		int  getY();
		int  getZ();
	private:
	  	int m_x;
	  	int m_y;
	  	int m_z;
};

#endif