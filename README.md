# Philosopher's Dinner Problem

## Descrição

Este repositório contém uma solução para o clássico problema dos "Filósofos à Mesa" (Philosophers Dinner Problem), um problema clássico em sistemas operacionais usado para ilustrar conceitos de sincronização e concorrência. O objetivo é simular a situação onde vários filósofos estão à mesa e precisam compartilhar recursos (garfos) de forma coordenada para evitar deadlocks e garantir que todos possam comer.

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
