#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include "mapa.h"
#include "personagem.h"
int WINDOW_WIDTH	= 800;
int WINDOW_HEIGHT	= 600;

void Init(void);
void motion(int x, int y);
void Display(void);




GLint direita =0,esquerda=0;
GLint acima =0,abaixo=0;
GLint rotX=0,rotY=0,rotZ=0;
GLfloat xx=0,yy=0,zz=0;//movimentação teste
GLfloat rr = 0; //rotação teste
GLdouble xmouse=0,ymouse=0,zmouse=0;
GLdouble  xfim =0,zfim=0,yfim=0;
GLint anima = 0;
GLfloat fAspect;
GLfloat angle=0;
GLint anguloZoom = 45;
GLint criaFruta = 0;
float q=0,a=0,w=0,s=0,e=0,d=0;
float r=0,f=0,t=0,g=0,h=0,u=0;
float i=0,j=0,o=0,k=0,p=0;
float l=0,m=0,n=0,b=0,v=0;
int kk=0;
int buscaFruta = 0;
int atual = 0;// fruta atual a ser buscada
int escolha = 1;
int finaliza = 0;
int numFrutas = 0;

Personagem pp;
Arvore *arvore;
Fruta *fruta;
GLUquadric* qobj;

//===========TEXTURA==================//

typedef struct BMPImagem {
	int width;
	int height;
	char *data;
} BMPImage;
GLuint texture_id[10];
int contTextura = 0;
BMPImage textura[10];

void getBitmapImageData(char *pFileName, BMPImage *pImage) {
	FILE *pFile = NULL;
	unsigned short nNumPlanes;
	unsigned short nNumBPP;
	int i;

	if ((pFile = fopen(pFileName, "rb")) == NULL)
		printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

	// Seek forward to width and height info
	fseek(pFile, 18, SEEK_CUR);

	if ((i = fread(&pImage->width, 4, 1, pFile)) != 1)
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ",
				pFileName);

	if ((i = fread(&pImage->height, 4, 1, pFile)) != 1)
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ",
				pFileName);

	if ((fread(&nNumPlanes, 2, 1, pFile)) != 1)
		printf(
				"ERROR: getBitmapImageData - Couldn't read plane count from %s.\n",
				pFileName);

	if (nNumPlanes != 1)
		printf("ERROR: getBitmapImageData - Plane count from %s.\n ",
				pFileName);

	if ((i = fread(&nNumBPP, 2, 1, pFile)) != 1)
		printf("ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ",
				pFileName);

	if (nNumBPP != 24)
		printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

	// Seek forward to image data
	fseek(pFile, 24, SEEK_CUR);

	// Calculate the image's total size in bytes. Note how we multiply the
	// result of (width * height) by 3. This is becuase a 24 bit color BMP
	// file will give you 3 bytes per pixel.
	int nTotalImagesize = (pImage->width * pImage->height) * 3;

	pImage->data = (char*) malloc(nTotalImagesize);

	if ((i = fread(pImage->data, nTotalImagesize, 1, pFile)) != 1)
		printf(
				"ERROR: getBitmapImageData - Couldn't read image data from %s.\n ",
				pFileName);

	//
	// Finally, rearrange BGR to RGB
	//

	char charTemp;
	for (i = 0; i < nTotalImagesize; i += 3) {
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i + 2];
		pImage->data[i + 2] = charTemp;
	}
}

void CarregaTextura(char* Filename) {
	getBitmapImageData(Filename, &textura[contTextura]);
	contTextura++;
}

void aplicaTextura(int id){
    glPushMatrix();
        //glGenTextures(id, &texture_id[id]);
        glBindTexture(GL_TEXTURE_2D, texture_id[id]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura[id].width, textura[id].height, 0,GL_RGB, GL_UNSIGNED_BYTE, textura[id].data);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
    glPopMatrix();
}

