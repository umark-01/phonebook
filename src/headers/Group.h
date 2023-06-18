#ifndef GROUP_H
#define GROUP_H

// class for group

#include "Contact.h"
#include "signUp.h"

using namespace std;

class Group
{
    private:
        string groupName;
    public:
        Group()
        {
            groupName = "";
        }
        string getName(){
            return this->groupName;
        }
        void setGroup(string groupname)
        {
            this->groupName = groupname;
        }
};

#endif