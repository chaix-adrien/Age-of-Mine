#ifndef MAIN_H_
#define MAIN_H_

#include "opengl.h"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
int createAtributeBuffer(int attributeId, const GLfloat *data, unsigned long size, int dim);

#define X 0
#define Y 1
#define Z 2

enum side {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

class Quad {
	public:
		Quad();
		Quad(int x, int y, int z, side side);
		void setSide(side side);
		void setPos(int x, int y, int z);
		int mooveX(int move);
		int mooveY(int move);
		int mooveZ(int move);
		void display();
		int  getX();
		int  getY();
		int  getZ();
	private:
		void _setDefaultVertex();
		void _addPosVertex();
		void _setVertex();
		int m_x;
		int m_y;
		int m_z;
		side m_side;
		GLfloat m_vertex[12];
		unsigned char *m_texture;
		int width;
		int height;
};

class Cube {
	public:
		Cube();
		Cube(int x, int y, int z, int texture);
		void display();
		void setTexture(int id);
		void setPos(int x, int y, int z);
		int mooveX(int move);
		int mooveY(int move);
		int mooveZ(int move);
		int  getX();
		int  getY();
		int  getZ();
	private:
		void _setQuadsPos();
		void _setQuadsSide();
	  	int m_x;
	  	int m_y;
	  	int m_z;
	  	int m_textureId;
	  	Quad m_quads[6];
};


#endif