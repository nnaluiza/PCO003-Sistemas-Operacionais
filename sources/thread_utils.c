#include "philosophers.h"

// Função para iniciar as threads dos filósofos e do monitor.
int start_philosophers(int n, t_philo *philos)
{
	int			i;                  // Índice para iteração.
	pthread_t	monitor_thread;     // Thread para o monitor dos filósofos.

	i = -1;
	philos->data->firststamp = timestamp();  // Marca o início da simulação.

	// Cria uma thread para cada filósofo, passando a função 'actions' como a função da thread.
	while (++i < n)
		pthread_create(&philos[i].thread, NULL, &actions, &philos[i]);

	// Cria uma thread para o monitor dos filósofos, passando a função 'philosopher_monitor'.
	pthread_create(&monitor_thread, NULL, &philosopher_monitor, philos);

	i = -1;
	// Espera todas as threads dos filósofos terminarem.
	while (++i < n)
		pthread_join(philos[i].thread, NULL);

	// Espera a thread do monitor terminar.
	pthread_join(monitor_thread, NULL);

	return (0);
}

// Função estática para verificar se todos os filósofos comeram o número necessário de vezes.
static int all_philos_ate(t_philo *philos)
{
	int	i;                  // Índice para iteração.
	int	had_dinner;         // Contador de filósofos que comeram o número necessário de vezes.

	had_dinner = 0;
	i = -1;
	// Verifica cada filósofo para ver se ele comeu o número necessário de vezes.
	while (++i < philos->data->number_of_philos)
	{
		if (get_meals(&philos[i]) == philos[i].data->times_must_eat)
			had_dinner++;
	}
	// Se todos os filósofos comeram o número necessário de vezes, retorna 1 (verdadeiro).
	if (had_dinner == philos->data->number_of_philos)
		return (1);
	return (0);  // Caso contrário, retorna 0 (falso).
}

// Função para monitorar o estado dos filósofos.
void *philosopher_monitor(void *ptr)
{
	int		i;                  // Índice para iteração.
	long	current_time;       // Tempo atual relativo ao início da simulação.
	long	time_to_die;        // Tempo máximo permitido sem comer antes de morrer.
	t_philo	*philos;           // Ponteiro para a lista de filósofos.

	philos = (t_philo *)ptr;
	time_to_die = philos->data->time_to_die;

	// Enquanto nem todos os filósofos comeram o número necessário de vezes,
	// o monitor verifica se algum filósofo morreu.
	while (!all_philos_ate(philos))
	{
		i = -1;
		while (++i < philos->data->number_of_philos)
		{
			current_time = timenow(philos->data->firststamp);  // Obtém o tempo atual.
			// Verifica se o tempo desde a última refeição do filósofo excede o tempo máximo permitido.
			if ((current_time - get_lastsupper(&philos[i])) > time_to_die)
			{
				finish_dinner(&philos[i]);  // Termina o jantar para o filósofo.
				print_action(&philos[i], DIED);  // Imprime que o filósofo morreu.
				return (NULL);  // Encerra a função do monitor.
			}
		}
		msleep(1);  // Pausa a execução por um curto período antes de verificar novamente.
	}
	return (NULL);  // Retorna NULL quando a função termina.
}
