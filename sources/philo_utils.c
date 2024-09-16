#include "philosophers.h"  // Inclui o cabeçalho com as definições e funções necessárias para o programa.

/*
** Função 'get_meals':
** - Obtém o número de refeições que o filósofo já fez.
** - Usa um mutex para garantir que o acesso à variável compartilhada 'meals' seja feito de forma segura em um ambiente multithread.
**
** Parâmetro:
** - 'philo': ponteiro para a estrutura do filósofo.
**
** Retorno:
** - O número de refeições feitas pelo filósofo.
*/
int	get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->lock_meals);  // Bloqueia o mutex para garantir acesso exclusivo à variável 'meals'.
	meals = philo->meals;                  // Copia o valor da variável 'meals'.
	pthread_mutex_unlock(philo->lock_meals);  // Desbloqueia o mutex após a leitura.
	return (meals);  // Retorna o número de refeições feitas pelo filósofo.
}

/*
** Função 'set_meals':
** - Incrementa o número de refeições que o filósofo já fez.
** - Usa um mutex para garantir que o acesso à variável 'meals' seja feito de forma segura.
**
** Parâmetro:
** - 'philo': ponteiro para a estrutura do filósofo.
*/
void	set_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_meals);  // Bloqueia o mutex para garantir acesso exclusivo à variável 'meals'.
	philo->meals++;                         // Incrementa o número de refeições feitas pelo filósofo.
	pthread_mutex_unlock(philo->lock_meals);  // Desbloqueia o mutex após a modificação.
}

/*
** Função 'get_lastsupper':
** - Obtém o timestamp da última refeição feita pelo filósofo.
** - Usa um mutex para garantir o acesso seguro à variável compartilhada 'lastsupper'.
**
** Parâmetro:
** - 'philo': ponteiro para a estrutura do filósofo.
**
** Retorno:
** - O timestamp da última refeição feita pelo filósofo.
*/
int	get_lastsupper(t_philo *philo)
{
	long	lastsupper;

	pthread_mutex_lock(philo->lock_supper);  // Bloqueia o mutex para garantir acesso exclusivo à variável 'lastsupper'.
	lastsupper = philo->lastsupper;         // Copia o valor do timestamp da última refeição.
	pthread_mutex_unlock(philo->lock_supper);  // Desbloqueia o mutex após a leitura.
	return (lastsupper);  // Retorna o timestamp da última refeição.
}

/*
** Função 'set_lastsupper':
** - Atualiza o timestamp da última refeição feita pelo filósofo.
** - Usa um mutex para garantir que o acesso à variável 'lastsupper' seja feito de forma segura.
**
** Parâmetro:
** - 'philo': ponteiro para a estrutura do filósofo.
*/
void	set_lastsupper(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_supper);  // Bloqueia o mutex para garantir acesso exclusivo à variável 'lastsupper'.
	philo->lastsupper = timenow(philo->data->firststamp);  // Atualiza o timestamp da última refeição para o tempo atual.
	pthread_mutex_unlock(philo->lock_supper);  // Desbloqueia o mutex após a modificação.
}
