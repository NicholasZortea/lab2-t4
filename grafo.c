#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct no{
    void *pdado;
    int id;
    struct no* next;
}no;

typedef struct aresta{
    void* pdado;
    int origem;
    int destino;
    struct aresta* prox;
}aresta;

typedef struct Consulta{
    int id;
    void * espaco;
    struct Consulta * prox;
}Consulta;

struct _grafo{
    int tam_no;
    int tam_aresta;
    int n_nos;
    no** adjacencias;
    aresta* arestas;
    int n_arestas;
    Consulta* consulta;
};





no* cria_no(int nmr, void* pdado, int tam_dado){
    no* novo_no = (no*)malloc(sizeof(no));
    if(novo_no == NULL){
        printf("Erro ao alocar memoria para no!\n");
        exit(0);
    }
    novo_no->id=nmr;
    novo_no->pdado = malloc(tam_dado);
    memcpy(novo_no->pdado, pdado, tam_dado);
    novo_no->next = NULL;
    return novo_no;
}


aresta* cria_aresta(Grafo self, void* pdado, int origem, int destino){
    //cria aresta
    aresta* nova_aresta = (aresta*) malloc(sizeof(aresta));
    if(nova_aresta == NULL){
        printf("Erro ao alocar memoria para aresta!\n");
        exit(0);
    }
    nova_aresta->origem = origem;
    nova_aresta->destino = destino;
    nova_aresta->pdado = malloc(self->tam_aresta);
    memcpy(nova_aresta->pdado, pdado, self->tam_aresta);
    nova_aresta->prox = NULL;

    return nova_aresta;
}   

aresta* busca_aresta(Grafo self, int origem, int destino){
    if(self->n_arestas==0){
        return NULL;
    } else {
        aresta* head = self->arestas;
        while(head != NULL){
            if(head->origem == origem && head->destino == destino){
                return head;
            }
            head = head->prox;
        }
        //nao encontrou a aresta com origem e destino fornecidos
        return NULL;
    }
}

void atualiza_adjacencias(Grafo self, aresta* nova_aresta){
    //1 procura de linha em linha na lista de lista de adjacencias para verificar se o head e o elemento origem
    //2 quando for, percorre essa lista ate encontrar um elemento nulo, a partir dele cria um novo no e insere ali
    for(int i = 0; i < self->n_nos; i++){
        no* head = self->adjacencias[i];
        if(head->id == nova_aresta->origem){//encontrou a sub lista de adjacencia correta
            while(head->next != NULL){
                head = head->next;
            }
            //aqui o head->next eh igual a NULL
            
            //procura pelo no de destino
            no* destino;
            for(int j = 0; j<self->n_nos; j++){
                destino = self->adjacencias[j];
                if(destino->id == nova_aresta->destino){
                    //encontrou o no de destino para aqui
                    break;
                }
            }
            head->next = cria_no(destino->id, destino->pdado, self->tam_no);
        }
    }
}

void insere_aresta_no_grafo(Grafo self, aresta* a_ser_inserida){
    if (self->arestas == NULL) {
        self->arestas = a_ser_inserida;
    } else {
        aresta* a = self->arestas;
        while (a->prox != NULL) {
            a = a->prox;
        }
        a->prox = a_ser_inserida;
    }
    self->n_arestas++;
    atualiza_adjacencias(self, a_ser_inserida);
}

void remove_adjacencia(Grafo self, int origem, int destino){
    for(int i = 0; i < self->n_nos; i++){
        no* atual = self->adjacencias[i];
        if(atual->id == origem){
            //nessa lista que deve ser removido o no destino
            no* anterior = NULL;
            while (atual != NULL) {
                if (atual->id == destino) {
                    if (anterior == NULL) {
                        // O nó a ser removido é o primeiro da lista de adjacência
                        self->adjacencias[i] = atual->next;
                    } else {
                        anterior->next = atual->next;
                    }
                    free(atual->pdado);
                    free(atual);
                    return;
                }
                anterior = atual;
                atual = atual->next;
            }
        }
    }
}

