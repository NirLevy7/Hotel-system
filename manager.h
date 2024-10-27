
#ifndef __MANAGER_H
#define __MANAGER_H
#define LENGTH 254


typedef struct Manager
{

	char* name[LENGTH];
	int phoneNum;


} Manager;


int printManagerDetails(Manager manager);
int changeName(Manager* manager);
int changePhoneNumber(Manager* manager);
#endif // __MANAGER_H







