#include <iostream>
#include <Tacticks/PassObject.h>
#include <Tacticks/BehaviourPipeline.h>
#include <Tacticks/AbstractNavigation.h>
#include <Tacticks/AbstractBehaviourModule.h>
#include <Tacticks/PassObjectArray.h>
#include <Tacticks/PassObjectBool.h>
#include <Tacticks/PassObject.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <glm/ext.hpp>
using namespace glm;
using namespace std;

BehaviourPipeline pipeline;

int n, m;
vector<vector<bool>> grid;
int catGroupID;
vector<int> catID;
int mouseID;

void init()
{
	srand(time(0));
	n = m = 20;
	grid.assign(n, vector<bool>(m, false));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(rand()%100 < 25) grid[i][j] = true;
			else grid[i][j] = false;

	catGroupID = pipeline.addGroup();
	AgentGroup* catGroup = pipeline.getGroupByID(catGroupID);
	for(int i = 0; i < 5; i++){
		catID.push_back(pipeline.addAgent());
		Agent* catAgent = pipeline.getAgentByID(catID.back());
		catGroup->addAgent(catAgent);
		dynamic_cast<AgentAttributeVec3*>(catAgent->getAttribute("Position"))->setValue(vec3(rand()%m, rand()%n, 0));
	}
	mouseID = pipeline.addAgent();
	dynamic_cast<AgentAttributeVec3*>(pipeline.getAgentByID(mouseID)->getAttribute("Position"))->setValue(vec3(rand()%m, rand()%n, 0));
}
void updatePos(const vector<pair<int, vec3>>& newPos)
{
	for(auto p : newPos){
		AgentAttributeVec3* pos = dynamic_cast<AgentAttributeVec3*>(pipeline.getAgentByID(p.first)->getAttribute("Position"));
		pos->setValue(pos->getValue() + p.second);
	}
}
void print()
{
	ivec3 mousePos = dynamic_cast<AgentAttributeVec3*>(pipeline.getAgentByID(mouseID)->getAttribute("Position"))->getValue();
	char arr[n][m+1]={};
	for(int i = 0; i < grid.size(); i++)
		for(int j = 0; j < grid.size(); j++)
			if(grid[i][j]) arr[i][j] = char(219);
			else arr[i][j] = char(32);
	arr[mousePos.y][mousePos.x] = 'M';
	for(int cID : catID){
		ivec3 catPos = dynamic_cast<AgentAttributeVec3*>(pipeline.getAgentByID(cID)->getAttribute("Position"))->getValue();
		arr[catPos.y][catPos.x] = 'C';
	}
	for(int i = 0; i < n; i++)
		printf("%s\n", arr[i]);
}
PassObject* grid2PassObject(vector<vector<bool> >& Grid)
{
    PassObjectArray* grid= new PassObjectArray(n, "grid");
    for(int i=0; i<n; i++)
    {
		PassObjectArray* row= new PassObjectArray(m, "row");
    	for(int j=0; j<m; j++)
			(*row)[j]=new PassObjectBool(Grid[i][j], "cell");
    	(*grid)[i]=row;
    }
    return grid;
}

int main()
{
	init();
	pipeline.addNavigationLibrary("2DNavigator")->getNav()->setParameters({grid2PassObject(grid)});
	pipeline.addForcesModule("CatnMouse")->getBeh()->setParameters({});

	pipeline.compile();
	int i = 0;
	while(true){
		cout << "Iteration" << i++ << endl;
		print();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		updatePos(pipeline.simulate());
		cout << endl << endl << endl;
	}
}
