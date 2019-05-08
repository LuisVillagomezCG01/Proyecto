#include "figuras.h"


const double PI = 3.1415926535897;
float text_der = 1.0;
float text_izq = 0.0;

void CFiguras::skybox(float largo, float altura, float profundidad, GLuint text) //Funcion creacion cielo
{
	GLfloat vertice[8][3] = {
		{ 0.5*largo ,-0.5*altura, 0.5*profundidad }, //Coordenadas V�rtice 1 V1
		{ -0.5*largo ,-0.5*altura , 0.5*profundidad }, //Coordenadas V�rtice 2 V2
		{ -0.5*largo ,-0.5*altura , -0.5*profundidad }, //Coordenadas V�rtice 3 V3
		{ 0.5*largo ,-0.5*altura , -0.5*profundidad }, //Coordenadas V�rtice 4 V4
		{ 0.5*largo ,0.5*altura , 0.5*profundidad }, //Coordenadas V�rtice 5 V5
		{ 0.5*largo ,0.5*altura , -0.5*profundidad }, //Coordenadas V�rtice 6 V6
		{ -0.5*largo ,0.5*altura , -0.5*profundidad }, //Coordenadas V�rtice 7 V7
		{ -0.5*largo ,0.5*altura , 0.5*profundidad }, //Coordenadas V�rtice 8 V8
	};

	glBindTexture(GL_TEXTURE_2D, text); // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON); //Left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON); //Bottom
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON); //Top
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.7f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.4f, 0.7f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.4f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void CFiguras::prisma(float altura, float largo, float profundidad, GLuint text)  //Funcion creacion prisma
{

	GLfloat vertice[8][3] = {
		{ 0.5*largo ,-0.5*altura, 0.5*profundidad },    //Coordenadas V�rtice 1 V1
		{ -0.5*largo ,-0.5*altura , 0.5*profundidad },    //Coordenadas V�rtice 2 V2
		{ -0.5*largo ,-0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 3 V3
		{ 0.5*largo ,-0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 4 V4
		{ 0.5*largo ,0.5*altura , 0.5*profundidad },    //Coordenadas V�rtice 5 V5
		{ 0.5*largo ,0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 6 V6
		{ -0.5*largo ,0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 7 V7
		{ -0.5*largo ,0.5*altura , 0.5*profundidad },    //Coordenadas V�rtice 8 V8
	};

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	glBegin(GL_POLYGON); //Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON); //Right
						 //glColor3f(0.0,0.0,1.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON); //Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
						  //glColor3f(1.0,1.0,1.0);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void CFiguras::prisma2(float altura, float largo, float profundidad, GLuint text)  //Funcion creacion prisma
{

	GLfloat vertice[8][3] = {
		{ 0.5*largo ,-0.5*altura, 0.5*profundidad },    //Coordenadas V�rtice 1 V1
		{ -0.5*largo ,-0.5*altura , 0.5*profundidad },    //Coordenadas V�rtice 2 V2
		{ -0.5*largo ,-0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 3 V3
		{ 0.5*largo ,-0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 4 V4
		{ 0.5*largo ,0.5*altura , 0.5*profundidad },    //Coordenadas V�rtice 5 V5
		{ 0.5*largo ,0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 6 V6
		{ -0.5*largo ,0.5*altura , -0.5*profundidad },    //Coordenadas V�rtice 7 V7
		{ -0.5*largo ,0.5*altura , 0.5*profundidad },    //Coordenadas V�rtice 8 V8
	};

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	glBegin(GL_POLYGON); //Front
	glNormal3f(0.0f, 0.0f, 32.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 32.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(32.0f, 32.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(32.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON); //Right
						 //glColor3f(0.0,0.0,32.0);
	glNormal3f(32.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(32.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(32.0f, 32.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 32.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON); //Back
	glNormal3f(0.0f, 0.0f, -32.0f);
	glTexCoord2f(0.0f, 32.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(32.0f, 32.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(32.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
						  //glColor3f(32.0,32.0,32.0);
	glNormal3f(-32.0f, 0.0f, 0.0f);
	glTexCoord2f(32.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(32.0f, 32.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 32.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -32.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(32.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(32.0f, 32.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 32.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 32.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(32.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(32.0f, 32.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 32.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void CFiguras::esfera(GLfloat radio, int meridianos, int paralelos, GLuint text )
{
	GLdouble theta, phi;

	float ctext_s = 1.0/meridianos;
	float ctext_t = 1.0/paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[]={0.0, 0.0, 0.0};
	float v2[]={0.0, 0.0, 0.0};
	float v3[]={0.0, 0.0, 0.0};
	float v4[]={0.0, 0.0, 0.0};
	int i, j;
	float angulom, angulop;
	angulom=2*3.141592654/meridianos;
	angulop=3.141592654/paralelos; 
	for(i=0;i<meridianos;i++)
	{
		for(j=0;j<paralelos;j++)
		{
			v1[0]=radio*cos(angulom*i)*sin(angulop*j);
			v1[1]=radio*cos(angulop*j);
			v1[2]=radio*sin(angulom*i)*sin(angulop*j);
			
			v2[0]=radio*cos(angulom*i)*sin(angulop*(j+1));
			v2[1]=radio*cos(angulop*(j+1));
			v2[2]=radio*sin(angulom*i)*sin(angulop*(j+1));
			
			v3[0]=radio*cos(angulom*(i+1))*sin(angulop*(j+1));
			v3[1]=radio*cos(angulop*(j+1));
			v3[2]=radio*sin(angulom*(i+1))*sin(angulop*(j+1));

			v4[0]=radio*cos(angulom*(i+1))*sin(angulop*j);
			v4[1]=radio*cos(angulop*j);
			v4[2]=radio*sin(angulom*(i+1))*sin(angulop*j);
			
			glBegin(GL_POLYGON);
				glNormal3fv(v1);
				glTexCoord2f(ctext_s*i, -ctext_t*j);	
				glVertex3fv(v1);
				glNormal3fv(v2);
				glTexCoord2f(ctext_s*i, -ctext_t*(j+1));	
				glVertex3fv(v2);
				glNormal3fv(v3);
				glTexCoord2f(ctext_s*(i+1), -ctext_t*(j+1));	
				glVertex3fv(v3);
				glNormal3fv(v4);
				glTexCoord2f(ctext_s*(i+1), -ctext_t*j);	
				glVertex3fv(v4);
			glEnd();
		}
	}
}

void CFiguras::cilindro(float radio, float altura, int resolucion, GLuint text)
{
	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	float v5[] = { 0.0, 0.0, 0.0 };

	float angulo = 2 * 3.14 / resolucion;

	//float ctext_s = 1/resolucion-1;
	float ctext_s = 3.0 / resolucion; //si colocamos valor mayor se repite textura, (linea 489 de figuras.cpp)
	float ctext_t = 0.0;


	for (int i = 0; i <resolucion; i++)
	{

		v2[0] = radio*cos(angulo*i);
		v2[1] = 0;
		v2[2] = radio*sin(angulo*i);

		v3[0] = radio*cos(angulo*(i + 1));
		v3[1] = 0;
		v3[2] = radio*sin(angulo*(i + 1));

		v4[0] = radio*cos(angulo*i);
		v4[1] = altura;
		v4[2] = radio*sin(angulo*i);

		v5[0] = radio*cos(angulo*(i + 1));
		v5[1] = altura;
		v5[2] = radio*sin(angulo*(i + 1));

		glBegin(GL_POLYGON);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0, altura, 0.0);
		glVertex3fv(v4);
		glVertex3fv(v5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, text);
		glBegin(GL_POLYGON);
		glNormal3f(v2[0], 0.0f, v2[2]);
		glTexCoord2f(ctext_s*i, 0.0f);		glVertex3fv(v2);
		glTexCoord2f(ctext_s*(i + 1), 0.0f);	glVertex3fv(v3);
		glTexCoord2f(ctext_s*(i + 1), 1.0f);	glVertex3fv(v5);
		glTexCoord2f(ctext_s*i, 1.0f);		glVertex3fv(v4); //cambiar valor para repetir verticalmente, (linea 531, 532 de figuras.cpp)
		glEnd();
	}

}

void CFiguras::cilindro2(float radio, float altura, int resolucion, GLuint text, GLuint text2)
{

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	float v5[] = { 0.0, 0.0, 0.0 };

	float angulo = 2 * 3.14 / resolucion;

	//float ctext_s = 1/resolucion-1;
	float ctext_s = 3.0 / resolucion; //si colocamos valor mayor se repite textura, (linea 489 de figuras.cpp)
	float ctext_t = 0.0;

	float baseH[] = { 0.0, 0.0 };
	float baseV[] = { 0.0, 0.0 };

	for (int i = 0; i < resolucion; i++)
	{
		baseH[0] = 0.5 + 0.5*cos(angulo*i);
		baseH[1] = 0.5 + 0.5*sin(angulo*i);

		baseV[0] = 0.5 + 0.5*cos(angulo*(i + 1));
		baseV[1] = 0.5 + 0.5*sin(angulo*(i + 1));

		v2[0] = radio * cos(angulo*i);
		v2[1] = 0;
		v2[2] = radio * sin(angulo*i);

		v3[0] = radio * cos(angulo*(i + 1));
		v3[1] = 0;
		v3[2] = radio * sin(angulo*(i + 1));

		v4[0] = radio * cos(angulo*i);
		v4[1] = altura;
		v4[2] = radio * sin(angulo*i);

		v5[0] = radio * cos(angulo*(i + 1));
		v5[1] = altura;
		v5[2] = radio * sin(angulo*(i + 1));

		glBindTexture(GL_TEXTURE_2D, text2);
		glBegin(GL_POLYGON);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, text2);
		glBegin(GL_POLYGON);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.5, 0.5f); glVertex3f(0.0, altura, 0.0);
		glTexCoord2fv(baseH); glVertex3fv(v4);
		glTexCoord2fv(baseV); glVertex3fv(v5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, text);
		glBegin(GL_POLYGON);
		glNormal3f(v2[0], 0.0f, v2[2]);
		glTexCoord2f(ctext_s*i, 0.0f);		glVertex3fv(v2);
		glTexCoord2f(ctext_s*(i + 1), 0.0f);	glVertex3fv(v3);
		glTexCoord2f(ctext_s*(i + 1), 1.0f);	glVertex3fv(v5);
		glTexCoord2f(ctext_s*i, 1.0f);		glVertex3fv(v4); //cambiar valor para repetir verticalmente, (linea 531, 532 de figuras.cpp)
		glEnd();
	}
}

void CFiguras::cono(float altura, float radio, int resolucion, GLuint text)
{
	
	float v1[]={0.0, 0.0, 0.0};
	float v2[]={0.0, 0.0, 0.0};
	float v3[]={0.0, 0.0, 0.0};
	float v4[]={0.0, 0.0, 0.0};

	float angulo=2*3.14/resolucion;
	float ctext_s = 1.0/resolucion;
	
	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	for(int i=0; i <resolucion; i++)
	{
		
		v2[0]=radio*cos(angulo*i);
		v2[1]=0;
		v2[2]=radio*sin(angulo*i);

		v3[0]=radio*cos(angulo*(i+1));
		v3[1]=0;
		v3[2]=radio*sin(angulo*(i+1));
		
		//glBegin(GL_LINE_LOOP);
        glBegin(GL_POLYGON); //Construye Base
			glNormal3f( 0.0f, -1.0f, 0.0f);
			glVertex3f(0.0,0.0,0.0);
			glVertex3fv(v2);
			glVertex3fv(v3);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, text);
		glBegin(GL_TRIANGLES);
			glNormal3f( v2[0], 0.0f, v2[2]);
			glTexCoord2f(ctext_s*i, 0.0f);		glVertex3fv(v2);
			glTexCoord2f(ctext_s*(i+1), 0.0f);	glVertex3fv(v3);
			glTexCoord2f(ctext_s*i, 1.0f);	glVertex3f(0.0,altura,0.0);
		glEnd();
	}
}

void CFiguras::esfera2(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}