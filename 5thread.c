#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT 1000
#define LOOP 10000

struct timespec ts[5][COUNT];

void busy(void)
{
	for (int i = 0; i < LOOP; i++)
	{

	}
}

void *fun(void *arg)
{
	int thn = (int)arg;
	for (int i = 0; i < COUNT; i++)
	{
		busy();
		clock_gettime(CLOCK_REALTIME, &ts[thn][i]);
	}
}

int main()
{
	struct timespec x;
	pthread_t th0;
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	pthread_t th4;
	
	clock_gettime(CLOCK_REALTIME, &x);
	long startt = x.tv_sec * 1000000000 + x.tv_nsec;

	pthread_create(&th0, NULL, fun, (void *)0);
	pthread_create(&th1, NULL, fun, (void *)1);
	pthread_create(&th2, NULL, fun, (void *)2);
	pthread_create(&th3, NULL, fun, (void *)3);
	pthread_create(&th4, NULL, fun, (void *)4);

	pthread_join(th0, NULL);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	pthread_join(th4, NULL);

	for (int thn = 0; thn < 5; thn++)
	{
		for (int i = 0; i < COUNT; i++)
		{
			long t = ts[thn][i].tv_sec * 1000000000 + ts[thn][i].tv_nsec;
			printf("%ld\t%d\n",t - startt, thn);
		}
	}
}