bool existe_no(Grafo self, int id){
    for(int i = 0; i < self->n_nos; i++){
        if(self->adjacencias[i]->id == id){
            return true;
        }
    }
    return false;
}

void remove_aresta(Grafo self, int origem, int destino) {
    aresta* atual = self->arestas;
    aresta* anterior = NULL;

    while (atual != NULL) {
        if (atual->origem == origem && atual->destino == destino) {
            if (anterior == NULL) {
                // Aresta a ser removida é a primeira da lista
                self->arestas = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual->pdado);
            free(atual);
            self->n_arestas--;
            //atualiza a lista de adjacencias 
            remove_adjacencia(self, origem, destino);
            return; // Aresta removida, pode retornar
        }
        anterior = atual;
        atual = atual->prox;
    }
    
}

bool grafo_valor_aresta(Grafo self, int origem, int destino, void *pdado){
    aresta* procurada = busca_aresta(self, origem, destino);
    if(procurada != NULL){
        if(procurada->pdado!=NULL && pdado!=NULL){
            memcpy(pdado, procurada->pdado, self->tam_aresta);
        }
        return true;
    }
    return false;
}


void altera_aresta(Grafo self, int origem, int destino, void *pdado){
    aresta* aresta = busca_aresta(self, origem, destino);
    if(aresta != NULL){
        memcpy(aresta->pdado, pdado, self->tam_aresta);
    }
}

// altera o valor da aresta que interliga o nó origem ao nó destino (copia de *pdado)
// caso a aresta não exista, deve ser criada
// caso pdado seja NULL, a aresta deve ser removida
void grafo_altera_valor_aresta(Grafo self, int origem, int destino, void *pdado){
    aresta* aresta = busca_aresta(self, origem, destino);
    if(aresta == NULL && pdado != NULL){
        //aresta nao existe e precisa ser criada
        if(existe_no(self, origem) && existe_no(self, destino)){
            insere_aresta_no_grafo(self, cria_aresta(self, pdado, origem, destino));
        }
        
    } else if(aresta != NULL && pdado == NULL){//deve remover a aresta 
        remove_aresta(self, origem, destino);
    } else if(aresta != NULL && pdado != NULL){//deve alterar o valor da aresta
        altera_aresta(self, origem, destino, pdado);
    }
}

void printa_arestas(Grafo self){
    aresta* atual = self->arestas;
    while(atual != NULL){
        printf("(%d, %d), peso: %d\n", atual->origem, atual->destino, (*(int*)atual->pdado));
        atual = atual->prox;
    }
}


Grafo grafo_cria(int tam_no, int tam_aresta){

    Grafo g = (Grafo)malloc(sizeof(struct _grafo));
    if(g == NULL){
        printf("Erro ao criar grafo!\n");
        exit(0);
    }
    g->adjacencias=NULL;
    g->arestas=NULL;
    g->tam_aresta= tam_aresta;
    g->tam_no=tam_no;
    g->n_nos=0;
    g->n_arestas = 0;
    g->consulta = NULL;
    return g;
}
Consulta* cria_consulta(int id, void *espaco, size_t tam_espaco) {
    Consulta* nova_consulta = (Consulta*)malloc(sizeof(Consulta));
    if (nova_consulta == NULL) {
        printf("Erro ao alocar memória para consulta!\n");
        exit(-1);
    }
    
    nova_consulta->id = id;
    nova_consulta->espaco = malloc(tam_espaco);
    if (nova_consulta->espaco == NULL) {
        printf("Erro ao alocar memória para espaco!\n");
        free(nova_consulta); // Limpa memória alocada para consulta
        exit(-1);
    }
    memcpy(nova_consulta->espaco, espaco, tam_espaco);
    nova_consulta->prox = NULL;
    
    return nova_consulta;
}

