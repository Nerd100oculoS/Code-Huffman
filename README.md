<h1 align="center">Compactação de Texto com Código de Huffman</h1>

<h2 id="1">1 - Introdução</h2>

<p align=justify>
  O Código de Huffman é uma estrutura que tem como base a construção de uma Árvore Binária - chamada de Árvore de Huffman<code>(AH)</code> -  em que todos os nós-folhas são caracters ou palavras. Cada uma destas palavras recebe uma codificação binária (por bits) conforme sua localização na Árvore. Essa codificação é feita ao caminhar da raíz até a folha e pegando as posições: <code>Para a direita = 1</code> e <code>Para a esquerda = 0</code>. Supondo que a palavra <code>Apple</code> recebá a codificação <code>1101</code>. Isso significa que, partindo da raíz e ao caminhar para o filho direito duas vezes consecutivas e em seguida caminhar uma vez para o filho esquerdo e novamente caminhar para filho direito, tem-se a palavra <code>Apple</code>. 
</p>

<h3>1.1 - Compressão de Texto</h3>

<p align=justify>
  Seguindo a codificação a cima podemos perceber que quanto mais proximo da raíz, menor será a quantidade de bits necessária para representar o caracter ou palavra. Tendo isso em mente, é possível usar o algoritmo de Huffman para compactar textos, sendo necessário apenas ordenar de forma crescente a entrada de caracters ou palavras conforme sua frequência-relativa no texto. Ou seja, ao montar a AH com as entradas já ordenadas, as palavras ou caracters de maior relevância ficaram mais próximos da raíz e portando receberão uma menor quantidade de bits como representação.<br>
  Já a descompactação do texto é feita da maneira inversa. Pega-se cada bit e conforme o seu valor <code> 0 ou 1</code>, se caminha na AH até encontrar um caracter ou palavra. Fazendo isso até todo o arquivo escrito apernas em bits, tem-se o texto novamente.
</p>

<h2>2 - Como foi feito?</h2>

<p align="justify">
  O Código de Huffman implementado neste repositório tokeniza palavras e é divido em 6 etapas:
</p>

<h3>2.1 - Etapa 1</h3>

<p align="justify">
  Foi utilizado um <code>Map</code> chamado <code>Umap</code> que recebe cada palavra ao tokenizar o arquivo de texto. A cada vez que uma palavra aparece novamente é incrementado <code>+1</code> em sua frequência. Além disso, a cada palavra que é inserida ou incremetada em sua frequência é contabilizado <code>+1</code> no contador total de palavras<br>
</p>

<h3>2.2 - Etapa 2</h3>

<p align="justify">
  A etapa 2, consiste em percorrer todo o <code>Umap</code> da etapa 1, criar um nó para cada posição deste Map com a palavra e sua respectiva frequência. Em seguida, este nó é inserido em um vetor de nós, chamado de <code>florest</code>.
</p>

<h3>2.3 - Etapa 3</h3>

<p align="justify">
  Nesta etapa, faz-se a ordenação do vetor <code>florest</code> de forma crescente, por meio da frequência de cada nó. Em seguida, faz-se a normalização da frequência de cada nó pela fórmula <code>(Fr-nó/total-palavras)</code> - Frequência da palavra, divido pelo total de palavras do texto. Após fazer estas duas pequenas partes, ainda nesta etapa, é montada a <code>(AH)</code> por uma função recursiva que cria um novo nó e insere os dois primeiros nós do vetor <code>florest</code> como filho esquerdo e direito respectivamente, uma vez que o vetor de nós ja se encontra ordenado. Este novo nó é inserido novamente em <code>florest</code> e é feita a chamada recursiva novamente até que sobre apenas um único nó neste vetor - que será a Árvore de Huffman. Por fim, obtem-se a <code>(AH)</code>.
</p>

<h3>2.4 - Etapa 4</h3>

<p align="justify">
  Agora, com a Árvore de Huffman ja construída, é construído um novo <code>Map</code> chamado <code>CodTable</code> - responsável por armazenas como chave a palavra e como valor sua codificação em bits. Assim, é feito o caminhamento partido de sua raíz, de acordo com a explicação do <a href="#1"> tópico 1</a>. Quando chegar em um nó folha, no qual estará a palavra, insere a palavra e a sua codificação em bits na <code>CodTable</code>.
</p>

<h3>2.5 - Etapa 5</h3>

<p align="justify">
  A etapa 5 é a codificação do arquivo texto. Primeiro o arquivo será tokenizado palavra por palavra e a cada palavra tokenizada é feito sua busca em  <code>CodTable</code>, assim que a palavra é encontrada, sua respectiva codificação é escrita em um outro arquivo de texto que será o arquivo codificado. É feito todo este processo até que a leitura de tokenização do arquivo de texto tenha acabado. Todos os dois arquivos referentes a esta etapa estão presentes na pasta <code>src/input</code>.
</p>

<h3>2.6 - Etapa 6</h3>

<p align="justify">
  Por fim, a 6ª e última etapa, se trata da decodificação do arquivo de texto codificado na etapa anterior. Faz-se a leitura do arquivo codificado, tokeniza bit a bit e conforme as regras de caminhamento do <a href="1"> tópico 1</a>, caminha-se a cada bit na Árvore de Huffman até encontrar o nó folha, onde se encontra a palavra. O processo continua até ter decodificado todo o arquivo. Durante a decodificação, cada palavra encontrada na <code>(AH)</code> é inserida em um novo arquivo de texto presente na pasta <code>src/output</code>.
</p>

![Captura de Tela 2022-09-23 às 22 33 47](https://user-images.githubusercontent.com/103065659/192074555-23f7396a-6e9a-4f70-98f0-9c8d6c20f09a.png)
<p align="right"> Função main da implementação.</p>

<h2>3 - Observações e Considerações Finais</h2>

<p align="justify">
  <li>
    Quando a contabilização de todas as frequências gera um desvio-padrão baixo, a compactação é mínima ou quase não a compactação com relação a tamanho do arquivo de texto.
  </li>
  <li>
    Não foi constatado nenhuma diminuição do arquivo codificado. Uma possível causa pode ser, o formato <code>.txt</code> do arquivo codificado.
  </li>
</p>

<h2>4 - Compilação e Execução</h2>
  
  | Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
