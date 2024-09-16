# Philosopher's Dinner Problem

## Descrição

Este repositório contém uma solução para o clássico problema do "Jantar dos Filósofos", um problema clássico em sistemas operacionais usado para ilustrar conceitos de sincronização e concorrência. O objetivo é simular a situação onde vários filósofos estão à mesa e precisam compartilhar recursos (garfos) de forma coordenada para evitar deadlocks e garantir que todos possam comer.

## Estrutura do Projeto

O projeto é dividido em várias partes principais:

- **Estruturas e Tipos**: Definições de estruturas e tipos para representar filósofos e o estado da refeição.
- **Inicialização**: Funções para inicializar os filósofos, garfos e dados necessários.
- **Ações dos Filósofos**: Funções que definem as ações dos filósofos, como comer, dormir e pensar.
- **Gerenciamento de Threads**: Funções para iniciar e gerenciar as threads dos filósofos e do monitor de estado.
- **Sincronização e Controle**: Funções para gerenciar a sincronização entre filósofos e monitorar o estado da refeição.

## Funcionalidades

- **Inicialização**: Configura o número de filósofos, tempos de alimentação e sono, e outras variáveis.
- **Ações dos Filósofos**: Cada filósofo realiza ações como pegar garfos, comer, dormir e pensar.
- **Sincronização**: Utiliza mutexes para garantir que apenas um filósofo acesse um garfo por vez e para proteger o acesso a variáveis compartilhadas.
- **Monitoramento**: Um monitor que verifica se algum filósofo morreu devido à falta de alimentação e encerra a refeição.

## Como Usar

1. **Compilação**

   Compile o projeto usando o `Makefile` incluído:

   ```bash
   make

2. **Execução**

   Execute o programa fornecendo os argumentos necessários:

   ```bash
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [times_must_eat]

- `<number_of_philosophers>`: Número de filósofos à mesa.
- `<time_to_die>`: Tempo em milissegundos após o qual um filósofo morre se não comer.
- `<time_to_eat>`: Tempo em milissegundos que um filósofo leva para comer.
- `<time_to_sleep>`: Tempo em milissegundos que um filósofo passa dormindo.
- `[times_must_eat] (opcional)`: Número de vezes que cada filósofo deve comer antes de a refeição ser considerada completa.

  Exemplo:

   ```bash
   ./philo 5 800 200 200 10

3. **Saída**

   O programa imprimirá ações dos filósofos como pegar garfos, comer, dormir e pensar, bem como notificações quando um filósofo morrer.

## Principais métodos

- `check_args`: Verifica a validade dos argumentos de entrada.
- `init_args`: Inicializa os dados com base nos argumentos fornecidos.
- `init_data`: Inicializa os mutexes e outros dados necessários.
- `init_forks`: Inicializa os mutexes dos garfos.
- `init_philos`: Inicializa os filósofos e seus mutexes.
- `start_philosophers`: Inicia as threads dos filósofos e do monitor.
- `print_action`: Imprime as ações dos filósofos com timestamps.
- `finish_dinner`: Marca a refeição como concluída se algum filósofo morrer.

  ## Referência

 - [The Dining Philosopher Problem](https://github.com/wwwwelton/philosophers?tab=readme-ov-file)
