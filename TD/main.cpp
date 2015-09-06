#include "GUI\GameWorld.h"

GameWorld world;

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	world.draw();

	glPopMatrix();
	glutSwapBuffers();
}

void Update(int a)
{
	world.update();
	glutPostRedisplay();
	glutTimerFunc(TIME, Update, 0);
}

void MouseHandler(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			world.mouseLeftClickPress(x, y);
			break;
		case GLUT_RIGHT_BUTTON:
			world.mouseRightClickPress(x, y);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			world.moseLeftClickRelease(x, y);
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
		}
	}
}

int main(int argc, char **argv)
{
	/*
	Set up the world
	*/
	int WIDTH = 700;
	int HEIGHT = 500;
	world.init(WIDTH / SCALE, HEIGHT / SCALE);
	/*
	Init OpenGL
	*/
	glutInit(&argc, argv);
	/*
	Create window
	*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Tower Defence");
	/*
	Configurate window
	*/
	glClearColor(0.2, 0.8, 0.4, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	glutDisplayFunc(Display);
	glutTimerFunc(60, Update, 0);
	glutMouseFunc(MouseHandler);

	glutMainLoop();
}
