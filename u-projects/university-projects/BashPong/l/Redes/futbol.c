#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define M_PIl        3.1415926535897932384626433832795029L  /* pi */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

GLuint num;

struct Jugador{
	int x;
	int y;
};
struct Juego{
	int x;
	int y;
	int M_L;
	int M_R;
	struct Jugador L1;
	struct Jugador L2;
	struct Jugador L3;
	struct Jugador L4;
	struct Jugador L5;
	struct Jugador R1;
	struct Jugador R2;
	struct Jugador R3;
	struct Jugador R4;
	struct Jugador R5;
	/*
	int lh1;
	int lh2;
	int lh3;
	int lh4;
	int lh5;
	int rh1;
	int rh2;
	int rh3;
	int rh4;
	int rh5;	
	* */
};
int width = 1024;
int height = 768;
int jugador;
int equipo;
int sock1, sock2;
struct Juego futbol;
struct sockaddr_in ad2, add2;





void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	//float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	///gluPerspective(45,ratio,1,1000);
	gluOrtho2D(-(width/2)-60,(width/2)+60,-(height/2)-200,(height/2)+200);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) 
	{
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	///cacha
		///pasto
		glColor3f(0.1, 0.5, 0.0);
		glBegin(GL_QUADS);
		
		glVertex3f(-width/2, height/2, 0);
		glVertex3f(width/2, height/2, 0);
		glVertex3f(width/2, -height/2, 0);
		glVertex3f(-width/2, -height/2, 0);

		glEnd();
		///lineas externas
		
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		
		glVertex3f(-(width/2)+10, (height/2)-10, 0);
		glVertex3f((width/2)-10, (height/2)-10, 0);
		glVertex3f((width/2)-10, -(height/2)+10, 0);
		glVertex3f(-(width/2)+10, -(height/2)+10, 0);
		glVertex3f(-(width/2)+10, (height/2)-10, 0);

		glEnd();
		
		///linea medio
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		
		glVertex3f(0, (height/2)-10, 0);
		glVertex3f(0, -(height/2)+10, 0);
		glEnd();
		
		///linea area grande izq
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		
		glVertex3f(-(width/2)+10, (height/2)-70, 0);
		glVertex3f(-(width/2)+175, (height/2)-70, 0);
		glVertex3f(-(width/2)+175, -(height/2)+70, 0);
		glVertex3f(-(width/2)+10, -(height/2)+70, 0);
		//glVertex3f(-(width/2)+10, (height/2)-10, 0);

		glEnd();
		
		///linea area chica izq
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		
		glVertex3f(-(width/2)+10, (height/2)-200, 0);
		glVertex3f(-(width/2)+100, (height/2)-200, 0);
		glVertex3f(-(width/2)+100, -(height/2)+200, 0);
		glVertex3f(-(width/2)+10, -(height/2)+200, 0);
		//glVertex3f(-(width/2)+10, (height/2)-10, 0);

		glEnd();
		
		///linea area grande der
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		
		glVertex3f((width/2)-10, (height/2)-70, 0);
		glVertex3f((width/2)-175, (height/2)-70, 0);
		glVertex3f((width/2)-175, -(height/2)+70, 0);
		glVertex3f((width/2)-10, -(height/2)+70, 0);
		//glVertex3f(-(width/2)+10, (height/2)-10, 0);

		glEnd();
		
		///linea area chica der
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		
		glVertex3f((width/2)-10, (height/2)-200, 0);
		glVertex3f((width/2)-100, (height/2)-200, 0);
		glVertex3f((width/2)-100, -(height/2)+200, 0);
		glVertex3f((width/2)-10, -(height/2)+200, 0);
		//glVertex3f(-(width/2)+10, (height/2)-10, 0);

		glEnd();
		
		///punto penal der
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		
		glVertex3f((width/2)-122, 5, 0);
		glVertex3f((width/2)-130, 5, 0);
		glVertex3f((width/2)-130, -5, 0);
		glVertex3f((width/2)-122, -5, 0);

		glEnd();
		
		
		///punto penal izq
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		
		glVertex3f(-(width/2)+122, 5, 0);
		glVertex3f(-(width/2)+130, 5, 0);
		glVertex3f(-(width/2)+130, -5, 0);
		glVertex3f(-(width/2)+122, -5, 0);

		glEnd();
		
		///punto centro cancha
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		
		glVertex3f(-5, 5, 0);
		glVertex3f(3.5, 5, 0);
		glVertex3f(3.5, -5, 0);
		glVertex3f(-5, -5, 0);

		glEnd();
		
		///ciruculo centro
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		double f;
		for(f = 0.0; f <= 2 * M_PIl; f += 0.1)
		{
			double y = 100 * sin(f);
			double x = 100 * cos(f);
			glVertex3f(x, y, 0);
			//glVertex2f(x,y);
		}
		glVertex3f(100, 0, 0);
		glEnd();
		
	///jugadores derecha
		
		///jugador 1d
		if(equipo == 1 && jugador == 1)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 0);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((width/2)-10)/8))-15+futbol.R1.x,(((height/2)-10)/2)+20+futbol.R1.y, 0);
		glVertex3f((2*(((width/2)-10)/8))+15+futbol.R1.x,(((height/2)-10)/2)+20+futbol.R1.y, 0);
		glVertex3f((2*(((width/2)-10)/8))+15+futbol.R1.x,(((height/2)-10)/2)-20+futbol.R1.y, 0);
		glVertex3f((2*(((width/2)-10)/8))-15+futbol.R1.x,(((height/2)-10)/2)-20+futbol.R1.y, 0);
		glVertex3f((2*(((width/2)-10)/8))-15+futbol.R1.x,(((height/2)-10)/2)+20+futbol.R1.y, 0);

		glEnd();
		
		///jugador 2d
		if(equipo == 1 && jugador == 2)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 0);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((width/2)-10)/8))-15+futbol.R2.x,(((-height/2)-10)/2)+20+futbol.R2.y, 0);
		glVertex3f((2*(((width/2)-10)/8))+15+futbol.R2.x,(((-height/2)-10)/2)+20+futbol.R2.y, 0);
		glVertex3f((2*(((width/2)-10)/8))+15+futbol.R2.x,(((-height/2)-10)/2)-20+futbol.R2.y, 0);
		glVertex3f((2*(((width/2)-10)/8))-15+futbol.R2.x,(((-height/2)-10)/2)-20+futbol.R2.y, 0);
		glVertex3f((2*(((width/2)-10)/8))-15+futbol.R2.x,(((-height/2)-10)/2)+20+futbol.R2.y, 0);

		glEnd();
		
		///jugador 3d
		if(equipo == 1 && jugador == 3)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 0);
		glBegin(GL_QUADS);

		
		glVertex3f((4*(((width/2)-10)/8))-15+futbol.R3.x,(((0)-10)/2)+20+futbol.R3.y, 0);
		glVertex3f((4*(((width/2)-10)/8))+15+futbol.R3.x,(((0)-10)/2)+20+futbol.R3.y, 0);
		glVertex3f((4*(((width/2)-10)/8))+15+futbol.R3.x,(((0)-10)/2)-20+futbol.R3.y, 0);
		glVertex3f((4*(((width/2)-10)/8))-15+futbol.R3.x,(((0)-10)/2)-20+futbol.R3.y, 0);
		glVertex3f((4*(((width/2)-10)/8))-15+futbol.R3.x,(((0)-10)/2)+20+futbol.R3.y, 0);

		glEnd();
		
		///jugador 4d
		if(equipo == 1 && jugador == 4)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 0);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((width/2)-10)/8))-15+futbol.R4.y,(((height/2)-10)/2)+20+futbol.R4.y, 0);
		glVertex3f((6*(((width/2)-10)/8))+15+futbol.R4.y,(((height/2)-10)/2)+20+futbol.R4.y, 0);
		glVertex3f((6*(((width/2)-10)/8))+15+futbol.R4.y,(((height/2)-10)/2)-20+futbol.R4.y, 0);
		glVertex3f((6*(((width/2)-10)/8))-15+futbol.R4.y,(((height/2)-10)/2)-20+futbol.R4.y, 0);
		glVertex3f((6*(((width/2)-10)/8))-15+futbol.R4.y,(((height/2)-10)/2)+20+futbol.R4.y, 0);

		glEnd();
		
		///jugador 5d
		if(equipo == 1 && jugador == 5)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 0);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((width/2)-10)/8))-15+futbol.R5.x,(((-height/2)-10)/2)+20+futbol.R5.y, 0);
		glVertex3f((6*(((width/2)-10)/8))+15+futbol.R5.x,(((-height/2)-10)/2)+20+futbol.R5.y, 0);
		glVertex3f((6*(((width/2)-10)/8))+15+futbol.R5.x,(((-height/2)-10)/2)-20+futbol.R5.y, 0);
		glVertex3f((6*(((width/2)-10)/8))-15+futbol.R5.x,(((-height/2)-10)/2)-20+futbol.R5.y, 0);
		glVertex3f((6*(((width/2)-10)/8))-15+futbol.R5.x,(((-height/2)-10)/2)+20+futbol.R5.y, 0);

		glEnd();
		
	///jugadores izquierda
		///jugador 1i
		if(equipo == 0 && jugador == 1)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((-width/2)-10)/8))-15+futbol.L1.x,(((height/2)-10)/2)+20+futbol.L1.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15+futbol.L1.x,(((height/2)-10)/2)+20+futbol.L1.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15+futbol.L1.x,(((height/2)-10)/2)-20+futbol.L1.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15+futbol.L1.x,(((height/2)-10)/2)-20+futbol.L1.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15+futbol.L1.x,(((height/2)-10)/2)+20+futbol.L1.y, 0);

		glEnd();
		
		///jugador 2iz
		if(equipo == 0 && jugador == 2)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((-width/2)-10)/8))-15+futbol.L2.x,(((-height/2)-10)/2)+20+futbol.L2.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15+futbol.L2.x,(((-height/2)-10)/2)+20+futbol.L2.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15+futbol.L2.x,(((-height/2)-10)/2)-20+futbol.L2.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15+futbol.L2.x,(((-height/2)-10)/2)-20+futbol.L2.y, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15+futbol.L2.x,(((-height/2)-10)/2)+20+futbol.L2.y, 0);

		glEnd();
		
		///jugador 3i
		if(equipo == 0 && jugador == 3)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((4*(((-width/2)-10)/8))-15+futbol.L3.x,(((0)-10)/2)+20+futbol.L3.y, 0);
		glVertex3f((4*(((-width/2)-10)/8))+15+futbol.L3.x,(((0)-10)/2)+20+futbol.L3.y, 0);
		glVertex3f((4*(((-width/2)-10)/8))+15+futbol.L3.x,(((0)-10)/2)-20+futbol.L3.y, 0);
		glVertex3f((4*(((-width/2)-10)/8))-15+futbol.L3.x,(((0)-10)/2)-20+futbol.L3.y, 0);
		glVertex3f((4*(((-width/2)-10)/8))-15+futbol.L3.x,(((0)-10)/2)+20+futbol.L3.y, 0);

		glEnd();
		
		///jugador 4i
		if(equipo == 0 && jugador == 4)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((-width/2)-10)/8))-15+futbol.R4.x,(((height/2)-10)/2)+20+futbol.R4.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15+futbol.R4.x,(((height/2)-10)/2)+20+futbol.R4.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15+futbol.R4.x,(((height/2)-10)/2)-20+futbol.R4.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15+futbol.R4.x,(((height/2)-10)/2)-20+futbol.R4.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15+futbol.R4.x,(((height/2)-10)/2)+20+futbol.R4.y, 0);

		glEnd();
		
		///jugador 5i
		if(equipo == 0 && jugador == 5)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((-width/2)-10)/8))-15+futbol.L5.x,(((-height/2)-10)/2)+20+futbol.L5.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15+futbol.L5.x,(((-height/2)-10)/2)+20+futbol.L5.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15+futbol.L5.x,(((-height/2)-10)/2)-20+futbol.L5.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15+futbol.L5.x,(((-height/2)-10)/2)-20+futbol.L5.y, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15+futbol.L5.x,(((-height/2)-10)/2)+20+futbol.L5.y, 0);

		glEnd();
		/*
		float xx = -(width/2)+10 + (((width-20)/16)*x);
		float yy = (height/2)-10 - (((height-20)/4)*y); 
		
		glVertex3f(-(width/2)+10, (height/2)-10, 0);
		glVertex3f((width/2)-10, (height/2)-10, 0);
		glVertex3f((width/2)-10, -(height/2)+10, 0);
		glVertex3f(-(width/2)+10, -(height/2)+10, 0);
		glVertex3f(-(width/2)+10, (height/2)-10, 0);
		* */
	/// balon
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		
		glVertex3f(futbol.x, futbol.y, 0);
		glVertex3f(futbol.x+8.5, futbol.y, 0);
		glVertex3f(futbol.x+8.5, futbol.y-10, 0);
		glVertex3f(futbol.x, futbol.y-10, 0);

		glEnd();
		
		char label[20];
		
		glColor3f(1, 1, 1);
		sprintf(label," %d - %d ", futbol.M_L, futbol.M_R);
		drawBitmapText(label,-27,(height/2)+100,0);
		glutSwapBuffers(); 
		
		glColor3f(1, 1, 1);
		sprintf(label,"Crazy Soccer");
		drawBitmapText(label,-27,-(height/2)-100,0);
		glutSwapBuffers();
		//cube(xx, xx + 0.05, yy, yy + 0.05, 0.0);
	

