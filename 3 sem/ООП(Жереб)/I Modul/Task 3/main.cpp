#include "Classes\Base.h"
#include "Classes\Alpha.h"
#include "Classes\Beta.h"
#include "Classes\Green.h"
#include "Classes\Red.h"
#include <list>

using namespace std;

void demo() {
    int count = 0; //number of objects
    cout << "Hello, lets create Base class object." << endl;
    Base b1;
    count++;
    cout << "b1 object is created." << endl << endl;
    cout << "Now let's create one more base object and connect him to b1 object" << endl;
    Base b2, *pb2;
    pb2 = &b2;
    count++;
    cout << "b2 object is created." << endl;
    b1.setPtr(pb2);
    cout << "b2 connected to b1" << endl << endl;
    cout << "Now let's create Alpha and Beta class objects." << endl;
    Alpha a1;
    count++;
    cout << "a1 object is created" << endl;
    Beta beta1;
    count++;
    cout << "beta1 object is created" << endl << endl;
    cout << "Now let's create Green and Red class objects." << endl;
    Green g1;
    count++;
    cout << "g1 object is created" << endl;
    Red r1;
    count++;
    cout << "r1 object is created" << endl << endl;
    cout << "End of demo(). Now it's will be destructors of classes." << endl << endl;

}



int main() {
    demo();
    cout << "Back in main(). Final S = " << S << endl;
    return 0;
}
