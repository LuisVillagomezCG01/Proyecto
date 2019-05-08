//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cilindro2(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma (float altura, float largo, float profundidad, GLuint text);
	void prisma2(float altura, float largo, float profundidad, GLuint text);
	void esfera2(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera

	
};
