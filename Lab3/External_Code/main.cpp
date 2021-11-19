#include "vect.hpp"
#include "toolib.hpp"
#include "external_code.hpp"

/******************************************************/
//Example:
//Input : Polygon : (100,150), (200,250), (300,200)
//        Clipping Area : (150,150), (150,200), (200,200), 
//                            (200,150) i.e. a Square    
//Output : (150, 162) (150, 200) (200, 200) (200, 174)

// Example:
//Polygon:
//(100, 200) (150, 203) (168, 279)
//Clipping area:
//(120, 130) (123, 150) (124, 170) (130, 200)
//Output:
//(130, 203) (130, 201) (130, 201)
/*****************************************************/

int main() {
    puts("Would you use test values? 1 - yes, else - no");
    int choise;
    getEl(choise, std::cin);
    if (choise != 1) {
        dialog();
    } else {
        test_coords();
    }
    return 0;

}