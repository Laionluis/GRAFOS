#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

typedef struct attList{
    char name[64];
    int number;
} attList;

attList* preencheTudo(Agraph_t* graph, Agnode_t* node);

attList* preencheTudo(Agraph_t* graph, Agnode_t* node){
    int i;
    long unsigned int alloc;
    int verify;
    char str[8];
    attList* list;
    Agsym_t* attribute;
    Agedge_t* edge;

    alloc = 128;
    list = (attList*) calloc(alloc, sizeof(attList));
    if(list == NULL){
        exit(1);
    }

    i = 0;
    verify = 0;

    //Verifica se o vertice ja possui algum atributo
    //E se possuir, coloca em uma lista
    for(attribute = agnxtattr(graph, AGNODE, NULL); attribute; attribute = agnxtattr(graph, AGNODE, attribute) ){
        if(atoi(agxget(node, attribute)) >= 1){
            strcpy(list[i].name, attribute->name);
            list[i].number = atoi(agxget(node, attribute));
            verify = 1;
            i++;
            if(i % (int) alloc == 0){
                alloc += alloc;
                list = (attList*) realloc(list, alloc*sizeof(attList));
            }
        }
    }

    //Caso o vertice nao tenha nenhum atributo, ele entra aqui
    if(verify == 0){
        free(list);
        //Nesse for, ele vai descendo por recursao em seus descendentes ate
        //achar algum que ja possua atributo, e com isso esses atributos sao passados para cima
        for(edge = agfstout(graph, node); edge ; edge = agnxtout(graph, edge)){
            list = preencheTudo(graph, edge->node);
            i = 0;
            while(list[i].number != 0){
                attribute = agattrsym(node, list[i].name);
                if(attribute){
                    list[i].number += atoi(agxget(node, attribute));
                }
                sprintf(str, "%d", list[i].number);
                agset(node, list[i].name, str);
                i++;
            }
            free(list);
        }

        //Apos ter verificado todos os filhos, esse segundo for junta tudo em uma lista
        //e manda para cima, caso tenha sido um vertice que chamou a funcao e nao o main
        list = (attList*) calloc(alloc, sizeof(attList));
        i = 0;
        for(attribute = agnxtattr(graph, AGNODE, NULL); attribute; attribute = agnxtattr(graph, AGNODE, attribute) ){
            if(atoi(agxget(node, attribute)) >= 1){
                strcpy(list[i].name, attribute->name);
                list[i].number = atoi(agxget(node, attribute));
                i++;
                if(i % (int) alloc == 0){
                    alloc += alloc;
                    list = (attList*) realloc(list, alloc*sizeof(attList));
                }
            }
        }
    }

    return list;
}

int main(void){

    attList* list;
    Agraph_t* graph = agread(stdin, NULL);

    //For em todos os vertices ate que todos estejam preenchidos
    for (Agnode_t* node = agfstnode(graph); node; node = agnxtnode(graph, node)){
        list = preencheTudo(graph, node);
        if(list != NULL){
            free(list);
        }
    }

    agwrite(graph, stdout);
    
    return 0;
}