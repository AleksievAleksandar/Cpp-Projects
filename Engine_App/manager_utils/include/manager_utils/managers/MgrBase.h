#ifndef MGR_BASE_H
#define MGR_BASE_H

//C system includes

//C++ system includes

//Thitrd-party includes

//Own includes

//Forward Declarations

enum
{
	DRAW_MGR_IDX,
	RSRC_MGR_IDX,
	MANAGERS_COUNT
};

class MgrBase 
{
public:
	MgrBase() = default;
	virtual ~MgrBase() = default;

	//forbid the copy and move constructors
	MgrBase(const MgrBase& other) = delete;
	MgrBase(MgrBase&& other) = delete;

	//forbid the copy and move assignment operators
	MgrBase& operator=(const MgrBase& other) = delete;
	MgrBase& operator=(MgrBase&& other) = delete;

	virtual void deInit() = 0;
	virtual void process() = 0;
};


#endif // !MGR_BASE_H
