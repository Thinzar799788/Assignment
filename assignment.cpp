#include<iostream>
#include<ctype.h>
#include<iomanip>

using namespace std;
int PLAN = 0;
int CUSTOMER  = 0;
int POSITION = 0;

class TrainingPlan{
    string TPName;
    int session;
    float feesPerWeek;
    float feesPerMonth;
    public:
        TrainingPlan(){
            TPName = "";
            session = 0;
            feesPerMonth = 0;
            feesPerWeek = 0;
        }
        TrainingPlan(string n, int s, float fpw, float fpm){
           	TPName = n;
            session = s;
            feesPerWeek = fpw;
            feesPerMonth = fpm;
            PLAN++;
        }
        void setPlan(){
            cout<<"input plan name : ";
            cin.get();
            getline(cin, TPName);
            cout<<"input sesion per week : ";
            cin>>session;
            feeLabel:
            cout<<"input fees per week(enter 0 if you consider adding fees per month) : ";
            cin>>feesPerWeek;
            cout<<"input fees per month(enter 0 if fees per week is already inputted) : ";
            cin>>feesPerMonth;
            if(feesPerMonth > 0 && feesPerWeek > 0) {
                cout<<"You entered both values greather than 0.\n";
                cin.get();
                goto feeLabel;
            }
            cout<<"Succeeded in created a training plan("<<TPName<<")!\n";
            cin.get();
            PLAN++;
        }
        void updatePlan(){
            cout<<"Plan name("<<TPName<<") : \n";
            cout<<"Input sessions per week ("<<session<<") : ";
            cin>>session;
            feeLabel:
            cout<<"Input fees per week ("<<feesPerWeek<<") : ";
            cin>>feesPerWeek;
            cout<<"Input fees per month ("<<feesPerMonth<<") : ";
            cin>>feesPerMonth;
            if(feesPerMonth > 0 && feesPerWeek > 0) {
                cout<<"You entered both values greather than 0.\n";
                cin.get();
                goto feeLabel;
            }
            cout<<"Successfully updated the training plan("<<TPName<<")!\n";
            cin.get();
        } 
        string getPlanName() {return TPName;}
        float getFeesPerWeek() {return feesPerWeek;}
        float getFeesPerMonth() {return feesPerMonth;}
        int getSessionsPerWeek() {return session;}
        void displayPlan(){
            cout<<setw(20)<<TPName
                <<setw(20)<<session
                <<setw(15)<<feesPerWeek
                <<setw(15)<<feesPerMonth;
        }
};
class Customer{
    string cusName;
    TrainingPlan trainingPlan;
    float currentWeight;
    int learntPosesCount;
    string learntPoses[10];
    int privateHours[4];
    bool privateHourOnOff[4];
    float cost;
    public:
        Customer(){
            cusName = "";
            currentWeight = 0;
            cost = 0;
            learntPosesCount = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = 0;
                privateHourOnOff[i] = 0;
            }
        }
        Customer(string n, TrainingPlan tp, float w, int h[4], bool OnOff[4]){
            cusName = n;
            trainingPlan = tp;
            currentWeight = w;
            cost = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = h[i];
                privateHourOnOff[i] = OnOff[i];
            }
            CUSTOMER++;
        }
        string setCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Input customer name : ";
            cin.get();
            getline(cin, cusName);

            trainingPlanLabel:
            cout<<"Enter training plan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                privateHourLabel:
                cout<<"Enter"<<i+1<<" th/st week private hours : \n";
                cin>>privateHours[i];
                if(privateHours[i] < 0 || privateHours[i] > 5) {
                    cout<<"It exceeded 5 or less than 0\n";
                    goto privateHourLabel;
                }
                
                onlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='0') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            CUSTOMER++;
            return trainingPlan.getPlanName();
        }
        string updateCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Updating Customer name("<<cusName<<") : \n";

            trainingPlanLabel:
            cout<<"Choose a training plan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Input weight(kg) : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                cout<<"Input week"<<i+1<<" private hours : \n";
                cin>>privateHours[i];
                onlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='0') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            return trainingPlan.getPlanName();
        }
        void displayPoses(){
            cout<<setw(30)<<"Learnt poses : ";
            for(int i=0; i<learntPosesCount; i++){
                cout<<learntPoses[i];
                if(i+1!=learntPosesCount) cout<<" ,";
            }
        }
        void addLearntPoses(string poses[]){
            char learnt = 'y';
            int ind = 0;
            int learntInd = 0;
            cout<<"Already learnt poses? (y/n) : ";
            cin>>learnt;
            if(learnt=='y') {
                for(int i=0; i<10; i++){
                    cout<<"("<<i+1<<")"<<poses[i];
                    if(i+1 != 10) cout<<" , ";
                }
                while(true){
                    char more = 'y';
                    cout<<"\nEnter pose index : ";
                    cin>>ind;
                    cout<<"Got more?(y/n) : ";
                    cin>>more;
                    learntPosesCount++;
                    learntPoses[learntInd] = poses[ind-1];
                    learntInd++;
                    if(more!='y') break;
                }
            }
            cout<<endl;
        }
        float getFinalCost(){
            // checking learn pose counts for discount
            int count = learntPosesCount;
            if(count > 5) count = 5;
            cost = 0;
            // if fees per month is not 0 sum the fees per month
            if(trainingPlan.getFeesPerMonth()!=0) cost += trainingPlan.getFeesPerMonth();
            else cost += trainingPlan.getFeesPerWeek()*4;
            // checking private hour if is is online multiply with 15000
            // if is online 17000
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) cost += 15000*privateHours[i];
                else cost += 17000*privateHours[i];
            }
            return cost - (cost*count)/100;
        }
        float getCost() {
            cost = 0;
            if(trainingPlan.getFeesPerMonth()!=0) cost += trainingPlan.getFeesPerMonth();
            else cost += trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) cost += 15000*privateHours[i];
                else cost += 17000*privateHours[i];
            }
            return cost;
        }
        void displayCustomer(){
            int online = 0, offline = 0;
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) online++;
                else offline++;
            }
            cout<<setw(20)<<cusName
                <<setw(20)<<trainingPlan.getPlanName()
                <<setw(20)<<learntPosesCount
                <<setw(20)<<online
                <<setw(20)<<offline
                <<setw(20)<<getFinalCost();
        }
        void displayCustomerDetails(){
            int count = learntPosesCount;
            if(count > 5) count = 5;
            int online = 0, offline = 0;
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) online += privateHours[i];
                else offline += privateHours[i];
            }
            cout<<setw(30)<<"Customer name : "<<setw(20)<<cusName<<endl
                <<setw(30)<<"Weight : "<<setw(20)<<currentWeight<<endl
                <<setw(30)<<"Training plan : "<<setw(20)<<trainingPlan.getPlanName()<<endl;
            displayPoses();
            cout<<endl;

            cout<<setw(30)<<"Sessions per week : "<<setw(20)<<trainingPlan.getSessionsPerWeek();
            if(trainingPlan.getFeesPerMonth()!=0) {
                cout<<setw(20)<<trainingPlan.getFeesPerMonth();
            }
            else {
                cout<<setw(20)<<trainingPlan.getFeesPerWeek()*4;
            }
            cout<<endl
                <<setw(30)<<"Private (Offline-17000) : "<<setw(20)<<offline<<setw(20)<<17000*offline<<endl
                <<setw(30)<<"Private (Online-15000) : "<<setw(20)<<online<<setw(20)<<15000*online<<endl
                <<setw(30)<<"Discount (%) : "<<setw(20)<<count<<setw(20)<<getCost()*count/100<<endl
                <<setw(30)<<"Total cost : "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
        }
};

