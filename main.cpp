#include <iostream>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include <MainTest.h>

pthread_mutex_t lock;

void *thread_proc(void *arg) {
	pthread_mutex_lock(&lock);
	std::cout << "from thread" << std::endl;
	pthread_mutex_unlock(&lock);

	return NULL;
}

// Linux socfpga 3.13.0-00298-g3c7cbb9-dirty #8 SMP Wed Jan 7 10:48:09 CST 2015 armv7l GNU/Linux

int main(void) {
	pthread_t t;
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);

	pthread_create(&t, NULL, &thread_proc, NULL);

	usleep(500000);
	std::cout << "Hi!!! it's DE0-Nano-SoC...." << std::endl;

	std::cout << "Program debugging ok...." << std::endl;

	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);

	MainTest *mt = new MainTest();
	mt->PrintFromClass();

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	std::cout << "sock=" << sock << std::endl;
	close(sock);

	pthread_join(t, NULL);

	return 0;
}
