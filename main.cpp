#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class person{
private:
    string Fname;
    string Lname;
    int PersonalId;
    double Salary=0.00;
    double CostPerHrs=0.00;
    double WorkHours=0.00;
public:
    person(){
        Fname="A";
        Lname="B";
        WorkHours=1;
        CostPerHrs=1;

    }
    void setSalary();
    double getSalary();
    void setFname(string);
    string getFname();
    void setLname(string);
    string getLname();
    void setPersonalId();
    int getPersonalId();
    void setWorkingHrs(double);
    double getWorkingHrs();
    void setCostPerHrs(double);
    double getCostPerHrs();
};

class HRM{
private:
    person Employes[100];
public:
    HRM(){
        ifstream inf;
    inf.open("Employee.txt");


    string Fn,Ln;
    double Wh,Wd;
    int index=1;


        while (inf && !inf.eof())
        {

            inf>>Fn>>Ln>>Wh>>Wd;

            Employes[index].setFname(Fn);
            Employes[index].setLname(Ln);


            Employes[index].setWorkingHrs(Wh);
            Employes[index].setCostPerHrs(Wd);
            Employes[index].setPersonalId();
            Employes[index].setSalary();

            index+=1;

        }
        inf.close();

    }

    void AddPerson();
    void DeletePerson();
    void UpdatePerson();
    int SearchPerson2(int);
    void SearchPerson();
    int ValidWorkHours(double);
    int ValidCostHrs(double);
    void Mainmenu();
};
int HRM::ValidWorkHours(double che){
    if (che<1 || che>60){
        return 1;
    }
    else{
        return 0;
    }
}
int HRM::ValidCostHrs(double chec) {
    if (chec<1){
        return 1;
    }
    else{
        return 0;
    }
}


void person::setFname(string n){
    Fname=n;
}
void person::setLname(string l){
    Lname=l;
}
string person::getFname(){
    return Fname;
}
string person::getLname(){
    return Lname;
}
void person::setPersonalId(){
    static int Id=1001;
    PersonalId=Id;
    Id=Id+1;
}
int person::getPersonalId(){
    return PersonalId;

}
void person::setWorkingHrs(double H){
    WorkHours=H;
}
double person::getWorkingHrs(){
    return WorkHours;
}
void person::setCostPerHrs(double c){
    CostPerHrs=c;
}
double person::getCostPerHrs(){
    return CostPerHrs;
}
void person::setSalary(){
    Salary=CostPerHrs*WorkHours*52.00;
}
double person::getSalary(){
    return Salary;
}



void HRM::AddPerson(){
double w,c;
string f,l;
string Dec="y";
static int index=6;
ofstream off;
off.open("Employee.txt",ios::app);
while(Dec=="y"){


    cout<<"Please enter the first name of the employee: ";
    cin>>f;
    Employes[index].setFname(f);
    cout<< "Please enter the last name of the employee: ";
    cin>>l;
    Employes[index].setLname(l);
    cout<<"How many hours a week does this employee work? ";
    cin>>w;


            while(ValidWorkHours(w)==1){
                cout<<"Error: enter valid work hours that is between 1 and 60 only. Please enter again. "<<endl;
                cout<<"How many hours a week does this employee work? ";
                cin>>w;
            }


    Employes[index].setWorkingHrs(w);
    cout<<"How much per hours is his/her wage? ";
    cin>>c;
            while(ValidCostHrs(c)==1){
                cout<<"Error: enter valid cost per hours(negative value is not accepted). Please enter again. "<<endl;
                cout<<"How much per hours is his/her wage? ";
                cin>>c;
            }

    Employes[index].setCostPerHrs(c);
    Employes[index].setPersonalId();
    off<<Employes[index].getFname()<<" "<<Employes[index].getLname()<<" "<<Employes[index].getWorkingHrs()<<" "<<Employes[index].getCostPerHrs()<<endl;

    cout<<"The employee with the following information has been added to the system:"<<endl;
    cout<<"First Name\t"<<"Last Name\t"<<"Personal Number\t"<<"Salary"<<endl;
    cout<<"---------\t"<<"---------\t"<<"---------------\t"<<"------"<<endl;
    Employes[index].setSalary();
    cout<<Employes[index].getFname()<<"\t\t"<<Employes[index].getLname()<<"\t\t"<<Employes[index].getPersonalId()<<"\t\t"<<Employes[index].getSalary()<<endl;
    cout<<"Do you want to add another employee (y/n)?";
    cin>>Dec;
    index=index+1;

}
off.close();
Mainmenu();
}


