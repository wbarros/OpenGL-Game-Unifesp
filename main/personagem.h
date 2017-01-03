typedef struct personagem {
	float posicao[3]; //posição corrente no mapa
	float posicaoMD[3]; //posição mao direita
	float colisao; //possilvel colisao com alguma arvore
	float angulo; // angulo de orientação
	float velo_andar; //velocidade que o personagem anda
} Personagem;

void cameraPerspectivaHumanoide(Personagem p,int x,int y,int z);
Personagem criaPersonagem();
Personagem andar(Personagem p);
void animaHumanoide(int velocidade);
void desenhaBracoEsquerdo(Personagem p,float rr,float xx,float yy,float zz, int i);
void desenhaBracoDireito(Personagem p,float rr,float xx,float yy,float zz);
void desenhaRosto(float xx,float yy,float zz);
void desenhapeitoral(float xx,float yy,float zz);
void desenhaPernaEsq(Personagem p,float rr,float xx,float yy,float zz);
void desenhaPernaDir(Personagem p,float rr,float xx,float yy,float zz);
void resetaAngulo(int valor);
void resetaTodosAngulosEstaticos();
void desenhaFrutaP(float x, float y, float z);
void rotacaoEstaticaBracoEsq(float Q, float A, float W, float S, float E, float D);
void rotacaoEstaticaBracoDir(float R, float F, float T, float G,float H, float U);
void rotacaoEstaticaPernaEsq(float I, float J, float O, float K, float P);
void rotacaoEstaticaPernaDir(float L, float M, float N, float B, float V);
void pegaFruta(int valor);

