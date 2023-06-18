/*
    Phoneboook application
    - User add account with username and password
    - Menu driven
        - Add contact by entering name, phone number, email
        - Delete contact
        - Search contact
            - by name 
            - by phone number
        - Edit contact
        - Create groups and manage contacts in group
        - Display contact in alphabetical order

    -Umar I added db for dat and txt files to save data in it, and it will be more comfortable
    to use several files instead of using only 1.
*/


#include "headers/Contact.h"
#include "headers/signUp.h"
#include "headers/user.h"
#include "headers/Group.h"

using namespace std;




string spaceGetter(string str){
    int num = 19;
    int len = str.length();
    num = num - len;
    string er = "";
    for (int i = 0; i < num; i++)
    {
        er += " ";
    }
    er += "\t";
    return er;
    
}

void menu()
{
    // menu driven

    cout << "\t\t\n\n\t\t\t\t\t   Menu";
    cout << "\t\n\t\t\t\t\t1. Add contact";
    cout << "\t\n\t\t\t\t\t2. Delete contact";
    cout << "\t\n\t\t\t\t\t3. Search contact";
    cout << "\t\n\t\t\t\t\t4. Edit contact";
    cout << "\t\n\t\t\t\t\t5. Create group";
    cout << "\t\n\t\t\t\t\t6. Display contacts in alphabetical order";
    cout << "\t\n\t\t\t\t\t7. Display contacts in group";
    cout << "\t\n\t\t\t\t\t0. Exit\n";

}

