#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		printf("child\n");
		sleep(2);
	}
}

int main()
{
	pthread_t th;
	if (pthread_create(&th, NULL, func, NULL) != 0)
	{
		write(2, "Error create thread\n", 20);
		exit(1);
	}
	for (int i = 0; i < 10; i++)
	{
		printf("parent\n");
		sleep(1);
	}
	pthread_join(th, NULL);
	return (0);
}
