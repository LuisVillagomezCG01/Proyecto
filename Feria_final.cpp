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
float sillas = 0.0, sillas_ab = -65.0;
float tira_pato = 0.0;
float g_carrusel = 0.0;
float g_martillo = 0.0;
//Variables animaciones

float rot_carrox = 0.0, rot_carroy = 0.0, rot_carroz = 0.0;
float mov_carrox = 0.0, mov_carroy = 0.0, mov_carroz = 0.0;

bool gira_rueda = false;
bool girando_rueda = true;

bool gira_carrusel = false;
bool girando_carrusel = true;

bool gira_sillas = false;
bool subiendo_sillas = true;
bool girando_sillas = false;
bool bajando_sillas = false;

bool gira_martillo = false;
bool baja_martillo = true;
bool sube_martillo = false;

//Montaña

//Recorrido automatica
float avanceZ = 0.0;
float roatCamara = 0.0;
bool recorrido = false;
bool inicio = true;
bool avance1 = true;
bool avance2 = false;
bool avance3 = false;
bool avance4 = false;
bool avance5 = false;
bool avance6 = false;
bool avance7 = false;
bool avance8 = false;
bool avance9 = false;
bool avance10 = false;
bool avance11 = false;
bool avance12 = false;
bool avance13 = false;
bool avance14 = false;
bool avance15 = false;
bool avance16 = false;
bool avance17 = false;
bool avance18 = false;
bool avance19 = false;
bool avance20 = false;
bool avance21 = false;
bool avance22 = false;
bool avance23 = false;
bool avance24 = false;
bool avance25 = false;
bool avance26 = false;
bool avance27 = false;
bool avance28 = false;
bool avance29 = false;
bool avance30 = false;

//bool
// VARIABLES KEYFRAMES

float varmartillo = 0;

//NOMBRE TEXTURAS

CTexture dia;
CTexture noche;
CTexture concreto;
CTexture cromo;
CTexture dorado;
CTexture morado_m;
CTexture negro_m;
CTexture rojo_m;
CTexture azul_m;
CTexture azulo_m;
CTexture verde_m;
CTexture verdeo_m;
CTexture rosa_m;
CTexture naranja_m;
CTexture amarillo_m;
CTexture vino_m;
CTexture vidrio;
CTexture amarillo_s;
CTexture rojo_s;
CTexture rayos;
CTexture pato1;
CTexture pato2;
CTexture madera_cerca;
CTexture hierro_negro;
CTexture base;
CTexture base2;
CTexture lona;
CTexture porcelana;
CTexture patron;
CTexture p_verde;
CTexture pasto;
CTexture camino;
CTexture luz;
CTexture carro_azul;

CFiguras figcielo; // para el cielo

#define MAX_FRAMES 200
int i_max_steps = 20;//Velocidad
int i_curr_steps = 0;

typedef struct _frame		//Encargada de guardar la información
{
	//Variables para GUARDAR Key Frames
	float varmartillo;
	//Incrementos
	float varmartilloInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];		//Arreglo de datos tipo frame
int FrameIndex = 50;			//introducir datos  COLOCAR UNO MAS QUE EL NUMERO DE DEFINICIONES MAS ABAJO
bool play = false;
int playIndex = 0;

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

	carro_azul.LoadTGA("textures/carro_azul.tga");
	carro_azul.BuildGLTexture();
	carro_azul.ReleaseImage();

	concreto.LoadTGA("textures/concreto.tga");
	concreto.BuildGLTexture();
	concreto.ReleaseImage();

	luz.LoadTGA("textures/luz.tga");
	luz.BuildGLTexture();
	luz.ReleaseImage();

	cromo.LoadTGA("textures/cromo.tga");
	cromo.BuildGLTexture();
	cromo.ReleaseImage();

	dorado.LoadTGA("textures/dorado.tga");
	dorado.BuildGLTexture();
	dorado.ReleaseImage();

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

	azulo_m.LoadTGA("textures/azulo_m.tga");
	azulo_m.BuildGLTexture();
	azulo_m.ReleaseImage();

	verde_m.LoadTGA("textures/verde_m.tga");
	verde_m.BuildGLTexture();
	verde_m.ReleaseImage();

	verdeo_m.LoadTGA("textures/verdeo_m.tga");
	verdeo_m.BuildGLTexture();
	verdeo_m.ReleaseImage();

	rosa_m.LoadTGA("textures/rosa_m.tga");
	rosa_m.BuildGLTexture();
	rosa_m.ReleaseImage();
	
	naranja_m.LoadTGA("textures/naranja_m.tga");
	naranja_m.BuildGLTexture();
	naranja_m.ReleaseImage();

	amarillo_m.LoadTGA("textures/amarillo_m.tga");
	amarillo_m.BuildGLTexture();
	amarillo_m.ReleaseImage();

	vino_m.LoadTGA("textures/vino_m.tga");
	vino_m.BuildGLTexture();
	vino_m.ReleaseImage();

	vidrio.LoadTGA("textures/vidrio.tga");
	vidrio.BuildGLTexture();
	vidrio.ReleaseImage();

	rojo_s.LoadTGA("textures/rojo_s.tga");
	rojo_s.BuildGLTexture();
	rojo_s.ReleaseImage();

	rayos.LoadTGA("textures/rayos.tga");
	rayos.BuildGLTexture();
	rayos.ReleaseImage();

	amarillo_s.LoadTGA("textures/amarillo_s.tga");
	amarillo_s.BuildGLTexture();
	amarillo_s.ReleaseImage();
	
	pato1.LoadTGA("textures/pato1.tga");
	pato1.BuildGLTexture();
	pato1.ReleaseImage();

	pato2.LoadTGA("textures/pato2.tga");
	pato2.BuildGLTexture();	
	pato2.ReleaseImage();

	madera_cerca.LoadTGA("textures/madera_perchero.tga");
	madera_cerca.BuildGLTexture();
	madera_cerca.ReleaseImage();

	hierro_negro.LoadTGA("textures/hierro_negro.tga");
	hierro_negro.BuildGLTexture();
	hierro_negro.ReleaseImage();

	base.LoadTGA("textures/base.tga");
	base.BuildGLTexture();
	base.ReleaseImage();
	 
	base2.LoadTGA("textures/base2.tga");
	base2.BuildGLTexture();
	base2.ReleaseImage();

	lona.LoadTGA("textures/lona_roja.tga");
	lona.BuildGLTexture();
	lona.ReleaseImage();

	porcelana.LoadTGA("textures/porcelana.tga");
	porcelana.BuildGLTexture();
	porcelana.ReleaseImage();

	patron.LoadTGA("textures/patron.tga");
	patron.BuildGLTexture();
	patron.ReleaseImage();

	p_verde.LoadTGA("textures/p_verde.tga");
	p_verde.BuildGLTexture();
	p_verde.ReleaseImage();

	camino.LoadTGA("textures/concreto_caminos.tga");
	camino.BuildGLTexture();
	camino.ReleaseImage();


	objcamera.Position_Camera(50, 20, 200, 50, 40.0f, 0, 0, 1, 0);

	}

