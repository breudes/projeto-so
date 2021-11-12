<p align="center">
  <a href="#sobre">Sobre</a> –
  <a href="#como-rodar">Como rodar?</a> –
  <a href="#autoras">Autoras</a>
</p>

## Sobre
Projeto desenvolvido para a Unidade I da disciplina de Sistemas Operacionais (SO) do curso Bacharelado em Tecnologia da Informação (BTI). Tem como principal objetivo trabalhar o conceito de <i>multiprogramação</i> ou <i>programação paralela</i>, através de processos e threads.

Os programas desenvolvidos e explicados abaixo realizam a mesma tarefa: multiplicação de matrizes e contabilização do tempo

## Como rodar?
Execute os seguintes comandos no seu terminal:

```bash
# Clone o repositório
$ git clone https://github.com/marianefelix/projeto-so.git
# Entre no repositório
$ cd projeto-so
# Rode o programa para gerar as matrizes aleatórias
$ g++ generate_matrices.cpp -o generate
# Execute o programa passando as dimensões das duas matrizes
$ ./generate 3 3 3 3
# Para compilar o programa de multiplição sequencial de matrizes digite:
$ g++ multiply_matrices_sequential.cpp -o sequential
# Para executar o programa digite:
$ ./sequential first_matrix.txt second_matrix.txt
# Para compilar o programa de multiplição de matrizes através de processos digite:
$ g++ multiply_matrices_process.cpp -o process
# Para executar o programa digite:
$ ./process first_matrix.txt second_matrix.txt 4
# Para compilar o programa de multiplição de matrizes através de threads digite:
$ g++ multiply_matrices_threads.cpp -o threads
# Para executar o programa digite:
$ ./threads first_matrix.txt second_matrix.txt 4
```

## Autoras
Feito por [Mariane Felix Fernandes](https://github.com/marianefelix) e [Brenda Alexandra de Souza Silva](https://github.com/breudes)
