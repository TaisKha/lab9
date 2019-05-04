#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    int day;
    int month;
}date;
typedef struct hotel
{
    char surname[NAME * 2 + 1];
    char name[NAME * 2 + 1];
    char patron[NAME * 2 + 1];
    int room;
    date dateIN;
    date dateOUT;
    int pay;
    char extra[EXTRAS * 2 + 1];
} hotel;
#endif