void aplicaTexturaMod(int id){
    glPushMatrix();
        //glGenTextures(id, &texture_id[id]);
        glBindTexture(GL_TEXTURE_2D, texture_id[id]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura[id].width, textura[id].height, 0,GL_RGB, GL_UNSIGNED_BYTE, textura[id].data);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

       glEnable(GL_TEXTURE_GEN_S);
       glEnable(GL_TEXTURE_GEN_T);
    glPopMatrix();
}

void iniciaTextura()
{
    CarregaTextura("C:\\Users\\Wellington Azevedo\\Desktop\\Trabalho Final CG\\TFCGdesk\\braco1.bmp");
    CarregaTextura("C:\\Users\\Wellington Azevedo\\Desktop\\Trabalho Final CG\\TFCGdesk\\camisa.bmp");
    CarregaTextura("C:\\Users\\Wellington Azevedo\\Desktop\\Trabalho Final CG\\TFCGdesk\\rosto.bmp");
    CarregaTextura("C:\\Users\\Wellington Azevedo\\Desktop\\Trabalho Final CG\\TFCGdesk\\ceu.bmp");
    CarregaTextura("C:\\Users\\Wellington Azevedo\\Desktop\\Trabalho Final CG\\TFCGdesk\\tronco.bmp");

}

//====================================//

// ARVORE =========================//
Arvore iniciaArvore(float x, float z) {

	Arvore a;

	a.local[0] = x;
	a.local[1] = 0.0f;
	a.local[2] = z;

	return a;
}

Fruta iniciaFruta(float x, float y, float z) {

	Fruta f;

	f.local[0] = x;
	f.local[1] = y;
	f.local[2] = z;

	return f;
}

void desenhaArvore(Arvore A)
{
    //TRONCO
    glPushMatrix();
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    aplicaTextura(4);
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.25f, 7.0f, 6, 6);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    //FOLHAS
    glPushMatrix();
    glColor3f(0.05f, 0.5f, 0.05f);
    glTranslatef(0.0f, 3.0f, 0.0f);
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glutSolidCone(3.0f, 3.0f, 10, 6);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.6f, 0.1f);
    glTranslatef(0.0f, 5.0f, 0.0f);
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 2.5f, 10, 6);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.9f, 0.1f);
    glTranslatef(0.0f, 6.0f, 0.0f);
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glutSolidCone(1.5f, 2.5f, 10, 6);
    glPopMatrix();
}

void desenhaFruta(Fruta f)
{
    glColor3f(1.0f,0.0f,0.0f);
    glTranslatef(f.local[0],f.local[1],f.local[2]);
    glutSolidSphere(0.3,10,5);
    glColor3f(0.2f,1.0f,0.2f);
    glTranslatef(-0.1,-0.40,-0.90);
    glRotated(-30,1,0,0);
    glBegin(GL_POLYGON);// DESENHA A FOLHA DA FRUTA
        glVertex3f( 0.0925 , 0.1533,1.00);
        glVertex3f( 0.0925 , 0.1867,1.00);
        glVertex3f( 0.1075 , 0.2400,1.00);
        glVertex3f( 0.1300 , 0.3033,1.00);
        glVertex3f( 0.1700 , 0.3633,1.00);
        glVertex3f( 0.2275 , 0.3967,1.00);
        glVertex3f( 0.3000 , 0.4300,1.00);
        glVertex3f( 0.3725 , 0.4433,1.00);
        glVertex3f( 0.4150 , 0.4533,1.00);
        glVertex3f( 0.4600 , 0.4567,1.00);
        glVertex3f( 0.4600 , 0.4467,1.00);
        glVertex3f( 0.4625 , 0.3967,1.00);
        glVertex3f( 0.4550 , 0.3500,1.00);
        glVertex3f( 0.4450 , 0.2967,1.00);
        glVertex3f( 0.4275 , 0.2600,1.00);
        glVertex3f( 0.4000 , 0.2200,1.00);
        glVertex3f( 0.3700 , 0.1967,1.00);
        glVertex3f( 0.3250 , 0.1767,1.00);
        glVertex3f( 0.2850 , 0.1600,1.00);
        glVertex3f( 0.2225 , 0.1533,1.00);
        glVertex3f( 0.1850 , 0.1500,1.00);
        glVertex3f( 0.1500 , 0.1467,1.00);
        glVertex3f( 0.1175 , 0.1467,1.00);
        glVertex3f( 0.0925 , 0.1533,1.00);
    glEnd();
}

