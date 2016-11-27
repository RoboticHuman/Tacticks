#include <iostream>
#include <Tacticks/PassObject.h>
#include <Tacticks/BehaviourPipeline.h>
#include <Tacticks/AbstractNavigation.h>
#include <vector>
#include <unistd.h>
using namespace std;

BehaviourPipeline pipeline;

int n, m;
vector<vector<bool>> grid;
int catID;
int mouseID;

void init()
{
	n = m = 20;
	grid.assign(n, vector<bool>(m, false));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(rand()%100 < 25) grid[i][j] = true;
			else grid[i][j] = false;
	catID = mouseID = -1;	//AddAgent
}
void printFrame()
{
	system("clear");
	for(int i = 0; i < grid.size(); i++, printf("\n"))
		for(int j = 0; j < grid.size(); j++)
			if(grid[i][j]) printf("%c", char(219));
			else printf("%c", char(32));
}
PassObject grid2PassObject(vector<vector<bool> >& Grid){
    PassArray grid(n);
    for(int i=0; i<n; i++)
    {
		PassArray row(m);
    	for(int j=0; j<m; j++)
			row[j]=PassObject("cell", Grid[i][j]);
		cout << "hmm" << endl;
    	grid[i]=PassObject("row", row);
		cout << "Well??" << endl;
    }
    return PassObject("grid",grid);
}

int main()
{
	init();
	pipeline.addMilestonesModule("CatnMouse")->getBeh()->init({});
	grid2PassObject(grid);
	//fun(grid);
	//pipeline.addNavigationLibrary("2DNavigator")->getNav()->init({grid2PassObject(grid)});

	for(int i = 0; i < 20; i++){
		printFrame();
		usleep(100*1000);
		//Simulate & Update
	}
}
