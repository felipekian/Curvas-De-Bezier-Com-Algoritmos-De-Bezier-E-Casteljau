#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define M 80
#define N 4
#define PONTO 8
#define BORDA 3

//estrutura para armazenar os pontos informados
typedef struct {
	float x;
	float y;
} Point;


void limpaTela(){
	system("clear");
}

void pausar(){
	cout << "Press para continuar...";
	getchar();
	getchar();
}

int continuar(){
	pausar();
	limpaTela();
	
	cout << "Deseja outro caso de teste S/N ? " << endl;
	char op;
	cin >> op;

	if(op=='S' || op=='s') return 1;
	else return 0;
}

int apresentacao(){
	limpaTela();
	cout << "\tCurva de Bezier			-->  		GRID = " << M << "x" << M << ".\n"<< endl;
	cout << "Escolha o caso de teste...\n1 - caso de teste 1\n2 - caso de teste 2\n3 - caso de teste 3\n4 - caso de teste 4\n>>> ";
	int op = -1;
	cin >> op;

	if(op >= 0 && op <=4) return op;
	else {
		limpaTela();
		apresentacao(); 
	}
}	
void zeraMatriz(int matrix[M][M]){
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < M ; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void imprimirMatrix(int matrix[M][M]){
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < M ; j++)
		{
			if(matrix[i][j] == 0){
				cout << "  ";
			}else{
				cout << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void lerArquivo(int op, Point p[N]){

	FILE * fp  = NULL;

	if(op == 1){
		fp = fopen("casosTeste/caso1.txt", "r");
	} else if(op == 2){
		fp = fopen("casosTeste/caso2.txt", "r");
	} else if(op == 3){
		fp = fopen("casosTeste/caso3.txt", "r");
	} else if(op == 4){
		fp = fopen("casosTeste/caso4.txt", "r");
	}

	fscanf(fp, "%f %f %f %f %f %f %f %f",&p[0].x,&p[0].y,&p[1].x,&p[1].y,&p[2].x,&p[2].y,&p[3].x,&p[3].y);

	fclose(fp);
}

void imprimirPontos(Point p[], int op){
	cout << "\n\nPontos do casos de teste " << op <<"." << endl;

	for(int i=0 ; i<N ; i++){
		cout << "P" << i << " (" << p[i].x << ", " << p[i].y << ")\n";
	}
}

void marcarPontosControle(int m[M][M], Point p[]) {
	for(int i = 0; i < N; i++){

		int x = (int) p[i].x;
		int y = (int) p[i].y;
 
		m[ x ][ y ] = PONTO;
	}
}

//retorna os pontos da curva e recebe os pontos , a quantidade de PONTOS DE CONTROLE E O T que varia de 0 até 1
void Casteljau(int m[M][M], Point *B, size_t b_len) {

	//parametros de incremento
	float incremento = 0.001;	

	for (float t=0; t<=1.0; t+=incremento) {
		
		Point q[b_len];
		size_t i, k;
		
		//for para transferir os pontos para uma struct auxiliar q.
		for (i=0; i<b_len; ++i) {
			q[i].x = B[i].x;
			q[i].y = B[i].y;
		}
		
		//calcula para cada ponto x e y com os N pontos de controle com a função de recorrência.
		for (k=1; k<b_len; ++k) {
			for (i=0; i<(b_len-k); ++i) {
				q[i].x = (1.0-t)*q[i].x + t*q[i+1].x;
				q[i].y = (1.0-t)*q[i].y + t*q[i+1].y;
			}
		}
		
		//transforma os pontos para inteiro
		int posX = (int) q[0].x;
		int posY = (int) q[0].y;

		//marca na matriz a coordenada encontrada.
		m[ posX ][ posY ] = BORDA;
	}
}

int main() {
	
	do{
		//declaracao
		Point p[N];	
		int matriz[M][M];

		//função para zerar a matriz.	
		zeraMatriz(matriz);

		//chama funcao que mostra uma apresentação e retorna a opcao escolhida pelo usuario.
		int op = apresentacao();
		
		//ler o arquivo da opcao com os dados. 
		lerArquivo(op, p);

		//imprime os pontos lidos do arquivo de teste.
		imprimirPontos(p, op);
		
		//recebe a matriz para colocar os pontos gerados, os pontos de controle p e o total de pontos N.
		Casteljau(matriz, p, N);
		
		//insere na matriz os pontos de controle para imprimir na tela.
		marcarPontosControle(matriz, p);
		
		//imprime na tela a matriz com resultado gerado.
		imprimirMatrix(matriz);

	//chama uma função para saber se deseja encerrar o programa.
	}while(continuar());

	return 0;
}