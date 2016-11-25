#include "2DNavigator.h"
#include <algorithm>
void 2DNavigator::init(std::vector<PassObject> args){
  PassArray grid = object.asArray();
  for (int i=0;i<grid.size();i++)
  {
    vector<bool> row;
    for(int j=0;j<grid[i].size();j++)
    {
      row.push_back((bool)grid[i][j]);
    }
    grid.push_back(row);
  }
}

std::vector<PassObject> 2DNavigator::getPossibleNextLocations(int x, int y){
  int di[]={1,-1,0,1};
  int dj[]={0,0,1,-1};
  std::vector<PassObject> tempVec;
  for(int i=0;<4;i++)
  {
    PassArray coordinate(2);
    int newX = x+di[i];
    int newY = y+dj[j];
    if(newX>=0 && newX<grid[0].size() && newY>=0 && newY<grid[0].size() && grid[newX][newY]!=1){
      coordinate[0]=newX; coordinate[1]=newY;
      tempVec.push_back(PassObject("coordinate",coordinate));
    }
  }
  std::random_shuffle(tempVec.begin(),tempVec.end());
  return tempVec;
}

std::vector<PassObject> 2DNavigator::getData(std::string dataName, std::vector<PassObject> args){
  if(dataName=="OneLove"){
    return getPossibleNextLocations(args[0].asInteger(),args[1].asInteger());
  }
}
