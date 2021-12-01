#include <stdio.h>
#include <stdlib.h>
#define TAM 20

//funcoes para a busca em profundidade: 
struct Pilha {
	int topo; /* posicoes elemento topo */
	int capa;
	float *pElem;
};

void criarpilha (struct Pilha *p, int c){
   p->topo = -1;
   p->capa = c;
   p->pElem = (float*) malloc (c * sizeof(float));
}

int estavazia (struct Pilha *p){
   if( p-> topo == -1 )
      return 1;   // true
   else
      return 0;   // false
}

int estacheia (struct Pilha *p){
	if (p->topo == p->capa - 1)
		return 1;
	else
		return 0;
}

void empilhar (struct Pilha *p, float v){
	p->topo++;
	p->pElem [p->topo] = v;
}

float desempilhar ( struct Pilha *p ){
   float aux = p->pElem [p->topo];
   p->topo--;
   return aux;
}

float retornatopo ( struct Pilha *p ){
   return p->pElem [p->topo];
}

int confirmar_destino (float v, float f){
	if (v == f ) return 1;
	else return 0; 
}

int existe_em(int visitados[], int cid){
	for(int x=0; x<TAM; x++){
		if(cid == visitados[x]){
			return 1;
		}
	}
	return 0;
}

//funcoes para a busca de custo uniforme:
struct caminhos{
    int expansoes[21];
    int custo_somado;
	int aux_pos;
};

struct no{
	int cidade;
    int custo;
    struct no * pai;
    struct no * link;
};
typedef struct no * ptno;

ptno criar_vazia (){
	return NULL;
}

void imprime_custo (ptno pri){
	ptno p;
	p = pri;
	while(p!=NULL){
		printf(" %d ", p->custo);
        
		p = p->link;
	}
}

void imprime_cidades (ptno pri){
	ptno p;
	p = pri;
	while(p != NULL){
		printf(" %d ", p->cidade);
		p = p->link;
	}
}

void imprime_pais (ptno nofinal, int inicio, int fim){
    ptno p;
    p = nofinal->pai;
		int solucao[20] = {0};
		int i = 0;

		solucao[i++] = nofinal->cidade;
    while(p !=  NULL){
        solucao[i++] = p->cidade;
        p = p->pai;
    }

		printf(" %d ", inicio);
		for(int x=19; x>-1; x--){
			if(solucao[x] != 0){
				printf(" %d ", solucao[x]);
			}
		}
		if(fim == 0){
			printf("%d", fim);
		}
}

void inserir (ptno *pri, int a, int b, ptno pai_atual){
	ptno novo, p , anterior;
	anterior = NULL;

	novo = (ptno) malloc(sizeof(ptno));

	novo->cidade = a;
	novo->custo = b;
    novo->pai = pai_atual;

	p = *pri;
	while(p!=NULL && novo->custo > p->custo){
		anterior = p;
		p= p->link;
	}
	if(p==*pri)
		*pri = novo;
	else
		anterior->link = novo;

	novo->link = p;
}

void ordenar_ligada (ptno pri){
	ptno p, p2;
	p = pri;
	while(p->link != NULL){
		p2 = p->link;
		while(p2->link != NULL){
			if(p->custo > p2->custo){
				int temp_info = p->custo;
				p->custo = p2->custo;
				p2->custo = temp_info;

        int temp_info2 = p->cidade;
				p->cidade = p2->cidade;
				p2->cidade = temp_info2;

        ptno temp = p->pai;
				p->pai = p2->pai;
				p2->pai = temp;

			}
			p2 = p2->link;
		}
		p = p->link;
	}
}

void remover_expandido (ptno *pri, int custo_expandido){
	ptno p, anterior;
    anterior = NULL;
    p=*pri;
    while(p != NULL && custo_expandido>p->custo)
    {
        anterior = p;
        p=p->link;
    }
    if (p == *pri)
        *pri = p->link;
    else
        anterior->link = p->link;
}

