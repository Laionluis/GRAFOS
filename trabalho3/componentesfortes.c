#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

//usar records do cgraph para "marcar" os vertices
typedef struct nodes{
    Agrec_t h;
    int estado;
    int pre;
    int pro;
} nodes;

//stack para pegar os vertices
typedef struct stack{
    Agnode_t *n;
    struct stack *next;
} stack;
stack *top = NULL;

void BuscaProfundidade(Agraph_t* graph);
void DFS_Recursivo(Agraph_t* graph,Agnode_t* node, int *t,nodes *data);
Agraph_t* InverterGrafo(Agraph_t* graph);
void ComponentesFortementeConexos(Agraph_t* graph,Agraph_t* graph1);
void Decompoe(Agraph_t* graph,Agraph_t* graph1,Agnode_t* node,int *t,nodes *data,int *cont);
void push(Agnode_t *n);

//empilha
void push(Agnode_t *item){
    stack *temp = malloc(sizeof(stack));
    temp->n = item;
    temp->next = top;
    top = temp;
}

//faz busca em profundidade e vai add vertices na stack
void BuscaProfundidade(Agraph_t* graph){
	int t = 0; //pre/pro
	char temp[6];
	strcpy(temp,"nodes");

	nodes *data;
	// definir todos vertices como nao visitado
	for (Agnode_t* node = agfstnode(graph); node; node = agnxtnode(graph, node))	{ 
		data = (nodes*)agbindrec(node,temp,sizeof(nodes),FALSE); //agbindrec adiciona os dados no node
		data->estado=0;
	}

	nodes *data2;
	// para cada vertice fazer a busca
	for (Agnode_t* node = agfstnode(graph); node; node = agnxtnode(graph, node))	{
		data2 = (nodes*)aggetrec(node,temp,1); //aggetrec pega os dados do node
		if(data2->estado == 0){
			DFS_Recursivo(graph,node,&t,data2);
		}			
	}
}

void DFS_Recursivo(Agraph_t* graph,Agnode_t* node,int *t,nodes *data){
	Agedge_t* edge;
	data->estado = 1;
	data->pre = ++(*t);

	char temp[6];
	strcpy(temp,"nodes");
	nodes *data2;
	//para cada descendente de node
	for(edge = agfstout(graph, node); edge ; edge = agnxtout(graph, edge)){
		data2 = (nodes*)aggetrec(edge->node,temp,1); //aggetrec pega os dados do node
		if(data2->estado == 0){
			DFS_Recursivo(graph,edge->node,t,data2);
		}
	}
	data->estado = 2;
	data->pro = ++(*t);
	push(node);
}

Agraph_t* InverterGrafo(Agraph_t *g){
	char temp0[10];
	strcpy(temp0,"resultado");
	Agraph_t* graph_invertido;
	graph_invertido = agopen(temp0, g->desc, NULL);
	Agnode_t *n;
	Agnode_t *u, *v;
	Agedge_t *e,*e1;

	for (n = agfstnode(g); n; n = agnxtnode(g,n)){
		for (e = agfstout(g,n); e; e = agnxtout(g,e)){
			u = agnode(graph_invertido,agnameof(n),TRUE);
			v = agnode(graph_invertido,agnameof(e->node),TRUE);
			e1 = agedge(graph_invertido,v,u,NULL,TRUE);
		}
	}

	return graph_invertido;
}

//vai fazer outra busca em profundidade no grafo transposto, primeiramente define os vertices como nao visitados
//depois, faz a busca a partir dos vertices da stack
void ComponentesFortementeConexos(Agraph_t* graph,Agraph_t* graph1){
	int cont = 0;
	int t = 0; //pre/pro
	char temp[6];
	strcpy(temp,"nodes");

	nodes *data;
	// definir todos vertices como nao visitado
	for (Agnode_t* node = agfstnode(graph); node; node = agnxtnode(graph, node)){ 
		data = (nodes*)agbindrec(node,temp,sizeof(nodes),FALSE); //agbindrec adiciona os dados no node
		data->estado=0;
	}

	nodes *data2;
	stack *aux;
    aux = top;
	//aqui vai achar os componentes fortemente conexos
    //vai retirar da stack cada vertice para começar a busca em profundidade
    while (aux != NULL){
    	Agnode_t* n = agnode(graph,agnameof(aux->n),FALSE); //pega vertice do grafo invertido com mesmo nome do vertice da stack
      	data2 = (nodes*)aggetrec(n,temp,1); //aggetrec pega os dados do node
		if(data2->estado == 0){
			++(cont);  //para definir os nomes dos subgrafos
			Decompoe(graph,graph1,n,&t,data2,&cont);
		}			
		aux = aux->next;
    }
}

//aqui define os componentes fortemente conexos do grafo
void Decompoe(Agraph_t* graph,Agraph_t* graph1,Agnode_t* node,int *t,nodes *data,int *cont)
{
	Agraph_t* h;
	Agedge_t* edge;
	data->estado = 1;
	data->pre = ++(*t);

	//cria os subgrafos
	char temp1[100];
	strcpy(temp1,"cluster");
	sprintf(temp1, "cluster%d", *cont);
	h = agsubg(graph1,temp1,TRUE);
	Agnode_t *n;
	n = agnode(h,agnameof(node),TRUE);

	char temp[6];
	strcpy(temp,"nodes");
	nodes *data2;
	//para cada descendente de node
	for(edge = agfstout(graph, node); edge ; edge = agnxtout(graph, edge))
	{
		data2 = (nodes*)aggetrec(edge->node,temp,1); //aggetrec pega os dados do node
		if(data2->estado == 0){
			Decompoe(graph,graph1,edge->node,t,data2,cont);
		}
	}
	data->pro = ++(*t);
}

int main(void)
{
	Agraph_t* graph = agread(stdin, NULL);
	BuscaProfundidade(graph);
	char temp0[10];
	strcpy(temp0,"resultado");
	Agraph_t* graph_t = agopen(temp0, graph->desc, NULL);;
	graph_t = InverterGrafo(graph);
	ComponentesFortementeConexos(graph_t,graph);
	agwrite(graph,stdout);
	return 0;
}


