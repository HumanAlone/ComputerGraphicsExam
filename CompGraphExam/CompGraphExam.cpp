// CompGraphExam.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "C:\Users\HumanAlone\Documents\Visual Studio 2015\Projects\CompGraphExam\CompGraphExam\Glaux.h"
#include <tchar.h>
#pragma comment (lib, "C:\\Users\\HumanAlone\\Documents\\Visual Studio 2015\\Projects\\CompGraphExam\\lib\\Glaux.lib")
using namespace std;

float angle = 0;
float bangle = 0;
float shift = 2.0;
float shift_cube = 0;

// Параметры материала чайника
float mat_diff[] = { 0.9f,0.2f,0.0f };
float mat_amb[] = { 0.2f,0.2f,0.2f };
float mat_spec[] = { 0.6f,0.6f,0.6f };
float mat_shininess = 0.1f * 128;

// Параметры материала куба
float mat_diff_cube[] = { 1.0f,1.0f,1.0f};
float mat_amb_cube[] = { 1.0f,1.0f,1.0f };
float mat_spec_cube[] = { 1.0f,1.0f,1.0f };
float mat_shininess_cube = 0.5f*128;

// Массив для хранения текстуры =)
GLuint  texture[1];     

// Загрузка картинки и конвертирование в текстуру
GLvoid LoadGLTextures()
{
	// Загрузка картинки
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(L"C:/Users/HumanAlone/Documents/Visual Studio 2015/Projects/CompGraphExam/images/1.bmp");
	//texture2 = auxDIBImageLoad(L"C:/Users/HumanAlone/Documents/Visual Studio 2015/Projects/CompGraphExam/images/2.bmp");
	//texture3 = auxDIBImageLoad(L"C:/Users/HumanAlone/Documents/Visual Studio 2015/Projects/CompGraphExam/images/3.bmp");
	//texture4 = auxDIBImageLoad(L"C:/Users/HumanAlone/Documents/Visual Studio 2015/Projects/CompGraphExam/images/4.bmp");
	//texture5 = auxDIBImageLoad(L"C:/Users/HumanAlone/Documents/Visual Studio 2015/Projects/CompGraphExam/images/5.bmp");
	//texture6 = auxDIBImageLoad(L"C:/Users/HumanAlone/Documents/Visual Studio 2015/Projects/CompGraphExam/images/6.bmp");

	// Создание текстуры
	glGenTextures(1, &texture[0]);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

}

// Функция инициализации, задаёт начальное сосотояние OpenGL
void init()
{
	LoadGLTextures();			// Загрузка текстур
	glEnable(GL_TEXTURE_2D);	// Разрешение наложение текстуры

	glClearColor(0.0, 0.6, 0.6, 0.7);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	GLfloat light_ambient[] = {0.0,0.0,0.0,1.0};
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1, 0.5, 0, 1 };
	GLfloat light_position[] = { 0, -0.5, 2.0, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Функция рендеринга куба в блоке glBegin()-glEnd()
void DrawCube()
{	
	glBegin(GL_QUADS);
	
	// Передняя грань
	glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
															 
	// Задняя грань
	glNormal3f(0.0f, 0.0f, -1.0f);     // Нормаль указывает от наблюдателя
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); 
															  
	// Верхняя грань
	glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); 
															
	// Нижняя грань
	glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
															 
	// Правая грань
	glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); 
	
	// Левая грань
	glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); 
	glEnd();        
}

// Функция для рендеринга геометрии
void display(void) 
{
	// Очищаем буфер кадра и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Рисуем куб
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb_cube);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff_cube);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec_cube);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_cube);

	glPushMatrix();
	
	glTranslatef(-1.5, shift_cube, -1.0);
	glRotatef(bangle, 1, 0, 1);
	DrawCube();
	
	glPopMatrix();

	// Чайник рисуем
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(shift,0.0,-1.0);
	glRotatef(angle,1,1,0);
	glutSolidTeapot(1.0);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

// Анимация
void motion()
{
//shift = 0.0004f * glutGet(GLUT_ELAPSED_TIME);
//shift_cube = 0.0004f * glutGet(GLUT_ELAPSED_TIME);
shift += 0.0007;
shift_cube += 0.0007;
angle = 0.04f * glutGet(GLUT_ELAPSED_TIME);
bangle = -0.04f * glutGet(GLUT_ELAPSED_TIME);

glutPostRedisplay();
}

// Выход при помощи клавиши Escape
void Keyboard(unsigned char key,int x, int y) 
{
	const char ESCAPE = '\033';
	const char SPACE = '\040';
	if (key == ESCAPE)
		exit(0);
	if (key == SPACE)
	{
		shift = 2.0;
		shift_cube = 0;
	}
}

// Функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,w,0,h,-1.0,-1.0);
	gluPerspective(45.0, (GLfloat)w / h, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0f,0.0f,8.0f,
		0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f
		);
	
}

// Главный цикл приложения
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366,768);
	glutCreateWindow("Экзамен по компьютерной графике");
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(motion);
	glutKeyboardFunc(Keyboard);
	init();
	glutMainLoop();
	
	return 0;
}