int verify (int visitados[], int possibilidade){
  for(int i = 0; i< TAM; i++){
    if(possibilidade == visitados[i])
    return 1;
  }
	return 0;
}

int main(){
	int matriz[TAM][TAM] = {0};
  matriz[0][1] = 75;  // cidade 0 -  Arad
  matriz[1][0] = 75;  // cidade 1 -  Zerind
  matriz[0][2] = 118; // cidade 2 -  Timisoara
  matriz[2][0] = 118; // cidade 3 -  Oradea
  matriz[1][3] = 71;  // cidade 4 -  Lugoj
  matriz[3][1] = 71;  // cidade 5 -  Sibiu
  matriz[2][4] = 111; // cidade 6 -  Mehadia
  matriz[4][2] = 111; // cidade 7 -  Fagaras
  matriz[0][5] = 140; // cidade 8 -  Rimnicu Vilcea
  matriz[5][0] = 140; // cidade 9 -  Dobreta
  matriz[3][5] = 151; // cidade 10 - Pitesti
  matriz[5][3] = 151; // cidade 11 - Craiova
  matriz[4][6] = 70;  // cidade 12 - Bucharest
  matriz[6][4] = 70;  // cidade 13 - Giurgiu
  matriz[5][7] = 99;  // cidade 14 - Urziceni
  matriz[7][5] = 99;  // cidade 15 - Vaskyu
  matriz[5][8] = 80;  // cidade 16 - Hirsova
  matriz[8][5] = 80;  // cidade 17 - Iasi
  matriz[6][9] = 75;  // cidade 18 - Eforie
  matriz[9][6] = 75;  // cidade 19 - Neamt
  matriz[8][10] = 97;
  matriz[10][8] = 97;
  matriz[8][11] = 146;
  matriz[11][8] = 146;
  matriz[9][11] = 120;
  matriz[11][9] = 120;
  matriz[10][11] = 138;
  matriz[11][10] = 138;
  matriz[7][12] = 211;
  matriz[12][7] = 211;
  matriz[10][12] = 101;
  matriz[12][10] = 101;
  matriz[12][13] = 90;
  matriz[13][12] = 90;
  matriz[12][14] = 85;
  matriz[14][12] = 85;
  matriz[14][15] = 142;
  matriz[15][14] = 142;
  matriz[14][16] = 98;
  matriz[16][14] = 98;
  matriz[15][17] = 92;
  matriz[17][15] = 92;
  matriz[16][18] = 86;
  matriz[18][16] = 86;
  matriz[17][19] = 87;
  matriz[19][17] = 87;

  for(int i =0;i<TAM;i++){
      for(int j = 0;j<TAM;j++){
          printf(" %3d", matriz[i][j]);
      }
      printf("\n");
  }
 
	struct Pilha minhapilha;
	int capacidade;
  float inicio, fim;
	int caminho1[40];
  int contador = 0;
	int valor;
  int visitado = 0;
	int custo_visitado;
  int visitados[TAM] = {0};


	int decisao;
	printf("\n\n>>>Menu de buscas");
	printf("\n1- Busca em profundidade");
	printf("\n2- Busca de custo uniforme");
	do{ printf("\n\n>>Digite o numero do tipo de busca vc gostaria de realizar: ");
	scanf("%d", &decisao);
	printf("\n");} while(decisao < 1 || decisao > 2);

	do {printf("\n>Por qual cidade deseja comecar?: ");
	scanf("%f", &inicio);} while(inicio < 0 || inicio >= TAM);
	getchar();
	do{printf("\n>Em qual cidade deseja chegar?: ");
	scanf("%f", &fim);} while(fim < 0 || fim >= TAM);
	getchar();

	if(decisao == 1){
		// profundidade
		criarpilha (&minhapilha, capacidade);

		empilhar(&minhapilha, inicio);
		
		while(1){	
			printf("\n\nVisitado: %d",visitado);
			valor = retornatopo(&minhapilha);
			printf("\nAtual (Topo) => %d", valor);
			caminho1[contador++] = valor;
      
			if (confirmar_destino(valor,fim) == 1){
				printf("\n\nCaminho realizado: ");
				for(int i=0;i<contador;i++) printf("%d ",caminho1[i]);
				break;
			}
			
			if(estavazia(&minhapilha) == 0){
				for(int i=0;i<TAM;i++){
        	if(visitados[i] == 0){
          	visitados[i] = retornatopo(&minhapilha);
            break;
        	}
      	}
				desempilhar(&minhapilha);
			}

			printf("\n");
			printf("Possibilidades: ");
    

      int encontrou = 0;
			if(inicio < fim){ 
				for(int i=1;i<TAM;i++){
					if (matriz[valor][i] != 0){
						if(existe_em(visitados, i) == 0){
              if (encontrou == 0) empilhar(&minhapilha, i);
							printf("%d ", i);
              if (i == fim) encontrou = 1;
						}
					}
				}
			}
  
			if (inicio > fim){
				for(int i=TAM - 1; i>0; i--){
					if (matriz[valor][i] != 0){
						if(existe_em(visitados, i) == 0){
              if (encontrou == 0) empilhar(&minhapilha, i);
							printf("%d ", i);
              if(i == fim) encontrou = 1;
						}
					}
				}
			}
			visitado = valor;
		}
	}
	
    if(decisao == 2){
			//custo uniforme
			struct caminhos caminho;
			ptno pri, pai_atual, nofinal;
			pri = criar_vazia();
			pai_atual = criar_vazia();
			nofinal = criar_vazia();
      int visitados[TAM];

      for(int i = 0; i<TAM; i++){
        visitados[i] = -1;
      }

			for(int x=0; x<21; x++){
				caminho.expansoes[x] = -1;
			}

			caminho.expansoes[caminho.aux_pos++] = inicio;
			caminho.custo_somado = 0; 
			caminho.aux_pos = 0;
			valor = inicio;


			while(1){
				if(valor == fim){
					printf("\n\nVoce chegou ao destino!!!");
					break;
				}

				printf("\n\nOrdem de expansao realizada: ");
				for(int z = 0; z<21; z++){
					if (caminho.expansoes[z] != -1) printf(" %d " , caminho.expansoes[z]);
				}
				printf("\nCusto somado no caminho atual: %d", caminho.custo_somado);

				printf("\n\nNovas possibilidades de expansao: ");
				for(int i=0;i<TAM;i++){
					if (matriz[valor][i] != 0 && (i != visitado) && (i != inicio)){
						if(verify(visitados, i) == 0){
              printf(" %d ", i);
              int a = i;
              int b = (caminho.custo_somado + matriz[valor][i]);
              inserir(&pri, a, b, pai_atual);
            }
					}
				}
				ordenar_ligada(pri);

				printf("\n\nLista ordenada das possibilidades: ");
				imprime_cidades(pri);
				printf("\nLista ordenada dos custos: ");
				imprime_custo(pri);

				visitado = valor;
				for(int x = 0; x<TAM; x++){
					if(visitados[x] == -1){
						visitados[x] = visitado;
						break;
					}
				}
				
				custo_visitado = pri->custo;

				caminho.expansoes[caminho.aux_pos++] = pri->cidade;
				caminho.custo_somado = pri->custo;
				valor = pri->cidade;
			
				printf("\n\nProximo a ser expandido: %d", valor);
				printf("\n\n");

				pai_atual = pri;
				if(pri->cidade == fim) nofinal = pri;
				
				remover_expandido(&pri, custo_visitado);
			}

			printf("\n\nExpansoes realizadas: ");
			for(int z = 0; z<21; z++) if (caminho.expansoes[z] != -1) printf(" %d " , caminho.expansoes[z]);
			printf("\nCusto total do caminho final: %d", caminho.custo_somado);
			printf("\nCaminho solucao: ");
			imprime_pais(nofinal, inicio, fim);
		}

	printf("\n\n>>>Fim do programa");
	printf("\n\n");
}