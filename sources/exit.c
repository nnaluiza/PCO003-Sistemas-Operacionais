#include "philosophers.h"  // Inclui o cabeçalho com as definições necessárias para o código.

void	deinit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos)
{
	int	i;

	i = -1;
	// Destrói e libera os mutexes dos garfos, se eles existirem.
	while (++i < n && forks)
		pthread_mutex_destroy(&forks[i]);  // Destroi o mutex associado a cada garfo.

	i = -1;
	// Destrói e libera os mutexes de cada filósofo, se existirem.
	while (++i < n && philos)
	{
		// Se o mutex 'lock_supper' estiver alocado, destrói e libera.
		if (philos[i].lock_supper)
			pthread_mutex_destroy(philos[i].lock_supper);  // Destroi o mutex 'lock_supper' (tempo da última refeição).
		// Se o mutex 'lock_meals' estiver alocado, destrói e libera.
		if (philos[i].lock_meals)
			pthread_mutex_destroy(philos[i].lock_meals);  // Destroi o mutex 'lock_meals' (número de refeições).
		free(philos[i].lock_supper);  // Libera a memória alocada para 'lock_supper'.
		free(philos[i].lock_meals);  // Libera a memória alocada para 'lock_meals'.
	}
	// Destrói os mutexes globais de controle, se existirem.
	if (data->lock_print)
		pthread_mutex_destroy(data->lock_print);  // Destroi o mutex para controle de impressão.
	if (data->lock_dinner)
		pthread_mutex_destroy(data->lock_dinner);  // Destroi o mutex para controle do estado do jantar.

	// Libera a memória alocada para os mutexes de controle.
	free(data->lock_print);  // Libera a memória alocada para 'lock_print'.
	free(data->lock_dinner);  // Libera a memória alocada para 'lock_dinner'.

	// Libera a memória alocada para os garfos e filósofos.
	free(forks);  // Libera a memória alocada para os garfos (mutexes).
	free(philos);  // Libera a memória alocada para os filósofos.
}

void	exit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos)
{
	int	i;

	i = -1;
	// Destrói e libera os mutexes dos garfos, assim como em 'deinit_philo'.
	while (++i < n && forks)
		pthread_mutex_destroy(&forks[i]);  // Destroi o mutex associado a cada garfo.

	i = -1;
	// Destrói e libera os mutexes de cada filósofo, assim como em 'deinit_philo'.
	while (++i < n && philos)
	{
		if (philos[i].lock_supper)
			pthread_mutex_destroy(philos[i].lock_supper);  // Destroi o mutex 'lock_supper'.
		if (philos[i].lock_meals)
			pthread_mutex_destroy(philos[i].lock_meals);  // Destroi o mutex 'lock_meals'.
		free(philos[i].lock_supper);  // Libera a memória alocada para 'lock_supper'.
		free(philos[i].lock_meals);  // Libera a memória alocada para 'lock_meals'.
	}
	// Destrói os mutexes globais de controle, assim como em 'deinit_philo'.
	if (data->lock_print)
		pthread_mutex_destroy(data->lock_print);  // Destroi o mutex 'lock_print'.
	if (data->lock_dinner)
		pthread_mutex_destroy(data->lock_dinner);  // Destroi o mutex 'lock_dinner'.

	// Libera a memória alocada para os mutexes de controle.
	free(data->lock_print);  // Libera a memória de 'lock_print'.
	free(data->lock_dinner);  // Libera a memória de 'lock_dinner'.

	// Libera a memória alocada para os garfos e filósofos.
	free(forks);  // Libera a memória alocada para os garfos.
	free(philos);  // Libera a memória alocada para os filósofos.

	// Encerra o programa com falha.
	exit(EXIT_FAILURE);  // Sai do programa indicando erro (EXIT_FAILURE).
}
