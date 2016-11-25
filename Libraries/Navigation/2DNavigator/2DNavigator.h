#pragma once
#include "Tacticks/AbstractNavigation"
#include "Tacticks/PassObject.h"
#include <vector>
class 2DNavigator : public AbstractNavigation{
private:
  PassObject passObject;
  std::vector<std::vector<bool>> grid;
  std::vector<PassObject> getPossibleNextLocations();
public:
  2DNavigator();
  ~2DNavigator ();
  virtual void init(std::vector<PassObject> args) override;
  virtual std::vector<PassObject> getData(std::string dataName, std::vector<PassObject> args) override;
};
