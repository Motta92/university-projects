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
pthread_mutex_t mutex;

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
	
	if(!(sock2 = socket(AF_INET, SOCK_STREAM, 0))){
		printf("ERROR : error creating socket\n");
	}
	struct sockaddr_in ad, add, ad2, add2;
	ad.sin_family = AF_INET;
	ad.sin_addr.s_addr = htonl(INADDR_ANY);
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
	listen(sock, 1);

	bind(sock2, (struct sockaddr *)&ad2, sizeof(ad2));
	listen(sock2, 1);

	int addrlen = sizeof(add);
	printf("dasdwqeqeqw\n");
	new1 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new1) printf("Conectador jugador 1 Equipo derecho\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	printf("dasdwqeqeqw\n");
	new2 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new2) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	/*
	addrlen = sizeof(add);
	new3 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new3) printf("Conectador jugador 2 Equipo derecho\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new4 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new4) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	/*
	addrlen = sizeof(add);
	new5 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new5) printf("Conectador jugador 3 Equipo derecho\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new6 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new6) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add);
	new7 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new7) printf("Conectador jugador 4 Equipo derecho\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new8 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new8) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add);
	new9 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new9) printf("Conectador jugador 5 Equipo derecho\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new10 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new10) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	
	addrlen = sizeof(add);
	new11 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new11) printf("Conectador jugador 1 Equipo izquierdo\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new12 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new12) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add);
	new13 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new13) printf("Conectador jugador 2 Equipo izquierdo\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new14 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new14) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add);
	new15 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new15) printf("Conectador jugador 3 Equipo izquierdo\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new16 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new16) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add);
	new17 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new17) printf("Conectador jugador 4 Equipo izquierdo\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new18 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new18) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add);
	new19 = accept(sock, (struct sockaddr *)&add, &addrlen);
	if(new19) printf("Conectador jugador 5 Equipo izquierdo\n");
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	addrlen = sizeof(add2);
	new20 = accept(sock2, (struct sockaddr *)&add2, &addrlen);
	if(new20) ;
	else {
		printf("ERROR : error connecting\n");
		exit(0);	
	}
	
*/
	char *Eq_Derecho = "1";
	char *Eq_Izquierdo = "0";
	char *jugador;
	jugador = malloc(2);
	jugador = "1";
	char *mensaje;
	mensaje = malloc(3);
	strcpy(mensaje, Eq_Derecho);
	strcat(mensaje, jugador);
	printf("desadsar3rewrwe");

	if(send(new1, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new1);
		exit(0);	
	}
	/*
	jugador = "2";
	strcpy(mensaje, Eq_Derecho);
	strcat(mensaje, jugador);
	if(send(new3, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new3);
		exit(0);	
	}/*
	jugador = "3";
	strcpy(mensaje, Eq_Derecho);
	strcat(mensaje, jugador);
	if(send(new5, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new5);
		exit(0);	
	}
	jugador = "4";
	strcpy(mensaje, Eq_Derecho);
	strcat(mensaje, jugador);
	if(send(new7, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new7);
		exit(0);	
	}
	jugador = "5";
	strcpy(mensaje, Eq_Derecho);
	strcat(mensaje, jugador);
	if(send(new9, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new9);
		exit(0);	
	}
	jugador = "1";
	strcpy(mensaje, Eq_Izquierdo);
	strcat(mensaje, jugador);
	if(send(new11, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new11);
		exit(0);	
	}
	jugador = "2";
	strcpy(mensaje, Eq_Izquierdo);
	strcat(mensaje, jugador);
	if(send(new13, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new13);
		exit(0);	
	}
	jugador = "3";
	strcpy(mensaje, Eq_Izquierdo);
	strcat(mensaje, jugador);
	if(send(new15, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new15);
		exit(0);	
	}
	jugador = "4";
	strcpy(mensaje, Eq_Izquierdo);
	strcat(mensaje, jugador);
	if(send(new17, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new17);
		exit(0);	
	}
	jugador = "5";
	strcpy(mensaje, Eq_Izquierdo);
	strcat(mensaje, jugador);
	if(send(new19, mensaje, 2, 0) == -1){
		perror("ERROR!\n");
		close(new19);
		exit(0);	
	}
	* */
	printf("dasdasd");

}

