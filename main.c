#pragma warning(push)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "functions.h"

int main()
{
	int choice;
	do
	{
		printf("\n1.  Add a hotel\n");
		printf("2.  Remove a hotel\n");
		printf("3.  Add a staff\n");
		printf("4.  Remove staff\n");
		printf("5.  Change/Add a manager to hotel\n");
		printf("6.  Add a room to hotel\n");
		printf("7.  Remove a room\n");
		printf("8.  Fill a room with residents\n");
		printf("9.  Remove residents from room\n");
		printf("10. Add task to staff member\n");
		printf("11. Print all hotels information\n");
		printf("12. Print specific hotel information\n");
		printf("13. Search for room by room number (After the hotel sorted!)\n");
		printf("14. Sort rooms\n");
		printf("15. Export to Text file\n");
		printf("16. Export to Binary file\n");
		printf("17. Upload from Binary/Text file\n");
		printf("18. Exit the program\n");

		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		clearInputBuffer();
		switch (choice)
		{
		case 1:
			case1();
			break;
		case 2:
			case2();
			break;
		case 3:
			case3();
			break;
		case 4:
			case4();
			break;
		case 5:
			case5();
			break;
		case 6:
			case6();
			break;
		case 7:
			case7();
			break;
		case 8:
			case8();
			break;
		case 9:
			case9();
			break;
		case 10:
			case10();
			break;
		case 11:
			case11();
			break;
		case 12:
			case12();
			break;
		case 13:
			case13();
			break;
		case 14:
			case14();
			break;
		case 15:
			case15();
			break;
		case 16:
			case16();
			break;
		case 17:
			case17();
			break;
		case 18:
			printf("Exiting the program. Goodbye!\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 18);

	return 0;
}
