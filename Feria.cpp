#include "texture.h"
#include "figuras.h"
#include "Camera.h"

//#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;  //Display List for the Monito

CFiguras mi_figura;
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
//static GLuint ciudad_display_list;   //Display List for the Monito


CCamera objcamera;  //Create objet Camera para edificio vista frontal

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };          // Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };          // Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };        // Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };       // Light Position


// VARIABLES
float cabina = 0.0;
float rueda = 0.0;// Rueda de la fortuna
float tex_skybox = 1.0; // Cambio dia/noche
float colorR = 1.0, colorG = 1.0, colorB = 1.0; // Color escenario
float varmartillo = 0.0;// Martillo mecánico
// VARIABLES

//NOMBRE TEXTURAS

CTexture dia;
CTexture noche;
CTexture concreto;
CTexture cromo;
CTexture morado_m;
CTexture negro_m;
CTexture rojo_m;
CTexture azul_m;
CTexture verde_m;
CTexture rosa_m;
CTexture naranja_m;
CTexture amarillo_m;

CFiguras figcielo; // para el cielo


void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);           // Negro de fondo 

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);                          // Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);                     // Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);                      // Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	//TEXTURAS

	dia.LoadTGA("textures/dia.tga");
	dia.BuildGLTexture();
	dia.ReleaseImage();

	noche.LoadTGA("textures/noche.tga");
	noche.BuildGLTexture();
	noche.ReleaseImage();

	concreto.LoadTGA("textures/concreto.tga");
	concreto.BuildGLTexture();
	concreto.ReleaseImage();

	cromo.LoadTGA("textures/cromo.tga");
	cromo.BuildGLTexture();
	cromo.ReleaseImage();

	morado_m.LoadTGA("textures/morado_m.tga");
	morado_m.BuildGLTexture();
	morado_m.ReleaseImage();

	negro_m.LoadTGA("textures/negro_m.tga");
	negro_m.BuildGLTexture();
	negro_m.ReleaseImage();

	rojo_m.LoadTGA("textures/rojo_m.tga");
	rojo_m.BuildGLTexture();
	rojo_m.ReleaseImage();

	azul_m.LoadTGA("textures/azul_m.tga");
	azul_m.BuildGLTexture();
	azul_m.ReleaseImage();

	verde_m.LoadTGA("textures/verde_m.tga");
	verde_m.BuildGLTexture();
	verde_m.ReleaseImage();

	rosa_m.LoadTGA("textures/rosa_m.tga");
	rosa_m.BuildGLTexture();
	rosa_m.ReleaseImage();
	
	naranja_m.LoadTGA("textures/naranja_m.tga");
	naranja_m.BuildGLTexture();
	naranja_m.ReleaseImage();

	amarillo_m.LoadTGA("textures/amarillo_m.tga");
	amarillo_m.BuildGLTexture();
	amarillo_m.ReleaseImage();

	



	objcamera.Position_Camera(0, 20, 90, 0, 40.0f, 0, 0, 1, 0);

	}

//-----Figuras-----

