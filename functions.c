#include "functions.h"

void swapStruct(hotel* left, hotel* right) {// поменять местами структуры
    hotel temp;
    temp = *left;
    *left = *right;
    *right = temp;
}
void printline(){ // печать линии
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
void sort(){ //функция сортировки по выбранному полю
    FILE* file = fopen("HOTEL.csv", "r+");
    if (file == NULL){
         fclose(file);
         printf("Unable to open file\n");
         exit(1);
    }
    fseek(file, 0, SEEK_END);
    int amount_of_people = ftell(file) / sizeof(hotel);
    rewind(file);
    printf("By which field do you want to sort?\n");
    hotel* block = (hotel*)malloc(sizeof(hotel) * amount_of_people);
    if (block == NULL){
        printf("Error of malloc\n");
        exit(1);
    }
    int i, j;
    for (i = 0; i < amount_of_people; i++){
        fread(block + i, sizeof(hotel), 1, file);
    }
    printf("\t\t1) Surname\n\t\t2) Name\n\t\t3) Patronimic\n\t\t4) Room\n\t\t5) Date of arrival\n\t\t6) Date of departure\n\t\t7) Payment\n");
    printline();
    int choice;
    do{
        printf("Your choice : ");
        choice = getInt();
    }while(choice < 1 || choice > 7);
    printline();
    switch (choice){
    case 1:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (strcmp(block[j-1].surname,block[j].surname) > 0){
                    swapStruct(&block[j-1], &block[j]);
                }
            }
        }
        break;
    case 2:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (strcmp(block[j-1].name,block[j].name) > 0){
                    swapStruct(&block[j-1], &block[j]);
                }
            }
        }
        break;
    case 3:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (strcmp(block[j-1].patron,block[j].patron) > 0){
                    swapStruct(&block[j-1], &block[j]);
                }
            }
        }
        break;

    case 4:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (block[j-1].room > block[j].room) {
                    swapStruct(&block[j-1], &block[j]);
                }
            }
        }
        break;
    case 7:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (block[j-1].pay > block[j].pay) {
                    swapStruct(&block[j-1], &block[j]);
                }
            }

        }
        break;
    case 5:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (block[j-1].dateIN.month > block[j].dateIN.month) {
                    swapStruct(&block[j-1], &block[j]);
                } else if((block[j-1].dateIN.month == block[j].dateIN.month) & (block[j-1].dateIN.day > block[j].dateIN.day)){
                           swapStruct(&block[j-1], &block[j]);
                       }
            }
        }
        break;
    case 6:
        for(i = 0; i < amount_of_people; i++){
            for(j = amount_of_people - 1; j > i; j--){
                if (block[j-1].dateOUT.month > block[j].dateOUT.month) {
                    swapStruct(&block[j-1], &block[j]);
                } else if((block[j-1].dateOUT.month == block[j].dateOUT.month) & (block[j-1].dateOUT.day > block[j].dateOUT.day)){
                           swapStruct(&block[j-1], &block[j]);
                       }
            }
        }
        break;
  }
  rewind(file);
  fwrite(block, sizeof(hotel), amount_of_people, file);
  free(block);
  fclose(file);      
  output();
}

