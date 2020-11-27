struct Patient{
    char name[255], month[255];
    int day, year;
    Patient *next, *prev;
}*head, *tail;
