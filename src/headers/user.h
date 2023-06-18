#ifndef USER_H
#define USER_H

#include "Contact.h"
#include "signUp.h"

using namespace std;

class User{
private:
    string user_name;
    string user_password;
    string date_added;
public:
    string getUsername(){
        return this->user_name;
    }
    string getUserPassword(){
        return this->user_password;
    }
    // string getDateAdded(){
    //     return this->date_added;
    // }
    void setData(string u, string p){
        this->user_name = u;
        this->user_password = p;
    }

};

#endif