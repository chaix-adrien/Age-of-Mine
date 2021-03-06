#include "main.h"

GLfloat texture_UV[4 * 2] = {
    0, 0,
    0, 1,
    1, 1,
    1, 0
};

int width = 1280;
int height = 720;
GLuint mvp_handle = 0;

float x = 5;
float y = 5;
float z = 5;

Quad quad(0,0, 0, TOP);
Cube cube(0, 0, 0, 2);
Cube cube2(0, 1, -1, 1);
Map map;

GLuint loadBMP_custom(const char * imagepath) {
    // Data read from the header of the BMP file
    int width, height;
    unsigned char* data =
        SOIL_load_image(imagepath, &width, &height, 0, SOIL_LOAD_RGB);
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return textureID;
}


int createAtributeBuffer(int attributeId, const GLfloat *data, unsigned long size, int dim) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(
        attributeId,                      // attribute. No particular reason for 1, but must match the layout in the shader.
        dim,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );
    return attributeId;
}

void activeZBuffer() {
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void projection() {
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
               glm::vec3(x,y,z), // Camera is at (4,3,3), in World Space
               glm::vec3(0,0,0), // and looks at the origin
               glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
               );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);
}

void affichage(void)
{
/*Initialisation des pixels */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    activeZBuffer();
    projection();

    cube.display();
    cube2.display();
    map.display();

    glutSwapBuffers();
    // /* On force l'affichage du resultat */
    glFlush();
}

void clavier(unsigned char touche, int Ix, int Iy)
{
    switch(touche)
      {
      case 'p': /* affichage du carre plein */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();break;
      case 'f': /* affichage en mode fil de fer */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();break;
      case 'x': /* la touche 'q' quitte le programme */
        exit(0);
      case 'q': /* la touche 'q' quitte le programme */
        x--;
        glutPostRedisplay();break;
      case 'd': /* la touche 'q' quitte le programme */
        x++;
        glutPostRedisplay();break;
      case 'z': /* la touche 'q' quitte le programme */
        y++;
        glutPostRedisplay();break;
      case 's': /* la touche 'q' quitte le programme */
        y--;
        glutPostRedisplay();break;
      }
}

GLuint loadTexture() {
    loadBMP_custom("grass.bmp");
    loadBMP_custom("stone.png");
    GLuint UVID = createAtributeBuffer(1, texture_UV, sizeof(texture_UV), 2);
    return UVID;
}

int main(int argc, char **argv)
{
    /* Initialisation de glut et création de la fenêtre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
    glShadeModel(GL_SMOOTH);
   

    glutInitWindowPosition(200, 200);
    glutInitWindowSize(width, height);
    glutCreateWindow("exemple 1");

    /* Initialisation d'OpenGl */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    GLuint programID = LoadShaders( "shader/Vshader.txt", "shader/Fshader.txt" );
    glUseProgram(programID);
    mvp_handle = glGetUniformLocation(programID, "MVP");
    /* On passe à 2 pixels pour des raisons de clarté */
    glPointSize(1.0);
    /* enregistrement des fonctions de rappels */
    GLuint UVID = loadTexture();
    glEnableVertexAttribArray(UVID);
    
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);

    /* entree dans la boucle principale de glut*/
    glutMainLoop();
    glDisableVertexAttribArray(UVID);
    return 0;
}
