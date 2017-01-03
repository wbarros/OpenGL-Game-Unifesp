#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "personagem.h"
#include "mapa.h"

//VARIAVEIS PARA ANIMAR O PERSONAGEM ANDANDO
float animaBraco = 25.0;
float animaAnteBraco = -25.0;
float veloBraco = 1.0;

float animaPerna = 25.0;
float animaCanela = 25.0;
float maxCanela = 25.0;
float veloPerna = 1.0;
int resetaAng = 0; //variavel para quando o personagem para ele para com angulos zerados ou seja com braços e pernas retas.
//==========================================

//VARIAVEIS PARA MOSTRAR AS ROTAÇÕES DO CORPO DO HUMANOIDE
float angPulsoEsqX = 0;//
float angPulsoEsqY = 0;//
float angPulsoEsqZ = 0;//
float angPulsoDirX = 0;//
float angPulsoDirY = 0;//
float angPulsoDirZ = 0;//
float angBracoEsqX = 0;//
float angBracoEsqZ = 0;//
float angBracoDirX = 0;//
float angBracoDirZ = 0;//
float angABracoEsqX = 0;//
float angABracoDirX = 0;//

float angPernaEsqX = 0;
float angPernaEsqZ = 0;
float angCPernaEsqX = 0;
float angPeEsqX = 0;
float angPeEsqY = 0;
float angPernaDirX = 0;
float angPernaDirZ = 0;
float angCPernaDirX = 0;
float angPeDirX = 0;
float angPeDirY = 0;
//========================================================

float camX=15,camY=15,camZ=30;
Personagem criaPersonagem(){
	Personagem p;
	p.posicao[0] = 100.0;
	p.posicao[1] = 0.0;
	p.posicao[2] = 100.0;
	p.posicaoMD[0] = 0.0;
	p.posicaoMD[1] = -0.5;
	p.posicaoMD[2] = 0.0;
	p.angulo = 90.0;
	p.velo_andar = 0.1;
	return p;
}

void cameraPerspectivaHumanoide(Personagem p,int x,int y,int z){
    gluLookAt(p.posicao[0] + x + camX,p.posicao[1] + y + camY,p.posicao[2] + z + camZ,
              p.posicao[0],p.posicao[1],p.posicao[2],
              0,1,0);
}

Personagem andar(Personagem p) {
	if(p.posicao[2] >= 0 && p.posicao[2] <= 200)
        p.posicao[2] += p.velo_andar*cos((M_PI/180)*p.angulo);
    else
        p.posicao[2] -= p.velo_andar*cos((M_PI/180)*p.angulo);
    if(p.posicao[0] >= 0 && p.posicao[0] <= 200)
        p.posicao[0] += p.velo_andar*sin((M_PI/180)*p.angulo);
    else
        p.posicao[0] -= p.velo_andar*sin((M_PI/180)*p.angulo);
	return p;
}

void animaHumanoide(int velocidade)
{
    if (animaBraco < animaAnteBraco || animaBraco > -(animaAnteBraco))
        veloBraco = -(veloBraco);
    animaBraco += (veloBraco*velocidade);
    if (animaPerna > maxCanela || animaPerna < -(maxCanela))
        veloPerna = -(veloPerna);
    if(velocidade < 1.0)
        animaPerna += (veloPerna*velocidade);
    else
        animaPerna += (veloPerna*velocidade*velocidade);

    glutPostRedisplay();
}

void resetaAngulo(int valor)
{
    resetaAng = valor;
}

void resetaTodosAngulosEstaticos()
{
    rotacaoEstaticaBracoEsq(0,0,0,0,0,0);
    rotacaoEstaticaBracoDir(0,0,0,0,0,0);
    rotacaoEstaticaPernaEsq(0,0,0,0,0);
    rotacaoEstaticaPernaDir(0,0,0,0,0);
}

