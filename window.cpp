#include "main.h"


int width = 1280;
int height = 720;
GLuint mvp_handle = 0;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
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
    glDepthMask(GL_TRUE);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST); // <-- it works here; anywhere above it doesn't work
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, 4.0/3, 0.1, 2);
}

void affichage(void)
{
/*Initialisation des pixels */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    activeZBuffer();
    
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
               glm::vec3(4,3,-3), // Camera is at (4,3,3), in World Space
               glm::vec3(0,0,0), // and looks at the origin
               glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
               );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);
    /* dessin d'un polygone (rectangle) avec les sommets en (0.25, 0.25, 0.0) et (0.75, 0.75, 0.0)*/

    GLuint vertexbufer = createAtributeBuffer(0, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
    glEnableVertexAttribArray(vertexbufer);
    
    GLuint colorbuffer = createAtributeBuffer(1, g_color_buffer_data, sizeof(g_color_buffer_data));
    glEnableVertexAttribArray(colorbuffer);


    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glutSwapBuffers();
    // /* On force l'affichage du resultat */
    // glFlush();
}

void clavier(unsigned char touche, int x, int y)
{
    switch(touche)
      {
      case 'p': /* affichage du carre plein */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();break;
      case 'f': /* affichage en mode fil de fer */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();break;
      case 's': /* affichage en mode sommet seul */
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutPostRedisplay();break;
      case 'q': /* la touche 'q' quitte le programme */
        exit(0);
      }
}

int main(int argc, char **argv)
{
    /* Initialisation de glut et création de la fenêtre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
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
