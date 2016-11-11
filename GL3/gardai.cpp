#include "include.h"

  void affichage(void)
  {
    /*Initialisation des pixels */
    glClear(GL_COLOR_BUFFER_BIT);
    /* dessin d'un polygone (rectangle) avec les sommets en (0.25, 0.25, 0.0) et (0.75, 0.75, 0.0)*/
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5, -0.5);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5, 0.5);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-0.5, 0.5);
    glEnd();

    /* On force l'affichage du resultat */
    glFlush();
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
    glutInitWindowSize(500, 500);
    glutCreateWindow("exemple 1");

    /* Initialisation d'OpenGl */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /* On passe à 2 pixels pour des raisons de clarté */
    glPointSize(1.0);

    /* enregistrement des fonctions de rappels */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);

    /* entree dans la boucle principale de glut*/
    glutMainLoop();

    return 0;
  }