void edit(){//функция редактирования по заданному полю
    FILE* file = fopen("HOTEL.csv", "r+");
     if (file == NULL){
        fclose(file);
        printf("Unable to open file\n");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    int amount_of_people = ftell(file) / sizeof(hotel);
    rewind(file);
    int editnum = 0;
    do{
        printf("Enter the number of the record you would like to edit : ");
        editnum = getInt();
    } while (editnum < 1 || editnum > amount_of_people);
    fseek(file, sizeof(hotel) * (editnum - 1), SEEK_SET);
    hotel Person;
    fread(&Person, sizeof(hotel), 1, file);
    printline();
    printf("What field would you like to edit?\n");
    printf("\t1) Surname\n\t2) Name\n\t3) Patronimic\n\t4) Room\n\t5) Date of arrival\n\t6) Date of departure\n\t7) Payment\n\t8) Extra services\n");
    int choice;
    printline();
    int room;
    int day;
    int month;
    int length;
    double pay;
    do{
        printf("Your choice : ");
        choice = getInt();
    }while(choice < 1 || choice > 8);
    printline();
    switch (choice){
    case 1:
        do{
        length = 0;
        printf("Enter surname (maximum %d symbols): ", NAME);
        fgets(Person.surname, 2 * NAME, stdin);
        length = strlen(Person.surname);
        }while(length - 1 > NAME);
        Person.surname[length - 1] = '\0';
        break;
    case 2:
        do{

        length = 0;
        printf("Enter name (maximum %d symbols): ", NAME);
        fgets(Person.name, 2 * NAME, stdin);
        length = strlen(Person.name);
        }while(length - 1 > NAME);
        Person.name[length - 1] = '\0';
        break;
    case 3:
        do{
        length = 0;
        printf("Enter patronimic (maximum %d symbols): ", NAME);
        fgets(Person.patron, 2 * NAME, stdin);
        length = strlen(Person.patron);
        }while(length - 1 > NAME);
        Person.patron[length - 1] = '\0';
        break;
    case 4:
        do {
        printf("Enter room (only integer): ");
        room = getInt();
        } while(room <= 0);
        Person.room = room;
        break;
    case 5:
        printf("Enter date of ARRIVAL\n");
        do {
        printf("Enter MONTH(1 - 12) : ");
        month = getInt();
        } while(month < 1 || month > 12);
        Person.dateIN.month = month;
        Person.dateIN.day = dayCheck(month);
        break;
    case 6:
        printf("Enter date of DEPARTURE\n");
        do {
        printf("Enter MONTH(1 - 12) : ");
        month = getInt();
        } while(month < 1 || month > 12);
        Person.dateOUT.month = month;
        Person.dateOUT.day = dayCheck(month);
        break;
    case 7:
        do {
        printf("Enter amount of payment (only integer) : ");
        pay = getInt();
        } while (pay <= 0);
        Person.pay = pay;
        break;
    case 8:
         do{
         printf("Enter additional services provided(maximum %d symbols): ", EXTRAS - 1);
         fgets(Person.extra, 2 * EXTRAS, stdin);
         length = strlen(Person.extra);
         }while(length > EXTRAS);
         Person.extra[length] = '\0';

         break;
    output();
    }

    fseek(file, sizeof(hotel) * (editnum - 1), SEEK_SET);
    fwrite(&Person, sizeof(hotel), 1, file);
    fclose(file);
    output();
}
void delete(){ //функция удаление выбранной записи

    FILE* file = fopen("HOTEL.csv", "r");
     if (file == NULL){
        fclose(file);
        printf("Unable to open file\n");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    int amount_of_people = ftell(file) / sizeof(hotel);
    rewind(file);
    int num = 0;
    do{
        printf("Enter the number of the record you would like to delete from the database : ");
        num = getInt();
    } while (num < 1 || num > amount_of_people);
    hotel* People = (hotel*)malloc(sizeof(hotel) * (amount_of_people - 1));
    if (People == NULL){
        printf("Erroe of malloc\n");
        exit(2);
    }
    int count = 0;
    for (int i = 0; i < amount_of_people; i++){
        if ((i + 1) != num){
            fread(People + count, sizeof(hotel), 1, file);
            ++count;
        }
        else {
            fseek(file, sizeof(hotel), SEEK_CUR);
        }
    
    }
    fclose(file);
    file = fopen("HOTEL.csv", "w");
    if (file == NULL){
        fclose(file);
        printf("Unable to open file\n");
        exit(1);
    }
    fwrite(People, sizeof(hotel), amount_of_people - 1, file);
    free(People);
    fclose(file);
    output();
}


void output(){// вывод базы данных на экран в табличной форме
    FILE* file = fopen("HOTEL.csv", "r");
    hotel Person;
    if (file == NULL){
        fclose(file);
        printf("Unable to open file\n");
        exit(1);
    }
    rewind(file);
    char name[] = "FIO";
    printf("\n№   | %-77s |  Room  | Arrival | Departure |     Payment    | Extra services \n",name);
    printline();
    int k = 1;
    while(1){
        fread(&Person, sizeof(hotel), 1, file);
        if (feof(file)){
           break;
        }
        printf("%-3d | %-25s %-25s %-25s | %6d |  %02d/%02d  |   %02d/%02d   |  %9d₽    | %s",k++, Person.surname, Person.name, Person.patron, Person.room, Person.dateIN.day, Person.dateIN.month, Person.dateOUT.day, Person.dateOUT.month,Person.pay, Person.extra);
    printline();
    }
    fclose(file);
}
void addperson(){// функция добавления одного человека в базу
     FILE* file = fopen("HOTEL.csv", "a"); //открываем файл для дозаписи
     if (file == NULL){
        fclose(file);
        printf("Unable to open file\n");
        exit(1);
    }
    hotel Person;
    addone(&Person);
    fwrite(&Person, sizeof(hotel), 1, file);
    fclose(file);
    output();
}
void addone(hotel* New_Person){//функция считывания даннных человека и запись в структуру, которая поступает в качестве аргумета

        int length;
        do{
        length = 0;
        printf("Enter surname (maximum %d symbols): ", NAME);
        fgets(New_Person->surname, 2 * NAME, stdin);
        length = strlen(New_Person->surname);
        }while(length - 1 > NAME);
        New_Person->surname[length - 1] = '\0';
        do{
        length = 0;
        printf("Enter name (maximum %d symbols): ", NAME);
        fgets(New_Person->name, 2 * NAME, stdin);
        length = strlen(New_Person->name);
        }while(length - 1 > NAME);
        New_Person->name[length - 1] = '\0';
        do{
        length = 0;
        printf("Enter patronimic (maximum %d symbols): ", NAME);
        fgets(New_Person->patron, 2 * NAME, stdin);
        length = strlen(New_Person->patron);
        }while(length - 1 > NAME);
        New_Person->patron[length - 1] = '\0';


    int room;
    do {
        printf("Enter room (only integer): ");
        room = getInt();
    } while(room <= 0);
    New_Person->room = room;
    int month;
    printf("Enter date of ARRIVAL\n");
    do {
        printf("Enter MONTH(1 - 12) : ");
        month = getInt();
    } while(month < 1 || month > 12);
    New_Person->dateIN.month = month;
    New_Person->dateIN.day = dayCheck(month);
    month = 0;
    printf("Enter date of DEPARTURE\n");
    do {
        printf("Enter MONTH(1 - 12) : ");
        month = getInt();
    } while(month < 1 || month > 12);
    New_Person->dateOUT.month = month;
    New_Person->dateOUT.day = dayCheck(month);
    double pay;
    do {
        printf("Enter amount of payment (only integer) : ");
        pay = getInt();
    } while (pay <= 0);
    New_Person->pay = pay;
    do{
        printf("Enter additional services provided(maximum %d symbols): ", EXTRAS - 1);
        fgets(New_Person->extra, 2 * EXTRAS, stdin);
        length = strlen(New_Person->extra);
    }while(length > EXTRAS);
    New_Person->extra[length] = '\0';
}


double getDouble(){ //проверка при получении вещественного числа
    char check[HALFSIZE];
    double number;
    fgets(check, HALFSIZE, stdin);
    number = atof(check);
    return number;
}

int getInt(){ //проверка на получение целого
    char check[HALFSIZE];
    int number;
    fgets(check, HALFSIZE, stdin);
    number = atoi(check);
    return number;
}

int dayCheck(int month){ //проверка, что существует такой день в конкретном месяце
   int day;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){

        do {
            printf("Enter DAY: ");
            day = getInt();
        } while(day < 1 || day > 31);
    }
    if(month == 2){
        do {
            printf("Enter DAY : ");
            day = getInt();
         } while(day < 1 || day > 29);
    }
    if (month == 4 || month == 6 || month == 9 || month == 10) {
        do {
            printf("Enter DAY : ");
            day = getInt();
        } while(day < 1 || day > 30);
    }
    return day;
}
void clean_stdin() { //очищение stdin 
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void filling(){// заново заполнение базы данных
    FILE* file;
    file = fopen("HOTEL.csv", "w");
    if (file == NULL){
        fclose(file);
        printf("Unable to open file\n");
        exit(1);
    }
    hotel New_Person;
    char c;

    do{
         addone(&New_Person);
         fwrite(&New_Person, sizeof(hotel), 1, file);
         fflush(file);
         printf("Enter 1, if you want to add another person or smth else to stop filling the database : ");
         c = getchar();
         clean_stdin();
    }while(c == '1');
    fclose(file);
    output();
}
void printone(hotel* Person, int k){//вывод на экран одного человека
printf("%-3d | %-20s %-20s %-20s | %4d |  %02d/%02d  |   %02d/%02d  |  %9d₽    | %s",k++, Person->surname, Person->name, Person->patron, Person->room, Person->dateIN.day, Person->dateIN.month, Person->dateOUT.day, Person->dateOUT.month,Person->pay, Person->extra);
    printline();
}
void search(){//поиск по заданному полю
    FILE* file = fopen("HOTEL.csv", "r");
     if (file == NULL){
         fclose(file);
         printf("Unable to open file\n");
         exit(1);
    }

    fseek(file, 0, SEEK_END);
    int amount_of_people = ftell(file) / sizeof(hotel);
    rewind(file);
    printf("Which field would you like to search?\n");
    printf("\t\t1) Surname\n\t\t2) Name\n\t\t3) Patronimic\n\t\t4) Room\n\t\t5) Date of arrival\n\t\t6) Date of departure\n\t\t7) Payment\n");
    int choice, room, day, month, length, pay, i;
    char surname[NAME*2+1], name[NAME*2+1], patron[NAME*2+1];
    bool flag = false;
    int num = 0;
    hotel Temp;
    printline();
    do{
        printf("Your choice : ");
        choice = getInt();
    }while(choice < 1 || choice > 7);
    printline();
    if (choice == 1){
        do{
        length = 0;
        printf("Enter surname to search by(maximum %d symbols): ", NAME);
        fgets(surname, 2*NAME, stdin);
        length = strlen(surname);
        }while(length - 1 > NAME);

        surname[length -1] = '\0';
        printline();
        for(i = 0; i < amount_of_people; i++){
            fread(&Temp, sizeof(hotel), 1, file);
            if (strcmp(Temp.surname, surname) == 0){
                flag = true;
                ++num;
                printone(&Temp, num);
            }
        }
    }

    if (choice == 2){
        do{
        length = 0;
        printf("Enter name to search by(maximum %d symbols): ", NAME);
        fgets(name, 2*NAME, stdin);
        length = strlen(name);
        }while(length - 1 > NAME);
        name[length -1] = '\0';
        printline();
        for(i = 0; i < amount_of_people; i++){
            fread(&Temp, sizeof(hotel), 1, file);
            if (strcmp(Temp.name, name) == 0){
                flag = true;
                ++num;
                printone(&Temp, num);
            }
        }
    }
    if (choice == 3){
        do{
        length = 0;
        printf("Enter patronimic to search by(maximum %d symbols): ", NAME);
        fgets(patron, 2*NAME, stdin);
        length = strlen(patron);
        }while(length - 1 > NAME);
        patron[length -1] = '\0';
        printline();
        for(i = 0; i < amount_of_people; i++){
            fread(&Temp, sizeof(hotel), 1, file);
            if (strcmp(Temp.patron, patron) == 0){
                flag = true;
                ++num;
                printone(&Temp, num);
            }
        }  
    }
    if (choice == 4){
        do{
            printf("Enter room to search by(only integer): ");
            room = getInt();
        }while(room <= 0);
        printline();
        for(i = 0; i < amount_of_people; i++){
            fread(&Temp, sizeof(hotel), 1, file);
            if (Temp.room == room){
                flag = true;
                ++num;
                printone(&Temp, num);

            }
        }
    }
    if (choice == 5|| choice == 6){
        month = 0; day = 0;
        printf("Enter date to search by: \n");
        do {
        printf("Enter MONTH(1 - 12) : ");
        month = getInt();
        } while(month < 1 || month > 12);
        day = dayCheck(month);
        printline();
        for(i = 0; i < amount_of_people; i++){
            fread(&Temp, sizeof(hotel), 1, file);
            if ((choice == 5 & Temp.dateIN.month == month & Temp.dateIN.day == day) || (choice == 6 & Temp.dateOUT.month == month & Temp.dateOUT.day == day)){
                flag = true;
                ++num;
                printone(&Temp, num);
            }
        }
    }
    if (choice == 7){
        do {
        printf("Enter sum to search by (only integer) : ");
        pay = getInt();
        } while(pay <= 0);
        printline();
        for(i = 0; i < amount_of_people; i++){
            fread(&Temp, sizeof(hotel), 1, file);
            if (Temp.pay == pay){
                flag = true;
                ++num;
                printone(&Temp, num);
            }
        }
    }
    if (flag == false){
            printf("Such a record is not found!\n");
    }
}
void intro(){//приветствие
    printline();
    printf("\t\tWelcome to HOTEL database. Choose something from MENU\n\t\tWARNING: if you will enter incorrect data then you will be asked to enter the data AGAIN. Thanks for understanding :)\n");
} 

void menu(){//меню
    int option;
    printline();
    printf("\t\tMENU\n");
    printf("\t\t(1)Filling the database\n\t\t(2)Adding a record to the database\n\t\t(3)Delete the specified record from the database\n\t\t(4)Search for a record by a given field\n\t\t(5)Editing a given record in the database\n\t\t(6)Sorting data in the database by a given field\n\t\t(7)Displaying the contents of the database in tabular form\n\t\t(8)Exit\n");
    printline();
    do {
        printf("Choose the option, please(just one integer from 1 to 8): ");
        option = getInt();
    }while (option < 1 || option > 8);
    printline();
    switch (option){
    case 1 :
        filling();
        break;
    case 2 :
        addperson();
        break;
    case 3 :  
        delete();
        break;
    case 4 :
        search();
        break;
    case 5 :
        edit();
        break;
    case 6:
        sort();
        break;
    case 7:
        output();
        break;
    case 8:
        exit(0);
        break;
    }

}