/*
	glBegin(GL_TRIANGLES);
		glVertex3f(-2,-2,-5.0);
		glVertex3f(2,0.0,-5.0);
		glVertex3f(0.0,2,-5.0);
	glEnd();
*/
	glutSwapBuffers();
}

void sendp(){
	char msg[sizeof(struct Jugador)]={0};
	struct Jugador temporal;
	if(equipo)
	{
		if(jugador == 1)
		{
			temporal = futbol.R1;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.rh1);
		}
		else if(jugador == 2)
		{
			temporal = futbol.R2;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.rh2);
		}
		else if(jugador == 3)
		{
			temporal = futbol.R3;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.rh3);
		}
		else if(jugador == 4)
		{
			temporal = futbol.R4;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.rh4);
		}
		else if(jugador == 5)
		{
			temporal = futbol.R5;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.rh5);
		}
	}
	else 
	{
		if(jugador == 1)
		{
			temporal = futbol.L1;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.lh1);
		}
		else if(jugador == 2)
		{
			temporal = futbol.L2;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.lh2);
		}
		else if(jugador == 3)
		{
			temporal = futbol.L3;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.lh3);
		}
		else if(jugador == 4)
		{
			temporal = futbol.L4;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.lh4);
		}
		else if(jugador == 5)
		{
			temporal = futbol.L5;
			memcpy(msg, &temporal, sizeof(temporal));
			//sprintf(msg, "%d", futbol.lh5);
		}
	}/*
	//char msg[4];
	
	struct play *p = (struct play *)msg;
	if(f)p -> x = lx;
	else p -> x = rx; */
	int addrlen;
	addrlen = sizeof(add2);
	sendto(sock2, msg, sizeof(temporal), 0, (struct sockaddr *)&add2 ,addrlen);
	//send(sock2, msg, sizeof(temporal), 0);
}
/*
void init()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);

}
void Reshape(int w, int h)
{
    	glViewport(0, 0, w, h);
    	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(45.0, (double)w/(double)h, 0.1, 200.0);
	
}*/
void keyboard(unsigned char key, int x, int y)
{
	if((char)key == 'w'){
		if (equipo == 0)
		{
			if(jugador == 1)
				futbol.L1.y += 3;
			else if(jugador == 2) 
				futbol.L2.y+= 3;
			else if(jugador == 3) 
				futbol.L3.y+= 3;
			else if(jugador == 4) 
				futbol.L4.y+= 3;
			else if(jugador == 5) 
				futbol.L5.y+= 3;
		}
		else if (equipo == 1)
		{
			if(jugador == 1) 
				futbol.R1.y+= 3;
			else if(jugador == 2) 
				futbol.R2.y+= 3;
			else if(jugador == 3) 
				futbol.R3.y+= 3;
			else if(jugador == 4) 
				futbol.R4.y+= 3;
			else if(jugador == 5) 
				futbol.R5.y+= 3;	
		}
		glutPostRedisplay();
		sendp();	
	}else if((char)key == 's'){
		if (equipo == 0)
		{
			if(jugador == 1)
				futbol.L1.y-= 3;
			else if(jugador == 2) 
				futbol.L2.y-= 3;
			else if(jugador == 3) 
				futbol.L3.y-= 3;
			else if(jugador == 4) 
				futbol.L4.y-= 3;
			else if(jugador == 5) 
				futbol.L5.y-= 3;
		}
		else if (equipo == 1)
		{
			if(jugador == 1) 
				futbol.R1.y-= 3;
			else if(jugador == 2) 
				futbol.R2.y-= 3;
			else if(jugador == 3) 
				futbol.R3.y-= 3;
			else if(jugador == 4) 
				futbol.R4.y-= 3;
			else if(jugador == 5) 
				futbol.R5.y-= 3;
		}
		glutPostRedisplay();
		sendp();	
		
	}/*else if((char)key == 'a'){
		if (equipo == 0)
		{
			if(jugador == 1)
				futbol.L1.x-= 3;
			else if(jugador == 2) 
				futbol.L2.x-= 3;
			else if(jugador == 3) 
				futbol.L3.x-= 3;
			else if(jugador == 4) 
				futbol.L4.x-= 3;
			else if(jugador == 5) 
				futbol.L5.x-= 3;
		}
		else if (equipo == 1)
		{
			if(jugador == 1) 
				futbol.R1.x-= 3;
			else if(jugador == 2) 
				futbol.R2.x-= 3;
			else if(jugador == 3) 
				futbol.R3.x-= 3;
			else if(jugador == 4) 
				futbol.R4.x-= 3;
			else if(jugador == 5) 
				futbol.R5.x-= 3;
		}
		glutPostRedisplay();
		sendp();	
		
	}else if((char)key == 'd'){
		if (equipo == 0)
		{
			if(jugador == 1)
				futbol.L1.x+= 3;
			else if(jugador == 2) 
				futbol.L2.x+= 3;
			else if(jugador == 3) 
				futbol.L3.x+= 3;
			else if(jugador == 4) 
				futbol.L4.x+= 3;
			else if(jugador == 5) 
				futbol.L5.x+= 3;
		}
		else if (equipo == 1)
		{
			if(jugador == 1) 
				futbol.R1.x+= 3;
			else if(jugador == 2) 
				futbol.R2.x+= 3;
			else if(jugador == 3) 
				futbol.R3.x+= 3;
			else if(jugador == 4) 
				futbol.R4.x+= 3;
			else if(jugador == 5) 
				futbol.R5.x+= 3;	
		}
		glutPostRedisplay();
		sendp();	
	}*/
}