int checaCliqueFruta(float xmouse,float ymouse,float zmouse,Arvore *a)
{
    int i;
    for(i=0;i<36;i++)
    {
        if( a[i].local[0] + 2.5 >= xmouse && a[i].local[0] - 2.5 <= xmouse )//verifica posição X da arvore e posição X do clique do mouse.
        {
            //printf("Cheguei no X\n");
            if( a[i].local[2] + 2.5 >= zmouse && a[i].local[2] - 2.5 <= zmouse ) //verifica posição Z da arvore e posição Z do clique do mouse.
            {
                //printf("Cheguei no Z\n");
                if( ymouse >= 3.4 && ymouse <= 7.5) //verifica posição Y da arvore e posição Y do clique do mouse.
                    {
                        //printf("Cheguei no Y\n");
                        return 1;
                    }
            }
        }
    }
    return 0;
}

//==================================//

void resetaVariaveisMain()
{
    r=0;f=0;t=0;g=0;h=0;u=0;
    q=0;a=0;w=0;s=0;e=0;d=0;
    i=0;j=0;o=0;k=0;p=0;
    l=0;m=0;n=0;b=0;v=0;
}

void iniciaAgricultor()
{
    pp = criaPersonagem();
    //m = initWorld();
    arvore = (Arvore *) malloc (NUMARVORES*sizeof(Arvore));
    fruta = (Fruta *) malloc (NUMFRUTAS*sizeof(Fruta));
}

void iniciaIluminacao(void)
{
    //ILIMINAÇÃO DO AMBIENTE
	GLfloat luzAmbiente[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat luzDifusa[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat	posicaoLuz[] = { 100.0, 20.0, 100.0, 0.0};

    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    //ILUMINAÇÃO DO PERSONAGEM
    GLfloat agricultor_luzAmbiente[4] = {0.3, 0.3, 0.3, 1.0};
    GLfloat agricultor_luzDifusa[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat agricultor_posicaoLuz[4] = {pp.posicao[0], pp.posicao[1], pp.posicao[2], 1.0};
    GLfloat agricultor_direcaoLuz[4] = {pp.posicao[0], pp.posicao[1], pp.posicao[2], 1.0};


    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, agricultor_posicaoLuz);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, agricultor_direcaoLuz);
    glLightfv(GL_LIGHT1, GL_AMBIENT, agricultor_luzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, agricultor_luzDifusa);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
}

void desenhaCerca(void){
    int i=0;
    glColor3f(1.0,1.0,1.0);
    for (i= 0;i<=200;i++){ //certa começa (0,0) ate (0,200)
        glPushMatrix();
            if (i > 90 && i < 110){

            }
            else{
                if(i% 2 != 0){
                    glTranslated(0,2,i);
                    glScaled(0.25,2,0.25);
                    glutSolidCube(2);
                }
                else{
                    if(i != 90 && i != 110){
                        glPushMatrix();
                            glTranslated(0,2.7,i);
                            glScaled(0.25,0.25,0.7);
                            glutSolidCube(2);
                        glPopMatrix();

                        glTranslated(0,1.5,i);
                        glScaled(0.25,0.25,0.7);
                        glutSolidCube(2);
                    }
                }
            }
        glPopMatrix();
    }
    for (i= 0;i<=200;i++){ //certa começa (0,0) ate (200,0)
        glPushMatrix();
            if(i% 2 != 0){
                glTranslated(i,2,0);
                glScaled(0.25,2,0.25);
                glutSolidCube(2);
            }
            else{

                glPushMatrix();
                    glTranslated(i,2.7,0);
                    glScaled(0.7,0.25,0.25);
                    glutSolidCube(2);
                glPopMatrix();

                glTranslated(i,1.5,0);
                glScaled(0.7,0.25,0.25);
                glutSolidCube(2);
            }
        glPopMatrix();
    }
     for (i= 0;i<=200;i++){ //certa começa (200,0) ate (200,200)
        glPushMatrix();
            if(i% 2 != 0){
                glTranslated(200,2,i);
                glScaled(0.25,2,0.25);
                glutSolidCube(2);
            }
            else{

                glPushMatrix();
                    glTranslated(200,2.7,i);
                    glScaled(0.25,0.25,0.7);
                    glutSolidCube(2);
                glPopMatrix();

                glTranslated(200,1.5,i);
                glScaled(0.25,0.25,0.7);
                glutSolidCube(2);
            }
        glPopMatrix();
    }
         for (i= 0;i<=200;i++){ //certa começa (0,200) ate (200,200)
        glPushMatrix();
            if(i% 2 != 0){
                glTranslated(i,2,200);
                glScaled(0.25,2,0.25);
                glutSolidCube(2);
            }
            else{

                glPushMatrix();
                    glTranslated(i,2.7,200);
                    glScaled(0.7,0.25,0.25);
                    glutSolidCube(2);
                glPopMatrix();

                glTranslated(i,1.5,200);
                glScaled(0.7,0.25,0.25);
                glutSolidCube(2);
            }
        glPopMatrix();
    }


}

void desenhaChao(void)
{
    GLUquadricObj *obj = gluNewQuadric();
    glColor3f(0.4, 1.0, 0.4);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 200);
        glVertex3f(200, 0, 200);
        glVertex3f(200, 0, 0);
    glEnd();

    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    aplicaTexturaMod(3);

    gluSphere(obj,300,20,20);
    glDisable(GL_TEXTURE_2D);
}

