#ifndef __DATE_H
#define __DATE_H
#define _CRT_SECURE_NO_WARNINGS
#define LENGTH 254

typedef struct
{
    int day, month, year;
} Date;

int ValidDate(Date* pDate);
void convertToDate(char date[LENGTH], Date* pDate);
int checkDepartureDateAfterArrivalDate(Date* productionDate, Date* expirationDate);

#endif // __DATE_H