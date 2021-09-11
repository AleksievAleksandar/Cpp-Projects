#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <pthread.h>
#include <mutex>
#include <condition_variable>

#define  MAX_CLIENTS 10

struct MemoryPool
{
	int values[MAX_CLIENTS];
	int timeWithoutRequest[MAX_CLIENTS];
	bool clients[MAX_CLIENTS];
	bool serverUpdateTheData[MAX_CLIENTS];
	bool newRequestFromClients[MAX_CLIENTS];
	bool serverUpdatesClientsData;

	//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	std::mutex mtx;
	std::condition_variable cv;
};

#endif
