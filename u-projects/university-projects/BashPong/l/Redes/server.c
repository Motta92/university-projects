/**
*Author :Tharindra Galahena
*Project:networked pong game using openGL and c
*Date   :29/12/2011
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

int new1, new2, new3, new4, new5, new6, new7, new8, new9, new10, new11, new12, new13, new14, new15, new16, new17, new18, new19, new20;
int f = 0;
int lmark = 0;
int rmark = 0;
int x = 1;
int y = 1;
int lim_sup = 10;
int lim_inf = 2;
int cant_jugadores; 
pthread_mutex_t mutex;
struct sockaddr_in ad, add, ad2, add2;

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


struct Juego futbol;
int height = (768/2)-10;
int width = (1024/2)-10;
int incx;
int incy;
int i = 0;
int th = 0;


void create_sock(int port, int port2){
	int sock, sock2;
	if(!(sock = socket(AF_INET, SOCK_STREAM, 0))){
		printf("ERROR : error creating socket\n");
	}
	if(!(sock2 = socket(AF_INET, SOCK_DGRAM, 0))){
		printf("ERROR : error creating socket\n");
	}
	
	ad.sin_family = AF_INET;
	ad.sin_addr.s_addr = INADDR_ANY;
	ad.sin_port = htons(port);

	ad2.sin_family = AF_INET;
	ad2.sin_addr.s_addr = INADDR_ANY;
	ad2.sin_port = htons(port2);
	
	int tr=1;

	// kill "Address already in use" error message
	if (setsockopt(sock2,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	
		// kill "Address already in use" error message
	if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	bind(sock, (struct sockaddr *)&ad, sizeof(ad));
	listen(sock, cant_jugadores);

	bind(sock2, (struct sockaddr *)&ad2, sizeof(ad2));
	//listen(sock2, cant_jugadores);

	int addrlen;
	printf("\neste es el numero :%d \n", cant_jugadores);
	if(cant_jugadores >= 2)
	{
		addrlen = sizeof(add);
		new1 = accept(sock, (struct sockaddr *)&add, &addrlen);
	
		if(new1) printf("Jugador 1 conectado\n");
		else {
			printf("ERROR : Conexion jugador 1\n");
			exit(0);	
		}
		
		addrlen = sizeof(add);
		new3 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new3) printf("Jugador 2 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 2\n");
			exit(0);	
		}
		
	}
	if(cant_jugadores <= 4 && cant_jugadores > 2)
	{
		addrlen = sizeof(add);
		new5 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new5) printf("Jugador 3 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 3\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new6 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new6) ;
		else {
			printf("ERROR : Conexion jugador 3\n");
			exit(0);	
		}
		addrlen = sizeof(add);
		new7 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new7) printf("Jugador 4 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 4\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new8 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new8) ;
		else {
			printf("ERROR : Conexion jugador 4\n");
			exit(0);	
		}
	}
	if(cant_jugadores <= 6 && cant_jugadores > 4)
	{
		addrlen = sizeof(add);
		new9 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new9) printf("Jugador 5 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 5\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new10 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new10) ;
		else {
			printf("ERROR : Conexion jugador 5\n");
			exit(0);	
		}
		addrlen = sizeof(add);
		new11 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new11) printf("Jugador 6 conectado\n");
		else {
			printf("ERROR : Conexion jugador 6\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new12 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new12) ;
		else {
			printf("ERROR : Conexion jugador 6\n");
			exit(0);	
		}
	}
	if(cant_jugadores <= 8 && cant_jugadores > 6)
	{
		addrlen = sizeof(add);
		new13 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new13) printf("Jugador 7 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 7\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new14 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new14) ;
		else {
			printf("ERROR : Conexion jugador 7\n");
			exit(0);	
		}
		addrlen = sizeof(add);
		new15 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new15) printf("Jugador 8 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 8\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new16 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new16) ;
		else {
			printf("ERROR : Conexion jugador 8\n");
			exit(0);	
		}
	}
	if(cant_jugadores <= 10 && cant_jugadores > 8)
	{
	addrlen = sizeof(add);
	new17 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new17) printf("Jugador 9 conectado\n\n");
	else {
		printf("ERROR : Conexion jugador 9\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
		new18 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new18) ;
		else {
			printf("ERROR : Conexion jugador 9\n");
			exit(0);	
		}
		addrlen = sizeof(add);
		new19 = accept(sock, (struct sockaddr *)&add, &addrlen);
		if(new19) printf("Jugador 10 conectado\n\n");
		else {
			printf("ERROR : Conexion jugador 10\n");
			exit(0);	
		}
		addrlen = sizeof(add2);
		new20 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
		if(new20) ;
		else {
			printf("ERROR : Conexion jugador 10\n");
			exit(0);	
		}
	}

	char *Eq_Derecho = "1";
	char *Eq_Izquierdo = "0";
	char *jugador;
	jugador = malloc(2);
	jugador = "1";
	char *mensaje;
	mensaje = malloc(3);
	strcpy(mensaje, Eq_Derecho);
	strcat(mensaje, jugador);
	
	if(cant_jugadores >= 2)
	{
		if(send(new1, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new1);
			exit(0);	
		}
		
		strcpy(mensaje, Eq_Izquierdo);
		strcat(mensaje, jugador);
		if(send(new3, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new3);
			exit(0);	
		}
	}
	if(cant_jugadores <= 4 && cant_jugadores > 2)
	{
		jugador = "2";
		strcpy(mensaje, Eq_Derecho);
		strcat(mensaje, jugador);

		if(send(new5, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new5);
			exit(0);	
		}
		
		strcpy(mensaje, Eq_Izquierdo);
		strcat(mensaje, jugador);
		if(send(new7, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new7);
			exit(0);	
		}
	}
	if(cant_jugadores <= 6 && cant_jugadores > 4)
	{
		jugador = "3";
		strcpy(mensaje, Eq_Derecho);
		strcat(mensaje, jugador);

		if(send(new9, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new9);
			exit(0);	
		}
		strcpy(mensaje, Eq_Izquierdo);
		strcat(mensaje, jugador);
		if(send(new11, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new11);
			exit(0);	
		}
	}
	if(cant_jugadores <= 8 && cant_jugadores > 6)
	{
		jugador = "4";
		strcpy(mensaje, Eq_Derecho);
		strcat(mensaje, jugador);

		if(send(new13, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new13);
			exit(0);	
		}
		
		strcpy(mensaje, Eq_Izquierdo);
		strcat(mensaje, jugador);
		if(send(new15, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new15);
			exit(0);	
		}
	}
	if(cant_jugadores <= 10 && cant_jugadores > 8)
	{
		jugador = "5";
		strcpy(mensaje, Eq_Derecho);
		strcat(mensaje, jugador);

		if(send(new17, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new17);
			exit(0);	
		}
		
		strcpy(mensaje, Eq_Izquierdo);
		strcat(mensaje, jugador);
		if(send(new19, mensaje, 2, 0) == -1){
			perror("ERROR!\n");
			close(new19);
			exit(0);	
		}
	}

}
void *threadFunc(void *arg){
	while(1){		
		if(th) usleep(500);
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int addrlen;
		addrlen = sizeof(add2);
		int cc = recvfrom(new2, msg, sizeof(temporal), 0,(struct sockaddr *)&add2, &addrlen);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.R1 = temporal;
		//futbol.rh1=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		lx = p -> x;
		free(msg);*/
	}
}
void *threadFunc2(void *arg){
	while(1){	
		if(!th) usleep(500);	
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new6, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.R2 = temporal;
		//futbol.rh2=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		rx = p -> x;
		free(msg);
		* */
	}
}
void *threadFunc3(void *arg){
	while(1){		
		if(th) usleep(500);
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new10, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.R3 = temporal;
		//futbol.rh1=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		lx = p -> x;
		free(msg);*/
	}
}
void *threadFunc4(void *arg){
	while(1){	
		if(!th) usleep(500);	
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new14, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.R4 = temporal;
		//futbol.rh2=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		rx = p -> x;
		free(msg);
		* */
	}
}
void *threadFunc5(void *arg){
	while(1){	
		if(!th) usleep(500);	
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new18, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.R5 = temporal;
		//futbol.rh2=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		rx = p -> x;
		free(msg);
		* */
	}
}
void *threadFuncl(void *arg){
	while(1){		
		if(th) usleep(500);
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int addrlen;
		addrlen = sizeof(add2);
		int cc = recvfrom(new4, msg, sizeof(temporal), 0,(struct sockaddr *)&add2 ,&addrlen);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.L1 = temporal;
		//futbol.rh1=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		lx = p -> x;
		free(msg);*/
	}
}
void *threadFunc2l(void *arg){
	while(1){	
		if(!th) usleep(500);	
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new8, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.L2 = temporal;
		//futbol.rh2=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		rx = p -> x;
		free(msg);
		* */
	}
}
void *threadFunc3l(void *arg){
	while(1){		
		if(th) usleep(500);
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new12, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.L3 = temporal;
		//futbol.rh1=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		lx = p -> x;
		free(msg);*/
	}
}
void *threadFunc4l(void *arg){
	while(1){	
		if(!th) usleep(500);	
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new16, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.L4 = temporal;
		//futbol.rh2=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		rx = p -> x;
		free(msg);
		* */
	}
}
void *threadFunc5l(void *arg){
	while(1){	
		if(!th) usleep(500);	
		struct Jugador temporal;
		char msg[sizeof(temporal)]={0};
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new20, msg, sizeof(temporal), 0);
		memcpy(&temporal, msg, sizeof(temporal));
		futbol.L5 = temporal;
		//futbol.rh2=atoi(msg);
		/*
		struct play *p = (struct play *)msg;
		rx = p -> x;
		free(msg);
		* */
	}
}


