#include<iostream>
#include<map>
using namespace std;

enum Vehicle_Type { 
    BIKE,
    CAR,
    TRUCK
};

class User{
    string username;
public:
    User(string name): username(name){}
};

class Vehicle{
    string vehicle_number;
    Vehicle_Type type;
    User* owner;
public:
    Vehicle(Vehicle_Type type, string vehicle_number, User* owner): type(type), 
    vehicle_number(vehicle_number), owner(owner){}

    Vehicle_Type getType(){
        return type;
    }
};

// abstract class
class ParkingSpot{
protected:
    int spotId;
    Vehicle_Type type;
    bool available;
    Vehicle* parkedVehicle;
    mutable mutex mtx; // mutable so const methods can lock too
public:
    ParkingSpot(int id, Vehicle_Type t) : spotId(id), type(t), 
        available(true), parkedVehicle(nullptr) {}
    virtual bool park(Vehicle* v) {
        lock_guard<mutex> lock(mtx); // lock immediately
        if (!isAvailable(v)) return false; // check under lock

        parkedVehicle = v;
        available = false;
        return true;
    }
    virtual Vehicle* release() {
        lock_guard<mutex> lock(mtx);
        Vehicle* vehicleToRelease = parkedVehicle;
        parkedVehicle = nullptr;
        available = true;
        return vehicleToRelease;
    }
    bool isAvailable(Vehicle* v) {  
        return v->getType() == type && available;
    }
    int getId() { return spotId; }
};

class BikeSpot : public ParkingSpot {
public:
    BikeSpot(int id) : ParkingSpot(id, Vehicle_Type::BIKE) {}
};

class CarSpot : public ParkingSpot {
public:
    CarSpot(int id) : ParkingSpot(id, Vehicle_Type::CAR) {}
};

class TruckSpot : public ParkingSpot {
public:
    TruckSpot(int id) : ParkingSpot(id, Vehicle_Type::TRUCK) {}
};

// abstact class
class ParkingSpotFactory{
public:
    virtual unique_ptr<ParkingSpot> createParkingSpot(int spotid) = 0;
    virtual ~ParkingSpotFactory(){}
};

class BikeParkingSpotFactory:public ParkingSpotFactory{
public:
    unique_ptr<ParkingSpot> createParkingSpot(int spotid) override{
        return make_unique<BikeSpot>(spotid);
    }
};

class CarParkingSpotFactory:public ParkingSpotFactory{
public:
    unique_ptr<ParkingSpot> createParkingSpot(int spotid) override{
        return make_unique<CarSpot>(spotid);
    }
};

class TruckParkingSpotFactory:public ParkingSpotFactory{
public:
    unique_ptr<ParkingSpot> createParkingSpot(int spotid) override{
        return make_unique<TruckSpot>(spotid);
    }
};
 
class ParkingFloor { 
    int floorNumber;
    vector<unique_ptr<ParkingSpot>> parkingSpots;
    unordered_map<Vehicle_Type, unique_ptr<ParkingSpotFactory>> parkingSpotFactories;

public:
    ParkingFloor(int floorNumber) : floorNumber(floorNumber) {
        parkingSpotFactories[BIKE]  = make_unique<BikeParkingSpotFactory>();
        parkingSpotFactories[CAR]   = make_unique<CarParkingSpotFactory>();
        parkingSpotFactories[TRUCK] = make_unique<TruckParkingSpotFactory>();
    }

    void addParkingSpot(Vehicle_Type vehicleType) {
        int nextSpotId = parkingSpots.size() + 1;  
        parkingSpots.push_back(parkingSpotFactories[vehicleType]->createParkingSpot(nextSpotId));
    }

    vector<ParkingSpot*> getParkingSpots() {
        vector<ParkingSpot*> rawPtrs;
        for (auto& spot : parkingSpots) rawPtrs.push_back(spot.get());
        return rawPtrs;
    }
};

class ParkingLotSystem{
    string name;
    vector<ParkingFloor*> floors;
    map<Vehicle*, ParkingSpot*> parkedVehicles;
public:
    ParkingLotSystem(string name){
        this->name = name;
    }
    void addFloor(){
        int floorNumber = floors.size(); // 0-based floor numbering
        this->floors.push_back(new ParkingFloor(floorNumber));
    }
    void removeFloor(){
        floors.pop_back();
    }
    ParkingSpot* getNearestParkingSpot(Vehicle* vehicle){
        // start searching from ground floor (floor=0)
        for(auto floor: floors){
            for(auto parkingSpot: floor->getParkingSpots()){
                if(parkingSpot->isAvailable(vehicle)){
                    return parkingSpot;
                }
            }
        }
        cout<<"Sorry, no parking spot available :(\n";
        cout<<"Please check after sometime...\n";
        return nullptr;
    }

    bool parkVehicle(Vehicle* vehicle){
        ParkingSpot* availableSpot = getNearestParkingSpot(vehicle);
        if(!availableSpot){
            return false;
        }
        availableSpot->park(vehicle);
        parkedVehicles[vehicle] = availableSpot;
        return true;
    }

    Vehicle* releaseVehicle(Vehicle* vehicle){
        if(!parkedVehicles.count(vehicle)){
            cout<<"Your vehicle is not parked here in " + name + " \n";
            return nullptr;
        }
        ParkingSpot* parkingSlot = parkedVehicles[vehicle];
        parkedVehicles.erase(vehicle);
        return parkingSlot->release();
    }
};