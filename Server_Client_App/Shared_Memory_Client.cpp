#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mman.h>
#include <iostream>

#include <time.h>

#include "../Header_Files/MemoryPool.h"

#define NOT_ACTIVE_CLIENT -1

class Client
{
private:
	int fd;
	int clientID;
	MemoryPool* memoryPool;

public:
	Client() :
		fd(0), clientID(NOT_ACTIVE_CLIENT), memoryPool(nullptr) {}

public:
	static void findFreeMemory(MemoryPool*& memoryPool, int& clientID)
	{
		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			if(memoryPool->clients[i] == false)
			{
				/*int ret_code = pthread_mutex_lock( &memoryPool->mutex );

				if (ret_code != EOK)
				{
					printf ("pthread_mutex_unlock() failed: %s\n", strerror(ret_code));
				}*/

				memoryPool->mtx.lock();
				memoryPool->clients[i] = true;
				clientID = i;
				memoryPool->mtx.unlock();
				break;

				//ret_code = pthread_mutex_unlock( &memoryPool->mutex );
				//break;
			}
		}
	}

public:
	void connectToServer()
	{
		/* Create a new memory object */
		fd = shm_open( "/bolts", O_RDWR, 0777 );
		if( fd == -1 )
		{
			fprintf( stderr, "Open failed:%s\n", strerror( errno ));
			return;
		}

		memoryPool = (MemoryPool*)mmap( 0, sizeof( MemoryPool ), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );

		std::cout << "Map addr is 0x%08x" << memoryPool << std::endl;
	}

	void run()
	{
		//pthread_t attr;
		//pthread_attr_init( &attr );
		//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

//		int ret_code = pthread_create( &attr, NULL, &findFreeMemory, &this->clientID );
//		if (ret_code != EOK)
//		{
//			printf ("Couldn't create first thread: %s\n", strerror (ret_code));
//		}
//
//		std::cout << "after creating the thread" << std::endl;
//		pthread_join(attr, NULL);

		this->connectToServer();

		findFreeMemory(this->memoryPool, this->clientID);

		if(this->clientID != NOT_ACTIVE_CLIENT)
		{
			std::cout << "Client ID -> " << this->clientID << std::endl;

			srand(time(NULL));
			while(1)
			{
				if(this->memoryPool->clients[this->clientID])
				{
					//this->memoryPool->mtx.lock();

					std::unique_lock<std::mutex> locker(this->memoryPool->mtx);
					this->memoryPool->cv.wait(locker, [&](){return this->memoryPool->serverUpdatesClientsData;});

					//if(this->memoryPool->serverUpdateTheData[this->clientID])
					//{
						std::cout << "the memoryPool->values[" << this->clientID << "] is: " << this->memoryPool->values[this->clientID] << std::endl;
					//}

					this->randomGenForNewRequest();

					locker.unlock();
					this->memoryPool->cv.notify_one();
					//this->memoryPool->mtx.unlock();
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			std::cout << "There is no free memory for this Client" << std::endl;
		}
	}

	void stop()
	{
		std::cout << "Client is shut down" << std::endl;

		if(this->clientID > -1 && this->clientID < MAX_CLIENTS)
		{
			memoryPool->clients[this->clientID] = false;
			memoryPool->serverUpdateTheData[this->clientID] = false;
		}
		//The memory object remains in
		//the system after the close
		close( fd );
	}

private:
	void randomGenForNewRequest()
	{
		//std::unique_lock<std::mutex> ul(this->memoryPool->mtx);
		//this->memoryPool->cv.wait(ul, [&]{return this->memoryPool->serverUpdateTheData[this->clientID];});
		/*if(randNum % 2 == 0)
		{
			this->memoryPool->newRequestFromClients[this->clientID] = false;
		}
		else
		{
			this->memoryPool->newRequestFromClients[this->clientID] = true;
			this->memoryPool->values[this->clientID] = randNum;
		}*/
		int randNum = rand() % 10 + 1;
		this->memoryPool->newRequestFromClients[this->clientID] = true;
		this->memoryPool->values[this->clientID] = randNum;
		this->memoryPool->serverUpdatesClientsData = false;
	}
};

int main(int argc, char *argv[])
{
	Client client;

	client.run();
	client.stop();

	return EXIT_SUCCESS;
}
