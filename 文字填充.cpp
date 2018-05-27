#include <gl/glut.h>
#include <iostream>

typedef float Color[3];  //��ɫ��������

void getpixel(GLint x , GLint y , Color color)  //��ȡ���ص����ɫ
{
	glReadPixels(x , y , 1 , 1 , GL_RGB , GL_FLOAT , color);
}

int compareColor(Color color1 , Color color2) //��ɫ�Ƚ�
{
	if(color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2])
	{
		return 0; //������ɫ��ͬ������0
	}
	else
	{
		return 1; //������ɫ��ͬ������1
	}
}


void boundaryFill4(int x , int y , Color fillColor , Color boarderColor)  //���ڽӵ����
{
	Color interiorColor;
	getpixel(x,y,interiorColor);
	if(compareColor(interiorColor , fillColor) == 0 && compareColor(interiorColor , boarderColor) == 0)
	{ //δ��߽���δ���ʹ�
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
		boundaryFill4(x+1 , y , fillColor , boarderColor);
		boundaryFill4(x-1 , y , fillColor , boarderColor);
		boundaryFill4(x , y+1 , fillColor , boarderColor);
		boundaryFill4(x , y-1 , fillColor , boarderColor);
	}
}

/* void boundaryFill8(int x , int y , Color fillColor , Color boarderColor)  //���ڽӵ����
{
	Color interiorColor , a , b , c , d;
	getpixel(x , y , interiorColor);
	getpixel(x+1 , y , a);
	getpixel(x , y-1 , b);
	getpixel(x , y+1 , c);
	getpixel(x-1 , y ,d);
	int i = 0;
	//���ڽӵ㳬����������߽���ɫ��ͬ����õ�ᱻ�����������ص�����
	if(compareColor(a , boarderColor) == 1) i++;
	if(compareColor(b , boarderColor) == 1) i++;
	if(compareColor(c , boarderColor) == 1) i++;
	if(compareColor(d , boarderColor) == 1) i++;
	if(i <= 1)
	{
		if(compareColor(interiorColor , fillColor) == 0 && compareColor(interiorColor , boarderColor) == 0)
		{
			glBegin(GL_POINTS);
	        glVertex2f(x , y);
	        glEnd();
			boundaryFill8(x+1 , y , fillColor , boarderColor);
			boundaryFill8(x , y-1 , fillColor , boarderColor);
			boundaryFill8(x-1 , y , fillColor , boarderColor);
			boundaryFill8(x , y+1 , fillColor , boarderColor);
			boundaryFill8(x+1 , y-1 , fillColor , boarderColor);
			boundaryFill8(x-1 , y-1 , fillColor , boarderColor);
			boundaryFill8(x-1 , y+1 , fillColor , boarderColor);
			boundaryFill8(x+1 , y+1 , fillColor , boarderColor);
		}
	}
}
*/


void shape()
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(3);
	glVertex2i(190 , 290);
	glVertex2i(240 , 290);
	glVertex2i(240 , 200);
	glVertex2i(190 , 200);
	glVertex2i(190 , 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(200 , 280);
	glVertex2i(230 , 280);
	glVertex2i(230 , 250);
	glVertex2i(200 , 250);
	glVertex2i(200 , 280);
	glEnd();

	
	glBegin(GL_LINE_LOOP);
	glVertex2i(200 , 240);
	glVertex2i(230 , 240);
	glVertex2i(230 , 210);
	glVertex2i(200 , 210);
	glVertex2i(200 , 240);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(270 , 270);
	glVertex2i(270 , 285);
	glVertex2i(300 , 285);
	glVertex2i(300 , 270);
	glVertex2i(270 , 270);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glLineWidth(3);
	glVertex2i(270 , 245);
	glVertex2i(270 , 265);
	glVertex2i(300 , 265);
	glVertex2i(300 , 245);
	glVertex2i(270 , 245);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(250 , 200);
	glVertex2i(260 , 220);
	glVertex2i(260 , 290);
	glVertex2i(310 , 290);
	glVertex2i(310 , 190);
	glVertex2i(290 , 220);
	glVertex2i(300 , 210);
	glVertex2i(300 , 240);
	glVertex2i(270 , 240);
	glVertex2i(270 , 220);
	glVertex2i(250 , 200);
	glEnd();

}


void display()
{
	Color fillColor = {0.0 , 0.0 , 0.0};// ��ɫ�������
	Color boarderColor = {0.0 , 0.0 , 0.0}; //������ɫ���ֱ߿�
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0 , 0 , 500 , 500);

	glColor3fv(boarderColor);
	shape();

	glColor3fv(fillColor);
	boundaryFill4(192 , 220 , fillColor , boarderColor); //���ڽӵ�����ٶȿ�
	boundaryFill4(265 , 250 , fillColor , boarderColor);
	glFlush();
}


int main(int argc , char *argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500 , 500);
    glutInitWindowPosition(100, 100);
	glutCreateWindow("My Word");
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0 , 500.0 , 0.0 , 500.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}