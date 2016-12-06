#include "2DNavigator.h"
#include <Tacticks/Navigation.h>
#include <algorithm>
#include <Tacticks/PassObjectArray.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectBool.h>

Navigator2D::Navigator2D(const World* world) : AbstractNavigation(world){}

bool Navigator2D::init()
{
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
						PassObjectBool* cellValue = dynamic_cast<PassObjectBool*>((*gridRow)[j]);
						if(cellValue)
							row.push_back((bool)(cellValue->getValue()));
					}
					navGrid.push_back(row);
			    }
		    }
			n = navGrid.size();
			m = navGrid[0].size();
		    clearDirty();
		}
	}
}

std::vector<PassObject*> Navigator2D::getPossibleNextLocations(int x, int y)
{
	int di[]={1,-1,0,0};
	int dj[]={0,0,1,-1};

	std::vector<PassObject*> tempVec;
	for(int i=0;i<4;i++)
    {
		PassObjectArray* tempCoordinate = new PassObjectArray(2);
		int newX = x+di[i];
		int newY = y+dj[i];
		if(newX>=0 && newX<m && newY>=0 && newY<n && !navGrid[newY][newX]){
			PassObjectInt* first= new PassObjectInt(di[i]); PassObjectInt* second = new PassObjectInt(dj[i]);
			(*tempCoordinate)[0]=first; (*tempCoordinate)[1]=second;
			tempVec.push_back(tempCoordinate);
			}
	}
    return tempVec;
}

std::vector<PassObject*> Navigator2D::getData(std::string dataName, std::vector<PassObject*> args)
{
    if(isDirty()){
        navGrid.clear();
        init();
    }
    if(dataName=="OneLove"){
	    PassObjectInt* X = dynamic_cast<PassObjectInt*>(args[0]);
	    PassObjectInt* Y = dynamic_cast<PassObjectInt*>(args[1]);
	    int x, y;
	    if(X && Y) {x = X->getValue(); y = Y->getValue();}
	    return getPossibleNextLocations(x,y);
	}
}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new Navigator2D(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{}};
}