void HRM::DeletePerson(){
int Pn;
int temp;

string Yes,Decide;
Yes="y";
Decide="";

    while(Yes =="y"){

    cout<<"Please enter the personal number of emplayee: ";
    cin>>Pn;
    temp=SearchPerson2(Pn);
        if (temp == 0){
            cout<<"Sorry there is no employee with the provided employee Id."<<endl;
            cout<<"Do you want to repeat delete by entering the new personal number (y/n)? ";
            cin>> Yes;
            }
        else{
            cout<<"Do you really want to delete employee "<<Employes[temp].getFname()<<" "<<Employes[temp].getLname()<< " (y/n)? ";
            cin>>Decide;

                if(Decide=="y"){

					string line, name;
                    name=Employes[temp].getFname();
                    ifstream myfile;
                    myfile.open("Employee.txt");
                    ofstream temps;
                    temps.open("temp.txt");
                    while (getline(myfile, line))
                    {
                    if (line.substr(0, name.size()) != name){
                    temps << line << endl;}
                    }
                    cout<<"The employee "<<Employes[temp].getFname()<<" "<<Employes[temp].getLname()<< " has been deleted."<<endl;
                    myfile.close();
                    temps.close();
                    remove("Employee.txt");
                    rename("temp.txt", "Employee.txt");

                    for (int i=temp;i<99;i++){
                        Employes[i]=Employes[i+1];
                    }

                }

            cout<<"Do you want to repeat delete by entering the new personal number (y/n)? ";
            cin>>Yes;

        }
    }
Mainmenu();

}


int HRM::SearchPerson2(int q){
    int tsk=0;
    for (int i=1;i<100;i++){
        if (Employes[i].getPersonalId()==q){
            return i;
            tsk=1;
        }
    }
       if(tsk != 1){
        return 0;
       }
}


void HRM::SearchPerson(){
    int r;
    int point=0;
    string Decision="y";
    while(Decision=="y"){
    cout<<"Please enter personal number of an employee? ";
    cin>>r;
    for (int i=1;i<100;i++){
        if (Employes[i].getPersonalId()==r){
                cout<<Employes[i].getPersonalId()<<endl;
            point=i;
            break;
        }
        else{
           point=0;
        }
    }
    if (point==0){
        cout<<"The employee with this Id does not exist"<<endl;
    }
    else{
    cout<<"First Name\t"<<"Last Name\t"<<"Personal Number\t"<<"Salary"<<endl;
    cout<<"---------\t"<<"---------\t"<<"---------------\t"<<"------"<<endl;
    cout<<Employes[point].getFname()<<"\t\t"<<Employes[point].getLname()<<"\t\t"<<Employes[point].getPersonalId()<<"\t\t"<<Employes[point].getSalary()<<endl;

    }
    cout<<"Do you want to search for another person? (y/n)";
    cin>>Decision;
    }
Mainmenu();
}


