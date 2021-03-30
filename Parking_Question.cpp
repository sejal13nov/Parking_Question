/* @author Sejal Patel*/
/*Input---- filename in the command line arguments*/
/* Please pass filename in the command line argument*/
#include<bits/stdc++.h>
using namespace std;
//enum for commands used in the file,
//if we want to add or delete any command it should be reflected here
enum string_code{
    // create_slots,
    park,
    slots_for_age,
    slot_for_car,
    leave,
    vehicles_for_age
};
// function to compare string (case insensitive)  park or Park ---> bith are treated equal
int compare_strings(string str1, string str2){
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    if(str1.compare(str2) == 0)
      return 1;
   return 0;

}
//mapped enum with strings such that strings can be used in switch cases--otherwise not possible
string_code map_enum(std::string const& inString) {
    // if (compare_strings(inString,"Create_parking_lot")) return create_slots;
    if (compare_strings(inString,"Park"))return park;
    if (compare_strings(inString,"Slot_numbers_for_driver_of_age")) return slots_for_age;
    if (compare_strings(inString, "Slot_number_for_car_with_number")) return slot_for_car;
    if (compare_strings(inString,"Leave")) return leave;
    if (compare_strings(inString, "Vehicle_registration_number_for_driver_of_age")) return vehicles_for_age;    
}
// class for parkingslots.. it will have car_no,driver_age and is it available or already alloted
class ParkingSlot{
public:
    bool available;  // true if its available, false if already alloted
    string car_number; //assumed any string value is possible for car_number
    int driver_age;

    parkingSlot(){
        available = true;
        car_number = "";
        driver_age = -1;
    }
};
class Parking{
    public :
        int parkinSlotSize;
        ParkingSlot parkingSlot[1000];
        void createParkingSlot(string);  // to create parking slots 
        int park_car(string, string);    // park car with car_number and driver_age
        int get_available_parking();
        vector<int> slot_no_age(string);  // get all slots with driver_age as given
        int slot_no_car(string);  // get slot number for given car number
        void leave_car(string);    // empty given slot_no when car leaves
        vector<string> vehicles_by_age(string);  // all vehicles number for given driver age
};
void Parking :: createParkingSlot(string size){    
    parkinSlotSize=stoi(size);
    for(int i =0;i<parkinSlotSize;i++){
        parkingSlot[i].available=true;
    }
}
int Parking :: get_available_parking(){
    int ans=-1;
    for(int i =0;i<parkinSlotSize;i++){
        if(parkingSlot[i].available==true){
            ans=i;
            break;
        }
    } 
    return ans;
}
int Parking :: park_car(string car_no, string age){
    int available_slot = get_available_parking();
    if(available_slot== -1){
        cout<<"Parking is Full,Sorry for the inconvenience"<<endl;
    }else{
        parkingSlot[available_slot].available=false;
        parkingSlot[available_slot].car_number=car_no;
        parkingSlot[available_slot].driver_age=stoi(age);
    }
    return available_slot;
}
vector<int> Parking :: slot_no_age(string age){
    vector<int> v1;
    for(int i =0;i<parkinSlotSize;i++){
        if(parkingSlot[i].driver_age==stoi(age)){
            v1.push_back(i+1);
        }
    }
    return v1;
}
int  Parking ::slot_no_car(string car_no){
  for(int i =0;i<parkinSlotSize;i++){
        // cout<<parkingSlot[i].car_number<<"  ----"<<car_no<<endl;
        if(parkingSlot[i].car_number==car_no){
            return i+1;
        }
    } 
}
void Parking :: leave_car(string slot){
    int slot_no=stoi(slot)-1;
    cout<<"Slot number"<<slot_no+1<<" vacated, the car with vehicle registration number ";
    cout<<parkingSlot[slot_no].car_number<<" left the space, the driver of the car was of age ";
    cout<<parkingSlot[slot_no].driver_age<<endl;
    parkingSlot[slot_no].available=true;
    parkingSlot[slot_no].car_number="";
    parkingSlot[slot_no].driver_age=-1;  
}
vector<string> Parking ::vehicles_by_age(string age){
    vector<string> v1;
    for(int i =0;i<parkinSlotSize;i++){
        if(parkingSlot[i].driver_age==stoi(age)){
            v1.push_back(parkingSlot[i].car_number);
        }
    }
    return v1;  
}
// to print int vector
void print_vector(vector<int> v1){
    for(int i=0;i<v1.size();i++){
        if(i==0)
            cout<<v1[i];
        else
            cout<<","<<v1[i];
    }
    cout<<endl;
}
//to print string vector
void print_vectorstr(vector<string> v1){
    for(int i=0;i<v1.size();i++){
        if(i==0)
            cout<<v1[i];
        else
            cout<<","<<v1[i];
    }
    cout<<endl;
}
int main(int argc, char **argv){
     fstream MyReadFile;
     string nextWord,car_no,age,firstWord;
     Parking parking;
     //open file to read
     MyReadFile.open(argv[1], std::fstream::in);
     if (!MyReadFile ) {
       	cout << "Cannot open file, plase check file name/path once ";
     }
     else{
        MyReadFile >> firstWord;
        if(compare_strings(firstWord,"Create_parking_lot")){
            MyReadFile >> nextWord;
            parking.createParkingSlot(nextWord);
            cout<<"Created parking of "<<nextWord<<" slots"<<endl;
        }else{
            cout<<"First line should always be for creating parking slots \n";
            cout<<"Please check the input file format \n";
            return 0;
        }
        while(!MyReadFile.eof()){
            MyReadFile >> nextWord;
            int availableslot,s;
            vector <int> v1;
            vector <string> vehicles;
            switch(map_enum(nextWord)){
                case  park             : MyReadFile >> car_no; // car_no
                                         MyReadFile >> nextWord;//driver_of_age
                                         MyReadFile >> age; //age
                                         availableslot=parking.park_car(car_no,age);
                                         if(availableslot!=-1){
                                                cout<<"Car with vehicle registration number \""<<car_no;
                                                cout<<"\" has been parked at slot number";
                                                cout<<availableslot+1<<endl;
                                         }
                                         
                                         break;

                case slots_for_age     : MyReadFile >> age;
                                         v1=parking.slot_no_age(age); //check for age
                                         print_vector(v1);
                                         break;
                case slot_for_car      :  MyReadFile >> car_no;
                                          s=parking.slot_no_car(car_no);
                                          cout<<s<<endl;
                                          break;
                case leave              : MyReadFile >> nextWord;
                                          parking.leave_car(nextWord);
                                          break;
                case vehicles_for_age   : MyReadFile >> age;
                                          vehicles=parking.vehicles_by_age(age);
                                          print_vectorstr(vehicles);
                                          break;
                default                 : cout<<"Format is not correct in input file :("<<endl;
                                          cout<<"can you please check once ??"<<endl;
                                          return 0;
                

            }
        }    
    }
      
MyReadFile.close();
return 0;
	
}