
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#define NUMBER_OF_DRUG_TYPES 4
using namespace std;
class Mutex{    
public:
    void lock(){cout<<"Mutex acquired the lock"<<endl;}
    void unlock(){cout<<"Mutex released the lock"<<endl;}
};
class drugInfo { 
protected:
    double dosage;
    bool sideEffects;
    string drugName;
    int drugIndex;
public:
    int getDrugIndex() {return drugIndex;}
    string getDrugName(){return drugName;}
    static string indexToName(int index){
        if(index == 0){return "DrugA";}
        if(index == 1){return "DrugB";}
        if(index == 2){return "DrugC";}
        if(index == 3){return "DrugD";}
    }
};
class DrugA: public drugInfo {
public:
    DrugA(){
        drugIndex=0;
        drugName="DrugA";
    }
};
class DrugB: public drugInfo {
public:
    DrugB(){
        drugIndex=1;
        drugName="DrugB";
    }
};
class DrugC: public drugInfo {
public:
    DrugC(){
        drugIndex=2;
        drugName="DrugC";
    }
};
class DrugD: public drugInfo {
public:
    DrugD(){
        drugIndex=3;
        drugName="DrugD";
    }
};
class baseTest { 
protected:
    string testName;
public:
    string getTestName(){ return testName; }
    virtual drugInfo* prescribeRelatedDrug()=0;
};
class baseBloodTest:public baseTest {};
class cardiologyBloodTest:public baseBloodTest {
public:
    cardiologyBloodTest(){ testName="cardiologyBloodTest"; }
    drugInfo* prescribeRelatedDrug(){ return new DrugA;}
};
class endocrinologyBloodTest:public baseBloodTest {
public:
    endocrinologyBloodTest() { testName=("endocrinologyBloodTest"); }
    drugInfo* prescribeRelatedDrug(){ return new DrugB;}
};
class baseRadiologicalTest:public baseTest {};
class cardiologyEKGTest:public baseRadiologicalTest {
public:
    cardiologyEKGTest(){testName="EKG";}
    drugInfo* prescribeRelatedDrug(){ return new DrugC;}
};
class orthopedicsXRayTest:public baseRadiologicalTest {
public:
    orthopedicsXRayTest(){testName="X-RAY";}
    drugInfo* prescribeRelatedDrug(){ return new DrugD;}
};
class baseInsurance
{};
class governmentInsurance:public baseInsurance
{};
class otherInsurance:public baseInsurance
{};
class demographicInfo
{
private:
    string email;
    string telephoneNum;
public:
    void setInfo(string setEmail, string setTelephoneNum){
        email=setEmail;
        telephoneNum=setTelephoneNum;
    }
    const string getEmail() {
        return email;
    }
};
class patient {
private:
    string name;
    demographicInfo* patientDemographicInfo;
    baseInsurance* patientInsurance;
    vector<baseTest*>* testsHaveDone;
    vector<drugInfo*> drugInformationsPatientHolds;
public:
    patient(){}
    ~patient(){
        delete patientInsurance;
        delete patientDemographicInfo;
        delete testsHaveDone;
    }
    patient(string Name="NoName", demographicInfo* Info=NULL, baseInsurance* insurance=NULL,vector<baseTest*>* Tests=NULL){
        name=Name;
        patientDemographicInfo=Info;
        patientInsurance=insurance;
        testsHaveDone=Tests;
    }
    vector<baseTest*>* getTestsHaveDone() {return testsHaveDone;}
    const string getEmail() {return patientDemographicInfo->getEmail();}
    const string getName(){return name;}
    vector<drugInfo *>* getDrugsPatientHolds(){return &drugInformationsPatientHolds;}
    void addDrugInfo(drugInfo* added){drugInformationsPatientHolds.push_back(added);}
    void Update(int drugIndex){cout<<name<<" has been informed about "<<drugInfo::indexToName(drugIndex)<<endl;}
};
class baseTestRequest {
protected:
    string testType;
    string testName;
public:
    virtual baseTest* requestTest()=0;
    string getType(){ return testType;}
    string getTestName(){ return testName;}
};
class EKGrequest:public baseTestRequest {
public:
    EKGrequest(){testType="radiological";testName="EKG";}
    baseTest* requestTest(){ return new cardiologyEKGTest;}
};
class XRAYrequest:public baseTestRequest {
public:
    XRAYrequest(){testType="radiological";testName="X-RAY";}
    baseTest* requestTest(){ return new orthopedicsXRayTest;}
};
