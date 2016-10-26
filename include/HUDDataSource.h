#pragma once
#include <Awesomium/DataSource.h>

class HUDDataSource : public Awesomium::DataSource {
private:
  /* data */
public:
  HUDDataSource(){};
  virtual ~HUDDataSource(){};
  /**
   * @brief      The is a function that translates a relative path to any file that will be used by the HUD using the (asset://) prefix.
   *
   * @param[in]  request_id  The identifier of the request issuer
   * @param[in]  request     The request 
   * @param[in]  path        The path to the file requested
   */
  virtual void OnRequest(int request_id,const Awesomium::ResourceRequest& request,const Awesomium::WebString& path);
};
