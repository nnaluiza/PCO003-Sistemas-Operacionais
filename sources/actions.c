#include "philosophers.h"

// Função que lida com o caso especial de quando há apenas um filósofo
static void	*go_eat_alone(t_philo *philo)
{
    // Trava o garfo da direita, já que o filósofo está sozinho
	pthread_mutex_lock(philo->fork_right);
    // Imprime a ação de pegar o garfo (já que ele só pode pegar um garfo)
	print_action(philo, TOOK_A_FORK);
    // Destrava o garfo da direita, pois ele não consegue comer sozinho com apenas um garfo
	pthread_mutex_unlock(philo->fork_right);
    // Retorna NULL, já que o filósofo não pode fazer mais nada nesse caso
	return (NULL);
}

// Função que controla o ato de comer dos filósofos
static void	go_eat(t_philo *philo)
{
    // Trava os garfos (primeiro o da direita, depois o da esquerda)
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->fork_left);

    // Verifica se o jantar já acabou; se sim, libera os garfos e retorna
	if (dinner_is_over(philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}

    // Imprime as ações de pegar os dois garfos e de começar a comer
	print_action(philo, TOOK_A_FORK);
	print_action(philo, TOOK_A_FORK);
	print_action(philo, EATING);

    // Atualiza o último momento em que o filósofo comeu
	set_lastsupper(philo);

    // Faz o filósofo "comer" por um tempo determinado (dormir por um tempo para simular a ação)
	msleep(philo->data->time_to_eat);

    // Libera os garfos após terminar de comer
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);

    // Atualiza o contador de refeições realizadas pelo filósofo
	set_meals(philo);
}

// Função que controla o ato de dormir dos filósofos
static void	go_sleep(t_philo *philo)
{
    // Imprime a ação de dormir
	print_action(philo, SLEEPING);

    // Faz o filósofo "dormir" por um tempo determinado (dormir por um tempo para simular a ação)
	msleep(philo->data->time_to_sleep);
}

// Função que controla o ato de pensar dos filósofos
static void	go_think(t_philo *philo)
{
    // Imprime a ação de pensar
	print_action(philo, THINKING);

    // Pequena espera (usleep) para simular o filósofo pensando
	usleep(500);
}

// Função principal das ações dos filósofos (executada como uma thread separada para cada filósofo)
void	*actions(void *ptr)
{
    // Converte o ponteiro recebido para o tipo t_philo (filósofo)
	t_philo	*philo;

	philo = (t_philo *)ptr;

    // Se o filósofo tem um número ímpar, ele espera um pouco para evitar que todos os filósofos tentem pegar garfos ao mesmo tempo
	if (philo->name % 2)
		msleep(5);

    // Se há apenas um filósofo, chama a função especial go_eat_alone
	if (philo->data->alone)
		return (go_eat_alone(philo));

    // Loop principal das ações do filósofo (comer, dormir e pensar) até o jantar acabar
	while (!dinner_is_over(philo))
	{
        // O filósofo tenta pegar os garfos e comer
		go_eat(philo);

        // Se ele atingiu o número máximo de refeições, a thread termina
		if (get_meals(philo) == philo->data->times_must_eat)
			return (NULL);

        // Após comer, o filósofo dorme e depois pensa
		go_sleep(philo);
		go_think(philo);
	}

    // Retorna NULL quando o jantar acabar
	return (NULL);
}