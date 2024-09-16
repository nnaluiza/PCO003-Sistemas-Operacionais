#include "philosophers.h"

// Função para verificar a validade dos argumentos passados para o programa.
void check_args(int argc, char **argv)
{
	int i;  // Índice para iterar sobre os argumentos.
	int j;  // Índice para iterar sobre cada caractere de um argumento.

	i = 0;
	// Itera sobre cada argumento passado.
	while (++i < argc)
	{
		j = -1;
		// Itera sobre cada caractere do argumento atual.
		while (argv[i][++j])
		{
			// Verifica se o caractere é um dígito e se o número convertido é válido.
			if (!ft_isdigit(argv[i][j])
				|| ft_atol(argv[i]) > 2147483647  // Verifica se o número excede o limite máximo para um int.
				|| ft_atol(argv[i]) == 0)        // Verifica se o número é zero (não permitido).
			{
				printf("Error!\n");  // Exibe uma mensagem de erro.
				exit(EXIT_FAILURE);  // Finaliza o programa com código de falha.
			}
		}
	}
	// Verifica o número total de argumentos e exibe uma mensagem de erro se necessário.
	if (argc > 6)
		printf("Too many args!\n");
	else if (argc < 5)
		printf("Too few args!\n");
	else
		return ;  // Se o número de argumentos estiver correto, retorna normalmente.
	exit(EXIT_FAILURE);  // Finaliza o programa com código de falha se o número de argumentos estiver incorreto.
}

// Função para verificar se o jantar já terminou.
int dinner_is_over(t_philo *philo)
{
	int dinner_is_over;  // Variável para armazenar o estado do jantar.

	pthread_mutex_lock(philo->data->lock_dinner);  // Bloqueia o mutex para acessar a variável compartilhada.
	dinner_is_over = 0;  // Inicializa a variável como 0 (jantar não terminado).
	if (philo->data->dinner_is_over)  // Verifica o estado do jantar.
		dinner_is_over = philo->data->dinner_is_over;  // Atualiza a variável com o estado atual.
	pthread_mutex_unlock(philo->data->lock_dinner);  // Desbloqueia o mutex.
	return (dinner_is_over);  // Retorna o estado do jantar.
}

// Função para marcar o jantar como terminado.
void finish_dinner(t_philo *philo)
{
	pthread_mutex_lock(philo->data->lock_dinner);  // Bloqueia o mutex para atualizar a variável compartilhada.
	philo->data->dinner_is_over = 1;  // Define o estado do jantar como terminado.
	pthread_mutex_unlock(philo->data->lock_dinner);  // Desbloqueia o mutex.
}

// Função para imprimir ações dos filósofos com base no estado atual.
void print_action(t_philo *philo, int action)
{
	long current_time;  // Tempo atual em milissegundos.

	pthread_mutex_lock(philo->data->lock_print);  // Bloqueia o mutex para acessar a área de impressão de forma segura.
	current_time = timenow(philo->data->firststamp);  // Obtém o tempo atual relativo ao início do jantar.
	// Verifica o tipo de ação e imprime a mensagem correspondente, se o jantar não estiver terminado.
	if (action == TOOK_A_FORK && !dinner_is_over(philo))
		printf("%5ld %3d has taken a fork\n", current_time, philo->name);
	else if (action == EATING && !dinner_is_over(philo))
		printf("%5ld %3d is eating\n", current_time, philo->name);
	else if (action == SLEEPING && !dinner_is_over(philo))
		printf("%5ld %3d is sleeping\n", current_time, philo->name);
	else if (action == THINKING && !dinner_is_over(philo))
		printf("%5ld %3d is thinking\n", current_time, philo->name);
	else if (action == DIED)
		printf("%5ld %3d died\n", current_time, philo->name);
	pthread_mutex_unlock(philo->data->lock_print);  // Desbloqueia o mutex.
}
