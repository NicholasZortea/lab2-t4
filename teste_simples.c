#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>


void teste_insercao_print(){
    Grafo graf = grafo_cria(4, 4);
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    grafo_insere_no(graf, &a);
    grafo_insere_no(graf, &b);
    grafo_insere_no(graf, &c);
    grafo_insere_no(graf, &d);
    grafo_insere_no(graf, &e);

    int f, g, h, i;
    f = 2;
    g = 5;
    h = 6;
    i = 7;
    grafo_altera_valor_aresta(graf, 0, 1, &f);
    grafo_altera_valor_aresta(graf, 1, 3, &h);
    grafo_altera_valor_aresta(graf, 2, 4, &g);
    grafo_altera_valor_aresta(graf, 4, 3, &i);
    
    printa_grafo(graf);
    grafo_destroi(graf);
}

void teste_alteracao_no() {
    // Cria o grafo com tamanhos apropriados para os dados dos nós e arestas
    Grafo g = grafo_cria(sizeof(int), sizeof(int));

    // Insere alguns nós
    int valor_no1 = 10;
    int valor_no2 = 20;
    int valor_no3 = 30;

    int id_no1 = grafo_insere_no(g, &valor_no1);
    int id_no2 = grafo_insere_no(g, &valor_no2);
    int id_no3 = grafo_insere_no(g, &valor_no3);

    grafo_altera_valor_aresta(g, id_no1, id_no2, &id_no3);
    grafo_altera_valor_aresta(g, id_no2, id_no1, &id_no3);
    grafo_altera_valor_aresta(g, id_no3, id_no3, &id_no3);
    printf("Grafo antes da alteracao:\n");
    printa_grafo(g);

    //Altera o valor do nó 2
    int novo_valor_no2 = 25;
    grafo_altera_valor_no(g, id_no2, &novo_valor_no2);

    printf("Grafo apos a alteracao:\n");
    printa_grafo(g);

    // Destroi o grafo para liberar a memória
    grafo_destroi(g);
}

void teste_remove_no() {
    Grafo g = grafo_cria(sizeof(int), sizeof(int));

    int a = 1, b = 2, c = 3, d = 4;
    grafo_insere_no(g, &a); // Nó 0
    grafo_insere_no(g, &b); // Nó 1
    grafo_insere_no(g, &c); // Nó 2
    grafo_insere_no(g, &d); // Nó 3

    // Insere algumas arestas
    int peso = 10;
    grafo_altera_valor_aresta(g, 0, 1, &peso);
    grafo_altera_valor_aresta(g, 1, 2, &peso);
    grafo_altera_valor_aresta(g, 2, 3, &peso);

    printf("Grafo antes de remover o nó:\n");
    printa_grafo(g);

    // Remove o nó 1
    grafo_remove_no(g, 1);

    printf("\nGrafo após remover o nó 1:\n");
    printa_grafo(g);

    grafo_destroi(g);
}

void teste_grafo_valor_no(){
    Grafo g = grafo_cria(sizeof(int), sizeof(int));

    int a = 1, b = 2, c = 3, d = 4;
    grafo_insere_no(g, &a); // Nó 0
    grafo_insere_no(g, &b); // Nó 1
    grafo_insere_no(g, &c); // Nó 2
    grafo_insere_no(g, &d); // Nó 3

    // Insere algumas arestas
    int peso = 10;
    grafo_altera_valor_aresta(g, 0, 1, &peso);
    grafo_altera_valor_aresta(g, 1, 2, &peso);
    grafo_altera_valor_aresta(g, 2, 3, &peso);

    printf("Grafo:\n");
    printa_grafo(g);

    int valor;
    grafo_valor_no(g, 2, &valor);
    printf("\nValor contido no no de id 2: %d", valor);

    grafo_destroi(g);
}

void teste_altera_valor_aresta() {
    Grafo g = grafo_cria(sizeof(int), sizeof(int));

    int a = 1, b = 2, c = 3, d = 4;
    grafo_insere_no(g, &a); // Nó 0
    grafo_insere_no(g, &b); // Nó 1
    grafo_insere_no(g, &c); // Nó 2
    grafo_insere_no(g, &d); // Nó 3

    int peso1 = 10;
    int peso2 = 20;

    // Inserir algumas arestas
    grafo_altera_valor_aresta(g, 0, 1, &peso1); // Aresta (0, 1)
    grafo_altera_valor_aresta(g, 1, 2, &peso1); // Aresta (1, 2)
    grafo_altera_valor_aresta(g, 2, 3, &peso1); // Aresta (2, 3)

    printf("Grafo após inserção de arestas:\n");
    printa_grafo(g);
    printa_arestas(g);

    // Alterar valor de uma aresta existente
    grafo_altera_valor_aresta(g, 1, 2, &peso2); // Aresta (1, 2) agora tem peso 20

    // Tentar alterar uma aresta que não existe (será criada)
    grafo_altera_valor_aresta(g, 3, 0, &peso2); // Aresta (3, 0)

    printf("\nGrafo após alterar arestas:\n");
    printa_grafo(g);
    printa_arestas(g);

    // Remover uma aresta
    grafo_altera_valor_aresta(g, 0, 1, NULL); // Remove aresta (0, 1)

    printf("\nGrafo após remover uma aresta:\n");
    printa_grafo(g);
    printa_arestas(g);

    grafo_destroi(g);
}

