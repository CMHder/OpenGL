#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
 
#define SOLID 1
#define WIRE 2
 
int moveX,moveY;
int spinX = 0;
int spinY = 0;
int des = 0;
 
 
void init() {   //��������λ�����ù�Դ
   //�����Դ����ɫ��λ��
   GLfloat ambient[] = { 0.5, 0.8, 0.1, 0.1 };  
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  
   GLfloat position[] = { -80.0, 50.0, 25.0, 1.0 };  
   
   //ѡ�����ģ��
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };  
   GLfloat local_view[] = { 0.0 };  
   glClearColor(0.0, 0.0, 0.0, 0.0);   //�ӿڱ������͵���ɫ
  glShadeModel(GL_FLAT);  
   
   //������Դ
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);  //���û�����
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);  //���������
   glLightfv(GL_LIGHT0, GL_POSITION, position);  //���ù�Դλ��
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);  
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);  
  
   //�������պ͹�Դ
   glEnable(GL_LIGHTING);   //��������
   glEnable(GL_LIGHT1);   //����һ�Ź�Դ
}
 
//����
void drawBall(double R, double x, double y,double z, int MODE) {
    glPushMatrix();
    glTranslated(x,y,z);
    if (MODE == SOLID) {
        glutSolidSphere(R,30,30);
    } 
	else if (MODE ==WIRE) {
        glutWireSphere(R,20,20);
    }
    glPopMatrix();
}
 
//������
void drawHalfBall(double R, double x, double y,double z, int MODE) {
    glPushMatrix();
    glTranslated(x,y,z);
    GLdouble eqn[4]={0.0, 1.0, 0.0, 0.0};
    glClipPlane(GL_CLIP_PLANE0,eqn);  
    glEnable(GL_CLIP_PLANE0);  //����ͼ���и�ܵ�,��glDisable���Ӧ
    if (MODE == SOLID) {
        glutSolidSphere(R,20,20);
    } 
	else if (MODE ==WIRE) {
        glutWireSphere(R,20,20);
    }
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}
 
//��������
void drawSkewed(double l, double w, double h, double x, double y, double z, int MODE) {
    glPushMatrix();
    glScaled(l, w, h);   //glScaled(10.0f,10.0f,10.0f)��ʾ����ǰͼ����x,y,z��ֱ�Ŵ�Ϊԭ����10��
    glTranslated(x, y, z);
    if (MODE == SOLID) {
        glutSolidCube(1);
    } 
	else if (MODE ==WIRE) {
        glutWireCube(1);
    }
    glPopMatrix();
}
 
void display(void) {
    //�����������ɫ
    glClear(GL_COLOR_BUFFER_BIT);
    //�����ɫ
    glColor3f(1.0, 1.0, 1.0); 
    //Բ�����������
    glLoadIdentity();

    //���ĸ��ط���
    gluLookAt(-2.0, -1.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //�ú�������һ����ͼ���󣬲��뵱ǰ������ˡ�
	//�൱�����ǵ��Դ�λ����(-2.0,-1.0,20.0)�����۾�����(0.0,0.0,0.0),��ԭ�㡣�������������(0.0,1.0,0.0),y��Ϊ1������Ϊ0����ʾ�Դ����ϣ���������������� 

    glPushMatrix();
    glRotated(spinX, 0, 1, 0); //glRotatef( angle, x, y, z )�����������ǽ���ǰ����ϵ��a( x, y, z )����Ϊ��ת����תangle�Ƕȡ�
    glRotated(spinY, 1, 0, 0);
    glTranslated(0, 0, des);
    
    drawBall(2, 0, 0, 0, SOLID);  //ͷ
   
    drawSkewed(5, 4, 4, 0, -1, 0, SOLID);  //����
    
    drawHalfBall(1, 3.5, -2, 0, SOLID);  //���
    drawHalfBall(1, -3.5, -2, 0, SOLID);
    
    drawSkewed(1, 3, 1, 3.5, -1.3, 0, SOLID);  //�첲
    drawSkewed(1, 3, 1, -3.5, -1.3, 0, SOLID);
    
    drawBall(1, 3.5, -6.4, 0, SOLID);  //��
    drawBall(1, -3.5, -6.4, 0, SOLID);
    
    drawSkewed(1.2, 3, 2, 1, -2.4, 0, SOLID);  //��
    drawSkewed(1.2, 3, 2, -1, -2.4, 0, SOLID);
 
    drawSkewed(1.5, 1, 3, 0.9, -9.2, 0, SOLID);  //��
    drawSkewed(1.5, 1, 3, -0.9, -9.2, 0, SOLID);

    glPopMatrix();
    glutSwapBuffers();
}

//������¼�
void mouseClick(int btn, int state, int x, int y) {
    moveX = x;
    moveY = y;
    GLfloat ambient[] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0.1 }; 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);    //���û����� 
    glEnable(GL_LIGHT0);  //���ù�Դ
}
 
//�����¼�
void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        spinX -= 2;
        break;
    case 'd':
         spinX += 2;  
        break;
    case 'w':
        des += 2;
        break;
    case 's':
        des -= 2;
        break;
    }
    glutPostRedisplay();
}

// ����ƶ��¼� 
void mouseMove(int x, int y) {
    int dx = x - moveX;
    int dy = y - moveY;
    printf("dx;%dx,dy:%dy\n",dx,dy);
    spinX += dx;
    spinY += dy;
    glutPostRedisplay();  //glutPostRedisplay�������ǵ�ǰ������������ʾ,�����ʹ��ѭ������ĵ�������ʾ����.    
	moveX = x;
    moveY = y;
}
 
void reshape(int w, int h) {
    
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);  //�����ӿڴ�С
    glMatrixMode(GL_PROJECTION);  //ͶӰ��ʾ
    glLoadIdentity();  //����ԭ������Ļ����
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);  //����ģ���Ӿ�
    glMatrixMode(GL_MODELVIEW);
}
 
int main(int argc, char** argv) {
   
    glutInit(&argc, argv);  //��ʼ��
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //������ʾģʽ
    glutInitWindowSize(500, 500);  //��ʼ�����ڴ�С
    glutInitWindowPosition(100, 100);  //�������ϽǴ���λ��
    glutCreateWindow(argv[0]);  //��������
    init();    //��ʼ��
    glutDisplayFunc(display);  //��ʾ����

    glutReshapeFunc(reshape);  //���ڴ�С�ı�ʱ����Ӧ
   
    glutMouseFunc(mouseClick);   //������¼�������������ɿ�ʱ����
    glutMotionFunc(mouseMove); //����ƶ��¼���"��갴��"���ƶ�ʱ����
    glutKeyboardFunc(keyPressed);  //�����¼�
 
    glutMainLoop(); //ѭ��
    return 0;
}
