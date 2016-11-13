#include "main.h"

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


GLuint loadBMP_custom(const char * imagepath) {
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;
	FILE * file = fopen(imagepath,"rb");
	if (!file){printf("Image could not be opened\n"); return 0;}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
	}
	if ( header[0]!='B' || header[1]!='M' ){
	    printf("Not a correct BMP file\n");
	    return 0;
	}
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	//Everything is in memory now, the file can be closed
	fclose(file);
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return textureID;
}

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
    GLfloat color_data[4 * 2] = {
      0, 0,
      0, 1,
      1, 1,
      1, 0
    };   
    GLuint vertextId = createAtributeBuffer(0, m_vertex, sizeof(m_vertex));
    glEnableVertexAttribArray(vertextId);
	
	GLuint texture = loadBMP_custom("grass.bmp");

 	GLuint colorId;
    glGenBuffers(1, &colorId);
    glBindBuffer(GL_ARRAY_BUFFER, colorId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_data), color_data, GL_STATIC_DRAW);
    glVertexAttribPointer(
        1,                      // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glDrawArrays(GL_QUADS, 0, 12);
    glDisableVertexAttribArray(vertextId);
    glDisableVertexAttribArray(1);

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