void insere_no_fim(Grafo self, int id, void *espaco) {
    Consulta* nova_consulta = cria_consulta(id, espaco, self->tam_aresta);
    
    if (self->consulta == NULL) {
        self->consulta = nova_consulta;
    } else {
        Consulta* atual = self->consulta;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova_consulta;
    }
}

void remove_primeira_consulta(Grafo self) {
    if (self->consulta == NULL) {
        printf("Lista de consultas vazia!\n");
        return;
    }

    Consulta* temp = self->consulta ;
    self->consulta  = temp->prox;
    free(temp->espaco);
    free(temp);
}

void destruir_consulta(Grafo self) {
    Consulta *atual = self->consulta;
    Consulta *temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp->espaco); // Libera o espaço associado
        free(temp); // Libera a própria consulta
    }
    
    self->consulta = NULL; // Garante que o ponteiro para a lista agora aponta para NULL
}

void destroi_arestas(Grafo self){
    if(self->arestas != NULL){
        aresta* comeco = self->arestas;
        while(comeco != NULL){
            aresta* tmp = comeco;
            comeco = comeco->prox;
            free(tmp->pdado);
            free(tmp);
        }
    }
}

void destroi_adjacencias(Grafo self){
    for(int i = 0; i < self->n_nos; i++){
        no* head = self->adjacencias[i];
        while (head != NULL)
        {
            no* tmp = head;
            head= head->next;
            free(tmp->pdado);
            free(tmp);
        }
    }
    free(self->adjacencias);
}

void grafo_destroi(Grafo self){

    destruir_consulta(self);
    destroi_arestas(self);
    destroi_adjacencias(self);
    free(self);
}

void remove_lista_adjacencia(int index, Grafo self) {
    no* atual = self->adjacencias[index];
    while(atual != NULL) {
        no* tmp = atual;
        atual = atual->next;
        free(tmp->pdado);
        free(tmp);
    }

    for (int i = index; i < self->n_nos - 1; i++) {
        self->adjacencias[i] = self->adjacencias[i + 1];
    }

    self->n_nos--;
    self->adjacencias = (no**)realloc(self->adjacencias, self->n_nos * sizeof(no*));
    printa_grafo(self);
}

void remove_no_adjacente(Grafo self, int id) {
    for (int i = 0; i < self->n_nos; i++) {
        no* atual = self->adjacencias[i];
        no* prev = NULL;
        while (atual != NULL) {
            if (atual->id == id) {
                if (prev == NULL) {
                    self->adjacencias[i] = atual->next;
                } else {
                    prev->next = atual->next;
                }
                no* tmp = atual;
                atual = atual->next;
                free(tmp->pdado);
                free(tmp);
            } else {
                prev = atual;
                atual = atual->next;
            }
        }
    }
}

void remove_aresta_relacionada(Grafo self, int id) {
    aresta* atual_aresta = self->arestas;
    aresta* prev_aresta = NULL;
    while (atual_aresta != NULL) {
        if (atual_aresta->origem == id || atual_aresta->destino == id) {
            if (prev_aresta == NULL) {
                self->arestas = atual_aresta->prox;
            } else {
                prev_aresta->prox = atual_aresta->prox;
            }
            aresta* tmp_aresta = atual_aresta;
            atual_aresta = atual_aresta->prox;
            free(tmp_aresta->pdado);
            free(tmp_aresta);
            self->n_arestas--;
        } else {
            prev_aresta = atual_aresta;
            atual_aresta = atual_aresta->prox;
        }
    }
}

void atualiza_ids_arestas(Grafo self, int id_removid) {
    aresta* atual = self->arestas;
    while (atual != NULL) {
        if(atual->origem>id_removid){
            atual->origem--;
        }
        if(atual->destino>id_removid){
            atual->destino--;
        }
        atual = atual->prox;
    }
}

