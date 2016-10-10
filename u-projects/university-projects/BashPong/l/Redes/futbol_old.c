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

struct Juego{
	int x;
	int y;
	int M_L;
	int M_R;
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
};

int width = 1024;
int height = 768;
int jugador;
int equipo;
int sock1, sock2;
int goles_L =0;
int goles_R =0;
struct Juego futbol;
	





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
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.rh1, 0);
		glVertex3f((2*(((width/2)-10)/8))+15,(((height/2)-10)/2)+20+futbol.rh1, 0);
		glVertex3f((2*(((width/2)-10)/8))+15,(((height/2)-10)/2)-20+futbol.rh1, 0);
		glVertex3f((2*(((width/2)-10)/8))-15,(((height/2)-10)/2)-20+futbol.rh1, 0);
		glVertex3f((2*(((width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.rh1, 0);

		glEnd();
		
		///jugador 2d
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.rh2, 0);
		glVertex3f((2*(((width/2)-10)/8))+15,(((-height/2)-10)/2)+20+futbol.rh2, 0);
		glVertex3f((2*(((width/2)-10)/8))+15,(((-height/2)-10)/2)-20+futbol.rh2, 0);
		glVertex3f((2*(((width/2)-10)/8))-15,(((-height/2)-10)/2)-20+futbol.rh2, 0);
		glVertex3f((2*(((width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.rh2, 0);

		glEnd();
		
		///jugador 3d
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((4*(((width/2)-10)/8))-15,(((0)-10)/2)+20+futbol.rh3, 0);
		glVertex3f((4*(((width/2)-10)/8))+15,(((0)-10)/2)+20+futbol.rh3, 0);
		glVertex3f((4*(((width/2)-10)/8))+15,(((0)-10)/2)-20+futbol.rh3, 0);
		glVertex3f((4*(((width/2)-10)/8))-15,(((0)-10)/2)-20+futbol.rh3, 0);
		glVertex3f((4*(((width/2)-10)/8))-15,(((0)-10)/2)+20+futbol.rh3, 0);

		glEnd();
		
		///jugador 4d
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.rh4, 0);
		glVertex3f((6*(((width/2)-10)/8))+15,(((height/2)-10)/2)+20+futbol.rh4, 0);
		glVertex3f((6*(((width/2)-10)/8))+15,(((height/2)-10)/2)-20+futbol.rh4, 0);
		glVertex3f((6*(((width/2)-10)/8))-15,(((height/2)-10)/2)-20+futbol.rh4, 0);
		glVertex3f((6*(((width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.rh4, 0);

		glEnd();
		
		///jugador 5d
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.rh5, 0);
		glVertex3f((6*(((width/2)-10)/8))+15,(((-height/2)-10)/2)+20+futbol.rh5, 0);
		glVertex3f((6*(((width/2)-10)/8))+15,(((-height/2)-10)/2)-20+futbol.rh5, 0);
		glVertex3f((6*(((width/2)-10)/8))-15,(((-height/2)-10)/2)-20+futbol.rh5, 0);
		glVertex3f((6*(((width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.rh5, 0);

		glEnd();
		
	///jugadores izquierda
		///jugador 1i
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((-width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.lh1, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15,(((height/2)-10)/2)+20+futbol.lh1, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15,(((height/2)-10)/2)-20+futbol.lh1, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15,(((height/2)-10)/2)-20+futbol.lh1, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.lh1, 0);

		glEnd();
		
		///jugador 2iz
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((2*(((-width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.lh2, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15,(((-height/2)-10)/2)+20+futbol.lh2, 0);
		glVertex3f((2*(((-width/2)-10)/8))+15,(((-height/2)-10)/2)-20+futbol.lh2, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15,(((-height/2)-10)/2)-20+futbol.lh2, 0);
		glVertex3f((2*(((-width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.lh2, 0);

		glEnd();
		
		///jugador 3i
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((4*(((-width/2)-10)/8))-15,(((0)-10)/2)+20+futbol.lh3, 0);
		glVertex3f((4*(((-width/2)-10)/8))+15,(((0)-10)/2)+20+futbol.lh3, 0);
		glVertex3f((4*(((-width/2)-10)/8))+15,(((0)-10)/2)-20+futbol.lh3, 0);
		glVertex3f((4*(((-width/2)-10)/8))-15,(((0)-10)/2)-20+futbol.lh3, 0);
		glVertex3f((4*(((-width/2)-10)/8))-15,(((0)-10)/2)+20+futbol.lh3, 0);

		glEnd();
		
		///jugador 4i
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((-width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.lh4, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15,(((height/2)-10)/2)+20+futbol.lh4, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15,(((height/2)-10)/2)-20+futbol.lh4, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15,(((height/2)-10)/2)-20+futbol.lh4, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15,(((height/2)-10)/2)+20+futbol.lh4, 0);

		glEnd();
		
		///jugador 5i
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		
		glVertex3f((6*(((-width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.lh5, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15,(((-height/2)-10)/2)+20+futbol.lh5, 0);
		glVertex3f((6*(((-width/2)-10)/8))+15,(((-height/2)-10)/2)-20+futbol.lh5, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15,(((-height/2)-10)/2)-20+futbol.lh5, 0);
		glVertex3f((6*(((-width/2)-10)/8))-15,(((-height/2)-10)/2)+20+futbol.lh5, 0);

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
		sprintf(label," %d - %d ", goles_L, goles_R);
		drawBitmapText(label,-27,(height/2)+100,0);
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
	char msg[sizeof(int)]={0};
	if(equipo)
	{
		if(jugador == 1)
			sprintf(msg, "%d", futbol.rh1);
		else if(jugador == 2)
			sprintf(msg, "%d", futbol.rh2);
		else if(jugador == 3)
			sprintf(msg, "%d", futbol.rh3);
		else if(jugador == 4)
			sprintf(msg, "%d", futbol.rh4);
		else if(jugador == 5)
			sprintf(msg, "%d", futbol.rh5);
	}
	else 
	{
		if(jugador == 1)
			sprintf(msg, "%d", futbol.lh1);
		else if(jugador == 2)
			sprintf(msg, "%d", futbol.lh2);
		else if(jugador == 3)
			sprintf(msg, "%d", futbol.lh3);
		else if(jugador == 4)
			sprintf(msg, "%d", futbol.lh4);
		else if(jugador == 5)
			sprintf(msg, "%d", futbol.lh5);
	}
	//printf("este es rh1: %d",rh1);
	send(sock2, msg, sizeof(int), 0);
}
void keyboard(unsigned char key, int x, int y)
{
	if((char)key == 'w'){
		if (equipo == 0)
		{
			if(jugador == 1)
				futbol.lh1++;
			else if(jugador == 2) 
				futbol.lh2++;
			else if(jugador == 3) 
				futbol.lh3++;
			else if(jugador == 4) 
				futbol.lh4++;
			else if(jugador == 5) 
				futbol.lh5++;
		}
		else if (equipo == 1)
		{
			if(jugador == 1) 
				futbol.rh1++;
			else if(jugador == 2) 
				futbol.rh2++;
			else if(jugador == 3) 
				futbol.rh3++;
			else if(jugador == 4) 
				futbol.rh4++;
			else if(jugador == 5) 
				futbol.rh5++;	
		}
		glutPostRedisplay();
		sendp();	
	}else if((char)key == 's'){
		if (equipo == 0)
		{
			if(jugador == 1)
				futbol.lh1--;
			else if(jugador == 2) 
				futbol.lh2--;
			else if(jugador == 3) 
				futbol.lh3--;
			else if(jugador == 4) 
				futbol.lh4--;
			else if(jugador == 5) 
				futbol.lh5--;
		}
		else if (equipo == 1)
		{
			if(jugador == 1) 
				futbol.rh1--;
			else if(jugador == 2) 
				futbol.rh2--;
			else if(jugador == 3) 
				futbol.rh3--;
			else if(jugador == 4) 
				futbol.rh4--;
			else if(jugador == 5) 
				futbol.rh5--;
		}
		glutPostRedisplay();
		sendp();	
		
	}
	/*
	else if((char)key == 'r'){
		jugador++;
	}
	else if((char)key == 'f'){
		jugador--;
	}*/
}




void timer(int a) {
	printf("edeqweqw");
	char msg[sizeof(struct Juego)]={0};
	//char msg[56];
	char *buff = "a";
	//int cc;
	int cc =recv(sock1, msg, sizeof(futbol), 0);
	printf("edeqweqw");
	memcpy(&futbol, msg, sizeof(futbol));
	/*printf("\n\ndatos reci %s\n\n",msg);
	struct ball *b = (struct ball *)msg;
	x = (int)b -> x;
	y = (int)b -> y;
	cantidad_L = (int)b->M_L;
	cantidad_R = (int)b->M_R;
	lh1 = (int)b->lh1;
	lh2 = (int)b->lh2;
	lh3 = (int)b->lh3;
	lh4 = (int)b->lh4;
	lh5 = (int)b->lh5;
	rh1 = (int)b->rh1;
	rh2 = (int)b->rh2;
	rh3 = (int)b->rh3;
	rh4 = (int)b->rh4;
	rh5 = (int)b->rh5;
	
	/*
	if(equipo)
	{
		if(jugador==1)
		{
			rh1 = (int)b -> s;
		}
		else if(jugador==2)
		{
			rh2 = (int)b -> s;
		}
		else if(jugador==3)
		{
			rh3 = (int)b -> s;
		}
		else if(jugador==4)
		{
			rh4 = (int)b -> s;
		}
		else if(jugador==5)
		{
			rh5 = (int)b -> s;
		}
		
	}
	else
	{
		if(jugador==1)
		{
			lh1 = (int)b -> s;
		}
		else if(jugador==2)
		{
			lh2 = (int)b -> s;
		}
		else if(jugador==3)
		{
			lh3 = (int)b -> s;
		}
		else if(jugador==4)
		{
			lh4 = (int)b -> s;
		}
		else if(jugador==5)
		{
			lh5 = (int)b -> s;
		}
	} 
	* */
	if(equipo){
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
	glutTimerFunc(500, timer, 0);
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


int main(int argc, char **argv) {
	
	if(argc < 2){
		printf("\n usage :\n\n ./game ip \n\n");		
		//return;
	}
	
	//int sock;
	
	printf("\n\n------------Pong--------------\n\n");
	
	sock1 = connect_sock(argv[1], "9012");
	sock2 = connect_sock(argv[1], "9013");
	
	printf("Connected to Server\n");
	
	futbol.x=0;
	futbol.y=0; 
	futbol.M_L=0;
	futbol.M_R=0;
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

	char s[2];
	int cc = recv(sock1, s, 2, 0);
	printf("informacion revibida\n %s", s);
	asignar_equipo(s[0]);
	asignar_jugador(s[1]);
	printf("wewew");

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
	
	//init();
	
	glutTimerFunc(500, timer, 0);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc( keyboard );

	// enter GLUT event processing loop
	glutMainLoop();

	return 1;
}
