#include <iostream>
#include "Core.h"
using namespace std;

int main(int argc, char* argv[]){
	cout<<"Hello world"<<endl;
	Core *coreInstance = new Core();
	if(!coreInstance->init()) return -1;
	coreInstance->start();
	delete coreInstance;
	return 0;
}