//-----Figuras-----
//Realizamos funciones para no extendernos demasiado en el codigo
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
void rueda_fortuna(float x, float y, float z, float t2, float t3)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0.0, -50.0, -20.0);
	mi_figura.prisma(5.0, 150.0, 90.0, base2.GLindex);//Base
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
	mi_figura.cilindro(100.0, 1.0, 300.0, t3);
	glTranslatef(0.0, -38.0, 0.0);
	mi_figura.cilindro(100.0, 1.0, 300.0, t3);
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
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Derecha
	glTranslatef(100.0, 0.0, 20.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Izquierda
	glTranslatef(-100.0, 0.0, 20.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Abajo derecha
	glTranslatef(60.0, 0.0, 90.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Abajo izquierda
	glTranslatef(-60.0, 0.0, 90.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Arriba derecha
	glTranslatef(75.0, 0.0, -40.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
	cabinas(azul_m.GLindex, cromo.GLindex);
	glPopMatrix();

	glPushMatrix();//Arriba izquierda
	glTranslatef(-75.0, 0.0, -40.0);
	glRotatef(cabina, 0.0, 1.0, 0.0);
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
	mi_figura.prisma(8, 85, 100, base.GLindex);
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
	mi_figura.esfera(12.0, 30.0, 30.0, t4);
	glTranslatef(15.0f, 0.0f, 0.0f);
	mi_figura.esfera(12.0, 30.0, 30.0, t4);
	glTranslatef(-30.0f, 0.0f, 0.0f);
	mi_figura.esfera(12.0, 30.0, 30.0, t4);
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
	mi_figura.prisma(4.0f, 6.0f, 33.0f, base.GLindex);
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
void taza(float t1, float t2) {

	glPushMatrix();

	mi_figura.cilindro(5.0, 1.0, 30.0, t1);
	glPushMatrix();
	glTranslatef(0.0, 7.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	mi_figura.esfera2(7.0, 20.0, 20.0, t2);
	glPopMatrix();

	glPushMatrix();//Agarradera
	glTranslatef(-8.0, 1.5, 0.0);
	mi_figura.cilindro(0.5, 3.0, 30.0, t1);
	
	glPushMatrix();
	mi_figura.esfera(0.5, 30.0, 30.0, t1);
	glTranslatef(0.0, 3.0, 0.0);
	mi_figura.esfera(0.5, 30.0, 30.0, t1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0, 3.0, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	mi_figura.cilindro(0.5, 1.4, 30.0, t1);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	mi_figura.cilindro(0.5, 3.4, 30.0, t1);
	glPopMatrix();
	
	glPopMatrix();//Agarradera

	glPushMatrix();//Asiento
	
	glTranslatef(-3.0, 3.0, 0.0);
	mi_figura.prisma(1.0, 1.0, 8.2, t1);
	glTranslatef(6.0, 0.0, 0.0);
	mi_figura.prisma(1.0, 1.0, 8.2, t1);

	glPopMatrix();//Asiento

	glPushMatrix();
	mi_figura.cilindro(0.2, 6.0, 30.0, cromo.GLindex);
	glTranslatef(0.0, 6.0, 0.0);
	mi_figura.cilindro(0.8, 0.2, 15.0, cromo.GLindex);
	glPopMatrix();

	glPopMatrix();

}
void tetera(float t) {
	glPushMatrix();

	glPushMatrix();
	mi_figura.esfera(10.0, 50.0, 50.0, t);
	glTranslatef(0.0, 3.0, 0.0);
	mi_figura.cilindro(9.0, 15.0, 8.0, t);
	glTranslatef(0.0, 15.0, 0.0);
	mi_figura.cilindro(8.0, 5.0, 8.0, t);
	glTranslatef(0.0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	mi_figura.esfera2(7.5, 5.0, 5.0, t);
	glPopMatrix();
	glTranslatef(-5.0, 4.0, 0.0);
	mi_figura.cilindro(0.5, 3.0, 15.0, t);
	glTranslatef(0.0, 3.0, 0.0);
	mi_figura.esfera(0.5, 20.0, 20.0, t);
	glPushMatrix();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.cilindro(0.5, 3.0, 15.0, t);
	glTranslatef(0.0, 3.0, 0.0);
	mi_figura.esfera(0.5, 20.0, 20.0, t);
	glPopMatrix();
	glTranslatef(-2.2, 2.2, 0.0);
	
	glPushMatrix();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	mi_figura.cilindro(0.5, 5.0, 15.0, t);
	glTranslatef(0.0, 5.0, 0.0);
	mi_figura.esfera(0.5, 20.0, 20.0, t);
	glPopMatrix();
	glTranslatef(-5.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(135.0, 0.0, 0.0, 1.0);
	mi_figura.cilindro(0.5, 3.0, 15.0, t);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();


}
void tacitas(float x, float y, float z, float t2, float t3, float t4) {

	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();//Base
	//glRotatef(90.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro2(50.0, 1.0, 50.0, base2.GLindex, base2.GLindex);
	glPopMatrix();//Base

	glPushMatrix();
	glTranslatef(0.0, 10.0, 0.0);
	tetera(t3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(150.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(210.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(240.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(300.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(330.0, 0.0, 1.0, 0.0);
	glTranslatef(35.0, 1.0, 0.0);
	taza(t3, t4);
	glPopMatrix();

	glPopMatrix();
	 
	glPopMatrix();

}
void algodon(float t1, float t2) {

	glPushMatrix();

	mi_figura.cilindro(0.05, 7.0, 15.0, t1);
	glTranslatef(0.0, 7.0, 0.0);
	mi_figura.cono(0.2, 0.4, 10.0, t2);
	glTranslatef(0.0, 1.0, 0.0);
	mi_figura.esfera(1.0, 20.0, 20.0, t2);
	glTranslatef(0.0, 0.4, 0.0);
	mi_figura.esfera(1.0, 20.0, 20.0, t2);
	glTranslatef(0.0, 0.4, 0.0);
	mi_figura.esfera(1.0, 20.0, 20.0, t2);

	glPopMatrix();
}
void algodonero(float x, float y, float z, float t1, float t2, float t3) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	mi_figura.cilindro(1.0, 20.0, 30.0, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 8.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 3.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, -2.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 6.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 1.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, -4.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 7.0, -1.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.0, -1.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -3.0, -1.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -1.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -6.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	//algodon

	glPushMatrix();
	glTranslatef(1.5, -4.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, -2.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, -6.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, -2.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	algodon(t2,t3);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
void globos(float t1, float t2) {

	glPushMatrix();

	mi_figura.cilindro(0.05, 7.0, 15.0, t1);
	glTranslatef(0.0, 7.0, 0.0);
	mi_figura.cono(0.2, 0.4, 10.0, t2);
	glTranslatef(0.0, 1.0, 0.0);
	mi_figura.esfera(1.0, 20.0, 20.0, t2);

	glPopMatrix();
}
void globero(float x, float y, float z, float t1, float t2, float t3) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	mi_figura.cilindro(1.0, 20.0, 30.0, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 8.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 3.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, -2.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 6.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 1.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, -4.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 7.0, -1.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.0, -1.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -3.0, -1.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -1.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -6.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	mi_figura.prisma(3.0, 1.0, 1.0, t1);
	glPopMatrix();

	//globos

	glPushMatrix();
	glTranslatef(1.5, -4.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, -2.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, -6.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, -2.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glTranslatef(0, 5.0, 0.0);
	glPushMatrix();
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	globos(t2, t3);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
void s_voladora(float t1, float t2, float t3) {

	glPushMatrix();//Todo
	mi_figura.prisma(0.5, 4.0, 3.0, t1);//Asiento

	glPushMatrix();//Izquierda
	glTranslatef(-1.9, 2.5, 0.0);
	mi_figura.prisma(0.5, 0.2, 3.0, t2);
	glTranslatef(0.0, -1.0, 1.25);
	mi_figura.prisma(2.5, 0.2, 0.5, t2);
	glTranslatef(0.0, 1.25, -2.5);
	mi_figura.prisma(5.0, 0.2, 0.5, t2);
	glPopMatrix();//Izquierda

	glPushMatrix();//Derecha
	glTranslatef(1.9, 2.5, 0.0);
	mi_figura.prisma(0.5, 0.2, 3.0, t2);
	glTranslatef(0.0, -1.0, 1.25);
	mi_figura.prisma(2.5, 0.2, 0.5, t2);
	glTranslatef(0.0, 1.25, -2.5);
	mi_figura.prisma(5.0, 0.2, 0.5, t2);
	glPopMatrix();//Derecha

	glPushMatrix();//Respaldo
	glTranslatef(0.0, 4.0, -1.25);
	mi_figura.prisma(2.0, 4.0, 0.2, t1);
	glTranslatef(0.0, -2.0, 0.0);
	mi_figura.prisma(0.8, 4.0, 0.2, t1);
	glPopMatrix();//Respaldo

	glPushMatrix();//Cadenas traseras
	glTranslatef(-1.9, 5.0, -1.25);

	glPushMatrix();//I

	glRotatef(15.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.08, 4.0, 15.0, t3);

	glPopMatrix();//I

	glTranslatef(3.8, 0.0, 0.0);

	glPushMatrix();//D
	glRotatef(15.0, 1.0, 0.0, 0.0);
	mi_figura.cilindro(0.08, 4.0, 15.0, t3);
	glPopMatrix();//D

	glPushMatrix();//Sujetador
	glTranslatef(-1.9, 3.8, 1.0);
	mi_figura.prisma(0.3, 4.0, 0.5, t3);
	glTranslatef(-1.5, 0.0, 0.0);
	mi_figura.cilindro(0.1, 20.0, 30.0, t3);
	glTranslatef(3.0, 0.0, 0.0);
	mi_figura.cilindro(0.1, 20.0, 30.0, t3);
	glPopMatrix();//Sujetador

	glPopMatrix();//Cadenas trasera

	glPushMatrix();//Cadenas delanteras
	glTranslatef(-1.9, 2.5, 1.4);
	glPushMatrix();//I
	mi_figura.cilindro(0.08, 6.5, 15.0, t3);
	glTranslatef(3.8, 0.0, 0.0);
	mi_figura.cilindro(0.08, 6.5, 15.0, t3);
	glPopMatrix();//I

	glPushMatrix();//D
	glTranslatef(1.9, 6.3, 0.0);
	mi_figura.prisma(0.3, 4.0, 0.5, t3);
	glTranslatef(-1.5, 0.0, 0.0);
	mi_figura.cilindro(0.1, 20.0, 30.0, t3);
	glTranslatef(3.0, 0.0, 0.0);
	mi_figura.cilindro(0.1, 20.0, 30.0, t3);
	glPopMatrix();//D

	glPopMatrix();//Cadenas delanteras

	glPopMatrix();//Todo
}
void dos_sillas(float t1, float t2, float t3) {

	glPushMatrix();
	s_voladora(t1, t2, t3);
	glTranslatef(10.0, 0.0, 0.0);
	s_voladora(t1, t2, t3);
	glPopMatrix();

}
void sillas_voladoras(float x, float y, float z, float t_rueda, float t1, float t2, float t3) {

	glPushMatrix();
	glTranslatef(x, y, z);
	

	glPushMatrix();
	
	mi_figura.cilindro(20.0, 100.0, 80.0, t_rueda);
	glTranslatef(0.0, 100.0, 0.0);
	//glPushMatrix();
	glRotatef(sillas, 0.0, 1.0, 0.0);
	glTranslatef(0.0, sillas_ab, 0.0);
	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	mi_figura.cilindro2(80.0, 20.0, 80.0, patron.GLindex, amarillo_m.GLindex);
	glPopMatrix();
	//glPopMatrix();
	glTranslatef(0.0, -29.0, 0.0);

	glPushMatrix();
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(15.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(75.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(105.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(135.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(150.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(165.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(195.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(210.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(225.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(240.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(255.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(285.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(300.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(315.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(330.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(345.0, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	dos_sillas(t1, t2, t3);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
/*
void pato_cae(int x, int y, GLuint text)
{
	glPushMatrix();
	glRotatef(90.0, 0.0, -1.0, 0.0);
	glRotatef(tira_pato, 1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	//glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, y, 0.0);
	glEnd();

	glPopMatrix();

	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void patos(int x, int y, GLuint text)
{
	glPushMatrix();
	glRotatef(90.0, 0.0, -1.0, 0.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	//glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, y, 0.0);
	glEnd();

	glPopMatrix();

	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
void grupo_pato1(float t) {

	glPushMatrix();
	glTranslatef(0.0, 0.0, -40.0);
	patos(5.0, 5.0, t);
	glTranslatef(0.0, 0.0, -30.0);
	patos(5.0, 5.0, t);
	glTranslatef(0.0, 0.0, -20.0);
	patos(5.0, 5.0, t);

	glPopMatrix();
}
void dispara_pato(float x, float y, float z, float roatY) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();
	mi_figura.prisma(3.0f, 70.0f, 70.0f, 0);
	//Pared trasera
	glPushMatrix();
	glTranslatef(34.0f, 31.5f, 0.0f);
	mi_figura.prisma(60.0f, 2.0f, 70.0f, 0);
	//Repisas
	glPushMatrix();
	glTranslatef(-6.0f, -10.0f, 0.0f);
	mi_figura.prisma(1.0f, 10.0f, 66.0f, 0);
	glTranslatef(0.0f, 12.0f, 0.0f);
	mi_figura.prisma(1.0f, 10.0f, 66.0f, 0);
	glTranslatef(0.0f, 12.0f, 0.0f);
	mi_figura.prisma(1.0f, 10.0f, 66.0f, 0);
	glPopMatrix();
	glPopMatrix();
	//Pared derecha
	glPushMatrix();
	glTranslatef(0.0f, 31.5f, 34.0f);
	mi_figura.prisma(60.0f, 66.0f, 2.0f, 0);
	glPopMatrix();
	//Pared izquierda
	glPushMatrix();
	glTranslatef(0.0f, 31.5f, -34.0f);
	mi_figura.prisma(60.0f, 66.0f, 2.0f, 0);
	glPopMatrix();
	//Techo
	glPushMatrix();
	glTranslatef(0.0f, 62.5f, 0.0f);
	mi_figura.prisma(2.0f, 72.0f, 72.0f, 0);
	glPopMatrix();
	glTranslatef(-34.0f, 11.5f, 0.0f);
	mi_figura.prisma(20.0f, 2.0f, 70.0f, 0);
	glPushMatrix();
	glTranslatef(0.0f, 11.0f, 0.0f);
	mi_figura.prisma(2.0f, 18.0f, 66.0f, 0);

	glPopMatrix();
	glPopMatrix();
	//Patos
	glPushMatrix();
	glTranslatef(25.0, 46.0, 15.0);
	glPushMatrix();
	grupo_pato1(pato1.GLindex);
	glTranslatef(0.0, 20.0, 0.0);
	grupo_pato1(pato1.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Patos


	glPopMatrix();
}

*/
void botella(float t1) {
	glPushMatrix();

	mi_figura.cilindro(1.0, 3.0, 30, t1);
	glTranslatef(0.0, 3.0, 0.0);
	mi_figura.cono(1.0, 1.0, 30, t1);
	glTranslatef(0.0, 0.5, 0.0);
	mi_figura.cilindro(0.3, 1.0, 30, t1);
	glTranslatef(0.0, 1.0, 0.0);
	mi_figura.cilindro(0.4, 0.2, 30, t1);
	glPopMatrix();
}
void grupo_botellas(float t1) {

	glPushMatrix();
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glTranslatef(2.0, 0.0, 0.0);
	botella(t1);
	glPopMatrix();
}
void aros_botellas(float x, float y, float z, float local, float techo, float t1, float t2, float roatY) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();//Local
	mi_figura.prisma(50, 90, 5, local);
	glTranslatef(0.0, -20.0, 42.5);
	mi_figura.prisma(10, 90, 15, techo);

	glPopMatrix();//Local

	glPushMatrix();// Techo
	glTranslatef(0.0, 27.0, 30);
	mi_figura.prisma(5.0, 90, 60, techo);

	glPopMatrix();// Techo
	glPushMatrix();//Izquierda

	glTranslatef(-42.5, 0.0, 25.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	mi_figura.prisma(50, 50, 5, local);

	glPopMatrix();//Izquierda

	glPushMatrix();//Derecha

	glTranslatef(42.5, 0.0, 25.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	mi_figura.prisma(50, 50, 5, local);

	glPopMatrix();//Derecha
	
	glPushMatrix();
	glTranslatef(-34.0, -15.0, 10.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, -15.0, 10.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glTranslatef(0.0, 0.0, 2.0);
	grupo_botellas(t1);
	glPopMatrix();
	
	glPushMatrix();//Bases
	glTranslatef(-20.0, -20.0, 23.0);	
	mi_figura.prisma(10, 35, 25, t2);
	glTranslatef(43.0, 0.0, 0.0);
	mi_figura.prisma(10, 35, 25, t2);
	glPopMatrix();//Bases


	glPopMatrix();
}
void encestar(float x, float y, float z, float local, float roatY) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();//Fondo

	mi_figura.prisma(50, 90, 5, local);
	glTranslatef(0.0, -20.0, 42.5);
	mi_figura.prisma(10, 90, 15, local);

	glPopMatrix();//Fondo

	glPushMatrix();//Izquierda

	glTranslatef(-42.5, 0.0, 25.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	mi_figura.prisma(50, 50, 5, local);

	glPopMatrix();//Izquierda

	glPushMatrix();//Derecha

	glTranslatef(42.5, 0.0, 25.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	mi_figura.prisma(50, 50, 5, local);

	glPopMatrix();//Derecha

	glPushMatrix();//Rejas

	glTranslatef(0.0, 0.0, 19.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	mi_figura.prisma(50, 32, 0.5, local);
	glTranslatef(0.0, 0.0, 20.0);
	mi_figura.prisma(50, 32, 0.5, local);
	glTranslatef(0.0, 0.0, -40.0);
	mi_figura.prisma(50, 32, 0.5, local);

	glPopMatrix();//Rejas

	glPushMatrix();//Aros
	glTranslatef(-30.0, 10.0, 8.0);
	mi_figura.cilindro(6.0, 3.0, 30.0, negro_m.GLindex);
	glTranslatef(20.0, 0.0, 0.0);
	mi_figura.cilindro(6.0, 3.0, 30.0, negro_m.GLindex);
	glTranslatef(20.0, 0.0, 0.0);
	mi_figura.cilindro(6.0, 3.0, 30.0, negro_m.GLindex);
	glTranslatef(20.0, 0.0, 0.0);
	mi_figura.cilindro(6.0, 3.0, 30.0, negro_m.GLindex);

	glPopMatrix();//Aros

	glPushMatrix(); //Pelotas
	glTranslatef(-30.0, -12.0, 45.0);
	mi_figura.esfera(3.0, 15.0, 15.0, naranja_m.GLindex);
	glTranslatef(20.0, 0.0, 0.0);
	mi_figura.esfera(3.0, 15.0, 15.0, naranja_m.GLindex);
	glTranslatef(20.0, 0.0, 0.0);
	mi_figura.esfera(3.0, 15.0, 15.0, naranja_m.GLindex);
	glTranslatef(20.0, 0.0, 0.0);
	mi_figura.esfera(3.0, 15.0, 15.0, naranja_m.GLindex);

	glPopMatrix();//Pelotas


	glPushMatrix();//Base

	glTranslatef(0.0, -24.5, 25.0);
	mi_figura.prisma(1.0, 90.0, 50.0, 0);


	glPopMatrix();//Base


	glPopMatrix();
}
void trenecito(float t1) {
	glPushMatrix();
	//glTranslatef(0.0f, 4.0f, -6.0f);//Translate para posicionar
	mi_figura.prisma(3.5f, 3.5f, 3.5f, t1);
	glPushMatrix();
	glTranslatef(0.0f, -1.25f, 0.0f);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0.0f, 1.75f, 0.0f);
	mi_figura.cilindro(1.25f, 0.75f, 40, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -1.25f, 0.0f);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0.0f, 1.75f, 0.0f);
	mi_figura.cilindro(1.25f, 0.75f, 40, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.625f, 2.75f, 1.625);
	mi_figura.prisma(2.0f, 0.25f, 0.25f, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.625f, 2.75f, 1.625);
	mi_figura.prisma(2.0f, 0.25f, 0.25f, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.625f, 2.75f, -1.625);
	mi_figura.prisma(2.0f, 0.25f, 0.25f, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.625f, 2.75f, -1.625);
	mi_figura.prisma(2.0f, 0.25f, 0.25f, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 3.625f, 0.0f);
	mi_figura.prisma(0.25f, 3.9f, 3.9f, t1);
	glPopMatrix();
	glTranslatef(0.0f, -1.0f, 2.5f);
	mi_figura.prisma(1.5f, 1.5f, 2.0f, t1);
	glPushMatrix();
	glTranslatef(0.0f, -0.75f, 0.0f);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0.0f, 0.75f, 0.0f);
	mi_figura.cilindro(0.75f, 0.5f, 40, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -0.75f, 0.0f);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0.0f, 0.75f, 0.0f);
	mi_figura.cilindro(0.75f, 0.5f, 40, t1);
	glPopMatrix();
	glPopMatrix();
	//Fin del trenecito

}
void oso(float t1) {
	//Oso
	glPushMatrix();
	mi_figura.esfera(3.0f, 40, 40, t1);
	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	mi_figura.cilindro(0.5, 4.5f, 40, t1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-45, 1, 0, 0);
	mi_figura.cilindro(0.5, 4.5f, 40, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -1.75f, 1.75f);
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.75, 4.0f, 40, t1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -1.75f, -1.75f);
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.75, 4.0f, 40, t1);
	glPopMatrix();
	glTranslatef(0.0f, 4.75f, 0.0f);
	mi_figura.esfera(2.0f, 40, 40, t1);
	glTranslatef(0.0f, 2.0, 1.0);
	mi_figura.esfera(0.75f, 40, 40, t1);
	glTranslatef(0.0f, 0.0f, -2.0f);
	mi_figura.esfera(0.75f, 40, 40, t1);
	glPopMatrix();
	//Fin del oso
}
void tienda(float x, float y, float z, float roatY) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();
	mi_figura.prisma(3.0f, 70.0f, 70.0f, amarillo_s.GLindex);
	//Pared trasera
	glPushMatrix();
	glTranslatef(34.0f, 31.5f, 0.0f);
	mi_figura.prisma(60.0f, 2.0f, 70.0f, amarillo_s.GLindex);
	//Repisas	
	glPushMatrix();
	glTranslatef(-6.0f, -10.0f, 0.0f);
	mi_figura.prisma(2.5f, 10.0f, 66.0f, rojo_m.GLindex);
	//Oso
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 6.0f);//Translate para posicionar
	oso(rojo_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Oso
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -27.0f);//Translate para posicionar
	oso(negro_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Oso
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 28.0f);//Translate para posicionar
	oso(azul_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -20.0f);//Translate para posicionar
	trenecito(naranja_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Oso
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -12.0f);//Translate para posicionar
	oso(amarillo_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -4.0f);//Translate para posicionar
	trenecito(negro_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 18.0f);//Translate para posicionar
	trenecito(azul_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	glTranslatef(0.0f, 14.0f, 0.0f);
	mi_figura.prisma(2.5f, 10.0f, 66.0f, rojo_m.GLindex);
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -28.0f);//Translate para posicionar
	trenecito(rojo_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -20.0f);//Translate para posicionar
	trenecito(cromo.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -12.0f);//Translate para posicionar
	oso(verde_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -6.0f);//Translate para posicionar
	trenecito(morado_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 2.0f);//Translate para posicionar
	oso(rosa_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 10.0f);//Translate para posicionar
	oso(cromo.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 16.0f);//Translate para posicionar
	trenecito(rosa_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 24.0f);//Translate para posicionar
	trenecito(verde_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	glTranslatef(0.0f, 14.0f, 0.0f);
	mi_figura.prisma(2.5f, 10.0f, 66.0f, rojo_m.GLindex);
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -18.0f);//Translate para posicionar
	oso(morado_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -28.0f);//Translate para posicionar
	trenecito(naranja_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -10.0f);//Translate para posicionar
	oso(0);
	glPopMatrix();
	//Fin del oso
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, -2.0f);//Translate para posicionar
	oso(negro_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 6.0f);//Translate para posicionar
	oso(azul_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 12.0f);//Translate para posicionar
	trenecito(amarillo_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 18.0f);//Translate para posicionar
	trenecito(rosa_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 3.75f, 24.0f);//Translate para posicionar
	trenecito(verde_m.GLindex);
	glPopMatrix();
	//Fin del trenecito
	glPopMatrix();
	glPopMatrix();
	//Pared derecha
	glPushMatrix();
	glTranslatef(0.0f, 31.5f, 34.0f);
	mi_figura.prisma(60.0f, 66.0f, 2.0f, amarillo_s.GLindex);
	glPopMatrix();
	//Pared izquierda
	glPushMatrix();
	glTranslatef(0.0f, 31.5f, -34.0f);
	mi_figura.prisma(60.0f, 66.0f, 2.0f, amarillo_s.GLindex);
	glPopMatrix();
	//Techo
	glPushMatrix();
	glTranslatef(0.0f, 62.5f, 0.0f);
	mi_figura.prisma(2.0f, 72.0f, 72.0f, rojo_s.GLindex);
	glPopMatrix();
	glTranslatef(-34.0f, 11.5f, 0.0f);
	mi_figura.prisma(20.0f, 2.0f, 70.0f, rojo_s.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 11.0f, 0.0f);
	mi_figura.prisma(2.0f, 18.0f, 66.0f, rojo_s.GLindex);
	//Oso de peluche
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 6.0f);//Translate para posicionar
	oso(verde_m.GLindex);
	glPopMatrix();
	//Fin del oso
	//Inicio del trenecito
	glPushMatrix();
	glTranslatef(0.0f, 4.0f, -6.0f);//Translate para posicionar
	trenecito(cromo.GLindex);
	glPopMatrix();
	//Fin del trenecito
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void c_carrusel(float t1) {

	glPushMatrix();
	mi_figura.cilindro(1.0f, 80.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 15.0f, 0.0f);
	glRotatef(90, 0, 1, 0);
	mi_figura.prisma(10.0f, 30.0f, 10.0f, t1);
	//Ruedas
	glPushMatrix();
	glPushMatrix();
	glTranslatef(9.5f, -3.0f, 6.0f);
	glRotatef(-90.0, 1, 0, 0);
	mi_figura.cilindro(3.725f, 1.0f, 40, negro_m.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-9.5f, -3.0f, 6.0f);
	glRotatef(-90.0, 1, 0, 0);
	mi_figura.cilindro(3.725f, 1.0f, 40, negro_m.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.5f, -3.0f, -6.0f);
	glRotatef(90.0, 1, 0, 0);
	mi_figura.cilindro(3.725f, 1.0f, 40, negro_m.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-9.5f, -3.0f, -6.0f);
	glRotatef(90.0, 1, 0, 0);
	mi_figura.cilindro(3.725f, 1.0f, 40, negro_m.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Cabina
	glPushMatrix();
	glTranslatef(7.25f, 5.0f, 4.25f);
	glPushMatrix();
	mi_figura.cilindro(0.25f, 8.0f, 40, negro_m.GLindex);
	glTranslatef(7.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 8.0f, 40, negro_m.GLindex);
	glTranslatef(0.0f, 0.0f, -8.5f);
	mi_figura.cilindro(0.25f, 8.0f, 40, negro_m.GLindex);
	glTranslatef(-7.0f, 0.0f, 0.0f);;
	mi_figura.cilindro(0.25f, 8.0f, 40, negro_m.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.5f, 4.0f, -4.25f);
	mi_figura.prisma(8.0f, 7.0f, 8.5f, vidrio.GLindex);//Vidrio
	glTranslatef(0.0f, 4.25f, 0.0f);
	mi_figura.prisma(0.5f, 10.0f, 10.0f, t1);
	glPopMatrix();
	glPopMatrix();
	//Vaporela
	glPushMatrix();
	glTranslatef(15.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 0, 0, 1);
	mi_figura.cilindro(4.0f, 0.5f, 40, negro_m.GLindex);
	glTranslatef(0.0f, 0.5f, 0.0f);
	mi_figura.cilindro(1.5f, 1.0f, 40, t1);
	glPopMatrix();
	//Asiento
	glPushMatrix();
	glTranslatef(-7.5f, 5.2f, 0.0f);
	mi_figura.prisma(0.4f, 9.0f, 9.0f, 0);//Asiento
	glPopMatrix();
	glPopMatrix();

}
void carrusel(float x, float y, float z, float roatY, float c1, float c2, float c4, float c5, float c6, float c7, float c8) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		glPushMatrix();
			mi_figura.cilindro2(85.0f, 2.0f, 40, base2.GLindex, base2.GLindex);
			//Control carrusel
			glPushMatrix();
				glTranslatef(0.0f, 9.0f, 88.5f);
				mi_figura.prisma(18.0f, 7.0f, 7.0f, c8);
				glPushMatrix();
					glTranslatef(-3.375f, 9.5f, 0.0f);
					mi_figura.prisma(1.0f, 0.25f, 7.0f, vidrio.GLindex);//vidrio
				glPopMatrix();
				glPushMatrix();
					glTranslatef(3.375f, 9.5f, 0.0f);
					mi_figura.prisma(1.0f, 0.25f, 7.0f, vidrio.GLindex);//vidrio
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 9.5f, -3.375f);
					mi_figura.prisma(1.0f, 7.0f, 0.25f, vidrio.GLindex);//vidrio
				glPopMatrix();
				glPushMatrix();
					glTranslatef(2.0f, 9.0f, -1.0f);
					mi_figura.cilindro(0.125f, 2.0f, 40, negro_m.GLindex);
					glTranslatef(0.0f, 2.0f, 0.0f);
					mi_figura.esfera(0.5f, 40, 40, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-2.0f, 9.0f, -1.0f);
					mi_figura.cilindro(0.125f, 2.0f, 40, negro_m.GLindex);
					glTranslatef(0.0f, 2.0f, 0.0f);
					mi_figura.esfera(0.5f, 40, 40, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(1.0f, 9.0f, 1.0f);
					mi_figura.cilindro(0.125f, 0.25f, 40, verdeo_m.GLindex);
					glTranslatef(-0.5f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125f, 0.25f, 40, amarillo_m.GLindex);
					glTranslatef(-0.5f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125f, 0.25f, 40, p_verde.GLindex);
					glTranslatef(-0.5f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125f, 0.25f, 40, c4);
					glTranslatef(-0.5f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125f, 0.25f, 40, c5);
				glPopMatrix();
			glPopMatrix();
			glRotatef(g_carrusel, 0, 1, 0);
			glTranslatef(0.0f, 2.0f, 0.0f);
			mi_figura.cilindro(68.0f, 1.0f, 40, amarillo_m.GLindex);
			glTranslatef(0.0f, 1.0f, 0.0f);
			mi_figura.cilindro(10.0f, 80.0f, 40, amarillo_m.GLindex);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 10.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -10.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(7.0f, 0.0f, 7.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-7.0f, 0.0f, 7.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(7.0f, 0.0f, -7.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-7.0f, 0.0f, -7.0f);
					mi_figura.cilindro(2.0f, 80.0f, 40, verdeo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			//Control carrusel

			//Soportes
			glPushMatrix();
				glTranslatef(0.0f, 60.0f, 0.0f);
				glPushMatrix();
					glRotatef(72.5, 0, 0, 1);
					mi_figura.cilindro(1.0f, 70.0f, 40, cromo.GLindex);
				glPopMatrix();
				glPushMatrix();
					glRotatef(-72.5, 0, 0, 1);
					mi_figura.cilindro(1.0f, 70.0f, 40, cromo.GLindex);
				glPopMatrix();
				glPushMatrix();
					glRotatef(72.5, 1, 0, 0);	
					mi_figura.cilindro(1.0f, 70.0f, 40, cromo.GLindex);
				glPopMatrix();
				glPushMatrix();
					glRotatef(-72.5, 1, 0, 0);	
					mi_figura.cilindro(1.0f, 70.0f, 40, cromo.GLindex);
				glPopMatrix();
			glPopMatrix();
			//Soportes
			//Techo
			glPushMatrix();
			glTranslatef(0.0f, 80.0f, 0.0f);
			mi_figura.cono(15.0f, 78.0f, 40, p_verde.GLindex);
			glPopMatrix();
			//Techo
			//Caballitos

			glPushMatrix();
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c1);
			glPopMatrix();

			glPushMatrix();
			glRotatef(45.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c2);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(negro_m.GLindex);
			glPopMatrix();

			glPushMatrix();
			glRotatef(135.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c4);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c5);
			glPopMatrix();

			glPushMatrix();
			glRotatef(225.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c6);
			glPopMatrix();

			glPushMatrix();
			glRotatef(270.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c7);
			glPopMatrix();

			glPushMatrix();
			glRotatef(315.0, 0.0, 1.0, 0.0);
			glTranslatef(-50.0f, 0.0f, 0.0f);
			c_carrusel(c8);
			glPopMatrix();


			//Caballitos


			//Techo
	glPopMatrix();
}
void martillo_golpe(float x, float y, float z, float roatY, float t2, float t3, float t4) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();
	//Base
	glPushMatrix();
	mi_figura.prisma(3.0f, 30.0f, 25.0f, base.GLindex);
	//Barandal izquierdo
	glPushMatrix();
	glTranslatef(14.5f, 1.5f, 12.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 18.0f, 0.0f);
	mi_figura.esfera(0.25f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-8.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-8.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-8.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 18.0f, 0.0f);
	mi_figura.esfera(0.25f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Barandal derecho
	glPushMatrix();
	glTranslatef(14.5f, 1.5f, -12.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 18.0f, 0.0f);
	mi_figura.esfera(0.25f, 40, 40, cromo.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-8.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-8.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glTranslatef(0.0f, 3.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(0.25f, 8.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-8.0f, 0.0f, 0.0f);
	mi_figura.cilindro(0.25f, 18.0f, 40, cromo.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, 18.0f, 0.0f);
	mi_figura.esfera(0.25f, 40, 40, 0);
	glPopMatrix();
	glPopMatrix();
	//Fin del barandal
	glTranslatef(-13.5f, 24.5f, 0.0f);
	mi_figura.prisma(46.0f, 3.0f, 25.0f, t2);
	glTranslatef(1.0f, -23.0f, 0.0f);
	mi_figura.cilindro(1.5f, 48.0f, 40, dorado.GLindex);
	//Campana
	glPushMatrix();
	glTranslatef(1.5f, 51.0f, 0.0f);
	glRotatef(90.0f, 0, 0, 1);
	mi_figura.cilindro2(6.0f, 1.5f, 40, cromo.GLindex, cromo.GLindex);
	glTranslatef(0.0f, -1.5f, 0.0f);
	mi_figura.cilindro2(4.0f, 0.75f, 40, cromo.GLindex, cromo.GLindex);
	glTranslatef(0.0f, -0.25f, 0.0f);
	mi_figura.cilindro(1.0f, 0.25f, 40, dorado.GLindex);
	glPopMatrix();
	//Tiras de puntaje
	glPushMatrix();
	glTranslatef(0.6f, 0.125f, 3.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.prisma(0.25f, 0.25f, 2.0f, amarillo_m.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Dummy
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	mi_figura.cilindro(7.0f, 1.0f, 40, t3);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	mi_figura.esfera2(6.0f, 40, 40, t4);
	glPopMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	mi_figura.cilindro(0.5f, 0.5f, 40, t3);
	glPopMatrix();
	//Martillo
	glPushMatrix();
	glTranslatef(30.0f, 20.0f, 0.0f);
	glRotatef(90.0f, 0, 0, 1);
	glRotatef(g_martillo, 0, 0, 1.0);
	mi_figura.cilindro(0.375f, 28.0f, 40, madera_cerca.GLindex);//Palo madera
	glTranslatef(5.0f, 30.0f, 0.0f);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	mi_figura.cilindro(3.0f, 10.0f, 40, cromo.GLindex);//Mazo
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void carrito_montania(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glTranslatef(mov_carrox, mov_carroy, mov_carroz);
	glRotatef(rot_carrox, 1, 0, 0);
	glRotatef(rot_carroy, 0, 1, 0);
	glRotatef(rot_carroz, 0, 0, 1);
	glPushMatrix();
	mi_figura.prisma(0.5f, 25.0f, 15.0f, 0);
	//Llantas
	glPushMatrix();
	glPushMatrix();
	glTranslatef(10.0f, 0.0f, 7.5f);
	glRotatef(90.0f, 1, 0, 0);
	mi_figura.cilindro(2.0f, 0.5f, 40, negro_m.GLindex);
	glTranslatef(-20.0f, 0.0f, 0.0f);
	mi_figura.cilindro(2.0f, 0.5f, 40, negro_m.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.0f, 0.0f, -7.5f);
	glRotatef(-90.0f, 1, 0, 0);
	mi_figura.cilindro(2.0f, 0.5f, 40, negro_m.GLindex);
	glTranslatef(-20.0f, 0.0f, 0.0f);
	mi_figura.cilindro(2.0f, 0.5f, 40, negro_m.GLindex);
	glPopMatrix();
	glPopMatrix();
	//Asiento
	glPushMatrix();
	glTranslatef(-7.5f, 1.0f, 0.0f);
	mi_figura.prisma(2.0f, 7.0f, 14.0f, carro_azul.GLindex);
	glPopMatrix();
	//Paredes laterales
	glPushMatrix();
	glTranslatef(0.0f, 4.5f, -7.0f);
	mi_figura.prisma(10.0f, 25.0f, 1.0f, carro_azul.GLindex);
	glTranslatef(0.0f, 0.0f, 14.0f);
	mi_figura.prisma(10.0f, 25.0f, 1.0f, carro_azul.GLindex);
	glPopMatrix();
	//Pared trasera
	glPushMatrix();
	glTranslatef(-12.0f, 5.25f, 0.0f);
	mi_figura.prisma(10.0f, 1.0f, 15.0f, carro_azul.GLindex);
	glTranslatef(0.0f, 5.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0f, -7.5f, 0.0f);
	mi_figura.cilindro(0.5f, 15.0f, 40, carro_azul.GLindex);
	glPopMatrix();
	//Pared delantera y soporte
	glPushMatrix();
	glTranslatef(12.0f, 5.25f, 0.0f);
	mi_figura.prisma(10.0f, 1.0f, 15.0f, carro_azul.GLindex);
	glPushMatrix();
	glRotatef(90.0f, 1, 0, 0);
	glTranslatef(0.0f, -7.75f, 0.0f);
	mi_figura.cilindro(5.0, 15.5f, 40, carro_azul.GLindex);
	glPopMatrix();
	glTranslatef(-6.0f, 4.5f, 0.0f);
	mi_figura.prisma(1.0f, 12.0f, 15.0f, carro_azul.GLindex);
	glTranslatef(-6.0f, 0.0f, 0.0f);
	//Agarradera
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(45.0f, 0, 0, 1);
	mi_figura.cilindro(0.25f, 3.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 0.0f, 14.0f);
	mi_figura.cilindro(0.25f, 3.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 3.0f, 0.0f);
	mi_figura.esfera(0.25f, 40, 40, cromo.GLindex);
	glRotatef(-90, 1, 0, 0);
	mi_figura.cilindro(0.25f, 14.0f, 40, cromo.GLindex);
	glTranslatef(0.0f, 14.0f, 0.0f);
	mi_figura.esfera(0.25f, 40, 40, cromo.GLindex);
	glPopMatrix();//Fin de la agarradera
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0f, -7.5f, 0.0f);
	mi_figura.cilindro(0.5f, 15.0f, 40, cromo.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void montania_rusa(float x, float y, float z, float roatY) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		glPushMatrix();
			//Inicio de los soportes
			glPushMatrix();
				glPushMatrix();
					glTranslatef(45.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 8.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 12.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 16.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 20.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 24.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 28.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 32.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 37.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 41.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 58.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 62.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 66.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 70.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 78.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 83.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 88.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 92.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 96.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 100.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 104.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 108.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 112.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					//Primera curva
					glTranslatef(6.0f, 0.0f, 1.75f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.375f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 5.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 10.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 10.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 2.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 112.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 108.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 103.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 98.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 94.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 88.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 84.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 78.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 68.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 64.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 58.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 38.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 34.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 29.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 24.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 20.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 14.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 10.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 5.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 63.0f);
					mi_figura.cilindro(0.75f, 5.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 10.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 14.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 19.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 24.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 29.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 34.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 39.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 59.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 64.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 69.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 79.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 84.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 88.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 93.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 98.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 103.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 108.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 113.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 118.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 123.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 128.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 133.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 137.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 142.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 147.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 152.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 157.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 162.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 167.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 172.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 177.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 182.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 186.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 191.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 196.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 3.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 3.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 4.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-3.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 198.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 193.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 188.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 183.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 179.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 174.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 169.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 164.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 159.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 154.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 149.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 144.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 140.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 135.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 130.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 125.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 120.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 115.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 110.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 105.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 101.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 96.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 91.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -4.0f);
					mi_figura.cilindro(0.75f, 91.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 95.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 100.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 105.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 110.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 115.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 120.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 125.0f, 40, madera_cerca.GLindex);
					glTranslatef(271.0f, 0.0f, -42.0f);
					mi_figura.cilindro(0.75f, 182.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 166.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 148.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.5f);
					mi_figura.cilindro(0.75f, 130.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 113.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.2f);
					mi_figura.cilindro(0.75f, 102.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 96.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 91.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 79.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 68.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 62.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 57.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -4.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -4.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, -7.5f);
					mi_figura.cilindro(0.75f, 55.5f, 40, madera_cerca.GLindex);
					glTranslatef(-5.0f, 0.0f, -7.5f);
					mi_figura.cilindro(0.75f, 55.5f, 40, madera_cerca.GLindex);
					glTranslatef(-5.0f, 0.0f, -7.5f);
					mi_figura.cilindro(0.75f, 55.5f, 40, madera_cerca.GLindex);
					glTranslatef(-5.0f, 0.0f, -7.5f);
					mi_figura.cilindro(0.75f, 55.5f, 40, madera_cerca.GLindex);
					glTranslatef(-2.5f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 55.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 55.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 55.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 53.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 53.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 53.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 52.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 52.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 52.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 51.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 51.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 51.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 47.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 45.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 45.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 45.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 43.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 43.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 43.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 42.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -12.0f);
					mi_figura.cilindro(0.75f, 38.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 35.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 33.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 30.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 28.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 26.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 22.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 20.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 18.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 14.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 12.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 10.0f, 40, madera_cerca.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(45.0f, 0.0f, -20.0f);
					mi_figura.cilindro(0.75f, 8.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 12.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 16.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 20.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0);
					mi_figura.cilindro(0.75f, 24.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 28.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 32.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 37.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 41.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 58.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 62.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 66.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 70.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 78.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 83.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 88.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 92.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 96.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 100.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 104.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 108.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 112.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					//Primera curva
					glTranslatef(6.0f, 0.0f, 1.75f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.375f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.25f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.25f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 3.25f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 7.25f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 10.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(6.5f, 0.0f, 13.5f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 114.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 112.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 108.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 103.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 98.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 94.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 88.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 84.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 78.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 68.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 64.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 58.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 38.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 34.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 29.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 24.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 20.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 14.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 10.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 5.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 63.0f);
					mi_figura.cilindro(0.75f, 5.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 10.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 14.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 19.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 24.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 29.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 34.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 39.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 59.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 64.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 69.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 79.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 84.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 88.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 93.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 98.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 103.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 108.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 113.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 118.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 123.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 128.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 133.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 137.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 142.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 147.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 152.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 157.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 162.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 167.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 172.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 177.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 182.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 186.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 191.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 196.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-4.0f, 0.0f, 7.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 6.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 4.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 201.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 198.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 193.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 188.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 183.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 179.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 174.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 169.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 164.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 159.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 154.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 149.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 144.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 140.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 135.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 130.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 125.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 120.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 115.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 110.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 105.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 101.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 96.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 91.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					//Inicio de la vuelta de cabeza
					glTranslatef(-7.0f, 0.0f, -3.5f);
					mi_figura.cilindro(0.75f, 89.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 94.5f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 100.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 104.5f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 109.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 114.5f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 119.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 123.5f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 129.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -5.0f);
					mi_figura.cilindro(0.75f, 133.5f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -6.75f);
					mi_figura.cilindro(0.75f, 146.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -10.75f);
					mi_figura.cilindro(0.75f, 169.0f, 40, madera_cerca.GLindex);
					glTranslatef(-7.0f, 0.0f, -10.75f);
					glTranslatef(-7.0f, 0.0f, -10.75f);
					glTranslatef(-7.0f, 0.0f, -10.75f);
					glTranslatef(10.0f, 0.0f, -5.5f);
					mi_figura.cilindro(0.75f, 220.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 234.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 251.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 268.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 286.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 301.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.0f);
					mi_figura.cilindro(0.75f, 311.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 318.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 325.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 332.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 337.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 344.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 350.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 2.5f);
					mi_figura.cilindro(0.75f, 357.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 360.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 358.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 358.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.5f);
					mi_figura.cilindro(0.75f, 356.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 355.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.75f);
					mi_figura.cilindro(0.75f, 354.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.5f);
					mi_figura.cilindro(0.75f, 353.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 352.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.0f);
					mi_figura.cilindro(0.75f, 351.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 350.5f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.5f);
					mi_figura.cilindro(0.75f, 346.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 338.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 332.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 324.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 318.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 310.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -1.5f);
					mi_figura.cilindro(0.75f, 304.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 296.0f, 40, madera_cerca.GLindex);
					glTranslatef(0.0f, 0.0f, 14.0f);
					mi_figura.cilindro(0.75f, 182.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 166.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 148.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.5f);
					mi_figura.cilindro(0.75f, 130.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 113.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.2f);
					mi_figura.cilindro(0.75f, 102.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 96.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 91.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 86.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 79.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 74.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 68.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 62.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 57.0f, 40, madera_cerca.GLindex);
					//Fin de la vuelta de cabeza
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 0.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, 1.0f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -4.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -4.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -7.5f);
					mi_figura.cilindro(0.75f, 56.5f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 56.0f, 40, madera_cerca.GLindex);
					glTranslatef(-10.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 56.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.5f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 55.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 55.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.25f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 55.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.5f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.25f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 54.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 53.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.25f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 53.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.25f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 53.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 52.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 52.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 52.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 51.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 51.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 51.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 50.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 49.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 48.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 47.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 47.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 47.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 46.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 45.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 45.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 45.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.0f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 44.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 43.0f, 40, madera_cerca.GLindex);
					glTranslatef(-1.325f, 0.0f, -14.25f);
					mi_figura.cilindro(0.75f, 43.0f, 40, madera_cerca.GLindex);
					glTranslatef(12.0f, 0.0f, -9.25f);
					mi_figura.cilindro(0.75f, 41.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 37.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 34.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 32.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 30.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 28.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 26.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 22.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 20.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.75f, 18.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 14.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 12.0f, 40, madera_cerca.GLindex);
					glTranslatef(10.0f, 0.0f, -0.5f);
					mi_figura.cilindro(0.75f, 10.0f, 40, madera_cerca.GLindex);
				glPopMatrix();
			glPopMatrix();
			//Inicio de los rieles
			glPushMatrix();
				mi_figura.prisma(2.0f, 70.0f, 1.5f, hierro_negro.GLindex);
				//Maderas de rieles
				glPushMatrix();
					glTranslatef(-32.0f, 0.0f, -10.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
				glPopMatrix();
				//Fin de maderas de rieles
				glTranslatef(0.0f, 0.0f, -20.0f);
				mi_figura.prisma(2.0f, 70.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(55.0f, 14.5f, 0.0f);
				glRotatef(35.0f, 0, 0, 1);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.0f, 20.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				//Maderas de rieles
				glPushMatrix();
					glTranslatef(-21.0f, 0.0f, -10.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
				glPopMatrix();
				//Fin de maderas de rieles
				glTranslatef(50.0f, 0.0f, 0.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.0f, -20.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(50.0f, 0.0f, 0.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.0f, 20.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(50.0f, 0.0f, 0.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.0f, -20.0f);
				mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(25.0f, 0.0f, 0.0f);
				glRotatef(-35.0f, 0, 0, 1);
				glTranslatef(14.4f, -0.2f, 0.0f);
				mi_figura.prisma(2.0f, 30.0f, 1.5f, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.0f, 20.0f);
				mi_figura.prisma(2.0f, 30.0f, 1.5f, hierro_negro.GLindex);
				//Madera de rieles
				glPushMatrix();
					glTranslatef(-12.0f, 0.0f, -10.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
					glTranslatef(6.0f, 0.0f, 0.0f);
					mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
				glPopMatrix();
				//Fin de maderas de rieles
				glTranslatef(27.5f, 0.0f, 7.375f);
				glPushMatrix();
					glRotatef(-30.0f, 0, 1, 0);
					mi_figura.prisma(2.0f, 30.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-15.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0f, 50.0f, 1.5f, hierro_negro.GLindex);
				glPopMatrix();
				glTranslatef(20.125f, 0.0f, 20.125f);
				glPushMatrix();
					glRotatef(-60.0f, 0, 1, 0);
					mi_figura.prisma(2.0f, 30.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-15.0f, 0.0f, -10.0f);
						mi_figura.prisma(1.0f, 2.0f, 20.0f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 20.0f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 20.0f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 20.0f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 20.0f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 20.0f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(0.0f, 0.0f, -20.0f);
					mi_figura.prisma(2.0f, 30.0f, 1.5f, hierro_negro.GLindex);
				glPopMatrix();
				glTranslatef(7.375f, 0.0f, 32.625f);
				glPushMatrix();
					glRotatef(-90.0f, 0, 1, 0);
					mi_figura.prisma(2.0f, 40.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-18.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas rieles
					glTranslatef(-5.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0f, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(44.8f, -14.2f, 17.5f);
					glRotatef(-35.0f, 0, 0, 1);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-18.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas rieles
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glRotatef(35.0f, 0, 0, 1);
					glTranslatef(45.0f, -14.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-18.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas rieles
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(45.0f, 14.0f, 0.0f);
					glRotatef(35.0f, 0, 0, 1);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-18.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas rieles
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 17.5f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(36.625f, 0.0f, 0.0f);
					glRotatef(-35.0f, 0, 0, 1);
					glTranslatef(0.0f, -6.8f, 0.0f);
					mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-7.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(18.25f, 0.0f, 22.375f);
					glRotatef(-30.0f, 0, 1, 0);
					mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
					//Madera de rieles
					glPushMatrix();
						glTranslatef(-9.0f, 0.0f, -7.5625f);
						mi_figura.prisma(1.0f, 2.0f, 13.125f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(0.0f, 0.0f, -15.125f);
					mi_figura.prisma(2.0, 38.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(18.25f, 0.0f, 20.0f);
					glRotatef(-30.0f, 0, 1, 0);
					mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
					//Maderas de rieles
					glPushMatrix();
						glTranslatef(-7.0f, 0.0f, -8.75f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 16.5f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(0.0f, 0.0f, -17.5f);
					mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(18.25f, 0.0f, 22.25f);
					glRotatef(-30.0f, 0, 1, 0);
					mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
					//Maderas de rieles
					glPushMatrix();
						glTranslatef(-8.0f, 0.0f, -7.625f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(5.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(-4.5f, 0.0f, -15.25f);
					mi_figura.prisma(2.0, 27.5f, 1.5f, hierro_negro.GLindex);
					glRotatef(-35.0f, 0, 0, 1);
					glTranslatef(35.8f, 7.75f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 15.25f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					//Maderas de rieles
					glPushMatrix();
						glTranslatef(-22.0f, 0.0f, -7.125f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -15.25f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 15.25f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -15.25f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(25.0f, 0.0f, 0.0f);
					glRotatef(35.0f, 0, 0, 1);
					glTranslatef(25.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, 15.25f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					//Maderas de rieles
					glPushMatrix();
						glTranslatef(-22.0f, 0.0f, -7.125);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glTranslatef(6.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
					glPopMatrix();
					//Fin de maderas de rieles
					glTranslatef(50.0f, 0.0f, 0.0f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glTranslatef(0.0f, 0.0f, -15.25f);
					mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
					glRotatef(35.0f, 0, 0, 1);
					glTranslatef(42.0f, -14.2f, 12.3f);
					glPushMatrix();
						glRotatef(-30.0f, 0, 1, 0);
						mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
						glTranslatef(5.0f, 0.0f, 13.25f);
						mi_figura.prisma(2.0, 45.0f, 1.5f, hierro_negro.GLindex);
						//Madera de rieles
						glPushMatrix();
							glTranslatef(-21.0f, 0.0f, -6.625f);
							mi_figura.prisma(1.0f, 2.0f, 12.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glTranslatef(6.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
						glPopMatrix();
						//Fin de maderas de rieles
						glTranslatef(47.5f, 0.0f, 0.0f);
						mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
						glTranslatef(-1.5f, 0.0f, -13.25f);
						mi_figura.prisma(2.0, 52.0f, 1.5f, hierro_negro.GLindex);
						glRotatef(35.0f, 0, 0, 1);
						glTranslatef(47.0f, -15.5f, 13.3f);
						glPushMatrix();
							mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
							//Madera de rieles
							glPushMatrix();
								glTranslatef(-21.0f, 0.0f, -6.65f);
								mi_figura.prisma(1.0f, 2.0f, 12.3f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(6.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glTranslatef(5.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
							glPopMatrix();
							//Fin de maderas de rieles
							glTranslatef(-0.5f, 0.5f, -13.3f);
							mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
							glTranslatef(50.0f, 0.0f, 0.0f);
							mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
							glTranslatef(0.0f, -0.5f, 13.3f);
							mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
							glRotatef(50.0f, 0, 0, 1);
							glTranslatef(41.0f, -18.5f, 0.0f);
							glPushMatrix();
								mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
								//Madera de rieles
								glPushMatrix();
									glTranslatef(-21.0f, 0.0f, -6.65f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glTranslatef(6.0f, 0.0f, 0.0f);
									mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
								glPopMatrix();
								//Fin de maderas de rieles
								glTranslatef(0.0f, 0.0f, -13.3f);
								mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
								glTranslatef(50.0f, 0.0f, 0.0f);
								mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
								glTranslatef(0.0f, 0.0f, 13.3f);
								mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
								glRotatef(30.0f, 0, 0, 1);
								glTranslatef(46.5f, -12.625f, 0.0f);
								glPushMatrix();
									mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
									//Madera de rieles
									glPushMatrix();
										glTranslatef(-21.0f, 0.0f, -6.65f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
										glTranslatef(6.0f, 0.0f, 0.0f);
										mi_figura.prisma(1.0f, 2.0f, 14.25f, madera_cerca.GLindex);
									glPopMatrix();
									//Fin de maderas de rieles
									glTranslatef(0.0f, 0.0f, -13.3f);
									mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
									glTranslatef(50.0f, 0.0f, 0.0f);
									mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
									glTranslatef(0.0f, 0.0f, 13.3f);
									mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
									glRotatef(30.0f, 0, 0, 1);
									glTranslatef(42.5f, -12.625f, 11.8f);
									glPushMatrix();
										glRotatef(-30.0f, 0, 1, 0);
										glRotatef(15.0f, 1, 0, 0);
										mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
										//Madera de rieles
										glPushMatrix();
											glRotatef(-15.0, 1, 0, 0);
											glTranslatef(-21.0f, 0.0f, -5.5f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glTranslatef(6.0f, 0.0f, 0.0f);
											mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
										glPopMatrix();
										//Fin de maderas de rieles
										glTranslatef(-2.0f, -3.0f, -11.0f);
										mi_figura.prisma(2.0, 58.0f, 1.5f, hierro_negro.GLindex);
										glTranslatef(54.0f, 0.0f, 0.0f);
										mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
										glTranslatef(-2.0f, 3.0f, 11.0f);
										mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
										glRotatef(30.0f, 0, 0, 1);
										glTranslatef(47.0f, -12.625f, 0.0f);
										glPushMatrix();
											mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
											//Madera de rieles
											glPushMatrix();
												glRotatef(-15.0, 1, 0, 0);
												glTranslatef(-21.0f, 0.0f, -5.5f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glTranslatef(6.0f, 0.0f, 0.0f);
												mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
											glPopMatrix();
											//Fin de maderas de rieles
											glTranslatef(0.0f, -2.0f, -11.0f);
											mi_figura.prisma(4.0, 50.0f, 1.5f, hierro_negro.GLindex);
											glTranslatef(50.0f, 0.0f, 0.0f);
											mi_figura.prisma(4.0, 50.0f, 1.5f, hierro_negro.GLindex);
											glTranslatef(0.0f, 2.0f, 11.0f);
											mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
											glRotatef(55.0f, 0, 0, 1);
											glTranslatef(40.0f, -21.0f, 0.0f);
											glPushMatrix();
												mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
												//Madera de rieles
												glPushMatrix();
													glTranslatef(-21.0f, 0.0f, -5.5f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glTranslatef(6.0f, 0.0f, 0.0f);
													mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
												glPopMatrix();
												//Fin de maderas de rieles
												glTranslatef(0.0f, 0.0f, -11.0f);
												mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
												glTranslatef(50.0f, 0.0f, 0.0f);
												mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
												glTranslatef(0.0f, 0.0f, 11.0f);
												mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
												glRotatef(30.0f, 0, 0, 1);
												glTranslatef(47.0f, -12.625f, 0.0f);
												glPushMatrix();
													mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
													//Madera de rieles
													glPushMatrix();
														glTranslatef(-21.0f, 0.0f, -5.5f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glTranslatef(6.0f, 0.0f, 0.0f);
														mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
													glPopMatrix();
													//Fin de maderas de rieles
													glTranslatef(0.0f, 0.0f, -11.0f);
													mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
													glTranslatef(50.0f, 0.0f, 0.0f);
													mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
													glTranslatef(0.0f, 0.0f, 11.0f);
													mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
													glRotatef(30.0f, 0, 0, 1);
													glTranslatef(47.0f, -12.625f, 0.0f);
													glPushMatrix();
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														//Madera de rieles
														glPushMatrix();
															glTranslatef(-21.0f, 0.0f, -5.5f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glPopMatrix();
														//Fin de maderas de rieles
														glTranslatef(0.0f, 0.0f, -11.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(50.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, 11.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glRotatef(30.0f, 0, 0, 1);
													glTranslatef(47.0f, -12.625f, 0.0f);
													glPushMatrix();
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														//Madera de rieles
														glPushMatrix();
															glTranslatef(-21.0f, 0.0f, -5.5f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glPopMatrix();
														//Fin de maderas de rieles
														glTranslatef(0.0f, 0.0f, -11.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(50.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, 11.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(50.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -11.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(33.25f, 0.0f, 15.875f);
														glRotatef(-30.0f, 0, 1, 0);
														mi_figura.prisma(2.0, 20.0f, 1.5f, hierro_negro.GLindex);
														//Madera de rieles
														glPushMatrix();
															glTranslatef(-10.0f, 0.0f, -4.75f);
															mi_figura.prisma(1.0f, 2.0f, 8.5f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(6.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glPopMatrix();
														//Fin de maderas de rieles
														glTranslatef(0.0f, 0.0f, -9.5f);
														mi_figura.prisma(2.0, 30.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(26.75f, 0.0f, 19.5f);
														glRotatef(-30.0f, 0, 1, 0);
														mi_figura.prisma(2.0, 40.0f, 1.5f, hierro_negro.GLindex);
														//Madera de rieles
														glPushMatrix();
															glTranslatef(-18.0f, 0.0f, -5.4375f);
															mi_figura.prisma(1.0f, 2.0f, 8.5f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glPopMatrix();
														//Fin de maderas de rieles
														glTranslatef(0.0f, 0.0f, -10.875);
														mi_figura.prisma(2.0, 40.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(32.125f, 0.0f, 18.325f);
														glRotatef(-30.0f, 0, 1, 0);
														mi_figura.prisma(2.0, 30.0f, 1.5f, hierro_negro.GLindex);
														//Madera de rieles
														glPushMatrix();
															glTranslatef(-18.0f, 0.0f, -4.9375f);
															mi_figura.prisma(1.0f, 2.0f, 8.5f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(1.0f, 2.0f, 10.0f, madera_cerca.GLindex);
														glPopMatrix();
														//Fin de maderas de rieles
														glTranslatef(0.0f, 0.0f, -9.875);
														mi_figura.prisma(2.0, 40.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(45.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(55.0f, 0.0f, 0.0f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(0.0f, 0.0f, -9.875f);
														mi_figura.prisma(2.0, 50.0f, 1.5f, hierro_negro.GLindex);
														glTranslatef(50.0f, 0.0f, 0.0f);
														glPushMatrix();
															glTranslatef(5.0f, 0.0f, 0.0f);
															mi_figura.prisma(2.0, 60.0f, 1.5f, hierro_negro.GLindex);
															glTranslatef(31.0f, 0.0f, 0.0f);
															glRotatef(-90.0f, 0, 1, 0);
															glTranslatef(4.9375f, 0.0f, 0.0f);
															mi_figura.prisma(2.0f, 9.875f, 1.5f, hierro_negro.GLindex);
														glPopMatrix();
														glTranslatef(-5.0f, 0.0f, 9.875f);
														mi_figura.prisma(2.0, 45.0f, 1.5f, hierro_negro.GLindex);
														glPushMatrix();
															glTranslatef(21.25f, -21.5f, 0.0f);
															glRotatef(-92.5f, 0, 1, 0);
															glPushMatrix();
																glTranslatef(76.5f, 0.0f, 0.0f);
																glRotatef(-15.0f, 0, 0, 1);
																mi_figura.prisma(2.5, 161.0f, 1.875f, hierro_negro.GLindex);
																glTranslatef(0.0f, 0.0f, -20.0f);
																mi_figura.prisma(2.5, 161.0f, 1.875f, hierro_negro.GLindex);
																//Madera de rieles
																glPushMatrix();
																	glTranslatef(-79.0f, 0.0f, 10.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																	glTranslatef(5.0f, 0.0f, 0.0f);
																	mi_figura.prisma(1.0f, 2.0f, 18.0f, madera_cerca.GLindex);
																glPopMatrix();
																//Fin de madera de rieles
															glPopMatrix();
														glPopMatrix();
													glPopMatrix();
													glPopMatrix();
												glPopMatrix();
											glPopMatrix();
										glPopMatrix();
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//Fin de los rieles
		glPopMatrix();
	glPopMatrix();
}

//Animacion del martillo
void a_martillo() {

	KeyFrame[0].varmartillo = 0.0f;
	KeyFrame[1].varmartillo = 10.0f;
	KeyFrame[2].varmartillo = -10.0f;
	KeyFrame[3].varmartillo = 20.0f;
	KeyFrame[4].varmartillo = -20.0f;
	KeyFrame[5].varmartillo = 30.0f;
	KeyFrame[6].varmartillo = -30.0f;
	KeyFrame[7].varmartillo = 40.0f;
	KeyFrame[8].varmartillo = -40.0f;
	KeyFrame[9].varmartillo = 50.0f;
	KeyFrame[10].varmartillo = -50.0f;
	KeyFrame[11].varmartillo = 60.0f;
	KeyFrame[12].varmartillo = -60.0f;
	KeyFrame[13].varmartillo = 70.0f;
	KeyFrame[14].varmartillo = -70.0f;
	KeyFrame[15].varmartillo = 80.0f;
	KeyFrame[16].varmartillo = -80.0f;
	KeyFrame[17].varmartillo = 90.0f;
	KeyFrame[18].varmartillo = -90.0f;
	KeyFrame[19].varmartillo = 100.0f;
	KeyFrame[20].varmartillo = -100.0f;
	KeyFrame[21].varmartillo = 110.0f;
	KeyFrame[22].varmartillo = -110.0f;
	KeyFrame[23].varmartillo = 120.0f;
	KeyFrame[24].varmartillo = -120.0f;
	KeyFrame[25].varmartillo = 130.0f;
	KeyFrame[26].varmartillo = -130.0f;
	KeyFrame[27].varmartillo = 140.0f;
	KeyFrame[28].varmartillo = -140.0f;
	KeyFrame[29].varmartillo = 150.0f;
	KeyFrame[30].varmartillo = -150.0f;
	KeyFrame[31].varmartillo = 160.0f;
	KeyFrame[32].varmartillo = -160.0f;
	KeyFrame[33].varmartillo = 170.0f;
	KeyFrame[34].varmartillo = -170.0f;
	KeyFrame[35].varmartillo = 180.0f;
	KeyFrame[36].varmartillo = 180.0f;
	KeyFrame[37].varmartillo = 180.0f;
	KeyFrame[38].varmartillo = 180.0f;
	KeyFrame[39].varmartillo = -30.0f;
	KeyFrame[40].varmartillo = 30.0f;
	KeyFrame[41].varmartillo = -20.0f;
	KeyFrame[42].varmartillo = 20.0f;
	KeyFrame[43].varmartillo = -10.0f;
	KeyFrame[44].varmartillo = 10.0f;
	KeyFrame[45].varmartillo = 0.0f;
	
}
//Recorrido predefinido
void camino_recorrido(float x, float y, float z, float roatY){
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		glPushMatrix();
			mi_figura.cilindro(80.0f, 0.5f, 80, camino.GLindex);
			glPushMatrix();
				glTranslatef(0.0f, 0.25f, 114.0f);
				mi_figura.prisma(0.5f, 20.0f, 70.0f, camino.GLindex);
				glPushMatrix();
					glTranslatef(-10.5f, 0.5, 12.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(10.5f, 0.5, 12.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glTranslatef(0.0f, 0.0f, -3.0f);
					mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-40.0f, 0.0f, 25.0f);
					mi_figura.prisma(0.5f, 60.0f, 20.0f,camino.GLindex);
					glPushMatrix();
						glTranslatef(29.0f, 0.5, -10.5f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(49.0f, 0.5, 10.5f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(-3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
					glPopMatrix();
					glTranslatef(-40.0F, 0.0F, 5.0F);
					mi_figura.prisma(0.5F, 20.0F, 30.0F, camino.GLindex);
					glPushMatrix();
						glTranslatef(10.5f, 0.5, 7.0f);
						mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glTranslatef(0.0f, 0.0f, 3.0f);
						mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glTranslatef(0.0f, 0.0f, 3.0f);
						mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-10.5f, 0.5, 7.0f);
						mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glTranslatef(0.0f, 0.0f, 3.0f);
						mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glTranslatef(0.0f, 0.0f, 3.0f);
						mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(85.0f, 0.0f, 25.0f);
					mi_figura.prisma(0.5f, 150.0f, 20.0f,camino.GLindex);
					glPushMatrix();
						glTranslatef(-73.0f, 0.5, 10.5f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(22.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-74.0f, 0.5, -10.5f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glTranslatef(3.0f, 0.0f, 0.0f);
						mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-35.0f, 0.0f, 60.0f);
						mi_figura.prisma(0.5f, 20.0f, 100.0f, camino.GLindex);
						glPushMatrix();
							glTranslatef(10.5f, 0.5, 49.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(-10.5f, 0.5, 49.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();
						glTranslatef(85.0F, 0.0F, 10.0F);
						mi_figura.prisma(0.5F, 20.0F, 40.0F, camino.GLindex);
						glPushMatrix();
							glTranslatef(10.5f, 0.5, 19.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(-10.5f, 0.5, 19.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -22.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();
						glTranslatef(85.0f, 0.0f, -42.5f);
						mi_figura.prisma(0.5f, 20.0f, 65.0f, camino.GLindex);
						glTranslatef(-57.5f, 0.0f, -42.5f);
						mi_figura.prisma(0.5f, 135.0f, 20.0f, camino.GLindex);
						glPushMatrix();
							glTranslatef(66.5f, 0.5, -10.5f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-25.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(44.5f, 0.5, 10.5f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glPopMatrix();
						glTranslatef(0.0f, 0.0f, -85.0f);
						mi_figura.prisma(0.5f, 20.0f, 150.0f, camino.GLindex);
						glPushMatrix();
							glTranslatef(-10.5f, 0.5, 74.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(10.5f, 0.5, 74.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -22.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, -3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(25.0f, 0.0f, 0.0f);
							mi_figura.prisma(0.5f, 30.0f, 20.0f, camino.GLindex);
							glPushMatrix();
								glTranslatef(-13.0f, 0.5, -10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(-13.0f, 0.5, 10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
						glPopMatrix();
						glTranslatef(-110.0f, 0.0f, -85.0f);
						mi_figura.prisma(0.5f, 240.0f, 20.0f, camino.GLindex);
						glPushMatrix();
							glTranslatef(99.0f, 0.5, 10.5f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-24.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(119.0f, 0.5, -10.5f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-23.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glTranslatef(-3.0f, 0.0f, 0.0f);
							mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(-40.0f, 0.0f, -85.0f);
							mi_figura.prisma(0.5f, 20.0f, 150.0f, camino.GLindex);
							glPushMatrix();
								glTranslatef(10.5f, 0.5, 73.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(-10.5f, 0.5, 73.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, -3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glPopMatrix();
						glPopMatrix();
						glPushMatrix();
							glTranslatef(-40.0f, 0.0f, 32.5f);
							mi_figura.prisma(0.5f, 20.0f, 45.0f, camino.GLindex);
							glPushMatrix();
								glTranslatef(-10.5f, 0.5, -20.5f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(10.5f, 0.5, -21.5f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
								glTranslatef(0.0f, 0.0f, 3.0f);
								mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glPopMatrix();
						glPopMatrix();
						glTranslatef(-130.0f, 0.0f, 117.5f);
						mi_figura.prisma(0.5f, 20.0f, 255.0f, camino.GLindex);
						glPushMatrix();
							glTranslatef(10.5f, 0.5, -106.5f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 25.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(-10.5f, 0.5, -121.5f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 23.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
							glTranslatef(0.0f, 0.0f, 3.0f);
							mi_figura.prisma(1.0f, 1.0f, 2.0f, rojo_s.GLindex);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(-20.0f, 0.0f, -50.0f);
							mi_figura.prisma(0.5f, 20.0f, 20.0f, camino.GLindex);
							glPushMatrix();
								glTranslatef(7.0f, 0.5, -10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(7.0f, 0.5, 10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
						glPopMatrix();
						glPushMatrix();
							glTranslatef(30.0f, 0.0f, 0.0f);
							mi_figura.prisma(0.5f, 40.0f, 20.0f, camino.GLindex);
							glPushMatrix();
								glTranslatef(-19.0f, 0.5, 10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(-19.0f, 0.5, -10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
						glPopMatrix();
						glTranslatef(15.0f, 0.0, 137.5f);
						mi_figura.prisma(0.5f, 50.0f, 20.0f, camino.GLindex);
						glPushMatrix();
								glTranslatef(-4.0f, 0.5, -10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
						glPushMatrix();
								glTranslatef(-24.0f, 0.5, 10.5f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
								glTranslatef(3.0f, 0.0f, 0.0f);
								mi_figura.prisma(1.0f, 2.0f, 1.0f, rojo_s.GLindex);
							glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void banca(float x, float y, float z, float roatY) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		glPushMatrix();
			mi_figura.prisma(5.0f, 1.5f, 1.5f, madera_cerca.GLindex);
			glPushMatrix();
				glTranslatef(10.0f, 2.5f, -3.25);
				mi_figura.prisma(1.0f, 21.0f, 7.5f, madera_cerca.GLindex);
			glPopMatrix();
			glTranslatef(20.0f, 0.0f, 0.0f);
			mi_figura.prisma(5.0f, 1.5f, 1.5f, madera_cerca.GLindex);
			glTranslatef(0.0f, 5.0f, -7.5f);
			mi_figura.prisma(15.0f, 1.5f, 1.5f, madera_cerca.GLindex);
			glTranslatef(-20.0f, 0.0f, 0.0f);
			mi_figura.prisma(15.0f, 1.5f, 1.5f, madera_cerca.GLindex);
			glPushMatrix();
				glTranslatef(0.0f, -1.0f, 0.0f);
				glRotatef(-90.0f, 0, 0, 1);
				mi_figura.cilindro(0.5f, 20.0f, 40, madera_cerca.GLindex);
				glTranslatef(-1.75f, 0.0f, 0.0f);
				mi_figura.cilindro(0.5f, 20.0f, 40, madera_cerca.GLindex);
				glTranslatef(-1.75f, 0.0f, 0.0f);
				mi_figura.cilindro(0.5f, 20.0f, 40, madera_cerca.GLindex);
				glTranslatef(-1.75f, 0.0f, 0.0f);
				mi_figura.cilindro(0.5f, 20.0f, 40, madera_cerca.GLindex);
				glTranslatef(-1.75f, 0.0f, 0.0f);
				mi_figura.cilindro(0.5f, 20.0f, 40, madera_cerca.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void poste(float x, float y, float z, float roatY) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		glPushMatrix();
			mi_figura.cilindro(0.75f, 60.0f, 40, hierro_negro.GLindex);
			glTranslatef(0.0f, 57.0f, 0.0f);
			glPushMatrix();
				glRotatef(90.0f, 0, 0, 1);
				mi_figura.cilindro(0.25f, 12.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 11.0f, 0.0f);
				glRotatef(90.0f, 0, 0, 1);
				mi_figura.cilindro(0.25f, 5.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 5.0f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(1.5f, 4.0f, 40, luz.GLindex);
				glPushMatrix();
					glTranslatef(1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
			glPopMatrix();
			glPushMatrix();
				glRotatef(-90.0f, 0, 0, 1);
				glRotatef(180.0f, 0, 1, 0);
				mi_figura.cilindro(0.25f, 12.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 11.0f, 0.0f);
				glRotatef(90.0f, 0, 0, 1);
				mi_figura.cilindro(0.25f, 5.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 5.0f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(1.5f, 4.0f, 40, luz.GLindex);
				glPushMatrix();
					glTranslatef(1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90.0f, 1, 0, 0);
				glRotatef(90, 0, 1, 0);
				mi_figura.cilindro(0.25f, 12.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 11.0f, 0.0f);
				glRotatef(90.0f, 0, 0, 1);
				mi_figura.cilindro(0.25f, 5.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 5.0f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(1.5f, 4.0f, 40, luz.GLindex);
				glPushMatrix();
					glTranslatef(1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
			glPopMatrix();
			glPushMatrix();
				glRotatef(-90.0f, 1, 0, 0);
				glRotatef(-90, 0, 1, 0);
				mi_figura.cilindro(0.25f, 12.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 11.0f, 0.0f);
				glRotatef(90.0f, 0, 0, 1);
				mi_figura.cilindro(0.25f, 5.0f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 5.0f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(1.5f, 4.0f, 40, luz.GLindex);
				glPushMatrix();
					glTranslatef(1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-1.625f, 0.0f, 0.0f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -1.625f);
					mi_figura.cilindro(0.125, 4.0f, 40, hierro_negro.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				mi_figura.cilindro(2.0f, 0.25f, 40, hierro_negro.GLindex);
				glTranslatef(0.0f, 0.25f, 0.0f);
				mi_figura.cilindro(0.75f, 0.25f, 40, hierro_negro.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void bote_basura(float x, float y, float z, float roatY) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		glPushMatrix();
			mi_figura.cilindro(3.0f, 0.5f, 40, amarillo_m.GLindex);
			glTranslatef(0.0f, 0.5f, 0.0f);
			glPushMatrix();
				glTranslatef(2.75f, 0.0f, 0.0f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(65, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2.75f, 0.0f, 0.0f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(-90, 0, 0, 1);
					glRotatef(-65, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(-2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(-2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(-2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(-2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(-2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 2.75f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(-25, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -2.75f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(155, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2.0f, 0.0f, -1.8f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(110, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2.0f, 0.0f, -1.8f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(205, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2.0f, 0.0f, 1.8f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(25, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.25f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2.0f, 0.0f, 1.8f);
				mi_figura.cilindro(0.25f, 12.0f, 40, amarillo_m.GLindex);
				glPushMatrix();
					glTranslatef(0.0f, 12.0f, 0.0f);
					mi_figura.esfera(0.25f, 40, 40, amarillo_m.GLindex);
				glPopMatrix();
				glTranslatef(0.0f, 2.0f, 0.0f);
				glPushMatrix();
					glRotatef(90, 0, 0, 1);
					glRotatef(-65, 1, 0, 0);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
					glTranslatef(2.0f, 0.0f, 0.0f);
					mi_figura.cilindro(0.25f, 2.0f, 40, amarillo_m.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void resetElements(void)
{
	varmartillo = KeyFrame[0].varmartillo;		//Asigna nuevamente los valores guardados, de la posición inicial
	
}
void interpolation(void)
{

	KeyFrame[playIndex].varmartilloInc = (KeyFrame[playIndex + 1].varmartillo - KeyFrame[playIndex].varmartillo) / i_max_steps;
	

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
		glTranslatef(0.0, 150.0, 0.0);
		figcielo.skybox(500.0, 450.0, 690.0, tex_skybox);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Poner codigo aqui
	glDisable(GL_LIGHTING);

	glPushMatrix(); //Plataforma principal
	glDisable(GL_LIGHTING);
	mi_figura.prisma2(1.0, 500.0, 690.0, concreto.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//     CONSTRUCCIÓN DE ESCENARIO

	glPushMatrix();

		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				//Miscelanea
				//Parte 1
				poste(-120.0f, 0.5f, 95.0f, 0);
				banca(-116.0f, 3.0f, 95.0f, 0);
				banca(-94.0f, 3.0f, 95.0f, 0);
				bote_basura(-68.0f, 0.5f, 92.0f, 0);
				banca(-63.0f, 3.0f, 95.0f, 0);
				banca(-41.0f, 3.0f, 95.0f, 0);
				poste(-11.0f, 0.5f, 95.0f, 0);
				//Parte 1-2
				poste(-120.0f, 0.5f, 118.0f, 0);
				banca(27.5f, 3.0f, 118.0f, 180);
				poste(40.0f, 0.5f, 118.0f, 0);
				bote_basura(67.0f, 0.5f, 120.0f, 0);
				banca(95.0f, 3.0f, 120.0f, 180);
				banca(117.0f, 3.0f, 120.0f, 180);
				banca(139.0f, 3.0f, 120.0f, 180);
				banca(161.0f, 3.0f, 120.0f, 180);
				poste(195.0f, 0.5f, 130.0f, 0);
				//
				banca(40.0f, 3.0f, 150.0f, 90);
				banca(40.0f, 3.0f, 172.0f, 90);
				banca(40.0f, 3.0f, 194.0f, 90);
				bote_basura(37.0f, 0.5f, 200.0f, 0);
				poste(40.0f, 0.5f, 206.0f, 0);
				//
				banca(65.0f, 3.0f, 128.0f, -90);
				banca(65.0f, 3.0f, 150.0f, -90);
				banca(65.0f, 3.0f, 172.0f, -90);
				bote_basura(68.0f, 0.5f, 200.0f, 0);
				poste(66.0f, 0.5f, 206.0f, 0);
				//
				banca(15.0f, 3.0f, 95.0f, 0);
				bote_basura(42.5f, 0.5f, 92.0f, 0);
				poste(50.0f, 0.5f, 95.0f, 0.0f);
				banca(53.0f, 3.0f, 95.0f, 0);
				banca(75.0f, 3.0f, 95.0f, 0);
				banca(97.0f, 3.0f, 95.0f, 0);
				bote_basura(122.0f, 0.5f, 92.0f, 0);
				banca(128.0f, 3.0f, 95.0f, 0);
				poste(151.0f, 0.5f, 95.0f, 0);
				//Parte 2
				poste(-25.0f, 0.5f, -153.0f, 0);
				banca(-22.0f, 3.0f, -155.0f, 0);
				bote_basura(5.0f, 0.5f, -156.0f, 0);
				banca(12.0f, 3.0f, -155.0f, 0);
				banca(34.0f, 3.0f, -155.0f, 0);
				banca(56.0f, 3.0f, -155.0f, 0);
				bote_basura(81.0f, 0.5f, -156.0f, 0);
				//Parte2-1
				poste(-120.0f, 0.5f, -130.0f, 0);
				banca(-98.0f, 3.0f, -130.0f, 180);
				banca(-76.0f, 3.0f, -130.0f, 180);
				banca(-54.0f, 3.0f, -130.0f, 180);
				poste(-52.0f, 0.5f, -153.0f, 0);
				//Parte3
				poste(-26.0f, 0.5f, -131.0f, 0);
				banca(0.0f, 3.0f, -130.0f, 180);
				bote_basura(5.0f, 0.5f, -126.0f, 0);
				banca(34.0f, 3.0f, -130.0f, 180);
				banca(56.0f, 3.0f, -130.0f, 180);
				banca(78.0f, 3.0f, -130.0f, 180);
				bote_basura(82.0f, 0.5f, -126.0f, 0);
				poste(90.0f, 0.5f, -131.0f, 0);
				//Juegos mecanicos
				martillo_golpe(205.0, 1.5f, 30.0, -180.0f, azul_m.GLindex, negro_m.GLindex, lona.GLindex);
				encestar(-200.0f, 25.0f, -70.0f, amarillo_m.GLindex, 90.0f);
				glPushMatrix();
					glScalef(1.0f, 0.9f, 0.9f);
					aros_botellas(-197.5, 25.0, 20.0, amarillo_s.GLindex, rojo_s.GLindex, vidrio.GLindex, porcelana.GLindex,90.0f);
				glPopMatrix();
				glPushMatrix();
					glScalef(1.0f, 1.5f, 1.0f);
					globero(135.0f, 10.5f, -10.0f, amarillo_s.GLindex, rojo_s.GLindex, morado_m.GLindex);
					algodonero(135.0f, 10.5f, -110.0f, amarillo_s.GLindex, rojo_s.GLindex, rosa_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glScalef(0.6f, 0.7f, 0.6f);
					carrusel(0.0, 1.0, -40.0, 0.0, azul_m.GLindex, rojo_m.GLindex, morado_m.GLindex, naranja_m.GLindex, rosa_m.GLindex, vino_m.GLindex, azulo_m.GLindex);
				glPopMatrix();
				glPushMatrix();
					glScalef(1.75f, 1.0f, 1.625f);
					camino_recorrido(0.0f, 0.5f, -30.0f, 0);
				glPopMatrix();
				sillas_voladoras(250.0, 0.0, -320.0, morado_m.GLindex, amarillo_m.GLindex, morado_m.GLindex, cromo.GLindex);
				rueda_fortuna(-80.0, 53.0, 190.0, porcelana.GLindex, rayos.GLindex);
				//Si agregamos tienda se traba en nuestra computadora
				tienda(185.0f, 2.0f, -60.0f, 0.0f);
				//Si agregamos tienda se traba en nuestra computadora
				carrito_montania(-40.0f, 3.5f, -310.0f);
				montania_rusa(-40.0f, 1.0f, -300.0f, 0);
				martillo_mecanico(175.0f, 4.5f, 185.0f, -90.0f, negro_m.GLindex, rojo_m.GLindex, azul_m.GLindex, verde_m.GLindex, naranja_m.GLindex);
				glPushMatrix();
					glScalef(1.5, 1.5, 1.5);
					tacitas(-100.0f, 0.5f, -145.0, rojo_m.GLindex, dorado.GLindex, porcelana.GLindex);
				glPopMatrix();
				carrito_montania(-40.0f, 3.5f, -310.0f);
			glPopMatrix();		
	
	glPopMatrix();
		
	//Transparencias aquí
	glPopMatrix();
	glPopMatrix();
	

	

	//Todo antes de esto
	glDisable(GL_BLEND);
	//Fin transparencias
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glColor3f(colorR, colorG, colorB);
	glutSwapBuffers();
	glPopMatrix();

}

//Separamos el recorrido de la montaña rusa porque fue lo ultimo que agregamos
bool mon_rusa = false;
bool recorrido_1 = true;
bool recorrido_2 = false;
bool recorrido_3 = false;
bool recorrido_4 = false;
bool recorrido_5 = false;
bool recorrido_6 = false;
bool recorrido_7 = false;
bool recorrido_8 = false;
bool recorrido_9 = false;
bool recorrido_10 = false;
bool recorrido_11 = false;
bool recorrido_12 = false;
bool recorrido_13 = false;
bool recorrido_14 = false;
bool recorrido_15 = false;
bool recorrido_16 = false;
bool recorrido_17 = false;
bool recorrido_18 = false;
bool recorrido_19 = false;
bool recorrido_20 = false;
bool recorrido_21 = false;
bool recorrido_22 = false;
bool recorrido_23 = false;
bool recorrido_24 = false;
bool recorrido_25 = false;
bool recorrido_26 = false;
bool recorrido_27 = false;


void animacion()
{	
	if (mon_rusa) {
		if (recorrido_1) {
			mov_carrox = mov_carrox + 2;
			if (mov_carrox > 32) {
				rot_carroz = 35.0;
				//mov_carroy = 6.0;
				recorrido_1 = false;
				recorrido_2 = true;
			}
		}
		if (recorrido_2) {
			mov_carrox = mov_carrox + 0.6;
			mov_carroy = mov_carroy + 0.42;
			if ((mov_carrox > 198) && (mov_carroy > 0)) {
				rot_carroz = 0.0;
				recorrido_2 = false;
				recorrido_3 = true;
			}
		}
		if (recorrido_3) {
			mov_carrox = mov_carrox + 1;

			if ((mov_carrox > 225)) {
				rot_carroy = -25.0;
				recorrido_3 = false;
				recorrido_4 = true;
			}
		}
		if (recorrido_4) {
			mov_carrox = mov_carrox + 1;
			mov_carroz = mov_carroz + 0.5;
			rot_carroy = -40;
			if ((mov_carrox > 12) && (mov_carroz > 13.0)) {
				recorrido_4 = false;
				recorrido_5 = true;
			}
		}
		if (recorrido_5) {
			mov_carrox = mov_carrox + 0.8;
			mov_carroz = mov_carroz + 1;
			rot_carroy = -60;
			if ((mov_carrox > 2.5) && (mov_carroz > 40)) {
				recorrido_5 = false;
				recorrido_6 = true;
			}
		}
		if (recorrido_6) {
			//mov_carrox = mov_carrox + 1;
			mov_carroz = mov_carroz + 1;
			rot_carroy = -90;
			if ((mov_carroz > 90)) {
				recorrido_6 = false;
				recorrido_7 = true;
			}
		}
		if (recorrido_7) {
			mov_carroy = mov_carroy - 0.7;
			mov_carroz = mov_carroz + 1;
			rot_carrox = 35;
			if ((mov_carroy < 1) && (mov_carroz > 0.8)) {
				recorrido_7 = false;
				recorrido_8 = true;
			}
		}
		if (recorrido_8) {
			mov_carroz = mov_carroz + 1;
			rot_carrox = 0;
			if (mov_carroz > 300) {
				rot_carroz = 35.0;
				recorrido_8 = false;
				recorrido_9 = true;
			}
		}
		if (recorrido_9) {
			mov_carroz = mov_carroz + 0.6;
			mov_carroy = mov_carroy + 0.42;
			if ((mov_carroz > 590) && (mov_carroy > 1)) {
				rot_carroz = 0.0;
				mov_carroy = 203.0;
				recorrido_9 = false;
				recorrido_10 = true;
			}
		}
		if (recorrido_10) {
			mov_carroz = mov_carroz + 1;

			if (mov_carroz > 610) {

				rot_carroy = -125.0;
				recorrido_10 = false;
				recorrido_11 = true;
			}
		}
		if (recorrido_11) {
			mov_carroz = mov_carroz + 1;
			mov_carrox = mov_carrox - 0.5;
			if ((mov_carroz > 643)) {
				rot_carroy = -180.0;
				recorrido_11 = false;
				recorrido_12 = true;
			}
		}
		if (recorrido_12) {
			mov_carrox = mov_carrox - 1;

			if ((mov_carrox < 220)) {
				rot_carroz = -35.0;
				recorrido_12 = false;
				recorrido_13 = true;
			}

		}
		if (recorrido_13) {
			mov_carrox = mov_carrox - 1.0;
			mov_carroy = mov_carroy - 0.7;
			if ((mov_carrox < 50) && (mov_carroy > 1)) {
				rot_carroz = 0.0;
				mov_carroy = 85.0;
				recorrido_13 = false;
				recorrido_14 = true;
			}
		}
		if (recorrido_14) {
			mov_carrox = mov_carrox - 1;

			if ((mov_carrox < -47)) {
				rot_carroz = 30;
				rot_carroy = -200;
				rot_carrox = -15.0;
				mov_carroy = 92;
				mov_carroz = 640;
				recorrido_14 = false;
				recorrido_15 = true;
			}

		}
		if (recorrido_15) {
			mov_carrox = mov_carrox - 1;
			mov_carroy = mov_carroy + 0.8;
			mov_carroz = mov_carroz - 1;
			if ((mov_carrox < -100) && (mov_carroy > -1) && (mov_carroz < 641)) {
				mov_carrox = -110;
				mov_carroz = 593;
				mov_carroy = 140;
				rot_carroz = 60.0;
				recorrido_15 = false;
				recorrido_16 = true;
			}
		}
		if (recorrido_16) {
			mov_carrox = mov_carrox - 0.4;
			mov_carroy = mov_carroy + 0.9;
			if ((mov_carrox < -120) && (mov_carroy > 220)) {
				mov_carrox = -132;
				mov_carroz = 558;
				mov_carroy = 230;
				rot_carroz = 125.0;
				recorrido_16 = false;
				recorrido_17 = true;
			}
		}
		if (recorrido_17) {
			mov_carrox = mov_carrox + 0.5;
			mov_carroy = mov_carroy + 0.9;
			if ((mov_carrox < -80) && (mov_carroy > 310)) {
				mov_carrox = -72;
				mov_carroz = 550;
				mov_carroy = 308;
				rot_carroz = 150.0;
				recorrido_17 = false;
				recorrido_18 = true;
			}
		}
		if (recorrido_18) {
			mov_carrox = mov_carrox + 0.5;
			mov_carroy = mov_carroy + 0.25;
			if ((mov_carrox < 5) && (mov_carroy > 343)) {
				mov_carrox = 13;
				mov_carroz = 570;
				mov_carroy = 348;
				rot_carroz = 180.0;
				rot_carroy = -180.0;
				recorrido_18 = false;
				recorrido_19 = true;
			}
		}
		if (recorrido_19) {
			mov_carrox = mov_carrox + 0.5;
			mov_carroy = mov_carroy + 0.1;
			if ((mov_carrox < 83) && (mov_carroy > 361)) {
				mov_carrox = 108;
				mov_carroz = 562;
				mov_carroy = 339;
				rot_carroz = 215.0;
				rot_carroy = -180.0;
				recorrido_19 = false;
				recorrido_20 = true;
			}
		}
		if (recorrido_20) {
			mov_carrox = mov_carrox + 5;
			mov_carroy = mov_carroy - 3;
			if ((mov_carroy < 310) && (mov_carrox > 170)) {
				mov_carrox = 178;
				mov_carroz = 562;
				mov_carroy = 278;
				rot_carroz = 270.0;
				rot_carrox = -30.0;
				recorrido_20 = false;
				recorrido_21 = true;
			}
		}
		if (recorrido_21) {
			mov_carroy = mov_carroy - 3;
			if ((mov_carroy < 190)) {
				mov_carrox = 172;
				mov_carroz = 562;
				mov_carroy = 182;
				rot_carroz = 300.0;
				rot_carrox = 0.0;
				recorrido_21 = false;
				recorrido_22 = true;
			}
		}
		if (recorrido_22) {
			mov_carrox = mov_carrox - 2;
			mov_carroy = mov_carroy - 3;
			if ((mov_carroy < 95) && (mov_carrox <115)) {
				// 
				mov_carrox = 114;
				mov_carroz = 562;
				mov_carroy = 98;
				rot_carroz = 330.0;
				rot_carrox = 0.0;
				recorrido_22 = false;
				recorrido_23 = true;
			}
		}
		if (recorrido_23) {
			mov_carrox = mov_carrox - 5;
			mov_carroy = mov_carroy - 3;
			if ((mov_carroy < 58)) {
				// && (mov_carrox < 20)
				mov_carrox = 25;
				mov_carroz = 573;
				mov_carroy = 60;
				rot_carroz = 0.0;
				rot_carrox = 0.0;
				rot_carroy = 0;
				recorrido_23 = false;
				recorrido_24 = true;
			}
		}
		if (recorrido_24) {
			mov_carrox = mov_carrox - 5;
			mov_carroy = mov_carroy - 0.3;
			if ((mov_carrox < -85)) {
				//mov_carrox = -25;
				mov_carroz = 583;
				mov_carroy = 54;
				rot_carroz = 180.0;
				rot_carroy = 90.0;
				rot_carrox = -180.0;
				recorrido_24 = false;
				recorrido_25 = true;
			}
		}
		if (recorrido_25) {
			mov_carroz = mov_carroz - 3;
			mov_carrox = mov_carrox - 3;
			if ((mov_carroz < 520)) {
				//mov_carrox = -25;
				//mov_carroz = 560;
				mov_carroy = 54;
				rot_carroz = 180.0;
				rot_carroy = 85.0;
				rot_carrox = -180.0;
				recorrido_25 = false;
				recorrido_26 = true;
			}
		}
		if (recorrido_26) {
			mov_carroz = mov_carroz - 3;
			mov_carroy = mov_carroy - 0.08;
			mov_carrox = mov_carrox - 0.2;
			if ((mov_carroz < 0)) {
				//mov_carrox = -25;
				//mov_carroz = 560;
				//mov_carroy = 54;
				rot_carroz = 165.0;
				rot_carroy = 180.0;
				rot_carrox = -180.0;
				recorrido_26 = false;
				recorrido_27 = true;
			}
		}
		if (recorrido_27) {
			mov_carroy = mov_carroy - 0.3;
			mov_carrox = mov_carrox + 1;
			if ((mov_carrox > -50)) {
				mov_carrox = -20;
				mov_carroz = 0;
				mov_carroy = 3.5;
				rot_carroz = 180.0;
				rot_carroy = 180.0;
				rot_carrox = -180.0;
				recorrido_27 = false;
				recorrido_27 = true;
			}
		}

	}

	if (recorrido) {
		if (inicio) {
			objcamera.Position_Camera(50, 20, 200, 50, 40.0f, 0, 0, 1, 0);
			inicio = false;
		}
		if (avance1) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 3.25) {
				avance1 = false;
				avance2 = true;
			}
		}
		if (avance2) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == 5.75) {
				avance2 = false;
				avance3 = true;
			}
		}
		if (avance3) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 7.75) {
				avance3 = false;
				avance4 = true;
			}
		}
		if (avance4) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == 0.0) {
				avance4 = false;
				avance5 = true;
			}
		}
		if (avance5) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 10.75) {
				avance5 = false;
				avance6 = true;
			}
		}
		if (avance6) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == (-5.75)) {
				avance6 = false;
				avance7 = true;
			}
		}
		if (avance7) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 13.0) {
				avance7 = false;
				avance8 = true;
			}
		}
		if (avance8) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == 0.0) {
				avance8 = false;
				avance9 = true;
			}
		}
		if (avance9) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 19.25) {
				avance9 = false;
				avance10 = true;
			}
		}
		if (avance10) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == (-5.75)) {
				avance10 = false;
				avance11 = true;
			}
		}
		if (avance11) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 24.75) {
				avance11 = false;
				avance12 = true;
			}
		}
		if (avance12) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == 0.0) {
				avance12 = false;
				avance13 = true;
			}
		}
		if (avance13) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 30.0) {
				avance13 = false;
				avance14 = true;
			}
		}
		if (avance14) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == -11.25) {
				avance14 = false;
				avance15 = true;
			}
		}
		if (avance15) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 35.25) {
				avance15 = false;
				avance16 = true;
			}
		}
		if (avance16) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == -5.75) {
				avance16 = false;
				avance17 = true;
			}
		}
		if (avance17) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 38.5) {
				avance17 = false;
				avance18 = true;
			}
		}
		if (avance18) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == -11.25) {
				avance18 = false;
				avance19 = true;
			}
		}
		if (avance19) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 47.0) {
				avance19 = false;
				avance20 = true;
			}
		}
		if (avance20) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == -16.75) {
				avance20 = false;
				avance21 = true;
			}
		}
		if (avance21) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 51.5) {
				avance21 = false;
				avance22 = true;
			}
		}
		if (avance22) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == -22.5) {
				avance22 = false;
				avance23 = true;
			}
		}
		if (avance23) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 53.25) {
				avance23 = false;
				avance24 = true;
			}
		}
		if (avance24) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == -11.25) {
				avance24 = false;
				avance25 = true;
			}
		}
		if (avance25) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 55.0) {
				avance25 = false;
				avance26 = true;
			}
		}
		if (avance26) {
			objcamera.Rotate_View(-CAMERASPEED);
			roatCamara -= 0.25;
			if (roatCamara == -16.75) {
				avance26 = false;
				avance27 = true;
			}
		}
		if (avance27) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 57.0) {
				avance27 = false;
				avance28 = true;
			}
		}
		if (avance28) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == -11.25) {
				avance28 = false;
				avance29 = true;
			}
		}
		if (avance29) {
			objcamera.Move_Camera(CAMERASPEED/2);
			avanceZ += 0.25;
			if (avanceZ == 60.5) {
				avance29 = false;
				avance30 = true;
			}
		}
		if (avance30) {
			objcamera.Rotate_View(CAMERASPEED);
			roatCamara += 0.25;
			if (roatCamara == 0.0) {
				avance30 = false;
				avanceZ = 0.0f;
			}
		}
	}

	if (gira_rueda) {

		if (girando_rueda) {
			rueda = rueda + 0.5;
			cabina = cabina - 0.5;
			if (rueda == 360) {
				girando_rueda = false;
			}
		}
	}

	if (gira_martillo) {
		if (baja_martillo) {
			g_martillo = g_martillo - 0.5;
			if (g_martillo == -20.0) {
				baja_martillo = false;
				sube_martillo = true;
			}
		}
		if (sube_martillo) {
			g_martillo = g_martillo + 1.5;
			if (g_martillo == 16.0) {
				sube_martillo = false;
			}
		}
	}

	if (gira_carrusel) {
		if (girando_carrusel) {
			g_carrusel = g_carrusel + 0.5;
			if (g_carrusel == 720) {
				girando_carrusel = false;
			}
		}
	}

	if (gira_sillas) {
		if (subiendo_sillas) {
			sillas_ab = sillas_ab + 1.0;

			if (sillas_ab == -25) {
				subiendo_sillas = false;
				girando_sillas = true;
			}

		}
		if (girando_sillas) {
			sillas = sillas - 2.0;
			if (sillas == -360) {
				girando_sillas = false;
				bajando_sillas = true;

			}
		}
		if (bajando_sillas) {
			sillas_ab = sillas_ab - 1.0;
			if (sillas_ab == -65) {
				bajando_sillas = false;

			}
		}
	}

	if (play)			//Variable que indica si se ejecuta la animación o no
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			varmartillo += KeyFrame[playIndex].varmartilloInc;
	
			i_curr_steps++;
		}

	}
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

	case 'Q':
	case 'q':
		PlaySound(TEXT("FERIA.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP );
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

	case 'j':
	case 'J':
		mon_rusa ^= true;
		inicio = true;
		avance1 = true;
		avanceZ = 0.0;
		gira_rueda ^= true;
		gira_carrusel ^= true;
		gira_sillas ^= true;
		
		break;
	case 'u':
	case'U':
		recorrido = true;
		roatCamara = 0.0;
		break;
	case 'x':
		rot_carrox = rot_carrox + 5;
		break;

	case 'X':
		rot_carrox = rot_carrox - 5;
		break;

	case 'y':
		rot_carroy = rot_carroy + 5;
	break;

	case 'Y':
		rot_carroy = rot_carroy - 5;
	break;

	case 'z':
		rot_carroz = rot_carroz + 5;
		break;

	case 'Z':
		rot_carroz = rot_carroz - 5;
		break;

	case 'v':
		mov_carrox = mov_carrox + 1;
		break;

	case 'V':
		mov_carrox = mov_carrox - 1;
		break;

	case 'b':
		mov_carroy = mov_carroy + 1;
		break;

	case 'B':
		mov_carroy = mov_carroy - 1;
		break;

	case 'n':
		mov_carroz = mov_carroz + 1;
		break;

	case 'N':
		mov_carroz = mov_carroz - 1;
		break;

	case 'l':
	case 'L':
		gira_martillo ^= true;
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				//Para resetear la animaci´´on
			interpolation();
			//printf("\nYa salí de la interpolacion\n");
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
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
		objcamera.UpDown_Camera(CAMERASPEED+0.05);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objcamera.UpDown_Camera(-CAMERASPEED- 0.05);
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

void menuKeyFrame(int id)
{
	switch (id)
	{

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	}
}

/*
void menu(int id)
{

}
*/

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

	//Funciones para keyframes

	a_martillo();
	//a_rueda();
	glutMainLoop();

	
	return 0;
}