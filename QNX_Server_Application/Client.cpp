#include "Client.h"

/*======================== ClientOne =========================================*/
ClientOne::ClientOne(CommunicationChanel& communicationChanel) :
	IClient(communicationChanel)
{}


/*======================== ClientTwo =========================================*/
ClientTwo::ClientTwo(CommunicationChanel& communicationChanel) :
	IClient(communicationChanel)
{}
