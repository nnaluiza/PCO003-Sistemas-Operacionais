#include "philosophers.h"

// Função para fazer a thread dormir por um período específico em milissegundos.
void msleep(int time_in_ms)
{
	long start_time;  // Tempo inicial em que a função começa a dormir.

	start_time = timestamp();  // Marca o tempo atual.
	// Enquanto o tempo decorrido desde o início for menor que o tempo desejado,
	// a função continua a dormir em intervalos curtos.
	while ((timestamp() - start_time) < (long)time_in_ms)
		usleep(10);  // Dorme por 10 microssegundos em cada iteração.
}

// Função para obter o timestamp atual em milissegundos desde a época Unix.
long timestamp(void)
{
	struct timeval time;  // Estrutura para armazenar o tempo.

	gettimeofday(&time, NULL);  // Obtém o tempo atual.
	// Converte o tempo obtido para milissegundos.
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Função para calcular o tempo decorrido desde um timestamp específico.
long timenow(long firststamp)
{
	return (timestamp() - firststamp);  // Retorna o tempo decorrido em milissegundos.
}
