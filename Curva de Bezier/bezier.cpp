#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
#define M 80
#define BORDA 3
#define PONTO 8 

using namespace std;

void limpaTela(){
	system("cls");
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


void zeraMatriz(int m[M][M]){
	for(int i = 0; i < M; i++)	
		for(int j = 0; j < M; j++)		
			m[i][j] = 0;
}

void imprimirMatriz(int m[M][M]){
	for(int i = 0; i < M; i++)	{
		for(int j = 0; j < M; j++){
			if(m[i][j]!=0){
				if(m[i][j]==8){
					cout << "0 ";
				}
				else {
					cout << ". ";
				}			   
			}
		   	else
			   	cout << "  ";	
		}
		cout << endl;
	}
}

void lerArquivo(int op, int x[], int y[]){

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

	fscanf(fp, "%d %d %d %d %d %d %d %d",&x[0],&y[0],&x[1],&y[1],&x[2],&y[2],&x[3],&y[3]);

	fclose(fp);
}

void imprimirPontos(int x[], int y[], int op){
	cout << "\n\nPontos do casos de teste " << op <<"." << endl;

	for(int i=0 ; i<N ; i++){
		cout << "P" << i << " (" << x[i] << ", " << y[i] << ")\n";
	}
}

void marcarPontosControle(int m[M][M], int x[], int y[]) {
	for(int i = 0; i < N; i++){
			m[ x[i] ][ y[i] ] = PONTO;
	}
}

void bezier (int m[M][M], int x[N], int y[N]) {

	double t, incremento=0.0005;

	for (t=0.0 ; t<1.0 ; t+=incremento) {
		
		double xt = pow(1-t,3) * x[0]+3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t,3)*x[3];
		double yt = pow(1-t,3) * y[0]+3*t*pow(1-t,2)*y[1]+3*pow(t,2)*(1-t)*y[2]+pow(t,3)*y[3];
		
		int posX = (int) xt;
		int posY = (int) yt;
		
		m[posX][posY] = BORDA;
	
	}
}

int main () {

	do{
		//declaração
		int x[N]={0}, y[N]={0};
		int matriz[M][M];	
		
		//funcao para zerar a matriz
		zeraMatriz(matriz);

		//funcao que retorna a opcao escolhida pelo usuario.
		int op = apresentacao();

		//funcao para ler o arquivo escolhido pelo usuario
		lerArquivo(op, x, y);
		
		//imprime os pontos que foram lidos do arquivo
		imprimirPontos(x, y, op);
		
		//chama a funcao de bezier passando a matriz que recebera os pontos e os vetores x e y com as posicoes dos pontos de controle.
		bezier(matriz, x, y);
		
		//marca os pontos de controle na matrix para melhor análise da curva.
		marcarPontosControle(matriz, x, y);
		
		//imprime a matrix gerada.
		imprimirMatriz(matriz);
	
	}while(continuar());
	
	return 0;
}