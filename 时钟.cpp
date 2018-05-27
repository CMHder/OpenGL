#include <gl\glut.h>    
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include<cmath>
#include<iostream>

const int Width = 600;
const int Height = 600;

const GLfloat PI = 3.141592653f;

// ��ǰʱ�䣬ʱ �� ��
float h = 0.0f;
float m = 0.0f;
float s = 0.0f;

void setPixel(int x, int y)
{

    glVertex2i(x, y);
}

/*
    8·�Գ�
*/
void Cirpot(int x0, int y0, int x, int y)
{
    // 1
    setPixel((x0 + x), (y0 + y));
    // 2
    setPixel((x0 + y), (y0 + x));
    // 3
    setPixel((x0 + y), (y0 - x));
    // 4
    setPixel((x0 + x), (y0 - y));
    // 5
    setPixel((x0 - x), (y0 - y));
    // 6
    setPixel((x0 - y), (y0 - x));
    // 7
    setPixel((x0 - y), (y0 + x));
    // 8
    setPixel((x0 - x), (y0 + y));
}

/*
    �е㻭Բ�㷨
*/
void MidPoint_Circle(int x0, int y0, int r)
{
    int x = 0;
    int y = r;
    float d = 1.25 - r;     
    Cirpot(x0, y0, x, y);
    while (x <= y)
    {
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        Cirpot(x0, y0, x, y);
    }
}


/*
��ʱ�ӵĺ���
*/
void myDisplay(void)
{
	// �õ�ǰ���ɫ�����ɫ�����������趨���ڵı���ɫ
    
    //glColor3f(0.1f, 0.2f, 0.1f); // ��ɫ
    int cx = Width / 2; //���ĵ�
    int cy = Height / 2;
    int R = 100; // �뾶��
    int i; 

    // 2 ����ʱ�� Բ�ϵĿ̶ȣ��̶ȴ�ϸ�����Ȳ�һ��
    int lines = 60;
    float ship1 = 10;
    float ship2 = 5;
    for (i = 0; i<lines; i++)
    {
        if (i % 5 == 0)    //  0��12��-11�Ķ���
        { 
            glLineWidth(5);
            //glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_LINES);
            glVertex2f(cx + (R - ship1)*sin(2 * PI / lines * i), cy + (R - ship1)*cos(2 * PI / lines * i));
            glVertex2f(cx + R*sin(2 * PI / lines * i), cy + R*cos(2 * PI / lines * i));
            glEnd();
        }
        else
        {
            glLineWidth(2);  //�����Ŀ̶�
            //glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_LINES);
            glVertex2f(cx + (R - ship2)*sin(2 * PI / lines * i), cy + (R - ship2)*cos(2 * PI / lines * i));
            glVertex2f(cx + R*sin(2 * PI / lines * i), cy + R*cos(2 * PI / lines * i));
            glEnd();
        }
    }

    // 3 ����ʱ �� ���ϵ����ĵ�С�ڵ�
    glBegin(GL_POLYGON);
    for (i = 0; i<100; ++i)
        glVertex2i(cx + 5 * cos(2 * PI / 100*i), cy + 5 * sin(2 * PI / 100*i));
    glEnd();

    // 4 ����ʱ �� ���룬����ֱ�ߣ����̴�ϸ��һ��
    int h_len = R - 3 * ship1;
    int m_len = R - ship1;
    int s_len = R - ship1 + 2 * ship1;

    float s_Angle = s / 60.0;
    float m_Angle = (m * 60 + s) / 3600.0;
    float h2 = h >= 12 ? (h - 12) : h;
    float h_Angle = (h2 * 60 * 60 + m * 60 + s) / (12 * 60 * 60);

    glLineWidth(1); // ��
    glBegin(GL_LINES);
    glVertex2f(cx - 2 * ship1 * sin(2 * PI*s_Angle), cy - 2 * ship1*cos(2 * PI*s_Angle));
    glVertex2f(cx + (R - ship2)*sin(2 * PI*s_Angle), cy + (R - ship2)*cos(2 * PI*s_Angle));
    glEnd();

    glLineWidth(5); // ʱ
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + h_len*sin(2 * PI*h_Angle), cy + h_len*cos(2 * PI*h_Angle));
    glEnd();

    glLineWidth(3); // ��
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + m_len*sin(2 * PI*m_Angle), cy + m_len*cos(2 * PI*m_Angle));
    glEnd();

    // ˢ��
    glFlush();
}

/*
�ص�����
*/
void timerFunc(int value)
{
    s += 1;
    int carry1 = 0;
    if (s >= 60)
    {
        s = 0;
        carry1 = 1;
    }
    m += carry1;
    int carry2 = 0;
    if (m >= 60)
    {
        m = 0;
        carry2 = 1;
    }
    h += carry2;
    if (h >= 24)
        h = 0;

    glutPostRedisplay(); // �ػ�

    glutTimerFunc(1000, timerFunc, 1); // ÿһ����ִ��һ��
}

/*
��ʼ������
���ñ�������ȡʱ��
*/
void SetupRC(void)
{
    // ���ô���Ϊ��ɫ
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // ��ȡ���ص�ǰʱ��
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    h = sys.wHour;
    m = sys.wMinute;
    s = sys.wSecond;
}

void reshapse(GLsizei w, GLsizei h)//����������״�������ı�
{  
	 w=w>h?h:w;  
	 glViewport(0, 0, w, h);  
}  

void display()
{	
	int cx = Width / 2; //���ĵ�
    int cy = Height / 2;
    int R = 100; // �뾶��
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
	MidPoint_Circle(cx,cy,R);
	glEnd();


	glBegin(GL_LINES);
	myDisplay();
	glEnd();

	glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//���ô������Ͻǵ�λ��   
    glutInitWindowSize(Width, Height);
    glutCreateWindow("clock");
    //�۲������x����ֵ��0��200��y�Ǵ�0��150  
    gluOrtho2D(0.0, Width, 0.0, Height);
	SetupRC();

	glutReshapeFunc(reshapse);//���ڴ�С�ı䱣֤ͼ�β���������
    glutDisplayFunc(display);
	
	glutTimerFunc(1000, timerFunc, 1);

    glutMainLoop(); // glut�¼�����ѭ��
	
    return 0;
}