void atualiza_nos(Grafo self, int id_removido){
    for(int i = id_removido; i < self->n_nos; i ++){
        self->adjacencias[i]->id-=1;
    }
    for(int i = 0; i < self->n_nos; i++){
        no* atual = self->adjacencias[i]->next;
        while(atual != NULL){
            if(atual->id>id_removido){
                atual->id--;
            }
            atual = atual->next;
        }
    }
}

void grafo_remove_no(Grafo self, int id) {
    if(id < self->n_nos){
        remove_lista_adjacencia(id, self);
        remove_no_adjacente(self, id);
        remove_aresta_relacionada(self, id);

        atualiza_nos(self, id);

        // Atualiza as arestas com os novos IDs
        atualiza_ids_arestas(self, id);
    }
}

void grafo_valor_no(Grafo self, int no, void *pdado){
    for(int i = 0 ; i < self->n_nos; i ++){
        if(no == self->adjacencias[i]->id){
            memcpy(pdado, self->adjacencias[i]->pdado, self->tam_no);
        }
    }
}

void grafo_altera_valor_no(Grafo self, int no, void *pdado){
    for(int i = 0; i < self->n_nos; i++){
        struct no* atual = self->adjacencias[i];
        if(atual->id == no){
            memcpy(atual->pdado, pdado, self->tam_no);
        }
        while(atual->next != NULL){
            if(atual->next->id == no){
                memcpy(atual->next->pdado, pdado, self->tam_no);
            }
            atual = atual->next;
        }
    }
}

int grafo_nnos(Grafo self){
    return self->n_nos;
}

void printa_grafo(Grafo self){
    for(int i = 0; i < self->n_nos; i++){
        no* head = self->adjacencias[i];
        while(head != NULL){
            printf("id: %d -> ", head->id);
            head = head->next;  
        }
        printf("\n");
    }
}

// inicia uma consulta a arestas que partem do nó origem
// as próximas chamadas a 'grafo_proxima_aresta' devem retornar os valores correspondentes
//   à cada aresta que parte desse nó
void grafo_arestas_que_partem(Grafo self, int origem){
    destruir_consulta(self);
    aresta* atual = self->arestas;
    if(atual != NULL){
        while(atual != NULL){
            if(atual->origem == origem){
                insere_no_fim(self, atual->destino, atual->pdado);
            } 
            atual = atual->prox;
        }
    }
}

// inicia uma consulta a arestas que chegam ao nó destino
// as próximas chamadas a 'grafo_proxima_aresta' devem retornar os valores correspondentes
//   à cada aresta que chega nesse nó
void grafo_arestas_que_chegam(Grafo self, int destino){
    destruir_consulta(self);
    aresta* atual = self->arestas;
    if(atual != NULL){
        while(atual != NULL){
            if(atual->destino == destino){
                insere_no_fim(self, atual->origem, atual->pdado);
            } 
            atual = atual->prox;
        }
    }
}

bool consultas_vazias(Grafo self){
    return self->consulta == NULL;
}

// retorna a próxima aresta, de acordo com a última consulta iniciada por 
//   'grafo_arestas_que_partem' ou 'grafo_arestas_que_chegam'
// o valor do nó vizinho ao nó da consulta deve ser colocado em 'vizinho' (se não for NULL),
//   o valor associado à aresta deve ser colocado em '*pdado' (se não for NULL) e a função
//   deve retornar true. Caso não exista mais aresta que satisfaça a consulta, retorna
//   false.


bool grafo_proxima_aresta(Grafo self, int *vizinho, void *pdado) {
    if(consultas_vazias(self)){
        return false;
    } else {
        *vizinho = self->consulta->id;
        if(pdado!=NULL){
            memmove(pdado, self->consulta->espaco, self->tam_aresta);
        }
        remove_primeira_consulta(self);
        return true;
    }
}


int grafo_insere_no(Grafo self, void* pdado) {

    self->adjacencias = (no**)realloc(self->adjacencias, (self->n_nos + 1) * sizeof(no*));
    if (self->adjacencias == NULL) {
        printf("Erro ao realocar memoria para lista de adjacencias!\n");
        exit(0);
    }
    self->adjacencias[self->n_nos] = cria_no(self->n_nos, pdado, self->tam_no);
    self->n_nos++;
    return self->n_nos - 1;
}

