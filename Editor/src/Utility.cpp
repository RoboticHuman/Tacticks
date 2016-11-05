#include <cstdio>
#include "Utility.h"

char* readAllFile(const char* fpath)
{
	unsigned long long fsz;
	char* buf;

	FILE* file = fopen(fpath, "r");
	if(file == nullptr){
		printf("Error:: Unable to load shader file: %s\n", fpath);
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	fsz = ftell(file);
	rewind(file);

	buf = new char[fsz+1]();
	if(fread(buf, 1, fsz, file) != fsz){
		printf("Unexpected error while reading file: %s\n", fpath);
		fclose(file);
		delete [] buf;
		return nullptr;
	}
	fclose(file);
	return buf;
}
