#ifndef SIGNUP_H
#define SIGNUP_H

#include "Contact.h"
#include "user.h"


#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>


using namespace std;

class SignUp
{
    private:
        string username;
        string password;
    public:
        void setUsername()
        {
            User user;
            fstream file_of_usernames;
            cout << "\nEnter new username: ";
            cin >> username;
            cout << "\nEnter new password: ";
            cin >> password;
            cout << "\nSign up successful\n";
            // string seee = "db/"+username;
            // const char* dir = seee.c_str();
            // //creating new directory for new user, and data for every user will save seperately
            // int f = mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            // if (f == -1) {
            //     cout <<"\n\t\t\t\t!!!!THERE SOME MISTAKE WHILE CREATING NEW USER!!!!\n";
            // }
            string filepath = "db/"+username;

            const char* chrt = filepath.c_str();
            if (mkdir(chrt, 0755) == -1) {
                //cerr << "Error :  " << strerror(errno) << endl;
            } else {
                cout << "Directory created\n";
            }
            file_of_usernames.open("db/UserNames.txt",ios:: in | ios::app | ios::binary);
            if (!file_of_usernames.is_open()) {
                cout << "Error opening file!" << endl;
            }
            fstream file_of_current_user;
            file_of_current_user.open("db/curruser.dat", ios::trunc | ios::in | ios::out | ios::binary);
            //time_t now = time(0); // get current dat/time with respect to system  
            //char* dt = ctime(&now); // convert it into string 
            user.setData(username, password);
            file_of_current_user.write((char*)&user, sizeof(user));
            file_of_usernames.write((char*)&user, sizeof(user)); //saving users data to usernames.txt binary file
            file_of_usernames.close();
            file_of_current_user.close();
        }
        void OpenApp()
        {   
            string usernameSignIN;
            string passwordSignIN;
            fstream file, curruser;
            User user;
            bool success = false;
            char answer = 'y';

            // opening application
            do
            {
                cout << "\nDo you want open Phonebook application? (y/n): ";
                cin >> answer;
            }while(answer != 'y');
            
            // Sign in with username and password
            file.open("db/UserNames.txt",ios:: in | ios::binary);
            curruser.open("db/curruser.dat", ios::trunc | ios::in | ios::binary);
            cout << "\nPlease sign in";
            while(!success)
            {
                cout << "\nEnter username: "; 
                cin >> usernameSignIN;
                cout << "\nEnter password: ";
                cin >> passwordSignIN;
                file.seekg(0);
                while (file.read((char*)&user, sizeof(user))){
                    cout << user.getUsername() << " " << user.getUserPassword() << endl;
                    if (usernameSignIN == user.getUsername() and passwordSignIN == user.getUserPassword()) {
                        cout << "\n\t\t\t\t\tLogin successful";
                        cout << "\n\t\t\t\tWelcome to Phonebook application";
                        cout << "\n\t\t\t\t\tHello:) " << usernameSignIN;
                        curruser.write((char*)&user, sizeof(user));
                        success = true;
                        break;
                    }
                }
                if (!success) {
                    cout << "\n\t\t\t\t\tLogin failed";
                    cout << "\n\t\t\t\t\tPlease try again";
                }
            }
            file.close();
            curruser.close();
        }
};

#endif