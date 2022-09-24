<h1 align="center">Compactação de Texto com Código de Huffman</h1>

<h2>1 - Introdução</h2>

<p align=justify>
  O Código de Huffman é uma estrutura que tem como base a construção de uma Árvore Binária - chamada de Árvore de Huffman<code>(AH)</code> -  em que todos os nós-folhas são caracters ou palavras. Cada uma destas palavras recebe uma codificação binária (por bits) conforme sua localização na Árvore. Essa codificação é feita ao caminhar da raíz até a folha e pegando as posições: <code>Para a direita = 1</code> e <code>Para a esquerda = 0</code>. Supondo que a palavra <code>Apple</code> recebá a codificação <code>1101</code>. Isso significa que, partindo da raíz e ao caminhar para o filho direito duas vezes consecutivas e em seguida caminhar uma vez para o filho esquerdo e novamente caminhar para filho esquerdo, tem-se a palavra <code>Apple</code>. 
</p>

<h3>1.1 - Compressão de Texto</h3>

<p align=justify>
  Seguinda a codificação a cima podemos perceber que quanto mais proximo da raíz, menor será a quantidade de bits necessária para representar o caracter ou palavra. Tendo isso em mente, é possível usar o algoritmo de Huffman para compactar textos, sendo necessário apenas ordenar de forma crescente a entrada conforme sua frequência-relativa no texto. Ou seja, ao montar a AH com as entradas já ordenadas, as palavras ou caracters de maior relevância ficaram mais próximos da raíz e portando receberão uma menor quantidade de bits como representação.<br>
  Já a descompactação do texto é feita da maneira inversa. Pega-se cada bit e conforme o seu valor <code> 0 ou 1</code>, se caminha na AH até encontrar um caracter ou palavra. Fazendo isso até todo o arquivo escrito apernas em bits, tem-se o texto novamente.
</p>

<h2>2 - Como foi feito?</h2>

<p align="justify">
  O Código de Huffman implementado neste repositório tokeniza palavras e é divido em 6 etapas:
</p>

<h3>2.1 - Etapa 1</h3>

<p align="justify">
  Foi utilizado um <code>Map</code> chamado <code>Umap</code> que recebe cada palavra ao tokenizar o texto. A cada vez que uma palavra aparece novamente é incrementado <code>+1</code> em sua frequência. Além disso, a cada palavra que é inserida ou incremetada em sua frequência é contabilizado <code>+1</code> no contador total de palavras<br>
</p>

<h3>2.2 - Etapa 2</h3>

<p align="justify">
  A etapa 2, consiste em percorrer todo o <code>Umap</code> da etapa 1, criar um nó para cada posição deste Map com a palavra e sua respectiva frequência. Em seguida, este nó é inserido em um vetor de nós, chamado de <code>florest</code>.
</p>
