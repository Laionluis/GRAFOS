Para esse trabalho foi escolhida a linguagem c, e foi feita o uso da biblioteca cgraph.
Primeiramente o programa lê o dot e transforma em um grafo com a funcao agread();
E com o uso das funcoes agfstnode(g) e agnxtnode(g,n) há um for que percorre todos os vertices do grafo em ordem;
Dentro desse for há um loop que percorre os atributos do grafo e adiciona cada um em uma fila(nome atributo, valor) e tambem 
verifica se o vértice é sumidouro;
Depois desse loop há outro loop para percorrer os filhos do vertice atual, usando as funcoes agfstout() e agnxtout(), que 
basicamente pega as arestas conectadas ao vertice atual, e entao usando aresta->node pega o filho do vertice.
Para cada um desses filhos é chamada uma funcao chamada caminhos(): nessa funcao ha um loop que percorre os filho do vertice
mandado e vai fazendo isso até chegar nos sumidouros, se o vertice mandado para a funcao for sumidouro ele procura na fila dos 
atributos do vertice atual o atributo do sumidouro e incrementa o valor, "contando os caminhos".Essa funcao faz isso 
recursivamente para todos os filhos do vertice mandado.
Quando termina de contar para todos os filhos do vertice atual, ha um loop que percorre a fila de atributos do vertice, e para
atributo ele adiciona esse atributo ao grafo, usando a funcao agset().
E faz isso tudo para cada vertice, contando os caminhos até os sumidouros.
No final é usado a funcao agwrite que imprime o grafo em formtato dot na saida padrao com todos os vertices setados com seus
atributos e valores corretos;

Unico problema nisso é que ele nao imprime os vertices em ordem igual ta na pagina da especificacao do trabalho, acho que é por 
causa que o programa esta setando os atributos no for para cada vertice, mas como no email disseram que pode ser em qualquer 
ordem entao acho que nao tem muito problema nisso. E tambem na saida padrao, quebra a linha em cada virgula dos atributos, 
pensamos em fazer a leitura e escrita sem usar as funcoes da biblioteca, porem nao tivemos tempo e o codigo ficaria muito mais 
"cheio".

