# Cálculo da Série de Taylor usando OpenMP

Este projeto foi desenvolvido por Marina Martin, como parte dda matéria de computação paralela feita na UPM, curso de ciências da computação.

## Descrição

O objetivo deste projeto é calcular a soma da série de Taylor para a função exponencial usando o OpenMP para paralelizar o cálculo. A série de Taylor é uma representação de uma função como uma soma infinita de termos, onde cada termo é calculado a partir das derivadas da função em um ponto específico.

O código em C utiliza a biblioteca OpenMP para dividir o cálculo da série de Taylor entre várias threads, aproveitando o paralelismo para acelerar o processamento.

Compilação e Execução
Para compilar o código, certifique-se de ter um compilador C com suporte a OpenMP instalado em seu sistema. Em sistemas baseados em Debian/Ubuntu, você pode instalar o OpenMP usando o seguinte comando:

sudo apt-get install libgomp1
Para compilar o código, use o seguinte comando:

gcc -fopenmp nome_do_arquivo.c -o nome_do_executavel
Substitua "nome_do_arquivo.c" pelo nome do arquivo de código-fonte e "nome_do_executavel" pelo nome desejado para o arquivo executável.

Para executar o programa, use o seguinte comando:

./nome_do_executavel
O programa calculará a soma da série de Taylor com o número de termos especificado e exibirá o resultado na tela.

## Funcionamento do Código

O código segue os seguintes passos:

1. Definição do número de termos da série de Taylor (N) e inicialização da variável de soma (soma).

2. Criação de uma região paralela usando a diretiva `#pragma omp parallel`.

3. Dentro da região paralela, cada thread obtém seu identificador único (thread_id) e o número total de threads (num_threads).

4. Cada thread possui uma variável local (soma_local) para acumular sua própria soma parcial.

5. O loop principal é dividido entre as threads usando a diretiva `#pragma omp for schedule(static)`. Cada thread calcula uma parte dos termos da série de Taylor e acumula o resultado em sua variável local (soma_local).

6. Após o loop paralelo, as somas parciais de cada thread são somadas na variável global (soma) usando a diretiva `#pragma omp critical` para evitar condições de corrida.

7. Por fim, o resultado da soma da série de Taylor é impresso na tela.

## Considerações Finais

Este projeto demonstra o uso do OpenMP para paralelizar o cálculo da série de Taylor, aproveitando o poder de processamento de múltiplos núcleos de CPU. O OpenMP simplifica a programação paralela, permitindo que o código seja dividido em regiões paralelas e distribuindo o trabalho entre as threads disponíveis.