void HRM::UpdatePerson(){
        int Pi;
        int Ud,tempu;
        string Ufn,Uln,name,line;
        double Uwh,Uph;
        string How="y";

    while(How=="y"){
        cout<<"Please enter the personal number of an employee? ";
        cin>>Pi;
        tempu=SearchPerson2(Pi);

        if (tempu==0){
               cout<<"Sorry, there is not the employee with requested personal number. "<<endl;
        }
        else{
            ifstream myfile;
            myfile.open("Employee.txt");
            ofstream temps;
            temps.open("temp.txt");
            cout<<"Please enter the related number of field which you would like to update: "<<endl;
            cout<<"(1. First name\n 2. Family name\n 3. Working hours per week\n 4. Payment for one hour)?\n Enter here>> ";
            cin>>Ud;
            if (Ud==1){
                cout<<"Please enter new first name for employee with "<<Pi<<" Id: ";
                cin>>Ufn;

                name=Employes[tempu].getFname();
                        while (getline(myfile, line))
                        {
                            if (line.substr(0, name.size()) != name){
                        temps << line << endl;
                        }
                            else{

                            temps<<Ufn<<" "<<Employes[tempu].getLname()<<" "<<Employes[tempu].getWorkingHrs()<<" "<<Employes[tempu].getCostPerHrs()<<endl;
                        }
                        }


                        myfile.close();
                        temps.close();
                        remove("Employee.txt");
                        rename("temp.txt", "Employee.txt");
                        Employes[tempu].setFname(Ufn);
                cout<<"The information for employee with " <<Pi <<" Id has been updated"<<endl;
            }
            else if(Ud==2){
                cout<<"Please enter new last name for employee with "<<Pi<<" Id: ";
                cin>>Uln;
                Employes[tempu].setLname(Uln);
                name=Employes[tempu].getFname();
                        while (getline(myfile, line))
                        {
                            if (line.substr(0, name.size()) != name){
                        temps << line << endl;
                        }
                            else{

                            temps<<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname()<<" "<<Employes[tempu].getWorkingHrs()<<" "<<Employes[tempu].getCostPerHrs()<<endl;
                        }
                        }


                        myfile.close();
                        temps.close();
                        remove("Employee.txt");
                        rename("temp.txt", "Employee.txt");

                cout<<"The information for employee with " <<Pi <<" Id has been updated"<<endl;

            }
            else if(Ud==3){
                cout<<"Please enter new Working hours per week for employee with named "<<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname()<<": ";
                cin>>Uwh;
                while(ValidWorkHours(Uwh)==1){
                cout<<"Error: enter valid work hours that is between 1 and 60 only. Please enter again. "<<endl;
                cout<<"How many hours a week does this employee work? ";
                cin>>Uwh;
            }
                Employes[tempu].setWorkingHrs(Uwh);
                Employes[tempu].setSalary();
                name=Employes[tempu].getFname();
                        while (getline(myfile, line))
                        {
                            if (line.substr(0, name.size()) != name){
                        temps << line << endl;
                        }
                            else{

                            temps<<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname()<<" "<<Employes[tempu].getWorkingHrs()<<" "<<Employes[tempu].getCostPerHrs()<<endl;
                        }
                        }


                        myfile.close();
                        temps.close();
                        remove("Employee.txt");
                        rename("temp.txt", "Employee.txt");
                cout<<"The information for " <<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname()<<" has been updated"<<endl;
            }
            else if(Ud==4){
                cout<<"Please enter new Payment for one hour in $ for employee with named "<<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname()<<": ";
                cin>>Uph;
                while(ValidCostHrs(Uph)==1){
                cout<<"Error: enter valid cost per hours(negative value is not accepted). Please enter again. "<<endl;
                cout<<"How much per hours is his/her wage? ";
                cin>>Uph;
            }
                Employes[tempu].setCostPerHrs(Uph);
                Employes[tempu].setSalary();
                name=Employes[tempu].getFname();
                        while (getline(myfile, line))
                        {
                            if (line.substr(0, name.size()) != name){
                        temps << line << endl;
                        }
                            else{

                            temps<<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname()<<" "<<Employes[tempu].getWorkingHrs()<<" "<<Employes[tempu].getCostPerHrs()<<endl;
                        }
                        }


                        myfile.close();
                        temps.close();
                        remove("Employee.txt");
                        rename("temp.txt", "Employee.txt");
                cout<<"The information for " <<Employes[tempu].getFname()<<" "<<Employes[tempu].getLname() <<" has been updated"<<endl;
            }
            else{
                cout<<"Please enter the number only between 1 to 4."<<endl;
                myfile.close();
                temps.close();
            }
        }
        cout<<"Do you want to repeat update by entering the new personal number (y/n)?";
        cin>>How;
    }
Mainmenu();
}

void HRM::Mainmenu(){

int choices=0;
//do{
cout<<endl;
cout<<"--------------------------------------------"<<endl;
cout<<"Welcome to Human Resource Management (HRM)."<<endl;
cout<<"--------------------------------------------"<<endl;
cout<<endl;
cout<<"---Main Menu---"<<endl;
cout<<"1. Add new employee"<<endl;
cout<<"2. Delete employee information"<<endl;
cout<<"3. Update employee information"<<endl;
cout<<"4. Search employee"<<endl;
cout<<"5. Quit"<<endl;
cout<<"Please enter your choice 1..5 : ";
cin>>choices;
switch (choices)
{
    case 1: AddPerson();
    case 2: DeletePerson();
    case 3: UpdatePerson();
    case 4: SearchPerson();
    case 5: cout<<"-------------------Thank you--------------------"<<endl;
    //default: cout<<"Please only enter the number between 1 to 5"<<endl;
};


//}while(choices<1 || choices>5);
cout<<endl;
}
int main()
{

HRM People1;
People1.Mainmenu();

return 0;
}
