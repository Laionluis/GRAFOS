#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/cgraph.h>

//estrutura da fila dos atributos
struct Node{
    char *nome_atributo;
    int numero;
    struct Node *prox;
};
typedef struct Node node;
int tam;

void inicia(node *FILA);
int vazia(node *FILA);
node *aloca(char *atri);
void insere(node *FILA,char *atri);
node *retira(node *FILA);
void modifica_atributo(node *FILA, char *atri);
void caminhos(Agraph_t *g, Agnode_t* v,node *FILA);

int main(void) 
{
    int verifica;

    Agraph_t *g = agread(stdin, NULL);

    Agnode_t* n0;
    Agedge_t* e;

    //para cada vertice do grafo verifica se tem atributos, se tiver
    //é um sumidouro e nao chama a funcao que conta os caminhos
    //se nao for sumidouro, para cada filho chama a funcao que conta 
    //recursivamente quantos caminhos tem até o sumidouro
    for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g,n))
    {
        //fila para os atributos
        node *FILA = (node *) malloc(sizeof(node));
        inicia(FILA);
        printf("%s\n", agnameof(n) );
        verifica = 0;
            for (Agsym_t *atributo=agnxtattr(g,AGNODE,NULL); 
            atributo; 
            atributo=agnxtattr(g,AGNODE,atributo))
            {
                //se o vertice contem atributo, significa que eh sumidouro
                if(strcmp (agxget(n, atributo), "1") == 0)
                {
                    verifica = 1;
                }
                //insere o atributo na fila de atributos
                insere(FILA,atributo->name);
            }
    
        for(e = agfstout(g,n); e ; e= agnxtout(g,e))
        {
            n0 = e->node;
            printf("o%s\n",agnameof(e->node)  );
            if(verifica == 0)
            {
                caminhos(g,n0,FILA);
            }  
        }
        //adiciona os atributos, se nao for sumidouro
        if(verifica == 0)
        {
            //cria_grafo(FILA,n,aux,arq);
                node *tmp;
                tmp = FILA->prox;
                while(tmp != NULL)
                {
                    char *str ;
                    str = malloc(16);
                    snprintf(str, 16, "%d", tmp->numero); //transforma int para char*
                    agset(n,tmp->nome_atributo,str);
                    tmp = tmp->prox;
                }
        }  
        free(FILA);
    }

    //funcao que mostra na saida padrao o grafo em dot com os atributo 
    //certos para cada vertice
    agwrite(g, stdout);
    agclose(g);
    return 0;
}

//funcao recursiva para contar os caminhos
void caminhos(Agraph_t *g,Agnode_t* v,node *FILA)
{
    int verifica;
    Agedge_t* e;
    Agedge_t* e1;
    Agnode_t* n0;

    //Caso o vertice mandado ja é um sumidouro ele faz a conta 
    /////////////
    for (Agsym_t *atributo=agnxtattr(g,AGNODE,NULL); 
            atributo; 
            atributo=agnxtattr(g,AGNODE,atributo))
            {
                //printf(" %s=\'%s\'", atributo->name, agxget(v, atributo));
                //se o vertice contem atributo, significa que eh sumidouro
                if(strcmp (agxget(v, atributo), "1") == 0)
                {
                    //procura na fila o atributo e soma +
                    //conta +1 no nome do atributoo
                    printf("oi eu so sumidouro\n");
                    modifica_atributo(FILA,atributo->name);
                }
            }
    /////////////////

    for(e = agfstout(g,v); e ; e= agnxtout(g,e))
    {
        verifica = 0;
                    printf("oo%s\n",agnameof(e->node)  );

        for (Agsym_t *atributo=agnxtattr(g,AGNODE,NULL); 
            atributo; 
            atributo=agnxtattr(g,AGNODE,atributo))
            {
                //printf(" %s=\'%s\'", atributo->name, agxget(v, atributo));
                //se o vertice contem atributo, significa que eh sumidouro
                if(strcmp (agxget(e->node, atributo), "1") == 0)
                {
                    verifica = 1;
                }
                if(strcmp (agxget(e->node, atributo), "1") == 0)
                {
                    //conta +1 no nome do atributoo
                    modifica_atributo(FILA,atributo->name);
                }
            }
        
        //para cada "filho faz a mesma coisa, recursivamente"
        for(e1 = agfstout(g,e->node); e1 ; e1= agnxtout(g,e1))
        {
            n0 = e1->node;
            if(verifica == 0)
            {
                caminhos(g,n0,FILA);
            }  
        }
    }
    return;
}

void modifica_atributo(node *FILA, char *atri)
{
    node *tmp;
    tmp = FILA->prox;
    while( tmp != NULL)
    {
        if(strcmp (tmp->nome_atributo, atri) == 0){
            tmp->numero++;
        }
        tmp = tmp->prox;
    }
}

void inicia(node *FILA)
{
    FILA->prox = NULL;
    tam=0;
}
    
int vazia(node *FILA)
{
    if(FILA->prox == NULL)
        return 1;
    else
        return 0;
}

node *aloca(char *atri)
{
    node *novo=(node *) malloc(sizeof(node));
    if(!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }else
    {
        novo->nome_atributo = atri;
        novo->numero = 0;
        return novo;
    }
}

void insere(node *FILA,char *atri)
{
    node *novo=aloca(atri);
    novo->prox = NULL;

    if(vazia(FILA))
        FILA->prox=novo;
    else
    {
        node *tmp = FILA->prox;

        while(tmp->prox != NULL)
          tmp = tmp->prox;

        tmp->prox = novo;
    }
    tam++;
}

node *retira(node *FILA)
{
    if(FILA->prox == NULL)
    {
        printf("Fila ja esta vazia\n");
        return NULL;
    }else
    {
        node *tmp = FILA->prox;
        FILA->prox = tmp->prox;
        tam--;
        return tmp;
    }
}

