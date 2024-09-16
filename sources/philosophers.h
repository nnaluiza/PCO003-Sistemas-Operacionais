#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H  // Protege o arquivo contra múltiplas inclusões.

# include <errno.h>      // Para lidar com códigos de erro.
# include <pthread.h>    // Para trabalhar com threads e mutexes.
# include <stdio.h>      // Para funções de entrada e saída, como printf.
# include <stdlib.h>     // Para funções de alocação de memória, como malloc e free.
# include <sys/time.h>   // Para trabalhar com o tempo do sistema.
# include <unistd.h>     // Para chamadas ao sistema como usleep (pausas em microsegundos).

// Definição de alias para o tipo pthread_mutex_t, usado para representar mutexes.
typedef pthread_mutex_t	t_mutex;

// Definição de constantes para representar diferentes ações dos filósofos.
# define TOOK_A_FORK 1  // Ação de pegar um garfo.
# define EATING 2       // Ação de comer.
# define SLEEPING 3     // Ação de dormir.
# define THINKING 4     // Ação de pensar.
# define DIED 5         // Estado de morte do filósofo.

// Estrutura que contém os dados globais do programa.
typedef struct s_data
{
	int				alone;           // Indica se há apenas um filósofo.
	int				number_of_philos;  // Número total de filósofos.
	int				dinner_is_over;  // Indica se o jantar acabou.
	int				time_to_die;     // Tempo que um filósofo pode passar sem comer antes de morrer.
	int				time_to_eat;     // Tempo que um filósofo leva para comer.
	int				time_to_sleep;   // Tempo que um filósofo leva para dormir.
	int				times_must_eat;  // Número de vezes que os filósofos devem comer.
	long			firststamp;      // Timestamp do início da simulação.
	pthread_mutex_t	*lock_print;     // Mutex para proteger a impressão das ações.
	pthread_mutex_t	*lock_dinner;    // Mutex para proteger o status do jantar.
}	t_data;

// Estrutura que contém os dados específicos de cada filósofo.
typedef struct s_philo
{
	int				name;           // Nome ou número do filósofo.
	int				meals;          // Quantidade de refeições feitas pelo filósofo.
	long			lastsupper;     // Timestamp da última refeição.
	pthread_t		thread;         // Identificador da thread associada ao filósofo.
	pthread_mutex_t	*fork_left;     // Ponteiro para o mutex do garfo à esquerda.
	pthread_mutex_t	*fork_right;    // Ponteiro para o mutex do garfo à direita.
	pthread_mutex_t	*lock_supper;   // Mutex para proteger o acesso ao timestamp da última refeição.
	pthread_mutex_t	*lock_meals;    // Mutex para proteger o acesso à contagem de refeições.
	t_data			*data;          // Ponteiro para a estrutura de dados globais.
}	t_philo;

// Declarações de funções utilitárias usadas no programa.

// Funções auxiliares para conversão de strings para inteiros e validação.
int		ft_atoi(const char *nptr);          // Converte uma string para um inteiro.
long	ft_atol(const char *nptr);          // Converte uma string para um valor long.
int		ft_isdigit(int c);                 // Verifica se o caractere é um dígito.

// Funções para verificar e manipular o estado do jantar.
int		dinner_is_over(t_philo *philo);    // Verifica se o jantar acabou.
int		get_lastsupper(t_philo *philo);    // Retorna o timestamp da última refeição de um filósofo.
int		get_meals(t_philo *philo);         // Retorna o número de refeições de um filósofo.

// Funções relacionadas ao ciclo de vida dos filósofos.
int		start_philosophers(int n, t_philo *philos);  // Inicia as threads dos filósofos.

// Funções relacionadas ao tempo.
long	timenow(long firststamp);          // Calcula o tempo atual relativo ao início da simulação.
long	timestamp(void);                   // Retorna o timestamp atual.

// Funções de inicialização e limpeza.
void	check_args(int argc, char **argv);                 // Verifica a validade dos argumentos de entrada.
void	deinit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos);  // Limpa os dados e destrói mutexes.
void	exit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos);    // Sai do programa em caso de erro.
void	finish_dinner(t_philo *philo);                     // Finaliza o jantar.
void	init_args(int argc, char **argv, t_data *data);    // Inicializa os argumentos e dados globais.
void	init_data(t_data *data, pthread_mutex_t **forks, t_philo **philos);  // Inicializa a estrutura de dados.
void	init_forks(int n, t_data *data, t_mutex **forks, t_philo **philos);  // Inicializa os mutexes (garfos).
void	init_philos(int n, t_data *data, t_mutex **forks, t_philo **philos);  // Inicializa os filósofos.

// Função auxiliar para colocar a thread para dormir por um tempo específico.
void	msleep(int time_in_ms);            // Pausa a execução da thread por um período em milissegundos.

// Função para imprimir a ação do filósofo.
void	print_action(t_philo *philo, int action);  // Imprime a ação realizada por um filósofo.

// Funções para manipulação das refeições e tempos dos filósofos.
void	set_lastsupper(t_philo *philo);    // Atualiza o timestamp da última refeição de um filósofo.
void	set_meals(t_philo *philo);         // Incrementa o contador de refeições de um filósofo.

// Funções principais que definem as ações dos filósofos.
void	*actions(void *ptr);               // Define as ações realizadas por um filósofo.
void	*philosopher_monitor(void *ptr);   // Monitora o estado de um filósofo.

#endif
