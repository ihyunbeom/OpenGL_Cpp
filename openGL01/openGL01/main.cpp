#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include<stdio.h>

GLfloat x, y; // 원의 초기 위치 값
GLfloat dx, dy; // 원의 이동 크기(속도)
GLfloat xDir, yDir; // 이동 방향

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
	
	x += xDir*dx; // 다음위치 = 방향 * 이동크기
	y += yDir*dy;

	/*
	x값이 화면을 넘어가는 경우(왼쪽,오른쪽)에 따라서 방향 값을 수정한다.
	범위는 이론상 -1~1,-2~2 이다.
	하지만 윈도우 창의 여백때문에 원이 잘리게 된다. 
	따라서 0.1 정도의 값을 뺐다.
	*/
	if ((xDir < 0 && x < -0.9) || (xDir > 0 && x > 0.9)) {
		xDir = -xDir; // 원이 화면 범위를 벗어나게 되면 -1를 곱해서 방향을 바꾼다.
	}
	if ((yDir < 0 && y < -1.9) || (yDir > 0 && y > 1.9)) { // 화면이 300*600 이기때문에 y의 범위는 -2~2 이다.
		yDir = -yDir;
	}	

}

void MyDisplay() {

	moveAndDraw(); // moveAndDraw() 함수 실행
	glClear(GL_COLOR_BUFFER_BIT); // 전에 있는 원의 흔적을 지운다.
	DrawCircle(x + dx, y + dy, 0.1); //원을 그린다.
	glEnd();
	glutSwapBuffers();

}

void MyTimer(int Value) {

	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv) {

	// 원의 초기 위치 값
	x = -0.9;
	y = 0;

	// 원의 이동 크기(속도)
	dx = 0.01;
	dy = 0.01;

	// 이동 방향
	xDir = 1;
	yDir = 1;	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(300, 600); // 당구대의 크기와 비슷하게 하기 위해서 크기를 조정.
	glutInitWindowPosition(100, 0);
	glutCreateWindow("OpenGL 이현범");
	glClearColor(0.2, 0.58, 0.2, 1.0); // 당구대의 느낌을 위해서 색을 조정.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
	glOrtho(-1.0, 1.0, -2.0, 2.0, 1.0, -1.0); // 화면이 1:2 비율이기 때문에, bottom 과 top 값을 두배로 늘려줘야 한다.   
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();
	return 0;
}
