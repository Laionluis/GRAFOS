Esse trabalho foi feito em C, utilizando-se da biblioteca Graphviz.

Nosso programa funciona do seguinte modo:
1-No main é feito a leitura do grafo usando o stdin, e após isso é executada a função preencheTudo para cada vértice do grafo.
2-Na função preencheTudo existem 2 casos de vértices que são analisados: Vértice com atributo(s) e Vértice sem atributo(s).
2.1-Caso o vértice possua atributos, eles são colocados em uma lista que é retornada.
2.2-Caso o vértice não possua atributos, ele entra recursivamente na função com seus filhos (1 de cada vez).
2.2.1-Após entrar na recursão pode ocorrer o caso 2.1 ou 2.2 novamente.
2.2.2-Quando finalmente ocorrer o caso 2.1 em todos seus filhos, o vértice vai ter todos os caminhos possíveis.
2.2.3-E após isso ele gera uma lista com esses atributos gerados, para um nível de recursão acima, ou para o main.
3-Após a execução do for no main, todos os vértices teram sido checados e portanto ocorrerá a impressão utilizando agwrite, com o stdout de saída.

Caso precise de mais informações, o código possui alguns comentários que podem ajudar.