void merge(Customer array[], int const left, int const mid, int const right){
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    Customer *leftArray = new Customer[subArrayOne],
         *rightArray = new Customer[subArrayTwo];

    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].getFinalCost()
            <= rightArray[indexOfSubArrayTwo].getFinalCost()) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(Customer array[], int const begin, int const end){
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

class Position{
    string name;
    int poseCounts;
    public:
        string poseType[10];
        string poseName[10];
        Position(){
            name = "";
            poseCounts = 0;
        }
        Position(string name, string type[10], string names[10], int pc){
            this->name = name;
            poseCounts = pc;
            for(int i=0; i<10; i++){
                poseType[i] = type[i];
                poseName[i] = names[i];
            }
            POSITION++;
        }
        void addPosition(){
            cout<<"Position name : "<<name<<endl;
            cout<<"Positions : \n";
            for(int i=0; i<poseCounts; i++) {
                cout<<poseName[i];
                if(i+1 != poseCounts) cout<<" , ";
                else cout<<endl;
            }
            if(poseCounts == 10) {
                cout<<"10 poses already added\n";
                cin.get();
                return;
            }
            char more = 'y';
            while(true){
                cin.get();
                if(poseCounts==10) break;

                cout<<"Enter position name("<<poseCounts+1<<") : ";
                getline(cin,poseName[poseCounts]);
                cout<<"Input position type("<<poseCounts+1<<") : ";
                getline(cin,poseType[poseCounts]);
                cout<<"Successfully added("<<poseName[poseCounts]<<")\n";
                poseCounts++;

                moreLabel:
                cout<<"Add more?(y/n) : ";
                cin>>more;
                if(more=='n') break;
            }
        }
        void createPosition(){
            cout<<"Enter position name : ";
            cin.get();
            getline(cin,name);
            POSITION++;
            addPosition();
        }
        void displayPosition(){
            cout<<setw(20)<<name<<endl;
            for(int i=0; i<poseCounts; i++){
                cout<<setw(25)<<""
                    <<setw(20)<<poseType[i]
                    <<setw(20)<<poseName[i]
                    <<endl;
            }
        }
};
void displayTrainingPlans(TrainingPlan plans[]);
void displayYogaPositions(Position poses[]);
void displayCustomers(Customer customers[]);

int main(){
    int menuCode;
    
    Position poses[5];
    string basicPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string basicPoseNames[10] ={"Archer Pose","Dolphin Pose","Frog Pose","Fallen Triangle","Big Toe Pose","Lion Pose","Airplane Pose","Side Lunge","Side Reclining","Bird Dog Pose"};
    Position pose1("BASIC",basicPoseType,basicPoseNames,10);
    
    string imPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string imPoseNames[10] ={"Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge","Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position pose2("INTERMEDIATE",imPoseType,imPoseNames,10);
    
    poses[0] = pose1;
    poses[1] = pose2;
    
    TrainingPlan plans[7];
    TrainingPlan basic("BASIC",3,25000,0);
    TrainingPlan inter("INTERMEDIATE",3,35000,0);
    TrainingPlan advan("ADVANCED",2,50000,0);
    TrainingPlan basicMonth("BASIC",3,0,95000);
    plans[0] = basic;
    plans[1] = inter;
    plans[2] = advan;
    plans[3] = basicMonth;

    Customer customers[50];
    int c1Private[4] = {1,1,3,2};
    bool c1OnOff[4] = {false,false,true,true};
    int c2Private[4] = {1,1,3,2};
    bool c2OnOff[4] = {true,false,true,false};
    int c3Private[4] = {1,1,3,2};
    bool c3OnOff[4] = {true,true,true,true};
    int c4Private[4] = {1,1,3,2};
    bool c4OnOff[4] = {true,false,true,true};
    int c5Private[4] = {1,1,3,2};
    bool c5OnOff[4] = {true,false,false,true};
    
    Customer c1("Mg Mg",plans[0],55,c1Private,c1OnOff);
    Customer c2("Thinzar",plans[0],55,c2Private,c2OnOff);
    Customer c3("Su Su",plans[0],55,c3Private,c3OnOff);
    Customer c4("Ko Ko",plans[1],55,c4Private,c4OnOff);
    Customer c5("Zin Zin",plans[2],55,c5Private,c5OnOff);
    customers[0] = c1;
    customers[1] = c2;
    customers[2] = c3;
    customers[3] = c4;
    customers[4] = c5;

    menuLabel:
    cout<<"Greeting from Amazing Sport Yoga System!\nHere are the menu available:\n1. Training plan.\n2. Yoga poses\n3. Customers\n0. Quit program.\n";
    cin>>menuCode;
    if(menuCode==1) {
        trainingPlanScreenLabel:
        int trainingMenuCode = 0;
        cout<<"1. Add a training plan.\n2. Show all training plans.\n3. Update a training plan.\n0. Return to main screen.\n";
        cin>>trainingMenuCode;
      
        if(trainingMenuCode < 0 || trainingMenuCode > 3) goto trainingPlanScreenLabel;
        if(trainingMenuCode == 0) goto menuLabel;
        else if(trainingMenuCode == 1) plans[PLAN].setPlan();
        else if(trainingMenuCode == 2) displayTrainingPlans(plans);
        else if(trainingMenuCode == 3) {
            int index = 0;
            displayTrainingPlans(plans);
            cout<<"Enter number to update : ";
            cin>>index;
            plans[index-1].updatePlan();
        }
        goto trainingPlanScreenLabel;
    } 
    else if(menuCode==2){
        yogaPoseScreenLabel:
        int yogaScreenCode = 0;
        cout<<"1. Add a yoga plan.\n2. Display yoga plans.\n3. Add yoga poses.\n0. Return to main screen.\n";
        cin>>yogaScreenCode;
        if(yogaScreenCode < 0 || yogaScreenCode > 3) goto yogaPoseScreenLabel;
      
        if(yogaScreenCode == 0) goto menuLabel;
        else if(yogaScreenCode == 1) {
            poses[POSITION].createPosition();
        }
        else if(yogaScreenCode == 2) displayYogaPositions(poses);
        else if(yogaScreenCode == 3) {
            int index = 0;
            displayYogaPositions(poses);
            cout<<"\nEnter yoga plan index to add : ";
            cin>>index;
            poses[index-1].addPosition();
        }
        goto yogaPoseScreenLabel;
    }
    else if(menuCode==3){
        customerScreenLabel:
        int customerScreenCode = 0;
        cout<<"1. Register a new customer.\n2. View all customers.\n3. Update customer info.\n4. Calculate costs for the customer.\n0. Return to main screen. \n";
        cin>>customerScreenCode;
        if(customerScreenCode < 0 || customerScreenCode > 4) goto customerScreenLabel;
      
        if(customerScreenCode == 0) goto menuLabel;
        else if(customerScreenCode == 1) {
            string planName = customers[CUSTOMER].setCustomer(plans);
            if(planName == "INTERMEDIATE") customers[CUSTOMER-1].addLearntPoses(poses[0].poseName);
            else if(planName == "ADVANCED") customers[CUSTOMER-1].addLearntPoses(poses[1].poseName);
            customers[CUSTOMER-1].displayCustomerDetails();
        }
        else if(customerScreenCode == 2) {
            mergeSort(customers, 0, CUSTOMER-1);
            displayCustomers(customers);
        }
        else if(customerScreenCode == 3) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to update : ";
            cin>>index;
            string planName = customers[index-1].updateCustomer(plans);
            if(planName == "INTERMEDIATE") customers[index-1].addLearntPoses(poses[0].poseName);
            else if(planName == "ADVANCED") customers[index-1].addLearntPoses(poses[1].poseName);
        }
        else if(customerScreenCode == 4) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to calculate costs : ";
            cin>>index;
            customers[index-1].displayCustomerDetails();
        }
        goto customerScreenLabel;
    }
    else if(menuCode==0) {
        cout<<"Thank you for using this systemn";
        return 0;
    }
    else goto menuLabel;
}

void displayTrainingPlans(TrainingPlan plans[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Plan name"
        <<setw(20)<<"Session per week"
        <<setw(15)<<"Fees per week"
        <<setw(15)<<"Fees per month"
        <<endl;
    for(int i=0; i<PLAN; i++) {
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
}
 
void displayYogaPositions(Position poses[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Position names"
        <<setw(20)<<"Pose type"
        <<setw(20)<<"Pose name"
        <<endl;
    for(int i=0; i<POSITION; i++) {
        cout<<setw(5)<<i+1;
        poses[i].displayPosition();
        cout<<endl;
    }
}

void displayCustomers(Customer customers[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Customer name"
        <<setw(20)<<"Training plan"
        <<setw(20)<<"Learnt poses count"
        <<setw(20)<<"Private(Online)"
        <<setw(20)<<"Private(Offline)"
        <<setw(20)<<"Cost(current month"
        <<endl;
    for(int i=0; i<CUSTOMER; i++) {
        cout<<setw(5)<<i+1;
        customers[i].displayCustomer();
        cout<<endl;
    }
}

