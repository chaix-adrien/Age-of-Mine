#include "main.h"


int width = 1280;
int height = 720;
GLuint mvp_handle = 0;

float x = 5;
float y = 5;
float z = 5;

Quad quad(0,0, 0, TOP);
Cube cube;

int createAtributeBuffer(int attributeId, const GLfloat *data, unsigned long size) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(
        attributeId,                      // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
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
        cube.mooveX(-1);
        glutPostRedisplay();break;
      case 'd': /* la touche 'q' quitte le programme */
        cube.mooveX(1);
        glutPostRedisplay();break;
      case 'z': /* la touche 'q' quitte le programme */
        cube.mooveY(-1);
        glutPostRedisplay();break;
      case 's': /* la touche 'q' quitte le programme */
        cube.mooveY(1);
        glutPostRedisplay();break;
      }
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


    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);

    /* entree dans la boucle principale de glut*/
    glutMainLoop();

    return 0;
}
