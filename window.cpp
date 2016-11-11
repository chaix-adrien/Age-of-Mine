#include "main.h"


int width = 1280;
int height = 720;
GLuint mvp_handle = 0;

static const GLfloat g_vertex_triangle_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f, //
   -1.5f, -1.5f, 0.5f,
   1.5f, -1.5f, 0.5f,
   0.5f,  1.5f, 0.5f
};

static const GLfloat g_color_triangle_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,//
    0.583f,  0.171f,  0.014f,
    0.669f,  0.215f,  0.436f,
    0.327f,  0.983f,  0.854f
};


  void affichage(void)
  {
    /*Initialisation des pixels */

    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
               glm::vec3(-5,3,3), // Camera is at (4,3,3), in World Space
               glm::vec3(0,0,0), // and looks at the origin
               glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
               );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);
    /* dessin d'un polygone (rectangle) avec les sommets en (0.25, 0.25, 0.0) et (0.75, 0.75, 0.0)*/
    

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_triangle_data), g_color_triangle_data, GL_STATIC_DRAW);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );
    glEnableVertexAttribArray(1);




    GLuint vertexbufer;
    glGenBuffers(1, &vertexbufer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_triangle_data), g_vertex_triangle_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);



   // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 2*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
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
    glutInitDisplayMode(GLUT_RGB);
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
