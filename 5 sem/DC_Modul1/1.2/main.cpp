#include <iostream>
#include "11_Variant.h"
#include <list>

void vA(std::list<Trip> trips) {
    std::cout << "Enter the number of ROUTE" << " (from 1 to" << trips.size() << "): " << std::endl;
    int num;
    cin >> num;
    for(int i = 0; i < trips.size(); i++){
        if(trips[i].getTripRoute().getRouteNumber() == num){
            std::cout << trips[i].getTripBus().getBrand()
            << " " << trips[i].getTripBus().getCarNumber()
            << " " << trips[i].getTripBus().getYearStartOfOperation()
            << " " << trips[i].getTripBus().getMileage() << endl;
        }
    }
}
void vB(std::list<Trip> trips) {
    std::cout << "Enter the year of starting operation with bus: " << std::endl;
    int num;
    cin >> num;
    for(int i = 0; i < trips.size(); i++){
        if(trips[i].getTripBus().getYearOfStartOperation + 5 < num){
            std::cout << trips[i].getTripBus().getBrand()
                      << " " << trips[i].getTripBus().getCarNumber()
                      << " " << trips[i].getTripBus().getYearStartOfOperation()
                      << " " << trips[i].getTripBus().getMileage() << endl;
        }
    }
}
void vC(std::list<Trip> trips) {
    std::cout << "Enter the mileage bus: " << std::endl;
    int num;
    cin >> num;
    for(int i = 0; i < trips.size(); i++){
        if(trips[i].getTripBus().getMileage() < num){
            std::cout << trips[i].getTripBus().getBrand()
                      << " " << trips[i].getTripBus().getCarNumber()
                      << " " << trips[i].getTripBus().getYearStartOfOperation()
                      << " " << trips[i].getTripBus().getMileage() << endl;
        }
    }
}

int main() {
    std::list<Trip> trips;
    Driver d1("Zubenko", "Mikhail", "Petrovich");
    Driver d2("Dimas", "Dimasevich", "Dimasov");
    Driver d3("d3", "d3ovich", "d3tov");
    Driver d4("d4name", "d4patronimyc", "d4surname");

    Bus b1("Mersedes", "AA1111SV", 2011, 500000);
    Bus b2("Slavuta", "SV1111AA", 2012, 600000);
    Bus b3("Audi", "SV1111SV", 2013, 7000000);
    Bus b4("BMW", "SV4444SV", 2014, 800000);

    Route r1("1", 50);
    Route r2("2", 60);
    Route r3("3", 70);
    Route r4("4", 80);

    Trip t1(d1,b1,r1);
    Trip t2(d2,b2,r1);
    Trip t3(d3, b3, r2);
    Trip t4(d4, b4, r4);
    trips.push_back(t1);
    trips.push_back(t2);
    trips.push_back(t3);
    trips.push_back(t4);

    vA(trips);
    vB(trips);
    vC(trips);

    return 0;
}