void desenhaHumanoide(Personagem p,float xx,float yy,float zz,float rr,int numFrutas)
{
    glTranslatef(p.posicao[0], p.posicao[1], p.posicao[2]);
    glRotatef(p.angulo, 0.0, 1.0, 0.0);
    glColor3f(0.5, 0.9, 0.5); //VERDE
	glPushMatrix();
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            aplicaTextura(0);
            desenhaRosto(0,0,0);
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_2D);
            aplicaTextura(1);
            desenhapeitoral(0,0,0);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            aplicaTextura(0);
            desenhaBracoEsquerdo(p,rr,xx,yy,zz,numFrutas);//numFrutas
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            aplicaTextura(0);
            desenhaBracoDireito(p,0,0,0,0);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            aplicaTextura(0);
            desenhaPernaEsq(p,0,0,0,0);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glColor3f(1, 1, 1); //VERDE
        glPushMatrix();
        glPopMatrix();
        glColor3f(0.5, 0.9, 0.5); //VERDE
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            aplicaTextura(0);
            desenhaPernaDir(p,0,0,0,0);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
	glPopMatrix();
}

void Display(void)
{
    int i,j=0;
    glClearColor(0.3, 0.3, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(anguloZoom, fAspect, 0.1f, 500.0f);
    glTranslatef(0,-2,0); //Deixa o zoom no meio do personagem
//    glRotated(rotX,1,0,0);
//    glRotated(rotY,0,1,0);
//    glRotated(rotZ,0,0,1); //GIRAR CAMERA
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	cameraPerspectivaHumanoide(pp,rotX,rotY,rotZ);

    glPushMatrix(); //Desenha o Humanoide no clique do mouse andando
        if (anima) {
            if(direita){
                if (pp.posicao[0] < xfim && xfim < 200){
                    resetaAngulo(1);
                    resetaVariaveisMain();
                    resetaTodosAngulosEstaticos();
                    pp = andar(pp);
                    animaHumanoide(1);
                    //printf("ANIMA = 1 posX:%.2f,posZ:%.2f,xmouse:%.2f,zmouse:%.2f\n",p.posicao[0],p.posicao[2],xfim,zfim);
                }
                else{
                    direita = 0;
                    anima = 0;
                    resetaAngulo(0);
                    //printf("ANIMA = 0 posX:%.2f,posZ:%.2f,xmouse:%.2f,zmouse:%.2f\n",p.posicao[0],p.posicao[2],xfim,zfim);
                }
            }
            if(esquerda){
                if (pp.posicao[0] > xfim && xfim > 0){
                    resetaAngulo(1);
                    resetaVariaveisMain();
                    resetaTodosAngulosEstaticos();
                    pp = andar(pp);
                    animaHumanoide(1);
                    //printf("ANIMA = 1 posX:%.2f,posZ:%.2f,xmouse:%.2f,zmouse:%.2f\n",p.posicao[0],p.posicao[2],xfim,zfim);
                }
                else{
                    esquerda = 0;
                    anima = 0;
                    resetaAngulo(0);
                }
            }
        }
        desenhaHumanoide(pp,xx,yy,zz,rr,numFrutas);
	glPopMatrix();

    glPushMatrix();// Desenha Frutas
        for(i=0;i<kk;i++){
            glPushMatrix();
                desenhaFruta(fruta[i]);
            glPopMatrix();
        }
    glPopMatrix();

	if(buscaFruta && atual < kk) //A partir da tecla 'c' o personagem ira realizar a tarefa automaticamente.
    {
        glPushMatrix(); //Desenha o Humanoide AnimandooO
                    if(escolha){
                        if(pp.posicao[0] < fruta[atual].local[0]){ //DESLOCAMENTO EM X
                            direita = 1;
                            escolha =0;
//                            printf("IREI PARA A DIREITA atual:%d\n",atual);
                        }
                        else{
                            escolha = 0;
                            esquerda = 1;
//                            printf("IREI PARA A ESQUERDA atual:%d\n",atual);
                        }
                        if(pp.posicao[2] < fruta[atual].local[2]) { //DESLOCAMENTO EM Z
                            abaixo = 1;
//                            printf("IREI PARA ABAIXO\n");
                        }
                        else{
                            acima = 1;
//                            printf("IREI PARA ACIMA\n");

                        }
                    }

                    float DeltaX = fruta[atual].local[0] - pp.posicao[0];
                    float DeltaZ = fruta[atual].local[2] - pp.posicao[2];
                    pp.angulo = atan2(DeltaX,DeltaZ)/M_PI*180.0f;

                    if(direita && acima ){
                        if (pp.posicao[0]+ 1.5 <= fruta[atual].local[0] || pp.posicao[2] - 1.5 >= fruta[atual].local[2]){
                            resetaAngulo(1);
                            resetaVariaveisMain();
                            resetaTodosAngulosEstaticos();
                            pp = andar(pp);
                            animaHumanoide(1);
                            desenhaHumanoide(pp,xx,yy,zz,rr,numFrutas);
                        }
                        else{
                            atual ++;
                            if(atual == kk)
                                buscaFruta = 0;
                            escolha = 1;
//                            printf("Entrei no else da direita\n");
                            direita = 0;
                            acima = 0;
                            numFrutas++;
                            resetaAngulo(0);
                            animaHumanoide(0);
                        }
                    }

                    if(esquerda && acima){
                        if (pp.posicao[0] - 1.5 >= fruta[atual].local[0] || pp.posicao[2] - 1.5 >= fruta[atual].local[2]){
                            resetaAngulo(1);
                            resetaVariaveisMain();
                            resetaTodosAngulosEstaticos();
                            pp = andar(pp);
                            animaHumanoide(1);
                            desenhaHumanoide(pp,xx,yy,zz,rr,numFrutas);
                        }
                        else{
                            atual++;
                            if(atual == kk)
                                buscaFruta=0;
                            escolha = 1;
                            esquerda = 0;
                            acima = 0;
                            numFrutas++;
                            resetaAngulo(0);
                            animaHumanoide(0);
                        }
                    }
                    if(esquerda && abaixo){
                        if (pp.posicao[0] - 1.5 >= fruta[atual].local[0] || pp.posicao[2] + 1.5 <= fruta[atual].local[2]){
                            resetaAngulo(1);
                            resetaVariaveisMain();
                            resetaTodosAngulosEstaticos();
                            pp = andar(pp);
                            animaHumanoide(1);
                            desenhaHumanoide(pp,xx,yy,zz,rr,numFrutas);
                        }
                        else{
                            atual++;
                            if(atual == kk)
                                buscaFruta=0;
                            escolha = 1;
                            esquerda = 0;
                            abaixo = 0;
                            numFrutas++;
                            resetaAngulo(0);
                            animaHumanoide(0);
                        }
                    }
                    if(direita && abaixo ){
                        if (pp.posicao[0]+ 1.5 <= fruta[atual].local[0] || pp.posicao[2] + 1.5 <= fruta[atual].local[2]){
                            resetaAngulo(1);
                            resetaVariaveisMain();
                            resetaTodosAngulosEstaticos();
                            pp = andar(pp);
                            animaHumanoide(1);
                            desenhaHumanoide(pp,xx,yy,zz,rr,numFrutas);
                        }
                        else{
                            atual ++;
                            if(atual == kk)
                                buscaFruta = 0;
                            escolha = 1;
//                            printf("Entrei no else da direita\n");
                            direita = 0;
                            abaixo = 0;
                            numFrutas++;
                            resetaAngulo(0);
                            animaHumanoide(0);
                        }
                    }
                    fruta[atual-1].local[0] = 500;
                    fruta[atual-1].local[1] = 500;
                    fruta[atual-1].local[2] = 500;
        glPopMatrix();
    }
    if(finaliza)//ENTÃO JA PEGUEI TODAS AS FRUTAS E RETORNAREI ATÉ O CELEIRO/CASA EU AINDA NAO DESENHEI.
    {
        float DeltaX = 0 - pp.posicao[0];
        float DeltaZ = 100 - pp.posicao[2];
        pp.angulo = atan2(DeltaX,DeltaZ)/M_PI*180.0f;
        glPushMatrix();
        if (pp.posicao[0]-1 >= 0)
        {
            resetaAngulo(1);
            resetaVariaveisMain();
            resetaTodosAngulosEstaticos();
            pp = andar(pp);
            animaHumanoide(1);
        }
        glPopMatrix();
    }

    glPushMatrix();
        desenhaChao();
    glPopMatrix();
    glPushMatrix();
        desenhaCerca();
    glPopMatrix();

    glPushMatrix(); //Desenha Arvores
        for(i=30;i<180;i+=10){
            glPushMatrix();
            arvore[j] = iniciaArvore(i,70);
            glTranslatef(arvore[j].local[0], 0.0f, arvore[j].local[2]);
            //printf("ARVORE --> x:%.2f,z:%.2f\n",a[j].local[0],a[j].local[2]);
            desenhaArvore(arvore[j]);
            glPopMatrix();
            j++;
        }
        for(i=80;i<140;i+=10){
            glPushMatrix();
            arvore[j] = iniciaArvore(170,i);
            glTranslatef(arvore[j].local[0], 0.0f, arvore[j].local[2]);
            //printf("ARVORE --> x:%.2f,z:%.2f\n",a[j].local[0],a[j].local[2]);
            desenhaArvore(arvore[j]);
            glPopMatrix();
            j++;

        }
        for(i=30;i<180;i+=10){
            glPushMatrix();
            arvore[j] = iniciaArvore(i,130);
            glTranslatef(arvore[j].local[0], 0.0f, arvore[j].local[2]);
            //printf("ARVORE --> x:%.2f,z:%.2f\n",a[j].local[0],a[j].local[2]);
            desenhaArvore(arvore[j]);
            glPopMatrix();
            j++;
        }
    glPopMatrix();
	glutSwapBuffers();
}

void cursor (int x, int y)
{

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    glEnable(GL_DEPTH_TEST);
    winX = (float) x;
    winY = (float) viewport[3] - (float) y;
    glReadPixels( x, (int) winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &xmouse, &ymouse, &zmouse);

    float DeltaX = xmouse - pp.posicao[0];
    float DeltaZ = zmouse - pp.posicao[2];

    angle = atan2(DeltaX,DeltaZ)/M_PI*180.0f;
}

void Reshape(int w, int h)
{
	if ( h == 0 )
		h = 1;
    glViewport(0, 0, w, h);

	fAspect = (GLfloat)w/(GLfloat)h;
}

void Keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
    //* ROTAÇÃO BRAÇO ESQUERDO //
    case 'q':
        if(q >= -180 && q < 30)
            q += 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'Q':
        if(q > -180 && q <= 30)
            q -= 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'a':
        if(a >= 0 && a < 165)
            a += 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'A':
        if(a > 0 && a <= 165)
            a -= 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'w':
        if (w >= -140 && w < 0)
            w += 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'W':
        if (w <= 0 && w > -140)
            w -= 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 's':
        if (s >= -50 && s < 50)
            s += 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'S':
        if (s > -50 && s <= 50)
            s -= 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'e':
        if(e >= -90 && e < 90)
            e += 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'E':
        if(e > -90 && e <=90)
            e -= 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'd':
        if(d >= -30 && d < 30)
            d += 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    case 'D':
        if(d > -30 && d <= 30)
            d -= 5;
        rotacaoEstaticaBracoEsq(q,a,w,s,e,d);
        break;
    //* FIM ROTAÇÃO BRAÇO ESQUERDO //
    //==============================//
    //* ROTAÇÃO BRAÇO DIREITO //
    case 'r':
        if(r >= -180 && r < 30)
            r += 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'R':
        if(r > -180 && r <= 30)
            r -= 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'f':
        if(f >= -165 && f < 0)
            f += 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'F':
        if(f > -165 && f <= 0)
            f -= 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 't':
        if (t >= -140 && t < 0)
            t += 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'T':
        if (t <= 0 && t > -140)
            t -= 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'g':
        if (g >= -50 && g < 50)
            g += 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'G':
        if (g > -50 && g <= 50)
            g -= 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'h':
        if(h >= -90 && h < 90)
            h += 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'H':
        if(h > -90 && h <=90)
            h -= 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'u':
        if(u >= -30 && u < 30)
            u += 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
    case 'U':
        if(u > -30 && u <= 30)
            u -= 5;
        rotacaoEstaticaBracoDir(r,f,t,g,h,u);
        break;
     //* FIM ROTAÇÃO BRAÇO DIREITO //
     //==============================//
     //* ROTAÇÃO PERNA ESQUERDA //
    case 'i':
        if(i >= -90 && i < 40)
            i += 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'I':
        if(i > -90 && i <= 40)
            i -= 5;
       rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'j':
        if(j >= 0 && j < 90)
            j += 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'J':
        if(j > 0 && j <= 90)
            j -= 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'o':
        if(o >= 0 && o < 110)
            o += 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'O':
        if(o > 0 && o <= 110)
            o -= 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'k':
        if(k >= -30 && k < 30)
            k += 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'K':
        if(k > -30 && k <= 30)
            k -= 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'p':
        if(p >= -30 && p < 30)
            p += 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
    case 'P':
        if(p > -30 && p <= 30)
            p -= 5;
        rotacaoEstaticaPernaEsq(i,j,o,k,p);
        break;
     //* FIM ROTAÇÃO PERNA ESQUERDA //
     //==============================//
      //* ROTAÇÃO PERNA DIREITA //
     case 'l':
        if(l >= -90 && l < 40)
            l += 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'L':
        if(l > -90 && l <= 40)
            l -= 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'm':
        if(m >= -90 && m < 0)
            m += 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'M':
        if(m <= 0 && m > -90)
            m -= 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'n':
        if(n >= 0 && n < 110)
            n += 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'N':
        if(n > 0 && n <= 110)
            n -= 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'b':
        if(b >= -30 && b < 30)
            b += 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'B':
        if(b > -30 && b <= 30)
            b -= 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'v':
        if(v >= -30 && v < 30)
            v += 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
    case 'V':
        if(v > -30 && v <= 30)
            v -= 5;
        rotacaoEstaticaPernaDir(l,m,n,b,v);
        break;
      //* FIM ROTAÇÃO PERNA DIREITA //
     //==============================//
    case 'X':
        rotX += 5;
        break;
    case 'x':
        rotX -= 5;
        break;
    case 'Y':
        rotY += 5;
        break;
    case 'y':
        rotY -= 5;
        break;
    case 'Z':
        rotZ += 5;
        break;
    case 'z':
        rotZ -= 5;
        break;
    case '+':
        /* Zoom-in */
        if (anguloZoom >= 10)
            anguloZoom -= 5;
		break;
    case '-':
        /* Zoom-out */
        if (anguloZoom <= 130)
            anguloZoom += 5;
		break;
    case 27 :
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y) {
//	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
//        xfim = xmouse;
//        zfim = zmouse;
//        yfim = ymouse;
//        pp.angulo = angle;
//        anima = 1;
//        if(pp.posicao[0] < xfim)
//            direita = 1;
//        else
//            esquerda = 1;
//	}
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
        xfim = xmouse;
        zfim = zmouse;
        yfim = ymouse;
	    if(checaCliqueFruta(xmouse,ymouse,zmouse,arvore)){
            if(kk < 100){
                fruta[kk] = iniciaFruta(xmouse,ymouse,zmouse);
                kk++;
                buscaFruta = 1;
            }
	    }
	}
	glutPostRedisplay();
}