int main()
{   
    SignUp signUp;
    Group group;

    int choice = 1;
    bool found = false;
    ofstream file_of_list_contacts;

    string deleteName;
    int searchType;
    string searchName;
    string searchPhone;

    vector<Contact> listContacts;
    vector<Group> listGroups;
    
    int choice1;
    
    while (true){
        cout << "\n\t\t\t\t1.Sign up | 2.Sign in\n";
        cout << "Enter your choice: ";cin >> choice1;
        if(choice1 == 2){
            signUp.OpenApp();
            break;
        } else if (choice1 == 1) {
            signUp.setUsername();
            break;
        }
    }
    
    
    
    //outfile.open("db/contact.txt",ios:: in | ios::app | ios::binary);

    while (choice != 0)
    {
        menu();
        cout << "\nEnter your choice: ";
        cin >> choice; 
        
        switch (choice)
        {
            case 1:
                {
                    Contact contact;
                    fstream outfile;
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
                    file_path = "db/"+path+"/contact.dat";
                    outfile.open(file_path.c_str(),ios:: in | ios::app | ios::binary);
                    // Adding contact
                    contact.setContact();
                    listContacts.push_back(contact);
                    outfile.write((char*)&contact, sizeof(contact));
                    outfile.close();
                }
                break;
            case 2:
                {
                    // Deleting contact
                    Contact contact1;
                    fstream outfile;
                    fstream tempFile;
                    //
                    bool found1 = false;
                    fstream curruser;
                    User usr;
                    string file_path,file_path1,path;
                    curruser.open("db/curruser.dat", ios::in | ios::binary);
                    curruser.seekg(0);
                    while (curruser.read((char*)&usr, sizeof(usr)))
                    {
                        path = usr.getUsername();
                        break;
                    }
                    curruser.close();
                    file_path = "db/"+path+"/contact.dat";
                    file_path1 = "db/"+path+"/temp.dat";
                    //
                    outfile.open(file_path.c_str(),ios:: in | ios::app | ios::binary);
                    cout << "\nEnter name to delete: ";
                    cin.ignore();
                    getline(cin, deleteName);
                    tempFile.open(file_path1.c_str(), ios::trunc | ios::out | ios::binary);
                    outfile.seekg(0);
                    while (outfile.read((char*)&contact1, sizeof(contact1)))
                    {
                        if(contact1.getName() != deleteName)
                        {
                            tempFile.write((char *)&contact1, sizeof(contact1));
                        } else {
                            found1 = true;
                        }
                    }
                    outfile.close();
                    tempFile.close();
                    remove(file_path.c_str());
                    rename(file_path1.c_str() , file_path.c_str());
                    if (found1){
                        cout << "\t\t\tContact deleted!!\n";
                    }
                }
                break;
            case 3: 
                {
                    // Searching contact
                    fstream fileBin;
                    vector<Contact> contacts;
                    Contact con;
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
                    file_path = "db/"+path+"/contact.dat";
                    fileBin.open(file_path.c_str(), ios::in | ios::app | ios::binary);
                    fileBin.seekg(0);
                    while(fileBin.read((char*)&con, sizeof(con))){
                        contacts.push_back(con);
                    }
                    sort(contacts.begin(), contacts.end()); // sorted list of contacts
                    cout << "\n\tEnter how to search: \n\t1. By name \n\t2. By phone number: \n\t3.By Email: ";
                    cout << "\n\tEnter your choice: ";cin >> searchType;
                    

                    
                    if(searchType == 1) // by name
                    {   
                        cout << "Enter name to search: ";
                        cin >> searchName;
                        for(int i = 0; i < contacts.size(); i++)
                        {
                            if(contacts[i].getName() == searchName)
                            {
                                
                                cout << "\t\n\t\tName \t\t Phone       \t\t Email" << endl;
                                cout << "\t\n\t\t"  << contacts[i].getName() << "\t\t " << contacts[i].getPhone() << "\t\t " << contacts[i].getEmail() << endl;
                                found = true;
                                break;
                            }
                        }
                        if(!found)
                        {
                            cout << "Contact not found" << endl;
                        }
                    }
                    else if(searchType == 2) // by phone number
                    {
                        cout << "Enter phone number to search: ";
                        cin >> searchPhone;
                        for(int i = 0; i < contacts.size(); i++)
                        {
                            if(contacts[i].getPhone() == searchPhone)
                            {
                                cout << "\t\n\t\tName \t\t Phone       \t\t Email" << endl;
                                cout << "\t\n\t\t"  << contacts[i].getName() << "\t\t " << contacts[i].getPhone() << "\t\t " << contacts[i].getEmail() << endl;
                                found = true;
                                break;
                            }
                            if(!found)
                            {
                                cout << "\nContact not found";
                            }
                        }
                    } else if (searchType == 3) {
                        string searchEmail;
                        cout << "Enter email to search: ";
                        cin >> searchEmail;
                        for(int i = 0; i < contacts.size(); i++)
                        {
                            if(contacts[i].getEmail() == searchEmail)
                            {
                                cout << "\t\n\t\tName \t\t Phone       \t\t Email" << endl;
                                cout << "\t\n\t\t"  << contacts[i].getName() << "\t\t " << contacts[i].getPhone() << "\t\t " << contacts[i].getEmail() << endl;
                                found = true;
                                break;
                            }
                            if(!found)
                            {
                                cout << "\nContact not found";
                            }
                        }
                    }
                    fileBin.close();
                }
                break;
            case 4:
                {
                    // Editing contact
                    Contact contact1;
                    fstream outfile;
                    fstream tempFile;
                    string name11;
                    bool found1 = false;

                    fstream curruser;
                    User usr;
                    string file_path,file_path1,path;
                    curruser.open("db/curruser.dat", ios::in | ios::binary);
                    curruser.seekg(0);
                    while (curruser.read((char*)&usr, sizeof(usr)))
                    {
                        path = usr.getUsername();
                        break;
                    }
                    curruser.close();
                    file_path = "db/"+path+"/contact.dat";
                    file_path1 = "db/"+path+"/temp.dat";
                    outfile.open(file_path.c_str(),ios:: in | ios::app | ios::binary);
                    cout << "\nEnter name to edit: ";
                    cin.ignore();
                    getline(cin, name11);
                    tempFile.open(file_path1.c_str(), ios::trunc | ios::out | ios::binary);
                    outfile.seekg(0);
                    while (outfile.read((char*)&contact1, sizeof(contact1)))
                    {
                        if(contact1.getName() != name11)
                        {
                            tempFile.write((char *)&contact1, sizeof(contact1));
                        } else {
                            Contact c;
                            c.editContact(contact1);
                            found1 = true;
                            tempFile.write((char *)&c, sizeof(c));
                        }
                    }
                    outfile.close();
                    tempFile.close();
                    remove(file_path.c_str());
                    rename(file_path1.c_str() , file_path.c_str());
                }
                break;

            case 5: 
                {
                    // Creating group
                    Group group;
                    fstream groupFile;
                    fstream file;
                    int num = 1;
                    Contact contacts;
                    vector <Contact> groups;
                    string groupName;

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
                    file_path = "db/"+path+"/contact.dat";

                    file.open(file_path.c_str(), ios::in | ios::app | ios::binary);

                    cout << "\n\tEnter group name: ";
                    cin >> groupName;
                    file.seekg(0);
                    while(file.read((char*)&contacts, sizeof(contacts)))
                    {
                        groups.push_back(contacts);
                    }
                    sort(groups.begin(), groups.end());
                    string answer = "y";
                    while (answer != "n")
                    {
                        cout << "\t\t\t\tChoose group members for " << groupName << "\n";


                        cout << "\t\n\t\tName\t\t        Phone\t\t        Email\t\t        Group Name" << endl;
                        for (int i = 0; i < groups.size(); i++)
                        {
                            cout << "\t\t"<<num << ") " << groups[i].getName() << spaceGetter(groups[i].getName()) << groups[i].getPhone() << spaceGetter(groups[i].getPhone()) << groups[i].getEmail() << endl;
                            num++;
                        }
                        int index;
                        cout << "Choose group members: "; cin >> index;

                        Contact cd = groups[index-1];
                        cd.setGroup(groupName);
                        Contact contact1;
                        fstream outfile;
                        fstream tempFile;
                        string name11 = cd.getName();
                        bool found1 = false;
                        fstream curruser1;
                        User usr1;
                        string file_path_,file_path1_,path_;
                        curruser1.open("db/curruser.dat", ios::in | ios::binary);
                        curruser1.seekg(0);
                        while (curruser1.read((char*)&usr1, sizeof(usr1)))
                        {
                            path_ = usr1.getUsername();
                            break;
                        }
                        curruser1.close();
                        file_path_ = "db/"+path_+"/contact.dat";
                        file_path1_ = "db/"+path_+"/temp.dat";//
                        outfile.open(file_path_.c_str(),ios:: in | ios::app | ios::binary);
                        tempFile.open(file_path1_.c_str(), ios::trunc | ios::out | ios::binary);
                        outfile.seekg(0);
                        while (outfile.read((char*)&contact1, sizeof(contact1)))
                        {
                            if(contact1.getName() != name11)
                            {
                                tempFile.write((char *)&contact1, sizeof(contact1));
                            } else {
                                found1 = true;
                                tempFile.write((char *)&cd, sizeof(cd));
                            }
                        }
                        outfile.close();
                        tempFile.close();
                        remove(file_path_.c_str());
                        rename(file_path1_.c_str() , file_path_.c_str());
                        cout << "\n\t\t\tContact added to group" << endl;
                        cout << "Do you want to add member again? (y/n): "; cin >> answer;
                    }
                    
                    file.close();
                    group.setGroup(groupName);

                    fstream curruser2;
                    User usr2;
                    string file_path2,path2;
                    curruser2.open("db/curruser.dat", ios::in | ios::binary);
                    curruser2.seekg(0);
                    while (curruser2.read((char*)&usr2, sizeof(usr2)))
                    {
                        path2 = usr2.getUsername();
                        break;
                    }
                    curruser2.close();
                    file_path2 = "db/"+path2+"/groups.dat";

                    groupFile.open(file_path2.c_str(), ios::in | ios::app | ios::binary);
                    groupFile.write((char*)&group, sizeof(group));
                    groupFile.close();
                }
                break;

            case 6: // Display contacts in alphabetical order
                {
                    fstream file2;
                    Contact newContact;
                    vector<Contact> confile;
                    cout << "\t\n\t\t\t           List of contacts : "; 
                    cout << "\t\n\t\tName\t\t        Phone\t\t        Email\t\t        Group Name" << endl;
                    
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
                    file_path = "db/"+path+"/contact.dat";
                    file2.open(file_path.c_str(), ios::in | ios::app | ios::binary);
                    file2.seekg(0);
                    while(file2.read((char*)&newContact, sizeof(newContact))){
                        confile.push_back(newContact);
                    }
                    sort(confile.begin(), confile.end());
                    for(int i = 0; i < confile.size(); i++)
                    {
                        cout << "\t\n\t\t"  << confile[i].getName() << spaceGetter(confile[i].getName()) << confile[i].getPhone() << spaceGetter(confile[i].getPhone()) << confile[i].getEmail() << spaceGetter(confile[i].getEmail())<< confile[i].getGroupName()<< endl;
                    }
                    file2.close();
                }
                break;
            case 7: 
                {
                    Group group;
                    Contact contact;
                    fstream file_of_groups;
                    fstream file_of_contacts;

                    fstream curruser;
                    User usr;
                    string file_path,file_path1,path;
                    curruser.open("db/curruser.dat", ios::in | ios::binary);
                    curruser.seekg(0);
                    while (curruser.read((char*)&usr, sizeof(usr)))
                    {
                        path = usr.getUsername();
                        break;
                    }
                    curruser.close();
                    file_path = "db/"+path+"/contact.dat";
                    file_path1 = "db/"+path+"/groups.dat";

                    file_of_groups.open(file_path1.c_str(), ios::in | ios::app | ios::binary);
                    file_of_contacts.open(file_path.c_str(), ios::in | ios::app | ios::binary);
                    file_of_groups.seekg(0);
                    while(file_of_groups.read((char*)&group, sizeof(group))){
                        cout << "\tGroup name: " << group.getName() << "\n";
                        cout << "\t\n\t\t\tName\t\t        Phone\t\t        Email\t\t" << endl;
                        file_of_contacts.seekg(0);
                        while(file_of_contacts.read((char*)&contact, sizeof(contact))){
                            if (contact.getGroupName() == group.getName())
                            {
                                cout << " \t\t\t " << contact.getName() << spaceGetter(contact.getName()) << contact.getPhone() << spaceGetter(contact.getPhone()) << contact.getEmail() << "\n";
                            }
                        }
                    }
                    file_of_contacts.close();
                    file_of_groups.close();
                }

                    break;
            default:
                break;
        }
    }
    


    return 0;
}






