#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mman.h>
#include <iostream>

#include "../Header_Files/MemoryPool.h"

class Server
{
private:
	int fd;
	const int cntForHangingClients;
	MemoryPool* memoryPool;

public:
	Server():
		fd(0), cntForHangingClients(50), memoryPool(nullptr) {}

public:
	void run(const int& argc)
	{
		this->createMemoryObj(argc);
		this->initMemoryPool();

		while(1)
		{
			//this->memoryPool->mtx.lock();
			std::unique_lock<std::mutex> locker(this->memoryPool->mtx);
			this->memoryPool->cv.wait(locker, [&](){return !this->memoryPool->serverUpdatesClientsData;});

			this->printOccupiedMemory();
			this->updateClientData();
			this->checkAndRemoveHangingClients();

			locker.unlock();
			this->memoryPool->cv.notify_all();
			//this->memoryPool->mtx.unlock();
		}
	}

	void stop()
	{
		//The memory object remains in
		//the system after the close
		close( fd );

		//To remove a memory object. You must unlink it like a file.
		//
		//This may be done by another process.
		shm_unlink( "/bolts" );
	}

private:
	void createMemoryObj(const int& argc)
	{
		//In case the unlink code isn't executed at the end
		if( argc != 1 )
		{
			shm_unlink( "/bolts" );
			return;
		}

		/* Create a new memory object */
		this->fd = shm_open( "/bolts", O_RDWR | O_CREAT, 0777 );
		if( fd == -1 )
		{
			fprintf( stderr, "Open failed:%s\n", strerror( errno ));
			return;
		}

		/* Set the memory object's size */
		if( ftruncate( this->fd, sizeof( MemoryPool ) ) == -1 )
		{
			fprintf( stderr, "ftruncate: %s\n", strerror( errno ));
			return;
		}

		/* Map the memory object */
		this->memoryPool = (MemoryPool*)mmap( 0, sizeof( MemoryPool ), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );

		if( this->memoryPool == MAP_FAILED )
		{
			fprintf( stderr, "mmap failed: %s\n", strerror( errno ));
			return;
		}
		else
		{
			new(&this->memoryPool->mtx) std::mutex();
			new(&this->memoryPool->cv) std::condition_variable();
		}
	}

	void initMemoryPool()
	{
		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			this->memoryPool->mtx.lock();

			this->memoryPool->values[i] = 0;
			this->memoryPool->timeWithoutRequest[i] = 0;
			this->memoryPool->clients[i] = false;
			this->memoryPool->serverUpdateTheData[i] = false;
			this->memoryPool->newRequestFromClients[i] = false;
			this->memoryPool->serverUpdatesClientsData = false;

			this->memoryPool->mtx.unlock();
		}
	}

	void printOccupiedMemory()
	{
		std::cout << "Occupied memory idx: ";
		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			std::cout << this->memoryPool->clients[i] << " ";
		}
		std::cout << std::endl;
	}

	void updateClientData()
	{
		//this->memoryPool->serverUpdatesClientsData = false;
		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			if(this->memoryPool->clients[i])
			{
				if(this->memoryPool->newRequestFromClients[i])
				{
					this->memoryPool->values[i] += 10;
					this->memoryPool->serverUpdateTheData[i] = true;
					this->memoryPool->newRequestFromClients[i] = false;
					this->memoryPool->timeWithoutRequest[i] = 0;
				}
				else
				{
					this->memoryPool->serverUpdateTheData[i] = false;
					this->memoryPool->timeWithoutRequest[i]++;
				}
			}
		}
		this->memoryPool->serverUpdatesClientsData = true;
	}

	void checkAndRemoveHangingClients()
	{

		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			if(this->memoryPool->clients[i] && this->memoryPool->timeWithoutRequest[i] >= this->cntForHangingClients)
			{
				this->memoryPool->clients[i] = false;
				this->memoryPool->newRequestFromClients[i] = false;
				this->memoryPool->serverUpdateTheData[i] = false;
				this->memoryPool->timeWithoutRequest[i] = 0;
				this->memoryPool->values[i] = 0;
			}
		}
	}
};

int main(int argc, char *argv[])
{
	Server server;

	server.run(argc);
	server.stop();

	return EXIT_SUCCESS;
}
