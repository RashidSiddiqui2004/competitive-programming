#include<iostream>
#include<thread>
#include<unistd.h> 

using namespace std;

class AadharIdDepartment{
    int aadharNumber;
public:
    AadharIdDepartment(){
        this->aadharNumber = 0;
    }
    int getAadharNumber(){  
        return aadharNumber;
    }

    void setAadharNumber(int id){
        aadharNumber = id;
    }
};

class AadharCenter{
    AadharIdDepartment* aadharIdDepartment;
    string centerName;
public:
    AadharCenter(string centerName, AadharIdDepartment* aadharIdDepartment){
        this->centerName = centerName;
        this->aadharIdDepartment = aadharIdDepartment;
    }
    void addNewAadhar(){
        int id = aadharIdDepartment->getAadharNumber();
        sleep(1);
        aadharIdDepartment->setAadharNumber(id+1); 
    }
};

void dwarkaCenterTask(AadharCenter* aadharCenter, AadharIdDepartment *aadharIdDepartment){
    for(int i=0;i<10;i++){
        aadharCenter->addNewAadhar();
        cout<<aadharIdDepartment->getAadharNumber()<<endl;
    }
}

void saketCenterTask(AadharCenter* aadharCenter, AadharIdDepartment *aadharIdDepartment){
    for(int i=0;i<10;i++){
        aadharCenter->addNewAadhar();
        cout<<aadharIdDepartment->getAadharNumber()<<endl;
    }
}

int main(){
    AadharIdDepartment* aadharIdDepartment = new AadharIdDepartment();
    AadharCenter* dwarkaCenter = new AadharCenter("dwarka", aadharIdDepartment);
    AadharCenter* saketCenter = new AadharCenter("saket", aadharIdDepartment);
    thread t1(dwarkaCenterTask, dwarkaCenter, aadharIdDepartment);
    thread t2(saketCenterTask, saketCenter, aadharIdDepartment);

    t1.join();
    t2.join();

    return 0;
}

// data inconsistency, can't rely on this data
// race condition
// when output changes based on order of execution
// shared resource
// critical section - the CS refers to the particular section of code where processes/
// threads access 
// shared resouces such as common variables, files, etc. and perform write operations
// on them.
// any thread/process can be interrupted min-execution

// thread scheduling algorithm can swap between threads at any point in time
// so we can't know the order of thread execution