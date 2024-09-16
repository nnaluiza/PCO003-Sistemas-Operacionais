#include "philosophers.h"  // Inclui o cabeçalho com as definições necessárias para o código.

/*
** Função 'init_args': inicializa os argumentos fornecidos pela linha de comando e armazena no struct 't_data'.
** - 'argc' é o número de argumentos.
** - 'argv' é um array de strings contendo os argumentos.
** - 'data' é o ponteiro para a estrutura de dados compartilhada pelos filósofos.
*/
void	init_args(int argc, char **argv, t_data *data)
{
	// Valida os argumentos de entrada.
	check_args(argc, argv);
	// Converte os argumentos de string para inteiros e armazena nos respectivos campos da estrutura 'data'.
	data->number_of_philos = ft_atoi(argv[1]);   // Número de filósofos.
	data->time_to_die = ft_atoi(argv[2]);        // Tempo até um filósofo morrer se não comer.
	data->time_to_eat = ft_atoi(argv[3]);        // Tempo que um filósofo leva para comer.
	data->time_to_sleep = ft_atoi(argv[4]);      // Tempo que um filósofo dorme.
	data->times_must_eat = -1;  // Inicializa 'times_must_eat' como -1 (indicando que não há limite de refeições).
	if (argc == 6)  // Se houver um quinto argumento (limite de refeições), ele é convertido e armazenado.
		data->times_must_eat = ft_atoi(argv[5]);
}

/*
** Função 'init_data': inicializa a estrutura 't_data' e aloca memória para os mutexes de impressão e controle do jantar.
** Também define o estado inicial dos filósofos e o número de mutexes necessários para os garfos e filósofos.
*/
void	init_data(t_data *data, pthread_mutex_t **forks, t_philo **philos)
{
	*forks = NULL;  // Inicializa o ponteiro para os garfos como NULL.
	*philos = NULL; // Inicializa o ponteiro para os filósofos como NULL.

	// Se houver apenas um filósofo, define o campo 'alone' como 1 (indicando que ele está sozinho).
	if (data->number_of_philos == 1)
		data->alone = 1;
	else
		data->alone = 0;  // Caso contrário, ele não está sozinho.

	data->dinner_is_over = 0;  // O jantar ainda não acabou.
	data->firststamp = 0;      // Inicializa o timestamp inicial como 0.

	// Aloca memória para os mutexes 'lock_print' (para impressão segura) e 'lock_dinner' (para controlar o estado do jantar).
	data->lock_print = (t_mutex *)malloc(sizeof(t_mutex) * 1);
	data->lock_dinner = (t_mutex *)malloc(sizeof(t_mutex) * 1);

	// Se não conseguir alocar memória para os mutexes, imprime uma mensagem de erro e encerra o programa.
	if (data->lock_print == NULL || data->lock_dinner == NULL)
	{
		printf("Failed to alloc mutex!\n");
		exit_philo (0, data, *forks, *philos);  // Função para encerrar e liberar memória.
	}

	// Inicializa os mutexes.
	pthread_mutex_init(data->lock_print, NULL);
	pthread_mutex_init(data->lock_dinner, NULL);
}

/*
** Função 'init_forks': aloca memória para os mutexes que representam os garfos e inicializa cada mutex.
** Cada filósofo terá dois garfos associados a ele.
*/
void	init_forks(int n, t_data *data, t_mutex **forks, t_philo **philos)
{
	int	i;

	// Aloca memória para 'n' garfos (um para cada filósofo).
	*forks = (t_mutex *)malloc(sizeof(t_mutex) * n);
	// Se a alocação falhar, imprime uma mensagem de erro e encerra o programa.
	if (*forks == NULL)
	{
		printf("Failed to alloc forks!\n");
		exit_philo(n, data, *forks, *philos);
	}

	// Inicializa cada mutex de garfo.
	i = -1;
	while (++i < n)
		pthread_mutex_init(&(*forks)[i], NULL);
}

/*
** Função 'init_philos': aloca memória para os filósofos, inicializa os mutexes de cada filósofo e define seus garfos.
** Cada filósofo terá dois garfos (um à direita e um à esquerda).
*/
void	init_philos(int n, t_data *data, t_mutex **forks, t_philo **philos)
{
	int	i;

	// Aloca memória para 'n' filósofos.
	*philos = (t_philo *)malloc(sizeof(t_philo) * n);
	// Se a alocação falhar, imprime uma mensagem de erro e encerra o programa.
	if (*philos == NULL)
	{
		printf("Failed to alloc philosophers!\n");
		exit_philo(n, data, *forks, *philos);
	}

	// Inicializa cada filósofo com seus respectivos garfos, mutexes e dados.
	i = -1;
	while (++i < n)
	{
		(*philos)[i].fork_right = &(*forks)[i];      // O garfo da direita é o garfo correspondente ao índice 'i'.
		(*philos)[i].fork_left = &(*forks)[i + 1];   // O garfo da esquerda é o próximo garfo.

		// Aloca e inicializa mutexes para controlar o acesso ao jantar e às refeições.
		(*philos)[i].lock_supper = (t_mutex *)malloc(sizeof(t_mutex) * 1);
		(*philos)[i].lock_meals = (t_mutex *)malloc(sizeof(t_mutex) * 1);

		// Inicializa os valores dos filósofos.
		(*philos)[i].name = i + 1;       // Nome do filósofo (baseado no índice).
		(*philos)[i].meals = 0;          // Inicializa o contador de refeições.
		(*philos)[i].lastsupper = 0;     // Inicializa o tempo da última refeição.
		(*philos)[i].data = data;        // Associa os dados gerais (compartilhados entre todos os filósofos).

		// Inicializa os mutexes do jantar e refeições.
		pthread_mutex_init((*philos)[i].lock_supper, NULL);
		pthread_mutex_init((*philos)[i].lock_meals, NULL);
	}

	// O último filósofo compartilha o garfo à esquerda com o primeiro filósofo.
	(*philos)[--i].fork_left = &(*forks)[0];
}