void *threadFuncd1(void *arg){
	while(1){
		char msg[sizeof(int)]={0};
		if(!th) usleep(500);
		//char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new2, msg, sizeof(int), 0);
		futbol.rh1=atoi(msg);
		printf("valor rh1: %d", futbol.rh1);
		//= (int)p -> x;
		//printf("este es rh1 : %d", rh1);
		//free(msg);
	}
}
void *threadFuncd2(void *arg){
	while(1){	
		if(!th) usleep(500);	
		char msg[sizeof(int)]={0};
		if(recv(new4, msg, sizeof(int), 0)==-1)
		{
			perror("ERROR!\n");
			close(new2);
		}
		futbol.rh2=atoi(msg);
		printf("valor rh2: %d", futbol.rh2);
	}
}
/*
void *threadFuncd3(void *arg){
	while(1){
		
		if(!th) usleep(500);
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new6, msg, 4, 0);
		struct play *p = (struct play *)msg;
		rh3 = p -> x;
		free(msg);
	}
}
void *threadFuncd4(void *arg){
	while(1){	
		if(!th) usleep(500);	
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new8, msg, 4, 0);
		struct play *p = (struct play *)msg;
		rh4 = p -> x;
		free(msg);
	}
}
void *threadFuncd5(void *arg){
	while(1){	
		if(!th) usleep(500);	
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new10, msg, 4, 0);
		struct play *p = (struct play *)msg;
		rh5 = p -> x;
		free(msg);
	}
}
void *threadFuncl1(void *arg){
	while(1){
		
		if(th) usleep(500);
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new12, msg, 4, 0);
		struct play *p = (struct play *)msg;
		lh1 = p -> x;
		free(msg);
	}
}
void *threadFuncl2(void *arg){
	while(1){	
		if(th) usleep(500);	
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new14, msg, 4, 0);
		struct play *p = (struct play *)msg;
		lh2 = p -> x;
		free(msg);
	}
}
void *threadFuncl3(void *arg){
	while(1){
		
		if(th) usleep(500);
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new16, msg, 4, 0);
		struct play *p = (struct play *)msg;
		lh3 = p -> x;
		free(msg);
	}
}
void *threadFuncl4(void *arg){
	while(1){	
		if(th) usleep(500);	
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new18, msg, 4, 0);
		struct play *p = (struct play *)msg;
		lh4 = p -> x;
		free(msg);
	}
}
void *threadFuncl5(void *arg){
	while(1){	
		if(th) usleep(500);	
		char *msg = (char *)malloc(sizeof(char) * 4);
		int cc = recv(new20, msg, 4, 0);
		struct play *p = (struct play *)msg;
		lh5 = p -> x;
		free(msg);
	}
}
*/
void sendd(){
	char msg [sizeof(struct Juego)]={0};
	memcpy(msg, &futbol, sizeof(futbol));
	/*char *buff = malloc(sizeof(char) * 56);
	struct ball *bb = (struct ball *)buff;
	bb -> x = b -> x;
	bb -> y = b -> y;
	bb -> M_L = b -> M_L;
	bb -> M_R = b -> M_R;
	bb -> lh1 = b -> lh1;
	bb -> lh2 = b -> lh2;
	bb -> lh3 = b -> lh3;
	bb -> lh4 = b -> lh4;
	bb -> lh5 = b -> lh5;
	bb -> rh1 = 0;
	bb -> rh2 = b -> rh2;
	bb -> rh3 = b -> rh3;
	bb -> rh4 = b -> rh4;
	bb -> rh5 = b -> rh5;
	//bb -> ra = rh1;
	//printf("\n x: %d	y: %d", bb->x, bb->y);
	//printf("\n M_L: %d	M_R: %d", bb->M_L, bb->M_R);
	//printf("\n rh1: %d", (int)b->rh1);
	//printf("\ndatos %s\n", buff);
	* */
	if(send(new1, msg, sizeof(futbol), 0) == -1){
		perror("ERROR!\n");
		close(new1);
		exit(0);	
	}/*
	bb -> ra = rh2;*/
	if(send(new3, msg, sizeof(futbol), 0) == -1){
		perror("ERROR!\n");
		close(new3);
		exit(0);	
	}/*
	bb -> ra = rh3;
	if(send(new5, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new5);
		exit(0);	
	}
	bb -> ra = rh4;
	if(send(new7, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new7);
		exit(0);	
	}
	bb -> ra = rh5;
	if(send(new9, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new9);
		exit(0);	
	}
	
	bb -> ra = lh1;
	if(send(new11, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new11);
		exit(0);	
	}
	bb -> ra = lh2;
	if(send(new13, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new13);
		exit(0);	
	}
	bb -> ra = lh3;
	if(send(new15, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new15);
		exit(0);	
	}
	bb -> ra = lh4;
	if(send(new17, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new17);
		exit(0);	
	}
	bb -> ra = lh5;
	if(send(new19, buff, 12, 0) == -1){
		perror("ERROR!\n");
		close(new19);
		exit(0);	
	}
	*/
	//free(buff);
	char *fla = (char *)malloc(sizeof(char) * 2);
	int cc=recv(new1, fla, 2, 0);
	/*
	recv(new3, fla, 2, 0);
	recv(new5, fla, 2, 0);
	recv(new7, fla, 2, 0);
	recv(new9, fla, 2, 0);
	recv(new11, fla, 2, 0);
	recv(new13, fla, 2, 0);
	recv(new15, fla, 2, 0);
	recv(new17, fla, 2, 0);
	recv(new19, fla, 2, 0);*/
	free(fla);
}
void move(){
	if(i > 0){
		i--;
		return;	
	}
	if(futbol.y + futbol.y*incy < -height || futbol.y + futbol.y*incy > height){
		futbol.y = -1*futbol.y;
		srand(time(NULL));
		incy = rand() % (35+1-15)+15 ;
		futbol.y += futbol.y*incy;	
	}else futbol.y += futbol.y*incy;
	if(futbol.x + futbol.x*incx < -width && futbol.y + futbol.y*incy < (height)-190 && futbol.y + futbol.y*incy > -(height)+210){
		th = 0;
		usleep(500);/*
		if(futbol.y >= lh5 - 10 && futbol.y <= lh5 + 10){
			x = -1*x;
			srand(time(NULL));
			incx = rand() % 3 + 1;
			if(incx == incy)
			if(incx == 3) incx = 1;
			else incx++;
			futbol.x += x*incx;
		}else{*/
			futbol.M_R++;
			futbol.x = 0;
			futbol.y = 0;
			srand(time(NULL));
			incx = 15 ;
			srand(time(NULL));
			incy = rand() % (2) ;
			if (incy == 1){
				srand(time(NULL));
				incy = -(rand() % (35+1-15)+15) ;
			}
			else
			{
				srand(time(NULL));
				incy = rand() % (35+1-15)+15 ;
			}
			//incx = 15;
			//incy = 20;	
			i = 3;
		}
	/*
	else if( futbol.x + x*incx > ((6*(((-width/2)-10)/8))+15))
	{
		if(futbol.y >= lh5 - 10 && futbol.y <= lh5 + 10){
			x = -1*x;
			srand(time(NULL));
			incx = rand() % 3 + 1;
			if(incx == incy)
			{
				if(incx == 3) incx = 1;
				else incx++;
			}
			futbol.x += x*incx;
		}
	}	
	else if( futbol.x + x*incx > ((6*(((width/2)-10)/8))-15))
	{
		if(futbol.y >= rh5 - 10 && futbol.y <= rh5 + 10){
			x = -1*x;
			srand(time(NULL));
			incx = rand() % 3 + 1;
			if(incx == incy)
			{
				if(incx == 3) incx = 1;
				else incx++;
			}
			futbol.x += x*incx;
		}
	}
	* */
	else if( futbol.x + futbol.x*incx > width && futbol.y + futbol.y*incy < (height)-190 && futbol.y + futbol.y*incy > -(height)+210){
		th = 1;
		usleep(500);	
		/*if(futbol.y >= rx - 1 && futbol.y <= rx + 7){
			x = -1*x;
			srand(time(NULL));
			incx = rand() % 3 + 1;
			if(incx == incy)
			if(incx == 3) incx = 1;
			else incx++;
			futbol.x += x*incx;		
		}else{*/
			futbol.M_L++;
			futbol.x = 0;
			futbol.y = 0;
			srand(time(NULL));
			incx = -15 ;
			srand(time(NULL));
			incy = rand() % (2) ;
			if (incy == 1){
				srand(time(NULL));
				incy = -(rand() % (35+1-15)+15) ;
			}
			else
			{
				srand(time(NULL));
				incy = rand() % (35+1-15)+15;
			}
			//incx = -15;
			//incy = 20;	
			i = 3;					
		}
	else if(futbol.x + futbol.x*incx < -width || futbol.x + futbol.x*incx > width)
	{
		futbol.x = -1*futbol.x;
		srand(time(NULL));
		incx = rand() % (35) ;
		futbol.x += futbol.x*incx;
		
	}
	else futbol.x += futbol.x*incx;
	
	if(lmark >= 4){
		futbol.x = 540;
		printf("Left side Won!\n\n");
		sendd();
	}else if(rmark >= 4){
		futbol.x = 550;
		printf("Right side Won!\n\n");
		sendd();
	}
//	printf("\n move rh1: %d", (int)b->rh1);
	
}