void timer(int a) {
	printf("x: %d	y: %d\n", futbol.x, futbol.y);
	struct Juego temporal;
	char msg[sizeof(struct Juego)]={0};
	//char msg[12];
	char *buff = "a";
	int cc;
	if((cc = recv(sock1, msg, sizeof(futbol), 0)) == -1){
		perror("ERROR");
		close(sock1);
		exit(0);
	}
	memcpy(&temporal, msg, sizeof(futbol));
	if (equipo == 0)
	{
		if(jugador == 1)
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			//futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			//futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 2) 
			{
				futbol.x=temporal.x;
				futbol.y=temporal.y; 
				futbol.M_L=temporal.M_L;
				futbol.M_R=temporal.M_R;
				futbol.L1=temporal.L1;
				//futbol.L2=temporal.L2;
				futbol.L3=temporal.L3;
				futbol.L4=temporal.L4;
				futbol.L5=temporal.L5;
				futbol.R1=temporal.R1;
				futbol.R2=temporal.R2;
				futbol.R3=temporal.R3;
				futbol.R4=temporal.R4;
				futbol.R5=temporal.R5;
				/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			//futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 3) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			//futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
				/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			//futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 4) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			//futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			//futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 5) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			//futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			//futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
	}
	else if (equipo == 1)
	{
		if(jugador == 1) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			//futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			//futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 2) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			//futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			//futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 3) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			//futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			//futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 4) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			//futbol.R4=temporal.R4;
			futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			//futbol.rh4=temporal.rh4;
			futbol.rh5=temporal.rh5;
			* */
		}
		else if(jugador == 5) 
		{
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.L1=temporal.L1;
			futbol.L2=temporal.L2;
			futbol.L3=temporal.L3;
			futbol.L4=temporal.L4;
			futbol.L5=temporal.L5;
			futbol.R1=temporal.R1;
			futbol.R2=temporal.R2;
			futbol.R3=temporal.R3;
			futbol.R4=temporal.R4;
			//futbol.R5=temporal.R5;
			/*
			futbol.x=temporal.x;
			futbol.y=temporal.y; 
			futbol.M_L=temporal.M_L;
			futbol.M_R=temporal.M_R;
			futbol.lh1=temporal.lh1;
			futbol.lh2=temporal.lh2;
			futbol.lh3=temporal.lh3;
			futbol.lh4=temporal.lh4;
			futbol.lh5=temporal.lh5;
			futbol.rh1=temporal.rh1;
			futbol.rh2=temporal.rh2;
			futbol.rh3=temporal.rh3;
			futbol.rh4=temporal.rh4;
			//futbol.rh5=temporal.rh5;
			* */
		}
	}
	/*
	struct ball *b = (struct ball *)msg;
	x = (int)b -> x;
	y = (int)b -> y;
	if(f) rx = (int)b -> s;
	else  lx = (int)b -> s;
	* */
	if(equipo)
	{
		if(futbol.x == 540){
			printf("\n\nYou Win!\n\n");
			close(sock1);
			close(sock2);
			exit(0);	
		}
		if(futbol.x == 550){
			printf("\n\nYou Lost!\n\n");
			close(sock1);
			close(sock2);
			exit(0);	
		}
	}else{
		if(futbol.x == 550){
			printf("\n\nYou Win!\n\n");
			close(sock1);
			close(sock2);
			exit(0);	
		}
		if(futbol.x == 540){
			printf("\n\nYou Lost!\n\n");
			close(sock1);
			close(sock2);
			exit(0);	
		}
	}
	glutPostRedisplay();		
	send(sock1, buff, 2, 0);
	glutTimerFunc(50, timer, 0);
}

