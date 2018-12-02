#include <iostream>

#define M 80
#define N 4
#define BORDA 3

using namespace std;

void apresentacao(){
	cout << "\tAlgortimo de Casteljau para GRAU 3 \t\tGRID: " << M << "x" << M << "." << endl;	
}

int fat(int n){
	if (n==0) return 1;
	else return n*fat(n-1);
}

int comb (int n, int r) {
	return (fat(n)/(fat(n-r)*fat(r)));
}

void zeraMatriz(int m[M][M]) {
	for(int i = 0; i < M; i++)
		for(int j = 0 ; j < M; j++)
			m[i][j] = 0;	
}

void imprimeMatriz(int m[M][M]) {
	for(int i = 0; i < M; i++){
		for(int j = 0 ; j < M; j++){
			if(m[i][j] == 0){
				cout << "  ";
			}else{
				cout << m[i][j] << " ";
			}	
		}
		cout << endl;
	}
}

void limpaPontos(double x[N][N], double y[N][N]){
	for(int i=0 ; i<N ; i++){
		for(int j=0 ; j<N ; j++){
			x[i][j] = 0;
			y[i][j] = 0;
		}
	}
}

void casteljau (int m[M][M], double x[N][N], double y[N][N]) {
	
	cout << "Casteljau" << endl;
	
	double t = 0.0;
	double incremento = 0.001;
	
	for (t = 0.0; t<1.0 ; t+=incremento) {
		
		for(int i = 1; i <=N ; i++){
			
			for(int j = 0; j < N-i ; j++){
				
				double xt = ((1-t) * x[i-1][j]) + (t * x[i-1][j+1]);
				double yt = ((1-t) * y[i-1][j]) + (t * y[i-1][j+1]);
				
				x[i][j] = xt;
				y[i][j] = yt;
				
				int posX = (int) xt;
				int posY = (int) yt;
				
			   	m[posX][posY] = BORDA;
 				
 					
			}
			
		}
		
	}
	
}

int main () {
	apresentacao();
	
	double x[N][N], y[N][N];
	int matriz[M][M];
	
	zeraMatriz(matriz);
	limpaPontos(x, y);
	
	for(int i = 0; i < N; i++){
		if (i==0) 
			cout << "\nInforme as coordenadas P(x,y) dos 4 pontos de controle.\n" << endl;
		
		cout << "P" << i << ": ";
		cin >> x[0][i] >> y[0][i];
	}
	
	casteljau(matriz, x, y);
	
	imprimeMatriz(matriz);
	
	
	return 0;
}