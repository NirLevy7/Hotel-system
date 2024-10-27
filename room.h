#ifndef __ROOM_H
#define __ROOM_H
#include "staff.h"
#define ROOMCAPACITY 4
#define PRINT_ROOM_DETAILS(room) \
    printf("Room Number: %d | Floor: %d | Residents: %d/%d\n", \
           (room)->roomNumber, (room)->floor + 1, (room)->numOfResidents, (room)->roomCapacity)

typedef enum Floor
{
	First,
	Second,
	Third
} Floor;

typedef enum sortField
{
	roomNumber,
	floor,
	numOfResidents,
	notSorted
} sortField;

typedef struct Room
{
	int roomNumber;
	Floor floor;
	int roomCapacity;
	int numOfResidents;
} Room;

typedef struct RoomManager
{
	struct Room* roomArr;
	int numOfRooms;
	int capacity;
	sortField sort;
} RoomManager;


int emptyRoom(RoomManager* roomMan, Room room, int numOfResidents);
int fillRoom(RoomManager* roomMan, Room room, int numOfResidents);
int addRoom(RoomManager* roomMan, Room room);
int roomMemoryAllocation(RoomManager* roomMan, int n);
int removeRoom(RoomManager* roomMan, Room room);
int getNumOfAvailableRooms(RoomManager* roomMan);
int printAvailableRooms(RoomManager* roomMan);
int printAllRoomsDetails(RoomManager* roomMan);
Room* returnRoom(RoomManager* roomMan, int roomNumber, int floor);
int compareRoomNumber(const void* a, const void* b);
int compareFloorNumber(const void* a, const void* b);
int compareNumResidents(const void* a, const void* b);
void handleRoomSearch(RoomManager* roomManager, int searchMethod, int searchKey, Room** result);
int isRoomNumberExists(RoomManager* roomMan, int roomNumber);

#endif //__ROOM_H_