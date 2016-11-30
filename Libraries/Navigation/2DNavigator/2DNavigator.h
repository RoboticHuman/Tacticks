#pragma once
#include "Tacticks/AbstractNavigation.h"
#include "Tacticks/PassObject.h"
#include <vector>
class Navigator2D : public AbstractNavigation{
private:
  std::vector<std::vector<bool>> navGrid;
  int n, m;
  std::vector<PassObject*> getPossibleNextLocations(int x, int y);
public:
    virtual bool init();
  virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args) override;
};
