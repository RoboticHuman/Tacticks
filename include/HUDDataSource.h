#pragma once
#include <Awesomium/DataSource.h>

class HUDDataSource : public Awesomium::DataSource {
private:
  /* data */
public:
  HUDDataSource(){};
  virtual ~HUDDataSource(){};
  virtual void OnRequest(int request_id,const Awesomium::ResourceRequest& request,const Awesomium::WebString& path);
};