void menu(int valor)
{
    switch(valor)
    {
    case 1:
        if(kk>0)
            finaliza = 1;
        break;
    case 2:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void criaMenu(){
    glutCreateMenu(menu);
    glutAddMenuEntry("FINALIZAR TAREFA", 1);
    glutAddMenuEntry("SAIR", 2);
    glutAddMenuEntry("ABAIXO OS COMANDOS SERÃO VIA TECLADO SOMENTE", 3);
    glutAddMenuEntry("ROTAÇÃO BRAÇO ESQUERDO EM X -> TECLA 'q' e 'Q'",4);
    glutAddMenuEntry("ROTAÇÃO BRAÇO ESQUERDO EM Z -> TECLA 'a' e 'A'",5);
    glutAddMenuEntry("ROTAÇÃO ANTEBRAÇO ESQUERDO EM X -> TECLA 'w' e 'W'",6);
    glutAddMenuEntry("ROTAÇÃO PULSO ESQUERDO EM X -> TECLA 's' e 'S'",7);
    glutAddMenuEntry("ROTAÇÃO PULSO ESQUERDO EM Y -> TECLA 'e' e 'E'",8);
    glutAddMenuEntry("ROTAÇÃO PULSO ESQUERDO EM Z -> TECLA 'd' e 'D'",9);
    glutAddMenuEntry("NO BRAÇO DIREITO USE R,F,T,G,H e U RESPECTIVAMENTE",10);
    glutAddMenuEntry("ROTAÇÃO PERNA ESQUERDA EM X -> TECLA 'i' e 'I'",11);
    glutAddMenuEntry("ROTAÇÃO PERNA ESQUERDA EM Z -> TECLA 'j' e 'J'",12);
    glutAddMenuEntry("ROTAÇÃO CANELA ESQUERDA EM X -> TECLA 'o' e 'O'",13);
    glutAddMenuEntry("ROTAÇÃO PE ESQUERDO EM X -> TECLA 'k' e 'K'",14);
    glutAddMenuEntry("ROTAÇÃO PE ESQUERDO EM Y -> TECLA 'p' e 'P'",15);
    glutAddMenuEntry("NA PERNA DIREITA USE L,M,N,B e V RESPECTIVAMENTE",16);
    glutAddMenuEntry("Zoom-in TECLA +, Zoom-out TECLA -",17);
    glutAddMenuEntry("ROTAÇÃO DA CAMERA TECLA 'X','x','Y','y','Z','z'",18);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("COLHEITA NO CÉU!");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMouseFunc(GerenciaMouse);
    glutKeyboardFunc(Keyboard);
    glutPassiveMotionFunc(cursor);

    iniciaAgricultor();
    iniciaTextura();
	iniciaIluminacao();
    criaMenu();
    glutMainLoop();

    return 0;
}