int connect_sock(char *ip, char *port){
	struct addrinfo hints, *res;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, port, &hints, &res);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(sock, res -> ai_addr, res -> ai_addrlen) == -1){
		printf("error\n");
		exit(0);	
	}
	return sock;
}
void asignar_equipo(char c){
	if(c == '1'){
		printf("\nIzquierda; ");
		equipo = 1;	
	}else{
		printf("\nDerecha; ");
		equipo = 0;	
	}
}
void asignar_jugador(char c){
	if(c == '1')
	{
		jugador = 1;	
	}
	else
	{
		if(c == '2')
		{
			jugador = 2;	
		}
		else
		{
			if(c == '3')
			{
				jugador = 3;	
			}
			else
			{
				if(c == '4')
				{
					jugador = 4;	
				}
				else
				{
					if(c == '5')
					{
						jugador = 5;	
					}
				}
			}
		}
	}
	printf("Jugador %d\n\n", jugador);
}
int main(int argc, char** argv)
{
	
	if(argc < 2){
		printf("\n Digite :\n\n ./futbol ip \n\n");		
		return 1;
	}
	//int sock;

	printf("\n\n------------Crazy Soccer--------------\n\n");

	sock1 = connect_sock(argv[1], "9012");
	
	/**/
	
	/**/
	//sock2 = connect_sock(argv[1], "9013");
	sock2 = socket(AF_INET, SOCK_DGRAM, 0);
	ad2.sin_family = AF_INET;
	ad2.sin_addr.s_addr = INADDR_ANY;
	ad2.sin_port = htons(9013);
	bind(sock2, (struct sockaddr *)&ad2, sizeof(ad2));
	

	printf("Conectado al Servidor\n");
	
	struct Jugador Personaje;
	Personaje.x = 0;
	Personaje.y = 0;
	
	futbol.x=0;
	futbol.y=0; 
	futbol.M_L=0;
	futbol.M_R=0;
	futbol.L1 = Personaje;
	futbol.L2 = Personaje;
	futbol.L3 = Personaje;
	futbol.L4 = Personaje;
	futbol.L5 = Personaje;
	futbol.R1 = Personaje;
	futbol.R2 = Personaje;
	futbol.R3 = Personaje;
	futbol.R4 = Personaje;
	futbol.R5 = Personaje;
	/*
	futbol.lh1=0;
	futbol.lh2=0;
	futbol.lh3=0;
	futbol.lh4=0;
	futbol.lh5=0;
	futbol.rh1=0;
	futbol.rh2=0;
	futbol.rh3=0;
	futbol.rh4=0;
	futbol.rh5=0;
	* */

	char s[2];
	if(recv(sock1, s, 2, 0) == -1){
		perror("ERROR");
		close(sock1);
		exit(0);
	}
	asignar_equipo(s[0]);
	asignar_jugador(s[1]);
	
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Crazy Soccer");
	//init();
	glutTimerFunc(50, timer, 0);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(renderScene);
	
	glutMainLoop();
	
	return 0;
}
