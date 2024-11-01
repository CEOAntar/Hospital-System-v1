#include<iostream>
using namespace std;

//Global variables
const int max_specialization = 20;
const int max_queue = 5;

//The DS
string names[max_specialization+1][max_queue];
int status[max_specialization+1][max_queue]; // 0 = regular , 1 = urgent
int queue_length[max_specialization+1]; //how many patient in each specialization

int menu()
{
    int choice = -1;
    while(choice == -1)
    {
        cout<<"Enter your Choice: "<<"\n";
        cout<<"1) Add New Patient"<<"\n";
        cout<<"2) Print All Patient"<<"\n";
        cout<<"3) Get Next Patient"<<"\n";
        cout<<"4) Exit"<<"\n";

        cin>>choice;

        if(!(1 <= choice && choice <= 4))
        {
            cout<<"Invalid choice. Try again\n";
            choice = -1;
        }
    }
    return choice;
}

void shift_left(int spec , string names_sp[] , int st_sp[])
{
    //help in remove patient
    int len = queue_length[spec];
    for(int i = 1 ; i < len ; i++)
    {
        names_sp[i-1] = names_sp[i];
        st_sp[-1] = st_sp[i];
    }
    queue_length[spec]--;
}

void shift_right(int spec , string names_sp[] , int st_sp[])
{
    //start from end
    int len = queue_length[spec];
    for(int i = len-1 ; i >= 0 ; i--)
    {
        names_sp[i+1] = names_sp[i];
        st_sp[i+1] = st_sp[i];
    }
    queue_length[spec]++;
}

bool add_patient()
{
    int spec;
    string name;
    int st;
    cout << "Enter the Specialization (1-20), Name, Status (0=Regular, 1=Urgent): ";
    cin>> spec >> name >> st;

    int pos = queue_length[spec];
    if(pos >= max_queue)
    {
        cout<<"Sorry We Have Enough Patient Here :) "<<"\n";
        return false;
    }

    if(st == 0)
    {
        names[spec][pos] = name;
        status[spec][pos] = st;
        queue_length[spec]++;
    }
    else
    {
        //urgent => shift , then add
        shift_right(spec,names[spec],status[spec]);
        names[spec][0] = name;
        status[spec][0] = st;
    }
    return true;
}

void print(int spec , string names_sp[] , int st_sp[])
{
    int len = queue_length[spec];
    if(len == 0)
        return;

    cout<<"there are "<<len<<" patient in Specialization "<< spec <<"\n";
    for(int i = 0 ; i < len ; i++)
    {
        cout<<names_sp[i]<<" ";
        if(st_sp[i])
            cout<<"Urgent"<<"\n";
        else
            cout<<"Regular"<<"\n";
    }
}

void print_patient()
{
    cout<<"************************************"<<"\n";
    for(int spec = 0 ; spec < max_specialization ; spec++)
        print(spec, names[spec],status[spec]);
    cout<<"************************************"<<"\n";
}

void get_patient()
{
    int spec;
    cout<<"Enter Specialization: ";
    cin>>spec;

    int len = queue_length[spec];
    if(len == 0)
    {
        cout<<"there is no patients here :) "<<"\n";
        return;
    }

    //patient goes to dr
    cout<<names[spec][0]<<" please go with Dr"<<"\n";

    //delete this patient from the queue
    shift_left(spec,names[spec],status[spec]);
}



void Hospital_System()
{
    for(;;)
    {
        int choice = menu();

        if(choice == 1)
        {
            add_patient();
        }
        else if(choice == 2)
        {
            print_patient();
        }
        else if(choice == 3)
        {
            get_patient();
        }
        else if(choice == 4)
        {
            break;
        }

    }
}

int main()
{
    Hospital_System();
    return 0;
}



