#include "HUDMenuHandler.h"
#include <Awesomium/STLHelpers.h>
void HUDMenuHandler::OnShowPopupMenu(Awesomium::WebView* caller, const WebPopupMenuInfo& menuInfo)
{
  auto items = menuInfo.items;
  for(int i=0; i<items.size();i++)
    std::cout<<ToString(items[i].label)<<std::endl;
}
void HUDMenuHandler::OnShowContextMenu(Awesomium::WebView *view,const Awesomium::WebContextMenuInfo &info) {
}
