## Descrição e informações relevantes:

O programa tem como objetivo ler uma matriz em um arquivo de texto (.txt) e retornar algumas informações de acordo com o exercício proposto.

### Resumo do exercício proposto:

A Matriz é a leitura de uma área plana oceânica poluída com ilhas de lixo flutuantes. Cada casa (i,j) da matriz representa um ㎡ de mar sendo que, se a posição estiver ocupada com o elemento "0", infere-se que não há lixo no respectivo ㎡, 
caso contrário, o elemento será igual ou maior que 1 e tal número representará a altura do lixo naquele espaço.

Elementos diferentes de 0 encontrados lado a lado verticalmente ou horizontalmente (não em diagonal) são pertencentes à mesma ilha de lixo, se forem separados por casas ocupadas por zeros são ilhas diferentes.

O lixo deverá ser transportado num container de base = 6㎡, mas de altura variável em função da entrada para o programa.

**O programa deve retornar:**
- A quantidade de ilhas de lixo encontradas na matriz
- As profundidades correspondentes a cada ilha, separadas por espaço (que é dada pelo somatório das alturas de uma mesma ilha dividida por 6)
- Uma combinação de profundidades que, somadas, resultam na profundidade exata do contêiner (caso não houver tal soma, imprime-se "Nao ha resposta valida!")

## Modo de executar via terminal:

 $ ./EXECUTAVEL <profundidade_container> <linhas_da_matriz> <colunas_da_matriz> ExemploAreaScaneada.txt
 
 (no caso do exemplo, <linhas_da_matriz> = 3, <colunas_da_matriz> = 7)

 Caso queira fazer alterações no código e usar outrous arquivos txt contendo outras matrizes, compile usando:
 $ gcc <Seu_Codigo>.c -o <Executavel>
 
 (lembre-se de separar os elementos da matriz com espaços e colocar o número certo de linhas e colunas representadas no arquivo de texto)

## Outras considerações:
Este, até então, não é um algoritmo **ótimo**, portanto sinta-se à vontade para usar fork e utiliza-lo como exercício de programação
