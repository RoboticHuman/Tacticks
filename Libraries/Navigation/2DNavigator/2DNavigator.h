#pragma once
#include "Tacticks/AbstractNavigation.h"
#include "Tacticks/PassObject.h"
#include <vector>
class Navigator2D : public AbstractNavigation{
private:
  PassObject passObject;
  std::vector<std::vector<bool>> navGrid;
  std::vector<PassObject> getPossibleNextLocations(int x, int y);
  bool initialized=false;
public:
  virtual void init(std::vector<PassObject> args) override;
  virtual std::vector<PassObject> getData(std::string dataName, std::vector<PassObject> args) override;
};
