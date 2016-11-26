#include "2DNavigator.h"
#include "Tacticks/Navigation.h"
#include <algorithm>
void Navigator2D::init(std::vector<PassObject> args){
  if (args.size()==0) fprintf(stdout, "%s\n","Args to 2DNavigator is empty :(");
  else{
    PassArray grid = args[0].asArray();
    for (int i=0;i<grid.size();i++)
    {
      std::vector<bool> row;
      for(int j=0;j<grid[i].asArray().size();j++)
      {
        row.push_back((bool)(grid[i].asArray()[j]).asInteger());
      }
      navGrid.push_back(row);
    }
    initialized = true;
}
}

std::vector<PassObject> Navigator2D::getPossibleNextLocations(int x, int y){
  int di[]={1,-1,0,1};
  int dj[]={0,0,1,-1};
  std::vector<PassObject> tempVec;
  if(initialized){
    for(int i=0;i<4;i++)
    {
      PassArray coordinate(2);
      int newX = x+di[i];
      int newY = y+dj[i];
      if(newX>=0 && newX<navGrid[0].size() && newY>=0 && newY<navGrid[0].size() && navGrid[newX][newY]!=1){
        coordinate[0]=PassObject("x",newX); coordinate[1]=PassObject("y",newY);
        tempVec.push_back(PassObject("coordinate",coordinate));
      }
    }
    std::random_shuffle(tempVec.begin(),tempVec.end());
}
  return tempVec;
}

std::vector<PassObject> Navigator2D::getData(std::string dataName, std::vector<PassObject> args){
  if(dataName=="OneLove"){
    return getPossibleNextLocations(args[0].asInteger(),args[1].asInteger());
  }
}

extern "C"
AbstractNavigation* newNav(){
  return new Navigator2D;
}

extern "C"
NavigationInfo declareDependencies(){
  return {{}};
}
