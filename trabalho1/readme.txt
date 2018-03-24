Para gerar todas as configurações do jogo da velha, implementei um algoritmo que,
dado a configuracao inicial, o programa faz a jogada com 'X', e depois para 'O', 
e "recursivamente" faz todas as possibilidade, para cada jogada ele faz todas as
possibilidades de jogadas possiveis, terminando quando da empate ou alguem ganha.
Para cada chamada de função escreve em um arquivo a configuração com um '->', 
e quando faz a jogada(colocando 'X' ou 'O') escreve no lado a configuração "jogada",
o '->' significa que vai dessa para outra configuração, que na linguagem dot serve
para demonstrar os arcos de um grafo direcionado.