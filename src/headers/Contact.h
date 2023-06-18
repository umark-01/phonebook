#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/stat.h>

#include "signUp.h"
#include "user.h"
#include "Group.h"

using namespace std;

class Contact
{   
    private:

    string name;
    string phone;
    string email;
    string groupName;

    
    public:
    
    // getting contact details from user

    void setGroup(string gname){
        this->groupName = gname;
    }

    bool is_empty(std::fstream& pFile)
    {
        return pFile.peek() == std::fstream::traits_type::eof();
    }

    void setContact()
    {
        cout << "\nEnter name: ";
        cin.ignore(); // to clear the newline character from the input stream
        getline(cin, name);
        cout << "\nEnter phone: ";
        cin >> phone;
        cout << "\nEnter email: ";
        cin >> email;
        string answer;
        fstream groupfile;
        Group group;
        vector<Group> vecGroup;
        int number;

        fstream curruser;
        User usr;
        string file_path,path;
        curruser.open("db/curruser.dat", ios::in | ios::binary);
        curruser.seekg(0);
        while (curruser.read((char*)&usr, sizeof(usr)))
        {
            path = usr.getUsername();
            break;
        }
        curruser.close();
        file_path = "db/"+path+"/groups.dat";

        groupfile.open(file_path.c_str(), ios::in | ios::app | ios::binary);
        groupfile.seekg(0);
        while (groupfile.read((char*)&group, sizeof(group)))
        {
            vecGroup.push_back(group);
        }
        
        cout << "Do you want to add this contact to group? (y/n) :"; cin >> answer;
        if (answer == "y")
        {     
            if (is_empty(groupfile))
            {   
                cout << "\nThere are no groups";
                this->groupName = "-";
            }           
            else{
            for (int i = 0; i < vecGroup.size(); i++)
            {
                cout << i+1 << ". " << vecGroup[i].getName() << "\n";
            }
            cout << "Choose group : "; cin >> number;
            this->groupName = vecGroup[number-1].getName();
            cout << "\n\t\t\t Your contact added to group " << groupName;
            }
        } 
        else {
            this->groupName = "-";
        }
        groupfile.close();
    }

    void editContact(Contact contact){
        this->name = contact.getName();
        this->phone = contact.getPhone();
        this->email = contact.getEmail();
        int number = 1;
        while(number != 4){
            cout << "\tEditing chosen contact\n";
            cout << "\t1.Edit name: " << name << "\n";
            cout << "\t2.Edit Phone number: " << phone << "\n";
            cout << "\t3.Edit email: " << email << "\n";
            cout << "\t4.Finish editing\n";
            cout << "\n\t\tEnter your choice: ";cin >> number;
            switch (number)
            {
            case 1:
                {
                    cout << "Enter new name of contact: ";
                    cin.ignore();
                    getline(cin, this->name);
                }
                break;
            case 2:
                {
                    cout << "Enter new Phone number of contact: ";
                    cin.ignore();
                    getline(cin, this->phone);
                }
                break;
            case 3:
                {
                    cout << "Enter new email of contact: ";
                    cin.ignore();
                    getline(cin, this->email);
                }
                break;
            case 4:
                cout << "\t\tContact edited!\n";
            default:
                break;
            }
        }

    }

    // displaying contact details
    void displayContact()
    {
        cout << "\t\n   List of contacts : "; 
        cout << "\t\nName \t\t Phone \t\t Email" << endl;
        cout << name << "\t\t" << phone << "\t\t" << email << endl;
    }
    string getName()
    {
        return name;
    }
    string getPhone()
    {
        return phone;
    }
    string getEmail()
    {
        return email;
    }
    string getGroupName(){
        return this->groupName;
    }
    // operator to sort contacts in alphabetical order
    bool operator<(const Contact& other) const
    {
        return name < other.name;
    }
};



#endif