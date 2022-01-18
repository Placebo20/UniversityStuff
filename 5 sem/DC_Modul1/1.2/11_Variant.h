//
// Created by dimag on 02.11.2021.
//

#ifndef DC_MODUL1_11_VARIANT_H
#define DC_MODUL1_11_VARIANT_H
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Driver {
private:
    string name;
    string patronimyc;
    string surname;
public:
    Driver(){
        name = "";
        patronimyc = "";
    }
    Driver(string name, string surname, string patronimyc) {
        this->name = name;
        this->patronimyc = patronimyc;
        this->surname = surname;
    }
    void fillingInEmptyDriver(string name,  string surname, string patronimyc) {
        this->name = name;
        this->patronimyc = patronimyc;
        this->surname = surname;
    }
    void setfullName(string name, string patronimyc, string surname) {
        this->name = name;
        this->patronimyc = patronimyc;
        this->surname = surname;
    }
    string getDriverName() {
        return name;
    }
    string getDriverPatronimyc() {
        return patronimyc;
    }
    string getDriverSurname() {
        return surname;
    }
    void toString() {
        cout << this->surname << " " << this->name[0] << ". " << this->patronimyc[0] << "." << endl;
    }

};

class Bus {
private:
    string brand;
    string carNumber;
    int yearStartOfOperation;
    int mileage;
public:
    Bus() {
        brand = "";
        carNumber = "";
        int yearStartOfOperation = 0;
        int mileage = 0;
    }
    Bus(string brand, int yearStartOfOperation, int mileage) {
        this->brand = brand;
        this->yearStartOfOperation = yearStartOfOperation;
        this->mileage = mileage;
    }
    Bus(string brand, int yearStartOfOperation, int mileage, string carNumber){
        this->brand = brand;
        this->carNumber = carNumber;
        this->yearStartOfOperation = yearStartOfOperation;
        this->mileage = mileage;
    }
    void setBrand(string brand){
        this->brand = brand;
    }
    void setCarNumber(string carNumber){
        this->carNumber = carNumber;
    }
    void setYearStartOfOperation(string yearStartOfOperation) {
        this->yearStartOfOperation = yearStartOfOperation;
    }
    void setMileage(string mileage){
        this->mileage = mileage;
    }
    string getCarBrand() {
        return brand;
    }
    string getCarNumber() {
        return carNumber;
    }
    int getYearStartOfOperation(){
        return yearStartOfOperation;
    }
    int returnMileage() {
        return mileage;
    }

};

class Route {
    string routeNumber;
    int durationInKilometers;
public:
    Route(){
        routeNumber = "";
        durationInKilometers = 0;
    }
    Route(string routeNumber, int durationInKilometers){
        this->routeNumber = routeNumber;
        this->durationInKilometers = durationInKilometers;
    }
    void setRouteNumber (string routeNumber){
        this->routeNumber = routeNumber;
    }
    void setDurationInKilometers(strint durationInKilometers){
        this->durationInKilometers = durationInKilometers;
    }
    string getRouteNumber() {
        return routeNumber;
    }
    int getDurationInKilometers() {
        return durationInKilometers;
    }
};

class Trip {
    Driver tripDriver;
    Bus tripBus;
    Route tripRoute;
public:
    Trip();
    Trip(Driver tripDriver, Bus tripBus, Route tripRoute){
        this->tripDriver.setfullName(tripDriver.getDriverName(),tripDriver.getDriverPatronimyc(),tripDriver.getDriverSurname());
        this->tripBus.setBrand(tripBus.getCarBrand());
        this->tripBus.setCarNumber(tripBus.getCarNumber());
        this->tripBus.setYearStartOfOperation(tripBus.getYearStartOfOperation());
        this->tripRoute.setRouteNumber(tripRoute.getRouteNumber());
        this->tripRoute.setDurationInKilometers(tripRoute.getDurationInKilometers());
    }
    void setDriver(Driver tripDriver) {
        this->tripDriver.setfullName(tripDriver.getDriverName(),tripDriver.getDriverPatronimyc(),tripDriver.getDriverSurname());
    }
    void setTripBus(Bus tripBus){
        this->tripBus.setBrand(tripBus.getCarBrand());
        this->tripBus.setCarNumber(tripBus.getCarNumber());
        this->tripBus.setYearStartOfOperation(tripBus.getYearStartOfOperation());
    }
    void setTripRoute(Route tripRoute){
        this->tripRoute.setRouteNumber(tripRoute.getRouteNumber());
        this->tripRoute.setDurationInKilometers(tripRoute.getDurationInKilometers());
    }
    Driver getDriver(){
        return tripDriver;
    }
    Bus getBus(){
        return tripBus;
    }
    Route getRoute() {
        return tripRoute;
    }
};
#endif //DC_MODUL1_11_VARIANT_H
