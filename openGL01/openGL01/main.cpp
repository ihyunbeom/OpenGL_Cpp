#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include<stdio.h>

GLfloat x, y; // ���� �ʱ� ��ġ ��
GLfloat dx, dy; // ���� �̵� ũ��(�ӵ�)
GLfloat xDir, yDir; // �̵� ����

void DrawCircle(float cx, float cy, float r)
{
	float x1, y1, x2, y2;
	float angle;
	double radius = r;

	x1 = cx, y1 = cy;
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();

}

void moveAndDraw() {
	
	x += xDir*dx; // ������ġ = ���� * �̵�ũ��
	y += yDir*dy;

	/*
	x���� ȭ���� �Ѿ�� ���(����,������)�� ���� ���� ���� �����Ѵ�.
	������ �̷л� -1~1,-2~2 �̴�.
	������ ������ â�� ���鶧���� ���� �߸��� �ȴ�. 
	���� 0.1 ������ ���� ����.
	*/
	if ((xDir < 0 && x < -0.9) || (xDir > 0 && x > 0.9)) {
		xDir = -xDir; // ���� ȭ�� ������ ����� �Ǹ� -1�� ���ؼ� ������ �ٲ۴�.
	}
	if ((yDir < 0 && y < -1.9) || (yDir > 0 && y > 1.9)) { // ȭ���� 300*600 �̱⶧���� y�� ������ -2~2 �̴�.
		yDir = -yDir;
	}	

}

void MyDisplay() {

	moveAndDraw(); // moveAndDraw() �Լ� ����
	glClear(GL_COLOR_BUFFER_BIT); // ���� �ִ� ���� ������ �����.
	DrawCircle(x + dx, y + dy, 0.1); //���� �׸���.
	glEnd();
	glutSwapBuffers();

}

void MyTimer(int Value) {

	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv) {

	// ���� �ʱ� ��ġ ��
	x = -0.9;
	y = 0;

	// ���� �̵� ũ��(�ӵ�)
	dx = 0.01;
	dy = 0.01;

	// �̵� ����
	xDir = 1;
	yDir = 1;	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(300, 600); // �籸���� ũ��� ����ϰ� �ϱ� ���ؼ� ũ�⸦ ����.
	glutInitWindowPosition(100, 0);
	glutCreateWindow("OpenGL ������");
	glClearColor(0.2, 0.58, 0.2, 1.0); // �籸���� ������ ���ؼ� ���� ����.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
	glOrtho(-1.0, 1.0, -2.0, 2.0, 1.0, -1.0); // ȭ���� 1:2 �����̱� ������, bottom �� top ���� �ι�� �÷���� �Ѵ�.   
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();
	return 0;
}
