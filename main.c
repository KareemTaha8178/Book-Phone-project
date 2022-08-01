#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
COORD coord = {0, 0};
void gotoxy(int, int);
typedef struct {
    char username[30], pass[30], confPass[30], gender[7], country[15], city[15], mail[50], ph_num[15], age[10], id[15];
}register_info;
typedef struct {
    char fullName[50], gender[7], country[15], city[15], mail[50], ph_num[15], age[10];
}contactInfo;
struct stackNode {
    contactInfo info;
    struct stackNode *next;
};
typedef struct stackNode node;
typedef struct stackNode* nodeptr;
void signUp(void);
void signIn(void);
bool checkValidation(char [], int);
void takeDataFromFile(nodeptr *);
void saveInFile(nodeptr);
void instructions(void);
void addition(nodeptr *);
void push(nodeptr *, contactInfo);
void modify(nodeptr *);
void pop(nodeptr *);
void deleteExistContact(nodeptr *);
void research(nodeptr);
void display(nodeptr);
void reset(nodeptr *);
bool isEmpty(nodeptr);
void welcome();
bool exceed(char []);
bool zerobegin(char input[]);
bool isString(char []);
bool pass_valid(char a[]);
bool isSubstring(char[], char[]);
bool email_is_valid(char []);
FILE *fptr;
char fname[] = {"file.txt"};
void main(void) {
    welcome();
    nodeptr top = NULL;
    int x ,p;
    gotoxy(53,6);
    printf(">> Enter 1 to sign up");
    gotoxy(53,8);
    printf(">> Enter 2 to sign in");
    gotoxy(53,10);
    printf(">> Enter your choice:");
    gotoxy(75,10);
    p=12;
    scanf("%d", &x);
    while(1){
       if (x == 1){
            signUp();
            break;
       }
       else if(x == 2){
            signIn();
            break;
       }
       else{
        gotoxy(53,p);
       printf(">> Enter a Valid Choice: ");
       gotoxy(78,p);
       scanf("%d", &x);
       p=p+2;
       }
    }
    takeDataFromFile(&top);
    char input[20];
    system("cls");
    instructions();
   gotoxy(65,22);
    while (1) {
        scanf("%s", input);
        system("cls");
        if (isString(input)){gotoxy(45,26); printf(">> Please, Enter a Valid Number <<");}
        else {
            int choice = atoi(input);
            switch(choice) {
                case 1:
                    addition(&top);
                    break;
                case 2:
                    if (isEmpty(top)){gotoxy(45,26);printf(">> Your Contacts is Empty <<");}
                    else modify(&top);
                    break;
                case 3:
                    if (isEmpty(top)){gotoxy(45,26);printf(">> Your Contacts is Empty <<");}
                    else {pop(&top);
                    gotoxy(45,26);printf(">> Contact Delete Successfully <<");
                    }
                    break;
                case 4:
                    if (isEmpty(top)){gotoxy(45,26);printf(">> Your Contacts is Empty <<");}
                    else deleteExistContact(&top);
                    break;
                case 5:
                    research(top);
                    break;
                case 6:
                    if (isEmpty(top)){gotoxy(45,26);printf(">> Your Contacts is Empty <<");}
                    else display(top);
                    getch();
                    system("cls");
                    break;
                case 7:
                    reset(&top);
                    gotoxy(45,26);
                    printf(">> Program Reset Done <<");
                    break;
                case 8:
                    system("color 08");
                    gotoxy(45,10);
                    printf(">> Thank You For Use Our Program <<\n\n\n\n\n\n");
                    return;
                default:
                    gotoxy(45,26);
                    printf(">> Invalid Choice <<");
                    break;
            }
        }
        instructions();
    }
}
void signUp() {
    int g;
    system("color 0b");
    system("cls");
    register_info data;
    gotoxy(43,2);
    printf("*>____________ ©Phone Book® ____________<*");
    gotoxy(56,4);
    printf("**>> Sign up <<**");
    gotoxy(0,8);
    printf(">> Enter Your User Name: ");
    fflush(stdin);
    do {
        scanf("%s",data.username);
    }while(checkValidation(data.username, 1));
    printf("\n>> Enter The Password: ");
    fflush(stdin);
    gets(data.pass);
    while(!pass_valid(data.pass)){
      printf("\n>> Enter The Password Again: ");
      gets(data.pass);
    }
    printf(">> Enter The Confirm Password: ");
    scanf("%s", data.confPass);
    while (1) {
        if (strcmp(data.confPass, data.pass) != 0){
        printf("\n>> The Confirm Password doesn't match, please try again: ");
        printf("\n>> Enter The Confirm Password: ");
        scanf("%s", data.confPass);
        }
        else break;
    }
    printf("\n>> Enter Your Gender: ");
    scanf("%s", data.gender);
    printf("\n>> Enter Your E-Mail: ");
    scanf("%s", data.mail);
    while(checkValidation(data.mail, 2) || !email_is_valid(data.mail)){
            if(checkValidation(data.mail, 2)){
        printf("\n>> Enter Your Valid E-Mail: ");
        scanf("%s", data.mail);
            }
            else if(!email_is_valid(data.mail)){
        printf ("\n>> Sorry, Enter a Valid E-Mail Form (Someone@example.com) <<");
        printf("\n>> Enter Your E-Mail Again:  ");
        scanf("%s", data.mail);
    }
    }
    printf("\n>> Enter your Age: ");
    scanf("%s", data.age);
        while (isString(data.age) || exceed(data.age) || zerobegin(data.age)) {
            if(isString(data.age)){
        printf ("\n>> Sorry, The Age must be Valid Number <<");
        printf("\n>> Enter your Age Again: ");
        scanf("%s", data.age);
            }
        else if(exceed(data.age)){
        printf ("\n>> Sorry, The Age mustn't exceed 150 years <<");
         printf("\n>> Enter your Age Again: ");
        scanf("%s", data.age);
            }
            else if(zerobegin(data.age)){
        printf ("\n>> Sorry, The Age can't be zero and can't begin with zero <<");
        printf("\n>> Enter your Age Again: ");
        scanf("%s", data.age);
            }
    }
    printf("\n>> Enter your Country: ");
    scanf("%s", data.country);
    printf("\n>> Enter Your City: ");
    scanf("%s", data.city);
    printf("\n>> Enter Your Phone Number: ");
    scanf("%s", data.ph_num);
    while (isString(data.ph_num) || checkValidation(data.ph_num, 3)) {
            if(isString(data.ph_num)){
        printf ("\n>> Sorry, The Phone Number must be Valid Number <<");
        printf("\n>> Phone Number  : ");
        fflush(stdin);
        scanf("%s", data.ph_num);
            }
            else if(checkValidation(data.ph_num, 3)){
        printf("\n>> Enter Your Valid Phone: ");
        scanf("%s", data.ph_num);
            }
        }
    strcpy(data.id, "");
    strncat(data.id, data.age, 2);
    strncat(data.id, data.ph_num, 11);
    fptr = fopen(fname, "ab+");
    fwrite(&data, sizeof(data), 1, fptr);
    fclose(fptr);
    strcpy(fname, data.id);
    strcat(fname, ".txt");
    system("cls");
    system("color e9");
    gotoxy(35,12);
    printf("**>>______Welcome To Our Program Book Phone______<<**");
    getch();
    system("cls");
    return;
}
bool checkValidation(char str[], int x) {
    register_info data;
    fptr = fopen(fname, "ab+");
    while(1) {
        fread(&data, sizeof(data), 1, fptr);
        if(feof(fptr))return false;
        if (x == 1) {
            if(!strcmp(data.username, str)) {
            printf("\n>> This User name Exist, please Enter another one");
            printf("\n>> Enter User name again:");
            return true;
            }
        }
        if (x == 2) {
            if(!strcmp(data.mail, str)) {
            printf("\n>> This Email Exist, please Enter another one");
            return true;
            }
        }
        if (x == 3) {
            if(!strcmp(data.ph_num, str)) {
            printf("\n>> This phone number Exist, please Enter another one");
            return true;
            }
        }
    }
}
void signIn(void) {
    system("color 0b");
    system("cls");
    register_info data;
    char name[30], pass[30];
    bool ok;
    gotoxy(43,2);
    printf("*>____________ ©Phone Book® ____________<*");
    gotoxy(56,4);
    printf("**>> Sign in <<**");
    gotoxy(0,8);
    printf(">> Enter Your User Name: ");
    fflush(stdin);
    scanf("%s",name);
    printf("\n>> Enter The Password: ");
    scanf("%s", pass);
    fptr = fopen(fname, "ab+");
    while(1) {
        fread(&data, sizeof(data), 1, fptr);
        if(feof(fptr)) {
            ok = false;
            break;
        }
        if (!strcmp(data.username, name) && !strcmp(data.pass, pass)) {
            ok = true;
            break;
        }
    }
    if (ok) {
        strcpy(fname, data.id);
        strcat(fname, ".txt");
        system("cls");
        system("color e9");
        gotoxy(35,12);
        printf("**>>______Welcome To Our Program Book Phone______<<**");
        getch();
        system("cls");
    }
    else {
        int choice;
        printf("\n>> your Info isn't valid \n>> Enter 1 if you need to log in again or Enter 2 to create an account\n>> Enter your Choice:");
        scanf("%d", &choice);
        if (choice == 1)signIn();
        if (choice == 2)signUp();
    }
    return;
}
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void welcome(){
system("color e9");
 gotoxy(38,2);
 printf("**>>>>________  Welcome To Phone Book  ________<<<<**");
 gotoxy(3,27);
 printf("**>> Created By [H,K,I,A,M] <<**\n");
 getch();
 return 0;
}
// Function to get and show data from file...
void takeDataFromFile(nodeptr *top) {
    nodeptr top2 = NULL;
    contactInfo data;
    fptr = fopen(fname, "ab+");
    while(1) {
        fread(&data, sizeof(data), 1, fptr);
        if(feof(fptr))break;
        nodeptr newnode = (nodeptr)malloc(sizeof(node));
        newnode->info = data;
        newnode->next = top2;
        top2 = newnode;
    }
    fclose(fptr);
    while(!isEmpty(top2)) {
        push(top, top2->info);
        top2 = top2->next;
    }
    return;
}
// Function to save data to file...
void saveInFile(nodeptr top) {
    //open file to save data to it...
    fptr = fopen(fname, "wb");
    //infinite loop until top=Null...
    while (!isEmpty(top)) {
            //write data into the file...
        fwrite(&(top->info), sizeof(top->info), 1, fptr);
        //make top = next element in stack to save it in the file...
        top = top->next;
    }
    //close file after make everything...
    fclose(fptr);
    return;
}
void instructions(void) {
    system("color 0b");
    gotoxy(45,4);
    printf ("*********** Welcome To Book Phone ***********");
    gotoxy(45,6);
    printf ("[1]- Add a new contact.        ");
    gotoxy(45,8);
    printf ("[2]- Modify an exist contact.  ");
    gotoxy(45,10);
    printf ("[3]- Delete the first contact. ");
    gotoxy(45,12);
    printf ("[4]- Delete an exist contact.  ");
    gotoxy(45,14);
    printf ("[5]- Research.                 ");
    gotoxy(45,16);
    printf ("[6]- Display your contacts.    ");
    gotoxy(45,18);
    printf ("[7]Reset.                      ");
    gotoxy(45,20);
    printf ("[8]End.                        ");
    gotoxy(45,22);
    printf ("Enter Your Choice:             ");
    return 0;
}
void addition(nodeptr *top) {
    int k;
    contactInfo userInfo;
    system("cls");
                system("color 0e");
                puts("");
                fflush(stdin);
                gotoxy(45,2);
                printf("*>____________ ©Phone Book® ____________<*");
                gotoxy(57,4);
                printf("*>> Add Contact <<*");
                gotoxy(5,6);
                printf(">> Full Name     : ");
                gotoxy(24,6);
                gets(userInfo.fullName);
                gotoxy(5,8);
                printf(">> Gender        : ");
                fflush(stdin);
                gotoxy(24,8);
                scanf("%s", userInfo.gender);
                gotoxy(5,10);
                printf(">> E-Mail        : ");
                gotoxy(24,10);
                scanf("%s", userInfo.mail);
                k=11;
        while (!email_is_valid(userInfo.mail)) {
                k=k+1;
        gotoxy(5,k);
        printf (">> Sorry, Enter a Valid E-Mail Form (Someone@example.com) <<");
        gotoxy(5,k+1);
        printf(">> E-Mail           : ");
        scanf("%s", userInfo.mail);
        k=k+2;
    }
    k++;
                gotoxy(5,k);
                printf(">> Age           : ");
                scanf("%s", &userInfo.age);
                k++;
    while (isString(userInfo.age) || exceed(userInfo.age) || zerobegin(userInfo.age)) {
            k++;
            if(isString(userInfo.age)){
        gotoxy(5,k);
        printf (">> Sorry, The Age must be Valid Number <<");
        gotoxy(5,k+1);
        printf(">> Age           : ");
        scanf("%s", userInfo.age);
    k++;
            }
        else if(exceed(userInfo.age)){
        gotoxy(5,k);
        printf (">> Sorry, The Age mustn't exceed 150 years <<");
        gotoxy(5,k+1);
        printf(">> Age           : ");
        scanf("%s", userInfo.age);
        k++;
            }
            else if(zerobegin(userInfo.age)){
        gotoxy(5,k);
        printf (">> Sorry, The Age can't be zero and can't begin with zero <<");
        gotoxy(5,k+1);
        printf(">> Age           : ");
        scanf("%s", userInfo.age);
        k++;
            }
            k++;
    }
    k++;
                gotoxy(5,k);
                printf(">> Country       : ");
                fflush(stdin);
                gotoxy(24,k);
                scanf("%s", userInfo.country);
                gotoxy(5,k+2);
                printf(">> City          : ");
                fflush(stdin);
                gotoxy(24,k+2);
                scanf("%s", userInfo.city);
                gotoxy(5,k+4);
                printf(">> Phone Number  : ");
                fflush(stdin);
                gotoxy(24,k+4);
                scanf("%s", userInfo.ph_num);
                k=k+5;
    while (isString(userInfo.ph_num)) {
            k++;
        gotoxy(5,k);
        printf (">> Sorry, The Phone Number must be Valid Number <<");
        gotoxy(5,k+1);
        printf(">> Phone Number  : ");
        fflush(stdin);
        gotoxy(24,k+1);
        scanf("%s", userInfo.ph_num);
    k=k+2;
    }
    k=k+2;
    push(top, userInfo);
    gotoxy(56,k);
    printf("*> Successfully Add <*\n\n");
    getch();
    system("cls");
}
void push(nodeptr *top, contactInfo userInfo) {
    nodeptr newnode = (nodeptr)malloc(sizeof(node));
    newnode->info = userInfo;
    newnode->next = *top;
    *top = newnode;
    saveInFile(*top);
    return;
}
void modify(nodeptr *top) {
    system("color 0c");
    gotoxy(42,2);
    printf("*>____________ ©Phone Book® ____________<*");
    gotoxy(52,4);
    printf("*>> Modify Contact <<*");
    nodeptr temp = *top, tomodifyPtr;
    int cnt = 1, choice, i = 0;
    char name[30];
    bool ok = false;
    gotoxy(2,8);
    printf(">> Enter The Name of Contact which you need to modify: ");
    fflush(stdin);
    gotoxy(57,8);
    scanf("%s",name);
    while(!isEmpty(temp)) {
         if (isSubstring(temp->info.fullName, name) && i == 0)tomodifyPtr = temp, i++;
         else if (isSubstring(temp->info.fullName, name) && i == 1) {
         printf("[%d]-\n", 1);
         printf ("\tFull Name   :- %s\n", tomodifyPtr->info.fullName);
         printf ("\tGender      :- %s\n", tomodifyPtr->info.gender);
         printf ("\tE-Mail      :- %s\n", tomodifyPtr->info.mail);
         printf ("\tAge         :- %s\n", tomodifyPtr->info.age);
         printf ("\tCountry     :- %s\n", tomodifyPtr->info.country);
         printf ("\tCity        :- %s\n", tomodifyPtr->info.city);
         printf ("\tPhone Number:- %s\n", tomodifyPtr->info.ph_num);
         puts("\n");
         ok = true;
  }
    if(isSubstring(temp->info.fullName, name) && ok) {
     printf("[%d]-\n", 1 + (i++));
     printf ("\tFull Name   :- %s\n", temp->info.fullName);
     printf ("\tGender      :- %s\n", temp->info.gender);
     printf ("\tE-Mail      :- %s\n", temp->info.mail);
     printf ("\tAge         :- %s\n", temp->info.age);
     printf ("\tCountry     :- %s\n", temp->info.country);
     printf ("\tCity        :- %s\n", temp->info.city);
     printf ("\tPhone Number:- %s\n", temp->info.ph_num);
     puts("\n");
  }
     temp = temp->next;
  }
    if (i == 0) {
        gotoxy(2,10);
        printf(">> Not Found << ");
        getch();
        system("cls");
        return;
  }
    else if (i != 1) {
        temp = *top;
        printf("\n>> Please, Choose one from the Following Contacts: ");
        scanf("%d", &choice);
      while(choice <=0 || choice > i){
           printf("\n>> Please Enter a Valid Choice:   ");
           scanf("%d", &choice);
  }
      while (1) {
        if (isSubstring(temp->info.fullName, name))
             if (cnt == choice) break;
             else cnt++;
        temp = temp->next;
}
}
    else temp = tomodifyPtr;
        printf ("\nThe Exist Contact is: \n\n");
        printf ("\tFull Name   :- %s\n", temp->info.fullName);
        printf ("\tGender      :- %s\n", temp->info.gender);
        printf ("\tE-Mail      :- %s\n", temp->info.mail);
        printf ("\tAge         :- %s\n", temp->info.age);
        printf ("\tCountry     :- %s\n", temp->info.country);
        printf ("\tCity        :- %s\n", temp->info.city);
        printf ("\tPhone Number:- %s\n", temp->info.ph_num);
        puts("\n");
        int subChoice;
    do{
       printf ("\nEnter Your choice:\n"
               " [1]- to modify The Name\n"
               " [2]- to modify The Gender\n"
               " [3]- to modify The Mail\n"
               " [4]- to modify The Age\n"
               " [5]- to modify The Country\n"
               " [6]- to modify The City\n"
               " [7]- to modify The Phone Number\n"
               " [8]- to modify The Entire Contact\n"
               " [0]- to save\n");
            scanf("%d" ,&subChoice);
     while (subChoice > 8 || subChoice < 0 ){
          printf("\n>>Enter a valid choice from '0 To 8'<<\n");
          scanf("%d", &subChoice);
  }
          switch(subChoice) {
          case 1:
          printf ("\nEnter The New Name: ");
          fflush(stdin);
          gets(temp->info.fullName);
          break;
          case 2:
          printf ("\nEnter The New Gender:");
          fflush(stdin);
          gets(temp->info.gender);
          break;
          case 3:
          printf ("\nEnter The New E-Mail:");
          fflush(stdin);
          gets(temp->info.mail);
          break;
          case 4:
          printf ("\nEnter The New Age:");
          fflush(stdin);
          scanf("%s", temp->info.age);
          break;
          case 5:
          printf ("\nEnter The New Country:");
          fflush(stdin);
          gets(temp->info.country);
          break;
          case 6:
          printf ("\nEnter The New City:");
          fflush(stdin);
          gets(temp->info.city);
          break;
          case 7:
          printf ("\nEnter The New Phone Number:");
          fflush(stdin);
          scanf("%s", temp->info.ph_num);
          break;
          case 8:
          fflush(stdin);
          printf("\nEnter The New Name :\n");
          gets(temp->info.fullName);
          printf ("\nEnter The New Gender :\n");
          fflush(stdin);
          scanf("%s", temp->info.gender);
          printf ("\nEnter The New Mail :\n");
          scanf("%s", temp->info.mail);
          printf ("\nEnter The New Age :\n");
          scanf("%s", temp->info.age);
          printf ("\nEnter The New Country :\n");
          fflush(stdin);
          scanf("%s", temp->info.country);
          printf ("\nEnter The New city :\n");
          scanf("%s", temp->info.city);
          printf ("\nEnter The New Phone Number :\n");
          scanf("%s", temp->info.ph_num);
          break;
 }
 } while (subChoice != 0);
         saveInFile(*top);
         printf("\n>> The Contact after modifying: \n\n");
         printf ("\tFull Name   :- %s\n", temp->info.fullName);
         printf ("\tGender      :- %s\n", temp->info.gender);
         printf ("\tE-Mail      :- %s\n", temp->info.mail);
         printf ("\tAge         :- %s\n", temp->info.age);
         printf ("\tCountry     :- %s\n", temp->info.country);
         printf ("\tCity        :- %s\n", temp->info.city);
         printf ("\tPhone Number:- %s\n", temp->info.ph_num);
         puts("\n");
         printf("\n\n>> Modify Done Successfully <<");
         getch();
         system("cls");
         return;
}
void pop(nodeptr *top) {
    nodeptr temp = *top;
    *top = (*top)->next;
    free(temp);
    saveInFile(*top);
    return;
}
void deleteExistContact(nodeptr *top) {
    system("color 09");
    system("cls");
    gotoxy(43,2);
    printf("*>____________ ©Phone Book® ____________<*");
    gotoxy(53,4);
    printf("*>> Delete Contact <<*");
    nodeptr temp = *top, toDeletePtr;
    int cnt = 1, choice, i = 0;
    char name[30];
    bool ok = false;
    gotoxy(2,8);
    printf(">> Enter The Name of Contact which you need to delete: ");
    fflush(stdin);
    scanf("%s",name);
   while(!isEmpty(temp)) {
         if (isSubstring(temp->info.fullName, name) && i == 0)toDeletePtr = temp, i++;
         else if (isSubstring(temp->info.fullName, name) && i == 1) {
         printf("[%d]-\n", 1);
         printf ("\tFull Name   :- %s\n", toDeletePtr->info.fullName);
         printf ("\tGender      :- %s\n", toDeletePtr->info.gender);
         printf ("\tE-Mail      :- %s\n", toDeletePtr->info.mail);
         printf ("\tAge         :- %s\n", toDeletePtr->info.age);
         printf ("\tCountry     :- %s\n", toDeletePtr->info.country);
         printf ("\tCity        :- %s\n", toDeletePtr->info.city);
         printf ("\tPhone Number:- %s\n", toDeletePtr->info.ph_num);
         puts("\n");
         ok = true;
  }
    if(isSubstring(temp->info.fullName, name) && ok) {
     printf("[%d]-\n", 1 + (i++));
     printf ("\tFull Name   :- %s\n", temp->info.fullName);
     printf ("\tGender      :- %s\n", temp->info.gender);
     printf ("\tE-Mail      :- %s\n", temp->info.mail);
     printf ("\tAge         :- %s\n", temp->info.age);
     printf ("\tCountry     :- %s\n", temp->info.country);
     printf ("\tCity        :- %s\n", temp->info.city);
     printf ("\tPhone Number:- %s\n", temp->info.ph_num);
     puts("\n");
  }
     temp = temp->next;
  }
    if (i == 0) {
        gotoxy(2,10);
        printf(">> Not Found << ");
        getch();
        system("cls");
        return;
  }
    else if (i != 1) {
        temp = *top;
        printf("\n>> Please, Choose one from the Following Contacts: ");
        scanf("%d", &choice);
      while(choice <=0 || choice > i){
           printf("\n>> Please Enter a Valid Choice:   ");
           scanf("%d", &choice);
  }
      while (1) {
        if (isSubstring(temp->info.fullName, name))
             if (cnt == choice) break;
             else cnt++;
        temp = temp->next;
}
}
    else temp = toDeletePtr;
    nodeptr top2 = NULL;
    while (*top != temp){
        push(&top2, (*top)->info);
        pop(top);
    }
    pop(top);
    while (top2 != NULL) {
        push(top, top2->info);
        pop(&top2);
    }
    saveInFile(*top);
    printf("\n\t\t\t\t\t>> The contact has been deleted completely <<");
    getch();
    system("cls");
    return;
}
void research(nodeptr top) {
    int j = 0;
    system("color 0d");
    system("cls");
    gotoxy(43,2);
    printf("*>____________ ©Phone Book® ____________<*");
    gotoxy(52,4);
    printf("*>> Research Contact <<*");
    char data[30];
    gotoxy(2,8);
    printf(">> Enter The Name or The Phone Number of Contact which you need to search: ");
    gotoxy(77,8);
    scanf("%s",data);
    puts("");
    bool ok = true;
    while (!isEmpty(top)) {
        if (isSubstring(top->info.fullName, data) || isSubstring(top->info.ph_num, data)) {
        j++;
        printf("\n\n\n[%d]-\n" ,j);
        printf ("\nFull Name    : %s\n", top->info.fullName);
        printf ("Gander       : %s\n", top->info.gender);
        printf ("E-Mail       : %s\n", top->info.mail);
        printf ("Age          : %u\n", top->info.age);
        printf ("Country      : %s\n", top->info.country);
        printf ("City         : %s\n", top->info.city);
        printf ("Phone number : %s\n", top->info.ph_num);
            ok = false;
        }
        top = top->next;
    }
    gotoxy(50,16);
    if (ok == true)printf(">> The Contact isn't exist <<");
    getch();
    system("cls");
    return;
}
void display(nodeptr top) {
    int z = 0;
    system("color 0a");
    system("cls");
    gotoxy(42,2);
    printf("*>____________ ©Phone Book® ____________<*");
    gotoxy(52,4);
    printf("*>> Display Contacts <<*");
    while(top != NULL) {
        z++;
        printf("\n\n\n[%d]-\n" ,z);
        printf ("\nFull Name    : %s\n", top->info.fullName);
        printf ("Gander       : %s\n", top->info.gender);
        printf ("E-Mail       : %s\n", top->info.mail);
        printf ("Age          : %u\n", top->info.age);
        printf ("Country      : %s\n", top->info.country);
        printf ("City         : %s\n", top->info.city);
        printf ("Phone number : %s\n", top->info.ph_num);
        top = top->next;
        puts("\n");
    }
    puts("");
    return;
}
void reset(nodeptr *top) {
    while(!isEmpty(*top))pop(top);
    saveInFile(*top);
    return;
}
bool isEmpty(nodeptr top) {
    return top == NULL;
}
bool isString(char input[]) {
    for (int i = 0; i < strlen(input); i++)
        if (!isdigit(input[i]))return true;
    return false;
}
bool isSubstring(char str1[], char str2[]) {
    for (int i = 0; str1[i] != NULL; i++)str1[i] = tolower(str1[i]);
    for (int i = 0; str2[i] != NULL; i++)str2[i] = tolower(str2[i]);
    char *ref = strstr(str1, str2);
    if (ref) return true;
    else return false;
}
bool exceed(char input[])
{
        if (atoi(input)>150)return true;
     return false;
}
bool zerobegin(char input[])
{
        if (input[0]=='0')return true;
     return false;
}
bool email_is_valid(char email[50]){
    if(!isalpha(email[0])) return 0; //checking if the first character is alpha or not
    /* variables (at) and (dot) is to determine
    the position of '@' and '.' in the string email. */
    int at = -5, dot = -5;
    for (int i = 0; i < strlen(email); ++i) { // searching for the position of '@' and '.'
        if(email[i] == '@') at = i;
        if(email[i] == '.') dot = i;
        if(email[i] == ' ') return 0;
    }
    if((dot - at) == 1 ) return 0;      //  check if there are  characters between'@' and '.'
    if(at == -5 || dot == -5) return 0; //  check if '@' and '.' are not exist
    if(at > dot) return 0;              //check if '@' after '.'
    return (dot != (strlen(email)) - 1); //check if dot at the end of string email
}
bool pass_valid(char a[])
{
int i,m=0,c=0,s=0,d=0,p=0,w=0,l=0;
for(i=0;i<strlen(a);i++)
{
if(strlen(a)<8) l++;
if(a[i]>='A'&&a[i]<='Z')c++;
if(a[i]>='a'&&a[i]<='z')s++;
if(a[i]>='0'&&a[i]<='9') d++;
if(a[i]=='#'||a[i]=='*'||a[i]=='^'||
a[i]=='$'||a[i]=='@'||a[i]=='%'||a[i]==')'
||a[i]=='(' ||a[i]=='=' ||a[i]=='!'||a[i]=='+'||
a[i]=='-'||a[i]=='_'||a[i]=='/'
||a[i]=='}'||a[i]=='\\'||a[i]=='{') p++;
if(a[i]==' ') w++;
}
if(l!=0)
{
printf("\n>>Password Must be at least eight characters.");
m=1;
}
if(c==0)
{
printf("\n>>Password Must contain at least oneUppercase character.");
m=1;
}



if(s==0)
{
printf("\n>>Password Must contain at least OneLowerCase character.");
m=1;
}
if(p==0)
{
printf("\n>>Password Must contain at least one SpecialCase Character.");
m=1;
}
if(w!=0)
{
printf("\n>>Password Mustn't contain White Spaces.");
m=1;
}
if(d==0)
{
printf("\n>>Password Must contain at least one digit.");
m=1;
}
puts("\n");
if(m==1){
return false;
}
else{
return true;
}
}