void cabinas(float t1, float t2)
{
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -25.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	
	mi_figura.cilindro(16.0, 5.0, 30.0, t1);
	glPopMatrix();

	glPushMatrix();// Base
	//glRotatef(90.0, 1.0, 0.0, 0.0);
	mi_figura.esfera2(16.0, 30.0, 30.0, t1);
	glPopMatrix();// Base

	//Barras
	glPushMatrix();
	glTranslatef(-16.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(16.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 16.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0, -16.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.5, 10.5, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.5, 10.5, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.5, -10.5, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.5, -10.5, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.5, 25.0, 30.0, t2);
	glPopMatrix();

	glPushMatrix();//Asiento
	glTranslatef(8.0, 0.0, 8.0);
	mi_figura.prisma(16.0, 5.0, 1.5, t1);
	glTranslatef(-16.0, 0.0, 0.0);
	mi_figura.prisma(16.0, 5.0, 1.5, t1);
	glPopMatrix();//Asiento

	glPopMatrix();


}

void rueda_fortuna(float x, float y, float z, float t1, float t2, float t3)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0.0, -50.0, -20.0);
	mi_figura.prisma(5.0, 150.0, 90.0, t1);//Base
	glPopMatrix();

	glTranslatef(0.0, 28.0, 0.0);
	glPushMatrix();//Barras

	glPushMatrix();
	glTranslatef(-30.0, 0.0, 0.0);
	glRotatef(-20.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(170.0, 10.0, 1.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0, 0.0, 0.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(170.0, 10.0, 1.0, t2);
	glPopMatrix();

	glPushMatrix();//Barras traseras
	glTranslatef(-30.0, 0.0, -41.0);
	glRotatef(-20.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(170.0, 10.0, 1.0, t2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0, 0.0, -41.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(170.0, 10.0, 1.0, t2);
	glPopMatrix();//Barras traseras

	glPopMatrix();//Barras

	glPushMatrix();//Centro
	glTranslatef(0.0, 80.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(8.0, 1.0, 30.0, t2);
	glPopMatrix();//Centro

	glPushMatrix();//Centro trasero
	glTranslatef(0.0, 80.0, -42.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(8.0, 1.0, 30.0, t2);
	glPopMatrix();//Centro trasero

	glPushMatrix();//Rueda
	glTranslatef(0.0, 80.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(rueda, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(0.0, -3.0, 0.0);
	mi_figura.cilindro(100.0, 1.0, 150.0, t3);
	glTranslatef(0.0, -38.0, 0.0);
	mi_figura.cilindro(100.0, 1.0, 150.0, t3);
	glPopMatrix();

	glTranslatef(0.0, -20.0, 0.0);
	
	glPushMatrix();
	glPushMatrix();//Abajo
	glTranslatef(0.0, 0.0, 126.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Arriba
	glTranslatef(0.0, 0.0, -70.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Derecha
	glTranslatef(100.0, 0.0, 20.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Izquierda
	glTranslatef(-100.0, 0.0, 20.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Abajo derecha
	glTranslatef(60.0, 0.0, 90.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Abajo izquierda
	glTranslatef(-60.0, 0.0, 90.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Arriba derecha
	glTranslatef(75.0, 0.0, -40.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Arriba izquierda
	glTranslatef(-75.0, 0.0, -40.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPopMatrix();//

	glPopMatrix();//Rueda

	glPopMatrix();

}

void martillo_mecanico(float x, float y, float z, float roatY, float t1, float t2, float t3, float t4, float t5) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();
	//Base
	mi_figura.prisma(8, 85, 100, t1);
	//Controlador
	glPushMatrix();
	glTranslatef(-25.0f, 13.0f, 35.0f);
	mi_figura.prisma(17.5f, 7.0f, 8.0f, t2);
	glPushMatrix();
	glTranslatef(1.0f, 8.25f, 2.0f);
	mi_figura.cilindro(0.25f, 3.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 3.5f, 0.0f);
	mi_figura.esfera(0.625f, 40, 40, t2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 8.25f, -2.0f);
	mi_figura.cilindro(0.25f, 3.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 3.5f, 0.0f);
	mi_figura.esfera(0.625f, 40, 40, t2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 8.25f, 3.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glTranslatef(0.0f, 0.0f, -1.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glTranslatef(0.0f, 0.0f, -1.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glTranslatef(0.0f, 0.0f, -1.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glTranslatef(0.0f, 0.0f, -1.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glTranslatef(0.0f, 0.0f, -1.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glTranslatef(0.0f, 0.0f, -1.0f);
	mi_figura.cilindro(0.375f, 0.75f, 40, t3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 9.5f, 3.875f);
	mi_figura.prisma(1.5f, 7.0f, 0.25f, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 9.5f, -3.875f);
	mi_figura.prisma(1.5f, 7.0f, 0.25f, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.375f, 9.5f, 0.0f);
	mi_figura.prisma(1.5f, 0.25f, 8.0f, 0);
	glPopMatrix();
	glPopMatrix();
	//Estructura del martillo
	glPushMatrix();
	glTranslatef(0.0f, 64.0f, 15.0f);
	mi_figura.prisma(120.0f, 12.0f, 3.0f, t4);
	glPushMatrix();
	glTranslatef(0.0f, 60.0f, 1.5f);
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(6.0f, 3.0f, 40, t4);
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, -30.0f);
	mi_figura.prisma(120.0f, 12.0f, 3.0f, t4);
	glPushMatrix();
	glTranslatef(0.0f, 60.0f, 1.5f);
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(6.0f, 3.0f, 40, t4);
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	mi_figura.cilindro(3.5f, 1.5f, 40, t4);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.cilindro(1.75f, 0.75f, 40, t4);
	glPopMatrix();
	glRotatef(varmartillo, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, -30.0f, 0.0f);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	mi_figura.cilindro(3.5f, 1.5f, 40, t4);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.cilindro(1.75f, 0.75f, 40, t4);
	glPopMatrix();
	mi_figura.cilindro(3.0f, 30.0f, 40, t4);
	glPushMatrix();
	glTranslatef(0.0f, 16.5f, 0.0f);
	mi_figura.prisma(3.0f, 7.0f, 165.0f, t4);
	//Cabina superior
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 88.5f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(12.0f, 6.0f, 40, t5);
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 18.0f);
	mi_figura.esfera2(12.0f, 40, 40, t5);
	glRotatef(-90, 1, 0, 0);
	glPushMatrix();
	glTranslatef(12.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glTranslatef(-24.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glTranslatef(12.0f, 0.0f, 12.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 0.0f, -24.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8.5f, 0.0, 8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8.5f, 0.0, -8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5f, 0.0, 8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5f, 0.0, -8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Cabina inferior
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -88.5f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0.0f, -6.0f, 0.0f);
	mi_figura.cilindro(12.0f, 6.0f, 40, t5);
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, -18.0f);
	glRotatef(180, 1, 0, 0);
	mi_figura.esfera2(12.0f, 40, 40, t5);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(8.5f, 0.0f, 8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8.5f, 0.0f, -8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5f, 0.0f, 8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5f, 0.0f, -8.5f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(12.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(-24.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(-12.0f, 0.0f, 12.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 0.0f, -24.0f);
	mi_figura.cilindro(0.5f, 18.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//Escalera
	glPushMatrix();
	glTranslatef(-45.5f, -2.0f, 0.0f);
	mi_figura.prisma(4.0f, 6.0f, 33.0f, t1);
	glPopMatrix();
	//Barandal
	glPushMatrix();
	//Barandal vertical
	glTranslatef(42, 4, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, 16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, 16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, 16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	mi_figura.esfera(0.5f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(-16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(-16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(-16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(-16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(-16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	mi_figura.esfera(0.5f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0, 0, -16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, -16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0, 0, -33.0f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	mi_figura.esfera(0.5f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0, 0, -16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, -16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	mi_figura.esfera(0.5f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(16.5f, 0, 0);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	mi_figura.esfera(0.5f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0, 0, 16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, 16.5f);
	mi_figura.cilindro(0.5f, 20.0f, 40, cromo.GLindex);
	glTranslatef(0, 0, 16.5f);
	//Fin del barandal Vertcal
	//Barandal horizontal
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, -16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, -49.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, 0);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, -16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, -16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(16.5f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 16.5f);
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	mi_figura.cilindro(0.5f, 16.5, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Fin del varandal Horizontal
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

//-----Figuras-----


void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();
	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objcamera.mPos.x, objcamera.mPos.y, objcamera.mPos.z,
		objcamera.mView.x, objcamera.mView.y, objcamera.mView.z,
		objcamera.mUp.x, objcamera.mUp.y, objcamera.mUp.z);

	glPushMatrix();
	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0.0, 60.0, 0.0);
	figcielo.skybox(500.0, 600.0, 500.0, tex_skybox);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Poner codigo aqui
	glDisable(GL_LIGHTING);

	glPushMatrix(); //Plataforma principal
	glDisable(GL_LIGHTING);
	mi_figura.prisma(1.0, 500.0, 500.0, concreto.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//     CONSTRUCCIÓN DE ESCENARIO

	glPushMatrix();

	rueda_fortuna(0.0, 58.0, 10.0, negro_m.GLindex, naranja_m.GLindex, 0);

	martillo_mecanico(150.0f, 4.5f, 100.0f, 0.0f, negro_m.GLindex, rojo_m.GLindex, azul_m.GLindex, verde_m.GLindex, negro_m.GLindex);

	glPopMatrix();

	// ESCENARIO
	
	
	//Transparencias aquí
	glPopMatrix();
	glPopMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Transparencias


	//Todo antes de esto
	glDisable(GL_BLEND);
	//Fin transparencias
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glColor3f(colorR, colorG, colorB);
	glutSwapBuffers();
	glPopMatrix();

}
//a
void animacion()
{
	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)                             // Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);                 // Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 600);

	glMatrixMode(GL_MODELVIEW);                     // Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objcamera.Move_Camera(CAMERASPEED + 0.05);
		break;

	case 's':
	case 'S':
		objcamera.Move_Camera(-(CAMERASPEED + 0.05));
		break;

	case 'a':
	case 'A':
		objcamera.Strafe_Camera(-(CAMERASPEED + 0.05));
		break;

	case 'd':
	case 'D':
		objcamera.Strafe_Camera(CAMERASPEED + 0.05);
		break;

	case 'u':
		rueda = rueda + 10; // Rueda de la fortuna con teclado
	break;

	case 'f':
		tex_skybox = 1.0;
	break;

	case 'F':
		tex_skybox = 2.0;
	break;

	case 'c':
		colorR = 1.0;
		colorG = 1.0;
		colorB = 1.0;
	break;

	case 'C':
		colorR = 0.5;
		colorG = 0.5;
		colorB = 0.5;
	break;

	case 'v':
		varmartillo = varmartillo + 10.0;
	break;

	case 'b':
		cabina = cabina + 10;
		break;

	case 'B':
		cabina = cabina - 10;
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objcamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objcamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objcamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objcamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(800, 700);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow(" Proyecto Final"); // Nombre de la Ventana
										 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	glutMainLoop();

	return 0;
}