void teste_grafo_valor_aresta() {
    Grafo g = grafo_cria(sizeof(int), sizeof(int));

    int a = 1, b = 2, c = 3, d = 4;
    grafo_insere_no(g, &a); // Nó 0
    grafo_insere_no(g, &b); // Nó 1
    grafo_insere_no(g, &c); // Nó 2
    grafo_insere_no(g, &d); // Nó 3

    int peso1 = 10;
    int peso2 = 20;

    // Inserir algumas arestas
    grafo_altera_valor_aresta(g, 0, 1, &peso1); // Aresta (0, 1)
    grafo_altera_valor_aresta(g, 1, 2, &peso2); // Aresta (1, 2)

    // Teste para aresta existente
    int valor;
    bool existe = grafo_valor_aresta(g, 0, 1, &valor);
    if (existe) {
        printf("Aresta (0, 1) existe com valor: %d\n", valor);
    } else {
        printf("Aresta (0, 1) não existe\n");
    }

    // Teste para aresta inexistente
    existe = grafo_valor_aresta(g, 0, 2, &valor);
    if (existe) {
        printf("Aresta (0, 2) existe com valor: %d\n", valor);
    } else {
        printf("Aresta (0, 2) não existe\n");
    }

    grafo_destroi(g);
}

Grafo cria_grafo_exemplo() {
    Grafo g = grafo_cria(sizeof(int), sizeof(int));
    
    // Adiciona nós
    int ids[] = {0, 1, 2};
    for (int i = 0; i < 3; i++) {
        grafo_insere_no(g, &ids[i]);
    }

    return g;
}

void testa_grafo_proxima_aresta() {
    Grafo g = cria_grafo_exemplo();
    
    // Testa arestas que partem do nó 0
    printf("Arestas que partem do nó 0:\n");
    grafo_arestas_que_partem(g, 0);
    
    int vizinho;
    int peso;
    while (grafo_proxima_aresta(g, &vizinho, &peso)) {
        printf("Para o nó %d, o peso da aresta é %d\n", vizinho, peso);
    }
    
    // Testa arestas que chegam ao nó 2
    printf("\nArestas que chegam ao nó 2:\n");
    grafo_arestas_que_chegam(g, 2);
    
    while (grafo_proxima_aresta(g, &vizinho, &peso)) {
        printf("Do nó %d, o peso da aresta é %d\n", vizinho, peso);
    }
    
    // Limpa o grafo
    grafo_destroi(g);
}

void teste_tem_ciclo(){
    Grafo g = cria_grafo_exemplo();
    int peso = 109;
    grafo_altera_valor_aresta(g, 1, 0, &peso);
    grafo_altera_valor_aresta(g, 2, 1, &peso);


    printf(grafo_tem_ciclo(g) ? "Tem ciclo\n" : "Nao tem ciclo\n"); 
    printa_arestas(g);
    printa_grafo(g);
    grafo_destroi(g);
}

void teste_ordem_topologica() {
    int tam_no = sizeof(int);
    int tam_aresta = sizeof(int);

    // Cria um grafo
    Grafo g = grafo_cria(tam_no, tam_aresta);

    // Insere nós no grafo
    int no1 = 1, no2 = 2, no3 = 3, no4 = 4;
    int id1 = grafo_insere_no(g, &no1);
    int id2 = grafo_insere_no(g, &no2);
    int id3 = grafo_insere_no(g, &no3);
    int id4 = grafo_insere_no(g, &no4);

    // Insere arestas no grafo
    int peso1 = 1, peso2 = 2, peso3 = 3;
    grafo_altera_valor_aresta(g, id1, id2, &peso1); // aresta de no1 a no2
    grafo_altera_valor_aresta(g, id2, id3, &peso2); // aresta de no2 a no3
    grafo_altera_valor_aresta(g, id3, id4, &peso3); // aresta de no3 a no4

    // Obtém a ordem topológica
    Fila ordem = grafo_ordem_topologica(g);
    printa_arestas(g);
    // Verifica se a ordem topológica é válida e imprime
    if (fila_vazia(ordem)) {
        printf("O grafo possui ciclos ou está vazio. Ordem topológica não disponível.\n");
    } else {
        printf("Ordem topológica:\n");
        while (!fila_vazia(ordem)) {
            int no;
            fila_remove(ordem, &no);
            printf("%d ", no);
        }
        printf("\n");
    }

    // Destroi a fila e o grafo
    fila_destroi(ordem);
    grafo_destroi(g);
}
int main(){
     teste_insercao_print();
     teste_alteracao_no();
     teste_grafo_valor_no();
     teste_remove_no();
    teste_altera_valor_aresta();
    testa_grafo_proxima_aresta();
    teste_grafo_valor_aresta();
    teste_tem_ciclo();
    teste_ordem_topologica();
    return 0;
}