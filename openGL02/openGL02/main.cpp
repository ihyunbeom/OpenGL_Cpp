#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include<stdio.h>

GLfloat theta = -60;
GLfloat mexTheta = 60;
GLfloat minTheta = -60;
GLfloat up = 1; // ���� ����(��:1 �Ʒ�:0)

void Draw_Body() {
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
}
/*---------------���---------------*/
void Draw_UpperArm() {
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.7, 0.3, 0.0);
	glVertex3f(0.7, 0.0, 0.0);
	glEnd();
}

void GoToShoulderCoordinates() {
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
}

void Draw_Left_UpperArm() { // ���� ���
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.7, 0.3, 0.0);
	glVertex3f(-0.7, 0.0, 0.0);
	glEnd();
}

void GoToShoulderCoordinates_L() {
	glTranslatef(-0.5, 0.5, 0.0);
	glRotatef(theta*-1, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
}
/*---------------�ȶ�---------------*/
void Draw_LowerArm() {
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.7, 0.3, 0.0);
	glVertex3f(0.7, 0.0, 0.0);
	glEnd();
}

void GoToElbowCoordinates() {
	glTranslatef(0.7, 0.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
}

void Draw_Left_LowerArm() { // ���� �ȶ�
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.7, 0.3, 0.0);
	glVertex3f(-0.7, 0.0, 0.0);
	glEnd();
}

void GoToElbowCoordinates_L() {
	glTranslatef(-0.7, 0.0, 0.0);
	glRotatef(theta*-1, 0.0, 0.0, 1.0);
}
/*---------------��---------------*/
void Draw_Hand() {
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.25, 0.35, 0.0);
	glVertex3f(0.5, 0.15, 0.0);
	glVertex3f(0.25, -0.05, 0.0);
	glEnd();
}

void GoToWristCoordinates() {
	glTranslatef(0.7, 0.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
}

void Draw_Left_Hand() { // �޼�
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.25, 0.35, 0.0);
	glVertex3f(-0.5, 0.15, 0.0);
	glVertex3f(-0.25, -0.05, 0.0);
	glEnd();
}

void GoToWristCoordinates_L() {
	glTranslatef(-0.7, 0.0, 0.0);
	glRotatef(theta*-1, 0.0, 0.0, 1.0);
}

void drawArm() { // ������ �� ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Draw_Body();
	glPushMatrix();
	
	GoToShoulderCoordinates();
	Draw_UpperArm();
	glPushMatrix();
	
	GoToElbowCoordinates();
	
	Draw_LowerArm();
	glPushMatrix();
	
	GoToWristCoordinates();
	Draw_Hand();
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawArm_L() { // ���� �� ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	Draw_Body();
	glPushMatrix();

	GoToShoulderCoordinates_L();
	Draw_Left_UpperArm();
	glPushMatrix();

	GoToElbowCoordinates_L();

	Draw_Left_LowerArm();
	glPushMatrix();

	GoToWristCoordinates_L();
	Draw_Left_Hand();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void wave_Arms() { // �� ���� �Լ�
	if (theta <= mexTheta && up == 1) { // ������ ���� ���⿡ ���� ������ �����մϴ�.
		theta++;
		if (theta > mexTheta)
			up = 0;
	}
	else if (theta >= minTheta && up == 0) {
		theta--;
		if (theta < minTheta)
			up = 1;
	}
}

void MyDisplay() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	wave_Arms();
	drawArm();
	drawArm_L();
	glEnd();
	glutSwapBuffers();

}

void MyTimer(int Value) {

	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600); 
	glutInitWindowPosition(100, 0);
	glutCreateWindow("OpenGL ������");
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();
	return 0;
}