void sendd(){
	char msg [sizeof(struct Juego)]={0};
	memcpy(msg, &futbol, sizeof(futbol));
	/*char *buff = (char *)malloc(sizeof(char) * 12);
	struct ball *bb = (struct ball *)buff;
	bb -> x = b -> x;
	bb -> y = b -> y;
	bb -> ra = rx;
	* */
	if(cant_jugadores >= 2)
	{
		if(send(new1, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new1);
			exit(0);	
		}
		//bb -> ra = lx;
		if(send(new3, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new3);
			exit(0);	
		}
	}
	if(cant_jugadores <= 4 && cant_jugadores > 2)
	{
		if(send(new5, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new5);
			exit(0);	
		}
		if(send(new7, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new7);
			exit(0);	
		}
	}
	if(cant_jugadores <= 6 && cant_jugadores > 4)
	{
		if(send(new9, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new9);
			exit(0);	
		}
		if(send(new11, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new11);
			exit(0);	
		}
	}
	if(cant_jugadores <= 8 && cant_jugadores > 6)
	{
		//bb -> ra = lx;
		if(send(new13, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new13);
			exit(0);	
		}
		if(send(new15, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new15);
			exit(0);	
		}
	}
	if(cant_jugadores <= 10 && cant_jugadores > 8)
	{
		if(send(new17, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new17);
			exit(0);	
		}
		if(send(new19, msg, sizeof(futbol), 0) == -1){
			perror("ERROR!\n");
			close(new19);
			exit(0);	
		}
	}
	//free(buff);
	char *fla = (char *)malloc(sizeof(char) * 2);
	if(cant_jugadores >= 2)
	{
		recv(new1, fla, 2, 0);
		recv(new3, fla, 2, 0);
	}
	if(cant_jugadores <= 4 && cant_jugadores > 2)
	{
		recv(new5, fla, 2, 0);
		recv(new7, fla, 2, 0);
	}
	if(cant_jugadores <= 6 && cant_jugadores > 4)
	{
		recv(new9, fla, 2, 0);
		recv(new11, fla, 2, 0);
	}
	if(cant_jugadores <= 8 && cant_jugadores > 4)
	{
		recv(new13, fla, 2, 0);
		recv(new15, fla, 2, 0);
	}
	if(cant_jugadores <= 10 && cant_jugadores > 8)
	{
		recv(new17, fla, 2, 0);
		recv(new19, fla, 2, 0);
	}
	free(fla);
}
void move(){
	printf("x: %d	y: %d\n", futbol.x, futbol.y);
	if(i > 0){
		i--;
		return;	
	}
	if(futbol.y + y*incy < -height || futbol.y + y*incy > height){
		y = -1*y;
		srand(time(NULL));
		incy = (rand() % (lim_sup)) + lim_inf ;
		futbol.y += y*incy;	
	}else futbol.y += y*incy;	
	if(futbol.x + x*incx < -width && futbol.y + y*incy < (height)-190 && futbol.y + y*incy > -(height)+210)
	{
		th = 0;
		usleep(500);
		futbol.M_R++;
		futbol.x = 0;
		futbol.y = 0;
		srand(time(NULL));
		incx = 15 ;
		srand(time(NULL));
		incy = rand() % (2) ;
		if (incy == 1)
		{
			srand(time(NULL));
			incy = -((rand() % (lim_sup)) + lim_inf) ;
		}
		else
		{
			srand(time(NULL));
			incy = (rand() % (lim_sup)) + lim_inf;
		}
		//incx = 15;
		//incy = 20;	
		i = 3;
	}
	else if( futbol.x + x*incx > width && futbol.y + y*incy < (height)-190 && futbol.y + y*incy > -(height)+210)
	{
		th = 1;
		usleep(500);	
		futbol.M_L++;
		futbol.x = 0;
		futbol.y = 0;
		incx = -15 ;
		srand(time(NULL));
		incy = rand() % (2) ;
		if (incy == 1){
			srand(time(NULL));
			incy = -((rand() % (lim_sup))+ lim_inf)  ;
		}
		else
		{
			srand(time(NULL));
			incy = (rand() % (lim_sup))+ lim_inf;
		}
		//incx = -15;
		//incy = 20;	
		i = 3;					
	}
	else if(futbol.x + x*incx < -width || futbol.x + x*incx > width)
	{
		x = -1*x;
		srand(time(NULL));
		incx = (rand() % (lim_sup))+ lim_inf ;
		futbol.x += x*incx;
		
	}
	else futbol.x += x*incx;
	
	if (futbol.x > 0)
	{
		if(((futbol.x + x*incx)-(futbol.x)) > 0)
		{
			if(((futbol.x + x*incx) > ((2*((width)/8))-15))&&((futbol.x + x*incx) < ((2*((width)/8))+15)))
			{
				float pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((2*((width)/8))-15)-futbol.x))+futbol.y;
				if(
				((yfinal <= (((height)/2)+20+futbol.R1.y)) 
				&& (yfinal >= (((height)/2)-20+futbol.R1.y)))
				||
				((yfinal <= (((-height)/2)+20+futbol.R2.y)) 
				&& (yfinal >= (((-height)/2)-20+futbol.R2.y))))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) > ((4*((width)/8))-15))&&((futbol.x + x*incx) < ((4*((width)/8))+15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((4*((width)/8))-15)-futbol.x))+futbol.y;
				if(yfinal <= (((-10)/2)+20+futbol.R3.y) && yfinal >= (((-10)/2)-20+futbol.R3.y))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) > ((6*((width)/8))-15))&&((futbol.x + x*incx) < ((6*((width)/8))+15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((6*((width)/8))-15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.R4.y) && yfinal >= (((height)/2)-20+futbol.R4.y))||(yfinal <= (((-height)/2)+20+futbol.R5.y) && yfinal >= (((-height)/2)-20+futbol.R5.y)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
		}
		else if(((futbol.x + x*incx)-(futbol.x)) < 0)
		{
			if(((futbol.x + x*incx) < ((2*((width)/8))+15))&&((futbol.x + x*incx) > ((2*((width)/8))-15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((2*((width)/8))+15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.R1.y) && yfinal >= (((height)/2)-20+futbol.R1.y))||(yfinal <= (((-height)/2)+20+futbol.R2.y) && yfinal >= (((-height)/2)-20+futbol.R2.y)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) < ((4*((width)/8))+15))&&((futbol.x + x*incx) > ((4*((width)/8))-15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((4*((width)/8))+15)-futbol.x))+futbol.y;
				if(yfinal <= (((-10)/2)+20+futbol.R3.y) && yfinal >= (((-10)/2)-20+futbol.R3.y))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) < ((6*((width)/8))+15))&&((futbol.x + x*incx) > ((6*((width)/8))-15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((6*((width)/8))+15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.R4.y) && yfinal >= (((height)/2)-20+futbol.R4.y))||(yfinal <= (((-height)/2)+20+futbol.R5.y) && yfinal >= (((-height)/2)-20+futbol.R5.y)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
		}
	}
	else 
	{
		if(((futbol.x + x*incx)-(futbol.x)) > 0)
		{
			if(((futbol.x + x*incx) > ((2*((-width-20)/8))-15))&&((futbol.x + x*incx) < ((2*((-width-20)/8))+15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((2*((-width-20)/8))-15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.L1.y) && yfinal >= (((height)/2)-20+futbol.L1.y))||(yfinal <= (((-height)/2)+20+futbol.L2.y) && yfinal >= (((-height)/2)-20+futbol.L2.y)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) > ((4*((-width-20)/8))-15))&&((futbol.x + x*incx) < ((4*((-width-20)/8))+15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((4*((-width-20)/8))-15)-futbol.x))+futbol.y;
				if(yfinal <= (((-10)/2)+20+futbol.L3.y) && yfinal >= (((-10)/2)-20+futbol.L3.y))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) > ((6*((-width-20)/8))-15))&&((futbol.x + x*incx) < ((6*((-width-20)/8))+15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((6*((-width-20)/8))-15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.L4.y) && yfinal >= (((height)/2)-20+futbol.L4.y))||(yfinal <= (((-height)/2)+20+futbol.L5.x) && yfinal >= (((-height)/2)-20+futbol.L5.x)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
		}
		else if(((futbol.x + x*incx)-(futbol.x)) < 0)
		{
			if(((futbol.x + x*incx) < ((2*((-width-20)/8))+15))&&((futbol.x + x*incx) > ((2*((-width-20)/8))-15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((2*((-width-20)/8))+15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.L1.y) && yfinal >= (((height)/2)-20+futbol.L1.y))||(yfinal <= (((-height)/2)+20+futbol.L2.y) && yfinal >= (((-height)/2)-20+futbol.L2.y)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) < ((4*((-width-20)/8))+15))&&((futbol.x + x*incx) > ((4*((-width-20)/8))-15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((4*((-width-20)/8))+15)-futbol.x))+futbol.y;
				if(yfinal <= (((-10)/2)+20+futbol.L3.y) && yfinal >= (((-10)/2)-20+futbol.L3.y))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
			else if(((futbol.x + x*incx) < ((6*((-width-20)/8))+15))&&((futbol.x + x*incx) > ((6*((-width-20)/8))-15)))
			{
				int pendiente = (((futbol.y+y*incy)-futbol.y)/((futbol.x+x*incx)-futbol.x));
				if (!pendiente)
					pendiente = 1;
				int yfinal = (pendiente * (((6*((-width-20)/8))+15)-futbol.x))+futbol.y;
				if((yfinal <= (((height)/2)+20+futbol.L4.y) && yfinal >= (((height)/2)-20+futbol.L4.y))||(yfinal <= (((-height)/2)+20+futbol.L5.y) && yfinal >= (((-height)/2)-20+futbol.L5.y)))
				{
					x = -1*x;
					srand(time(NULL));
					incx = (rand() % (lim_sup))+ lim_inf ;
					futbol.x += x*incx;								
				}
			}
		}
	}
	
	if(futbol.M_L >= 4){
		futbol.x = 540;
		printf("Left side Won!\n\n");
		sendd();
	}else if(futbol.M_R >= 4){
		futbol.x = 550;
		printf("Right side Won!\n\n");
		sendd();
	}
	
}

int main(int argc, char** argv){
	printf("\n\n------------Servidor Crazy Soccer--------------\n\n");
	if(argc < 2){
		printf("\n digitar :\n\n ./futbol numeros_jugadores_par_positiva \n\n");		
		return 1;
	}
	cant_jugadores = atoi(argv[1]);
	if((cant_jugadores%2) != 0)
	{
		printf("\n la cantidad de jugadores es par \n\n");
		return 1;
	}
	if(cant_jugadores== 0)
	{
		printf("\n la cantidad de jugadores es cero \n\n");
		return 1;
	}
	create_sock(9012, 9013);
	
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

	incx = 15 ;
	srand(time(NULL));
	incy = (rand() % (lim_sup))+ lim_inf;
	pthread_t pth, pth2, pth3, pth4, pth5, pthl, pth2l, pth3l, pth4l, pth5l;

	if(cant_jugadores >= 2)
	{
		pthread_create(&pthl, NULL, threadFuncl, "...");
		pthread_create(&pth, NULL, threadFunc, "...");
	}
	if(cant_jugadores <= 4 && cant_jugadores > 2)
	{
		pthread_create(&pth2, NULL, threadFunc2, "...");
		pthread_create(&pth2l, NULL, threadFunc2l, "...");
	}
	if(cant_jugadores <= 6 && cant_jugadores > 4)
	{
		pthread_create(&pth3, NULL, threadFunc3, "...");
		pthread_create(&pth3l, NULL, threadFunc3l, "...");
	}
	if(cant_jugadores <= 8 && cant_jugadores > 6)
	{
		pthread_create(&pth4, NULL, threadFunc4, "...");
		pthread_create(&pth4l, NULL, threadFunc4l, "...");
	}
	if(cant_jugadores <= 10 && cant_jugadores > 8)
	{
		pthread_create(&pth5, NULL, threadFunc5, "...");
		pthread_create(&pth5l, NULL, threadFunc5l, "...");
	}

	
	while(1){
		move();
		sendd();
		usleep(500);
	}
	if(cant_jugadores >= 2)
	{
		close(new1);
		close(new2);
		close(new3);
		close(new4);
	}
	if(cant_jugadores <= 4 && cant_jugadores > 2)
	{
		close(new5);
		close(new6);
		close(new7);
		close(new8);
	}
	if(cant_jugadores <= 6 && cant_jugadores > 4)
	{
		close(new9);
		close(new10);
		close(new11);
		close(new12);
	}
	if(cant_jugadores <= 8 && cant_jugadores > 6)
	{
		close(new13);
		close(new14);
		close(new15);
		close(new16);
	}
	if (cant_jugadores <= 10 && cant_jugadores > 8)
	{
		close(new17);
		close(new18);
		close(new19);
		close(new20);
	}
	return 0;
}
