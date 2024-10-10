#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT 1000
#define LOOP 10000
#define TIME_COUNT 100
#define GET_COUNT COUNT/TIME_COUNT

pthread_mutex_t mutex;
struct timespec ts[4][COUNT];

void busy(void)
{
	for (int i = 0; i < LOOP; i++)
	{

	}
}

void *fun(void *arg)
{
	int thn = (int)arg;
	int ts_index = 0;
	
	for (int i = 0; i < GET_COUNT; i++)
	{
		pthread_mutex_lock(&mutex);
		for (int j = 0; j < TIME_COUNT;j++)
		{
			busy();
			clock_gettime(CLOCK_REALTIME,&ts[thn][ts_index]);
			ts_index++;
		}
		pthread_mutex_unlock(&mutex);
		busy();
	}	
}

int main()
{
	struct timespec x;
	pthread_t th0;
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	
	pthread_mutex_init(&mutex, NULL);	
	clock_gettime(CLOCK_REALTIME, &x);
	long startt = x.tv_sec * 1000000000 + x.tv_nsec;

	pthread_create(&th0, NULL, fun, (void *)0);
	pthread_create(&th1, NULL, fun, (void *)1);
	pthread_create(&th2, NULL, fun, (void *)2);
	pthread_create(&th3, NULL, fun, (void *)3);

	pthread_join(th0, NULL);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);

	for (int thn = 0; thn < 4; thn++)
	{
		for (int i = 0; i < COUNT; i++)
		{
			long t = ts[thn][i].tv_sec * 1000000000 + ts[thn][i].tv_nsec;
			printf("%ld\t%d\n",t - startt, thn);
		}
	}
}
