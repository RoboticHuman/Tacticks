#include "2DNavigator.h"
#include "Tacticks/Navigation.h"
#include <algorithm>
#include "Tacticks/PassObjectArray.h"
#include "Tacticks/PassObjectInt.h"
void Navigator2D::init(std::vector<PassObject*> args){
  if (args.size()==0) fprintf(stdout, "%s\n","Args to 2DNavigator is empty :(");
  else{
    PassObjectArray* grid = dynamic_cast<PassObjectArray*>(args[0]);
    if(grid)
    {
        for (int i=0;i<grid->getSize();i++)
        {
          std::vector<bool> row;
          PassObjectArray* gridRow = dynamic_cast<PassObjectArray*>((*grid)[i]);
          if(gridRow){
          for(int j=0;j<gridRow->getSize();j++)
          {
            PassObjectInt* cellValue = dynamic_cast<PassObjectInt*>((*gridRow)[j]);
            if(cellValue)
            row.push_back((bool)(cellValue->getValue()));
          }
          navGrid.push_back(row);
        }
        }
        initialized = true;
    }
    }
}

std::vector<PassObject*> Navigator2D::getPossibleNextLocations(int x, int y){
  int di[]={1,-1,0,1};
  int dj[]={0,0,1,-1};
  std::vector<PassObject*> tempVec;
  if(initialized){
    for(int i=0;i<4;i++)
    {
      PassObjectArray* tempCoordinate = new PassObjectArray(2);
      int newX = x+di[i];
      int newY = y+dj[i];
      if(newX>=0 && newX<navGrid[0].size() && newY>=0 && newY<navGrid[0].size() && navGrid[newX][newY]!=1){
        PassObjectInt* first= new PassObjectInt(newX); PassObjectInt* second = new PassObjectInt(newY);
        (*tempCoordinate)[0]=first; (*tempCoordinate)[1]=second;
        tempVec.push_back(tempCoordinate);
      }
    }
}
  return tempVec;
}

std::vector<PassObject*> Navigator2D::getData(std::string dataName, std::vector<PassObject*> args){
  if(dataName=="OneLove"){
    PassObjectInt* X = dynamic_cast<PassObjectInt*>(args[0]);
    PassObjectInt* Y = dynamic_cast<PassObjectInt*>(args[1]);
    int x, y;
    if(X && Y) {x = X->getValue(); y = Y->getValue();}
    return getPossibleNextLocations(x,y);
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