void rotacaoEstaticaPernaDir(float L, float M, float N, float B, float V)
{
    angPernaDirX = L;
    angPernaDirZ = M;
    angCPernaDirX = N;
    angPeDirX = B;
    angPeDirY = V;
}

void rotacaoEstaticaPernaEsq(float I, float J, float O, float K, float P)
{
    angPernaEsqX = I;
    angPernaEsqZ = J;
    angCPernaEsqX = O;
    angPeEsqX = K;
    angPeEsqY = P;
}

void rotacaoEstaticaBracoEsq(float Q, float A, float W, float S, float E, float D)
{
    angBracoEsqX = Q;//
    angBracoEsqZ = A;//
    angABracoEsqX = W;//
    angPulsoEsqX = S;//
    angPulsoEsqY = E;//
    angPulsoEsqZ = D;//
}

void rotacaoEstaticaBracoDir(float R, float F, float T, float G,float H, float U)
{
    angBracoDirX = R;//
    angBracoDirZ = F;//
    angABracoDirX = T;
    angPulsoDirX = G;//
    angPulsoDirY = H;//
    angPulsoDirZ = U;//
}

void desenhaBracoEsquerdo(Personagem p,float rr,float xx,float yy,float zz, int i) //I sera o numero de frutas no balde
{
    GLUquadricObj *obj = gluNewQuadric();
    int j;
    float raio = 0.13;
    glColor3f(1, 1, 1);
    glPushMatrix();//===========================================================================================
        glTranslatef(0.80,3.20,0.0);
        glRotatef(resetaAng*(-(animaBraco)),1,0,0); // ROTACAO DE TODO O BRAÇO AQUI
        glRotatef(angBracoEsqX,1,0,0); //ROTAÇÂO ESTATICA DO BRAÇO ESQUERDO EM X
        glRotatef(angBracoEsqZ,0,0,1); //ROTAÇÂO ESTATICA DO BRAÇO ESQUERDO EM Z
        glRotatef(10,0,0,1);
        glPushMatrix();// BRAÇO ESQUERDO PARTE DE CIMA
            glScalef(0.25, 0.6, 0.25);
            glTranslatef(0, -0.6,0);
            glutSolidSphere(1.0,10,10);
        glPopMatrix(); //=============================
        glPushMatrix();//==================================================================================
            glTranslatef(0,-1,0.10);
            if(animaBraco < 5)
                glRotatef(resetaAng*(animaAnteBraco/2),1.0,0,0);
            else
                glRotatef(resetaAng*(animaAnteBraco*(animaBraco/10)),1.0,0,0);
            glRotatef(angABracoEsqX,1,0,0);
            glPushMatrix();
                glScalef(0.20, 0.4, 0.20); //BRAÇO ESQUERDO PARTE DE BAIXO
                glTranslatef(0.0, -0.4, 0.0);
                glutSolidSphere(1.0,10,10);//=============================
            glPopMatrix();
            glPushMatrix();//====================================================================
                glTranslatef(0,-0.50,0);
                glRotatef(-90,0,1,0); // ROTACIONA O PULSO PARA NAO ANDAR DE MAO ABERTA
                glRotatef(angPulsoEsqX,1,0,0); // ROTAÇÃO DE TODO PULSO PARA BAIXO
                glRotatef(angPulsoEsqY,0,1,0);
                glRotatef(angPulsoEsqZ,0,0,1);
                glPushMatrix(); //PULSO ESQUERDO
                    glScalef(0.1,0.05,0.1);
                    glTranslatef(0.0,-1,0.0);
                    glutSolidSphere(1.0,10,10);
                glPopMatrix(); //===============
                glPushMatrix(); //MAO ESQUERDA
                    glScalef(0.14,0.11,0.11);
                    glTranslatef(0.0,-1,0.0);
                    glutSolidSphere(1.0,10,10);
                glPopMatrix(); //=============
                glPushMatrix();
                    glColor3f(1, 0.5, 0.5);
                    glTranslatef(0.10,-1.20,-0.10);
                    glRotated(-91,1,0,0);
                    gluCylinder(obj, 0.4, 0.6, 0.9, 10, 10); //BALDE
                    //glTranslatef(xx,yy,zz);
                    glRotated(-91,1,0,0);
                    glBegin(GL_POLYGON);
                    for(j=0;j<360;j+= 1)
                        glVertex3f(raio*cos(j)*M_PI,0,raio*sin(j)*M_PI);
                    glEnd();
                glPopMatrix();
                glPushMatrix();
                if(i > 0){ //Se tiver frutas no balde
                    glPushMatrix();
                        if(i == 1){
                            glPushMatrix();
                                desenhaFrutaP(0.0,-0.90,-0.10);
                            glPopMatrix();
                        }
                    glPopMatrix();
                    glPushMatrix();
                        if(i == 2){
                            glPushMatrix();
                            desenhaFrutaP(0.0,-0.90,-0.10);
                            glPopMatrix();
                            glPushMatrix();
                            desenhaFrutaP(-0.10,-0.60,0.0);
                            glPopMatrix();
                        }
                    glPopMatrix();
                    glPushMatrix();
                        if(i > 2){
                            glPushMatrix();
                            desenhaFrutaP(0.0,-0.90,-0.10);
                            glPopMatrix();
                            glPushMatrix();
                            desenhaFrutaP(-0.10,-0.60,0.0);
                            glPopMatrix();
                            glPushMatrix();
                            desenhaFrutaP(0.30,-0.30,0.0);
                            glPopMatrix();
                        }
                    glPopMatrix();
                }
                glPopMatrix();
                glColor3f(0.5, 0.9, 0.5);//VERDE
                //glRotatef(rr,1,0,0);// ROTAÇÃO DOS DEDOS VAI DE 0 ATE -24 -------------------------------------------------------------------------
                glPushMatrix();//======================================================
                    glTranslatef(0.14,-0.12,0.0); // Translada dedão parte 1
                    glPushMatrix(); //DEDAO MAO ESQUERDA PARTE 1
                        //ROTACÃO EM Y APENAS AQUI NO DEDAO PARA FECHALO JUNTO AOS OUTROS DEDOS
                        glRotatef(-32,0,0,1);
                        glScalef(0.08,0.04,0.04);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //===========================
                    glTranslatef(-0.10,-0.06,0.0);
                    //glRotatef(rr/2,1,0,0); // ROTACÃO DE TODA PARTE 1 DOS DEDOS MENOS DO DEDAO++++++++++++++++++++++++++++++++++++++++++
                    glPushMatrix(); //DEDO INDICADOR PARTE 1
                        glRotatef(5,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=======================
                    glTranslatef(-0.06,-0.02,0.0);
                    glPushMatrix(); //DEDO DO MEIO PARTE 1
                        glRotatef(7.0,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=====================
                    glTranslatef(-0.04,0.02,0.0);
                    glPushMatrix(); //DEDO DEPOIS DO MEIO PARTE 1
                        glRotatef(-9.0,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //============================
                    glTranslatef(-0.04,0.04,0.0);
                    glPushMatrix(); //DEDO MINDINHO PARTE 1
                        glRotatef(-19,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //======================
                glPopMatrix(); //=======================================================
                glPushMatrix();//=======================================================
                    glTranslatef(0.18,-0.18,0.0);
                    glPushMatrix(); //DEDAO MAO ESQUERDA PARTE 2
                        glRotatef(-28,0,0,1);
                        glScalef(0.05,0.02,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //===========================
                    glTranslatef(-0.14,-0.08,0.0);
                    //glRotatef(1*rr,1,0,0); // ROTACÃO DE TODA PARTE 2 DOS DEDOS MENOS DO DEDAO+++++++++++++++++++++++++++++++++++++++++++++++
                    glPushMatrix(); //DEDO INDICADOR PARTE 2
                        glRotatef(16,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=======================
                    glTranslatef(-0.06,-0.01,0.0);
                    glPushMatrix(); //DEDO DO MEIO PARTE 2
                        glRotatef(10.0,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=====================
                    glTranslatef(-0.06,0.01,0.0);
                    glPushMatrix(); //DEDO DEPOIS DO MEIO PARTE 2
                        glRotatef(-8.0,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //============================
                    glTranslatef(-0.05,0.05,0.0);
                    glPushMatrix(); //DEDO MINDINHO PARTE 2
                        glRotatef(-24.0,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //======================
                glPopMatrix();//========================================================
                glPushMatrix();//=======================================================
                    glTranslatef(0.05,-0.31,0.0);
                    //glRotatef(2*rr,1,0,0); // ROTACÃO DE TODA PARTE 3 DOS DEDOS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    glPushMatrix(); //DEDO INDICADOR PARTE 3
                        glRotatef(14,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=======================
                    glTranslatef(-0.07,-0.01,0.0);
                    glPushMatrix(); //DEDO DO MEIO PARTE 3
                        glRotatef(7,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=====================
                    glTranslatef(-0.07,0.02,0.0);
                    glPushMatrix(); //DEDO DEPOIS DO MEIO PARTE 3
                        glRotatef(-12,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //============================
                    glTranslatef(-0.06,0.05,0.0);
                    glPushMatrix(); //DEDO MINDINHO PARTE 3
                        glRotatef(-24,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //======================
                glPopMatrix();//========================================================
            glPopMatrix(); //===FIM DO PULSO ATE OS DEDOS======================================
        glPopMatrix();//===FIM BRAÇO ESQUERDO PARTE DE BAIXO ATE OS DEDOS=============================
    glPopMatrix();//====FIM BRAÇO ESQUERDO PARTE DE CIMA OU SEJA BRAÇO INTEIRO
}

void desenhaFrutaP(float x, float y, float z)
{
    glColor3f(1.0f,0.0f,0.0f);
    glTranslatef(x,y,z);
    glPushMatrix();
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
    glPopMatrix();
}

void desenhaBracoDireito(Personagem p,float rr,float xx,float yy,float zz)
{
    glColor3f(1, 1, 1);
    glPushMatrix();//===========================================================================================
        glTranslatef(-0.80,3.20,0.0);
        glRotatef(resetaAng*(animaBraco),1,0,0); // ROTACAO DE TODO O BRAÇO AQUI
        glRotatef(angBracoDirX,1,0,0);//
        glRotatef(angBracoDirZ,0,0,1);//
        glPushMatrix();// BRAÇO ESQUERDO PARTE DE CIMA
            glScalef(0.25, 0.6, 0.25);
            glTranslatef(0, -0.6,0);
            glutSolidSphere(1.0,10,10);
        glPopMatrix(); //=============================
        glPushMatrix();//==================================================================================
            glTranslatef(0,-1,0.10);
            if(animaBraco < -5)
                glRotatef(resetaAng*((animaAnteBraco*(animaBraco/-10))),1.0,0,0);
            else
                glRotatef(resetaAng*((animaAnteBraco/2)),1.0,0,0);
            glRotatef(angABracoDirX,1,0,0);
            glPushMatrix();
                glScalef(0.20, 0.4, 0.20); //BRAÇO DIREITO PARTE DE BAIXO
                glTranslatef(0.0, -0.4, 0.0);
                glutSolidSphere(1.0,10,10);//=============================
            glPopMatrix();
            glPushMatrix();//====================================================================
                glTranslatef(0,-0.5,0);
                glRotatef(-90,0,1,0); // ROTACIONA O PULSO PARA NAO ANDAR DE MAO ABERTA
                glRotatef(angPulsoDirX,1,0,0); // ROTAÇÃO DE TODO PULSO PARA BAIXO
                glRotatef(angPulsoDirY,0,1,0);
                glRotatef(angPulsoDirZ,0,0,1);
                glPushMatrix(); //PULSO DIREITO
                    glScalef(0.1,0.05,0.1);
                    glTranslatef(0.0,-1,0.0);
                    glutSolidSphere(1.0,10,10);
                glPopMatrix(); //===============
                glPushMatrix(); //MAO DIREITA
                    glScalef(0.14,0.11,0.11);
                    glTranslatef(0.0,-1,0.0);
                    glutSolidSphere(1.0,10,10);
                glPopMatrix(); //=============
                glRotatef(0,1,0,0);// ROTAÇÃO DOS DEDOS VAI DE 0 ATE -24 -------------------------------------------------------------------------
                glPushMatrix();//======================================================
                    glTranslatef(0.14,-0.12,0.0); // Translada dedão parte 1
                    glPushMatrix(); //DEDAO MAO DIREITA PARTE 1
                        //ROTACÃO EM Y APENAS AQUI NO DEDAO PARA FECHALO JUNTO AOS OUTROS DEDOS
                        glRotatef(-32,0,0,1);
                        glScalef(0.08,0.04,0.04);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //===========================
                    glTranslatef(-0.10,-0.06,0.0);
                    //glRotatef(0,1,0,0); // ROTACÃO DE TODA PARTE 1 DOS DEDOS MENOS DO DEDAO++++++++++++++++++++++++++++++++++++++++++
                    glPushMatrix(); //DEDO INDICADOR PARTE 1
                        glRotatef(5,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=======================
                    glTranslatef(-0.06,-0.02,0.0);
                    glPushMatrix(); //DEDO DO MEIO PARTE 1
                        glRotatef(7.0,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=====================
                    glTranslatef(-0.04,0.02,0.0);
                    glPushMatrix(); //DEDO DEPOIS DO MEIO PARTE 1
                        glRotatef(-9.0,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //============================
                    glTranslatef(-0.04,0.04,0.0);
                    glPushMatrix(); //DEDO MINDINHO PARTE 1
                        glRotatef(-19,0,0,1);
                        glScalef(0.03,0.05,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //======================
                glPopMatrix(); //=======================================================
                glPushMatrix();//=======================================================
                    glTranslatef(0.18,-0.18,0.0);
                    glPushMatrix(); //DEDAO MAO ESQUERDA PARTE 2
                        glRotatef(-28,0,0,1);
                        glScalef(0.05,0.02,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //===========================
                    glTranslatef(-0.14,-0.08,0.0);
                    //glRotatef(0,1,0,0); // ROTACÃO DE TODA PARTE 2 DOS DEDOS MENOS DO DEDAO+++++++++++++++++++++++++++++++++++++++++++++++
                    glPushMatrix(); //DEDO INDICADOR PARTE 2
                        glRotatef(16,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=======================
                    glTranslatef(-0.06,-0.01,0.0);
                    glPushMatrix(); //DEDO DO MEIO PARTE 2
                        glRotatef(10.0,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=====================
                    glTranslatef(-0.06,0.01,0.0);
                    glPushMatrix(); //DEDO DEPOIS DO MEIO PARTE 2
                        glRotatef(-8.0,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //============================
                    glTranslatef(-0.05,0.05,0.0);
                    glPushMatrix(); //DEDO MINDINHO PARTE 2
                        glRotatef(-24.0,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //======================
                glPopMatrix();//========================================================
                glPushMatrix();//=======================================================
                    glTranslatef(0.05,-0.31,0.0);
                    //glRotatef(0,1,0,0); // ROTACÃO DE TODA PARTE 3 DOS DEDOS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    glPushMatrix(); //DEDO INDICADOR PARTE 3
                        glRotatef(14,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=======================
                    glTranslatef(-0.07,-0.01,0.0);
                    glPushMatrix(); //DEDO DO MEIO PARTE 3
                        glRotatef(7,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //=====================
                    glTranslatef(-0.07,0.02,0.0);
                    glPushMatrix(); //DEDO DEPOIS DO MEIO PARTE 3
                        glRotatef(-12,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //============================
                    glTranslatef(-0.06,0.05,0.0);
                    glPushMatrix(); //DEDO MINDINHO PARTE 3
                        glRotatef(-24,0,0,1);
                        glScalef(0.02,0.04,0.03);
                        glTranslatef(0,-1,0.0);
                        glutSolidSphere(1.0,10,10);
                    glPopMatrix(); //======================
                glPopMatrix();//========================================================
            glPopMatrix(); //===FIM DO PULSO ATE OS DEDOS======================================
        glPopMatrix();//===FIM BRAÇO ESQUERDO PARTE DE BAIXO ATE OS DEDOS=============================
    glPopMatrix();//====FIM BRAÇO ESQUERDO PARTE DE CIMA OU SEJA BRAÇO INTEIRO
}

void desenhaPernaEsq(Personagem p,float rr,float xx,float yy,float zz)
{
        glColor3f(1, 1, 1);
        glTranslatef(0.32,1.65,0.0);
        glRotatef(resetaAng*(animaPerna),1,0,0); // ROTACIONA TODA PERNA ESQUERDA
        glRotatef(angPernaEsqX,1,0,0);
        glRotatef(angPernaEsqZ,0,0,1);
        glPushMatrix();  //PARTE DE CIMA DA PERNA ESQUERDA
            glScalef(0.25, 0.6, 0.25);
            glTranslatef(0, -0.75,0);
            glutSolidSphere(1.0,10,10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0,-0.83,0.0);
            if(animaPerna < 5)
                glRotatef(resetaAng*(animaCanela*(fabs(animaPerna)/20.0)),1.0,0.0,0.0);
            else
                glRotatef(resetaAng*(animaCanela*(fabs(animaPerna)/10.0)),1.0,0.0,0.0);
            glRotatef(angCPernaEsqX,1,0,0);
            glPushMatrix(); //PARTE DE BAIXO DA PERNA ESQUERDA
                glScalef(0.15, 0.4, 0.15);
                glTranslatef(0, -0.75,0);
                glutSolidSphere(1.0,10,10);
            glPopMatrix();
            glTranslatef(0.0,-0.65,0.13);
            glRotatef(angPeEsqX,1,0,0);
            glRotatef(angPeEsqY,0,1,0);
            glPushMatrix(); //PÉ ESQUERDO ESQUERDO
                glScalef(0.12, 0.12, 0.25);
                glTranslatef(0, -0.25,0);
                glutSolidSphere(1.0,10,10);
            glPopMatrix();
        glPopMatrix();
}

void desenhaPernaDir(Personagem p,float rr,float xx,float yy,float zz)
{
        glColor3f(1, 1, 1);
        glTranslatef(-0.32,1.65,0.0);
        glRotatef(resetaAng*(-animaPerna),1,0,0); // ROTACIONA TODA PERNA DIREITA
        glRotatef(angPernaDirX,1,0,0);
        glRotatef(angPernaDirZ,0,0,1);
        glPushMatrix();  //PARTE DE CIMA DA PERNA DIREITA
            glScalef(0.25, 0.6, 0.25);
            glTranslatef(0, -0.75,0);
            glutSolidSphere(1.0,10,10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0,-0.83,0.0);
            if(animaPerna < 5)
                glRotatef(resetaAng*(animaCanela*(fabs(animaPerna)/10.0)),1.0,0.0,0.0);
            else
                glRotatef(resetaAng*(animaCanela*(fabs(animaPerna)/20.0)),1.0,0.0,0.0);
            glRotatef(angCPernaDirX,1,0,0);
            glPushMatrix(); //PARTE DE BAIXO DA PERNA DIREITA
                glScalef(0.15, 0.4, 0.15);
                glTranslatef(0, -0.75,0);
                glutSolidSphere(1.0,10,10);
            glPopMatrix();
            glTranslatef(0.0,-0.65,0.13);
            glRotatef(angPeDirX,1,0,0); // ROTAÇÃO DO PÉ
            glRotatef(angPeDirY,0,1,0);
            glPushMatrix(); //PÉ DIREITO
                glScalef(0.12, 0.12, 0.25);
                glTranslatef(0, -0.25,0);
                glutSolidSphere(1.0,10,10);
            glPopMatrix();
        glPopMatrix();
}

void desenhapeitoral(float xx,float yy,float zz)
{
        glColor3f(1, 1, 1);
        glPushMatrix(); //OMBRO ESQUERDO
            glTranslatef(-0.72,3.18,0.0);
            glutSolidSphere(0.3,10,10);
        glPopMatrix();//================

        glPushMatrix();//OMBRO DIREITO
            glTranslatef(0.72,3.18,0.0);
            glutSolidSphere(0.3,10,10);
        glPopMatrix(); //=============

        glPushMatrix(); //VIRILHA ESQUERDA
            glTranslatef(0.33,1.56,0.0);
            glutSolidSphere(0.27,10,10);
        glPopMatrix();//================

        glPushMatrix(); //VIRILHA DIREITA
            glTranslatef(-0.33,1.56,0.0);
            glutSolidSphere(0.27,10,10);
        glPopMatrix();//================

        glPushMatrix();
			glScalef(0.3, 0.4, 0.20);
			glTranslatef(0,6.44,0);
			glutSolidCube(4);
        glPopMatrix(); //FIM PEITORAL
}

void desenhaRosto(float xx,float yy,float zz)
{
    int j;
    float raio = 0.3;
        glColor3f(1,1,1);
        glPushMatrix();
            glTranslatef(0.0,4.51,0.0);
            glPushMatrix();
                glTranslatef(0.0, -0.5, 0.0);
                glutSolidSphere(0.50,20,10); //CABEÇA
			glPopMatrix();
			glTranslatef(0.0,-0.24,0.0);
			glPushMatrix();
                glColor3f(1, 1, 1); // BRANCO
                glTranslatef(0, -0.80, 0);
                glutSolidSphere(0.2,20,10); //PESCOÇO
			glPopMatrix();
			glTranslatef(0.14,-0.14,0.27);
			glPushMatrix();
                glColor3f(1, 1, 1); // BRANCO
                glutSolidSphere(0.2,20,10); //OLHO ESQUERDO
			glPopMatrix();
			glTranslatef(-0.27,0.0,0.0);
			glPushMatrix();
                glutSolidSphere(0.2,20,10); // OLHO DIREITO
            glPopMatrix();
            glTranslatef(0.13,-0.09,0.07);
            glPushMatrix();
                glutSolidCone(0.1,0.3,20,10); //NARIZ
            glPopMatrix();
			glColor3f(0, 0, 0);// PRETO
			glTranslatef(0.18,0.12,0.02);
			glPushMatrix();
                glutSolidSphere(0.1,50,50); //BOLINHA DO OLHO ESQUERDO
            glPopMatrix();
            glTranslatef(-0.35,0.0,0.0);
            glPushMatrix();
                glutSolidSphere(0.1,50,20); //BOLINHA DO OLHO DIREITO
            glPopMatrix();
        glPopMatrix();
        glTranslatef(0.0,4.33,0.0);
        glPushMatrix();
            glRotatef(-10,1,0,0);
            glColor3f(0, 0, 0);
            glBegin(GL_POLYGON);
                for(j=0;j<360;j+= 1)
                    glVertex3f(raio*cos(j)*M_PI,0,raio*sin(j)*M_PI);
            glEnd();
        glPopMatrix();
        glTranslatef(0.0,-0.11,-0.04);
        glPushMatrix();
            glutSolidSphere(0.40,50,50); //PARTE DE CIMA DO CHAPEU
        glPopMatrix();
    glPopMatrix();
}