bool grafo_tem_ciclo(Grafo self)
{
  // inicializa um vetor com o grau de entrada dos nós
  int ge[self->n_nos];
  //get_vetor_com_posicoes_corretas(self, ge);

  for (int no=0; no<self->n_nos; no++) {
        ge[no] = 0;
        // incrementa o GE do nó para cada aresta que chega nele
        grafo_arestas_que_chegam(self, no);
        int vizinho;
        while(grafo_proxima_aresta(self, &vizinho, NULL)){
            ge[no]++;
        }
  }
  // inicializa uma fila com todos os nós que têm GE 0 (isso poderia ser feito no final do segundo for acima)
  Fila f = fila_cria(sizeof(int));
  for (int no=0; no<self->n_nos; no++) {
    if (ge[no] == 0) {
      fila_insere(f, &no);
    }
  }
  int analisados = 0;  // conta o número de nós analisados (que têm GE 0)
  while (!fila_vazia(f)) {
    int no;
    fila_remove(f, &no);
    // Inicia uma consulta para arestas que partem do nó atual
        grafo_arestas_que_partem(self, no);

        // Decrementa o grau de entrada de cada nó destino de uma aresta que parte do nó analisado
        // Insere na fila se o grau de entrada ficou 0
        int vizinho;
        while (grafo_proxima_aresta(self, &vizinho, NULL)) {
            ge[vizinho]--;
            if (ge[vizinho] == 0) {
                fila_insere(f, &vizinho);
            }
        }
    analisados++;
  }
  fila_destroi(f);
  // se todos os nós foram analisados, o grafo é acíclico.
  return !(analisados == self->n_nos);
}

// retorna uma fila contendo os números dos nós do grafo em uma ordem em que, se o nó 'a'
//   antecede 'b', não existe uma aresta de 'b' para 'a' no grafo
// deve retornar uma fila vazia caso tal ordem não exista
// quem chama esta função é responsável por destruir a fila.
Fila grafo_ordem_topologica(Grafo self){
    // inicializa um vetor com o grau de entrada dos nós
  int ge[self->n_nos];
  //get_vetor_com_posicoes_corretas(self, ge);

  for (int no=0; no<self->n_nos; no++) {
        ge[no] = 0;
        // incrementa o GE do nó para cada aresta que chega nele
        grafo_arestas_que_chegam(self, no);
        int vizinho;
        while(grafo_proxima_aresta(self, &vizinho, NULL)){
            ge[no]++;
        }
    }
  // inicializa uma fila com todos os nós que têm GE 0
  Fila f = fila_cria(sizeof(int));
  for (int no=0; no<self->n_nos; no++) {
    if (ge[no] == 0) {
      fila_insere(f, &no);
    }
  }
  // inicializa uma fila que conterá os nós em ordem topológica
  Fila ordem = fila_cria(sizeof(int));
  int ordenados = 0;  // conta o número de nós na fila ordem
  while (!fila_vazia(f)) {
    int no;
    fila_remove(f, &no);
    // decrementa o GE de cada nó destino de uma aresta que parte do nó analisado
    // insere na fila se o GE ficou 0
    grafo_arestas_que_partem(self, no);

        // Decrementa o grau de entrada de cada nó destino de uma aresta que parte do nó analisado
        // Insere na fila se o grau de entrada ficou 0
        int vizinho;
        while (grafo_proxima_aresta(self, &vizinho, NULL)) {
            ge[vizinho]--;
            if (ge[vizinho] == 0) {
                fila_insere(f, &vizinho);
            }
        }
    fila_insere(ordem, &no);
    ordenados++;
  }
  fila_destroi(f);
  if (ordenados != self->n_nos) {
    // o grafo tem ciclo, não tem ordem topológica
    
  }
  return ordem;
}