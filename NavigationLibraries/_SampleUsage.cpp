#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include "NavLibContainer.h"
#include "SampleNavLib.h"

#include "NLrcPolyMesh.h"
#include "NLrcCompactHeightfield.h"
#include "NLrcPolyMeshDetail.h"
#include "NLrcHeightfield.h"
#include "NLrcContourSet.h"
using namespace std;



int main() {
    
    shared_ptr<SampleNavLib> t1 = NavLibContainer<SampleNavLib>::getNavigationLibrary(1,0);
    shared_ptr<SampleNavLib> t2 = NavLibContainer<SampleNavLib>::getNavigationLibrary(1);
    shared_ptr<SampleNavLib> t3 = NavLibContainer<SampleNavLib>::getNavigationLibrary(1,1);
    
    cout << t1 << ' ' << t2 << ' ' << (t1 == t2) << endl;
    cout << t2 << ' ' << t3 << ' ' << (t2 == t3) << endl;
    
    return 0;
}



