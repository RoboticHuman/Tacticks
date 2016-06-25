#include "Core.h"

int main(int argc, char* argv[]){
	Core *coreInstance = new Core();
	if(!coreInstance->init()) return -1;
	coreInstance->start();
	coreInstance->shutdown();
	delete coreInstance;
	return 0;
}
