#include "philosophers.h"  // Inclui o cabeçalho com as definições e funções necessárias para o programa.

/*
** Função 'main': ponto de entrada do programa.
** - 'argc' é o número de argumentos fornecidos pela linha de comando.
** - 'argv' é o array de strings contendo os argumentos.
** Esta função inicializa o ambiente do problema dos filósofos e inicia a simulação.
*/
int	main(int argc, char **argv)
{
	t_data	data;      // Estrutura que contém os dados globais da simulação (número de filósofos, tempos, mutexes, etc.).
	t_mutex	*forks;    // Ponteiro para os mutexes que representam os garfos.
	t_philo	*philos;   // Ponteiro para a estrutura de cada filósofo.

	// Inicializa os argumentos do programa (número de filósofos, tempos de ação, limite de refeições).
	init_args(argc, argv, &data);

	// Inicializa os dados globais (como os mutexes de controle) e define o estado inicial da simulação.
	init_data(&data, &forks, &philos);

	// Inicializa os mutexes que representam os garfos. Cada filósofo terá dois garfos (à direita e à esquerda).
	init_forks(data.number_of_philos, &data, &forks, &philos);

	// Inicializa os filósofos e os associa aos seus respectivos garfos e mutexes.
	init_philos(data.number_of_philos, &data, &forks, &philos);

	// Inicia a simulação dos filósofos (as threads são criadas aqui e começam a executar as ações dos filósofos).
	start_philosophers(data.number_of_philos, philos);

	// Finaliza a simulação, desalocando recursos e destruindo os mutexes utilizados.
	deinit_philo(data.number_of_philos, &data, forks, philos);

	return (0);  // Retorna 0 indicando que o programa terminou com sucesso.
}
