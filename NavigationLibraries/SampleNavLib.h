#ifndef SampleNavLib_h
#define SampleNavLib_h

#include "NavLibContainer.h"



/**
 * @brief      A sample Navigation Library
 * @details    - All Navigation Libraries must implement "constructedWithSameParams(...)" that returns true if it
 *                  believes that the parameters passed will construct an exact copy of this navigation library
 * - "constructedWithSameParams(...)" basically judges whether it is worth constructing an entirely new
 *                  Navigation Library or if this same one can be used instead
 * - There should be a "constructedWithSameParams(...)" to match every single possible valid constructor of
 *                  the Navigation Library
 */
class SampleNavLib {
    int area;
    float precision;
public:
    
    SampleNavLib(int a){
        area = a;
        precision = 0;
    };
    
    SampleNavLib(int a, float b){
        area = a;
        precision = b;
    };
    
    // This means that the user wishes to use "a" as a parameter for the first constructor
    bool constructedWithSameParams(int a){
        return (a == area && abs(0-precision) < 0.0000001);
    }
    // This means that the user wishes to use "a" and "b" as parametera for the second constructor
    bool constructedWithSameParams(int a, float b){
        return (a == area && abs(b-precision) < 0.0000001);
    }
    
    
};

#endif