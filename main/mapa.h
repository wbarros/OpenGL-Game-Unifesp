#define NUMFRUTAS 1000
#define NUMARVORES 1000

typedef struct arvore {

	float local[3]; //x,y,z onde o humanoide ira gerar frutas e colher

} Arvore;

typedef struct fruta {

	float local[3]; //x,y,z onde o humanoide ira colher

} Fruta;

Arvore iniciaArvore(float x, float z);
void desenhaArvore(Arvore a);
Fruta iniciaFruta(float x, float y , float z);
void desenhaFruta(Fruta f);
int checaCliqueFruta(float xmouse,float ymouse,float zmouse,Arvore *a);
void sweepTranslacional();
