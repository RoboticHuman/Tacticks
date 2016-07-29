#include "HUDDataSource.h"
#include <Awesomium/STLHelpers.h>
#include "Utility.h"
#include <iostream>
using namespace std;
void HUDDataSource::OnRequest(int request_id,const Awesomium::ResourceRequest& request,const Awesomium::WebString& path)
{
  const char* str = readAllFile(ToString(path).c_str());
  SendResponse(request_id,strlen(str),(const unsigned char*)str,Awesomium::WSLit("text/html"));
}

//FUCK AWESOMIUM...
#ifdef __linux__
  Awesomium::DataSource::~DataSource()
  {
  }
#endif