int main(){
	printf("\n\n------------Pong Game Server--------------\n\n");
	create_sock(9012, 9013);
	
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

	srand(time(NULL));
	incx = 15 ;
	srand(time(NULL));
	incy = rand() % (35+1-15)+15;

	while(1){
		move();
		printf("x: %d, y: %d", futbol.x, futbol.y);
		sendd();
		usleep(500);
	}
	
	pthread_t pthl1, pthl2;//, pthl3, pthl4, pthl5, pthd1, pthd2, pthd3, pthd4, pthd5;

	pthread_create(&pthl1, NULL, threadFuncd1, "...");
	pthread_create(&pthl2, NULL, threadFuncd2, "...");
	/*
	pthread_create(&pthl3, NULL, threadFuncl3, "...");
	pthread_create(&pthl4, NULL, threadFuncl4, "...");
	pthread_create(&pthl5, NULL, threadFuncl5, "...");
	pthread_create(&pthd1, NULL, threadFuncd1, "...");
	pthread_create(&pthd2, NULL, threadFuncd2, "...");
	pthread_create(&pthd3, NULL, threadFuncd3, "...");
	pthread_create(&pthd4, NULL, threadFuncd4, "...");
	pthread_create(&pthd5, NULL, threadFuncd5, "...");
	* */
	close(new1);
	close(new2);
	close(new3);
	close(new4);
	return 0;
}
