#define List_Size 30
#define List_Increment 5

typedef struct
{
    char name[20];
    char number[10];
    char duty[20];
}Staff;

typedef struct
{
    Staff *p;
    int length;
    int listsize;
}StaffList;