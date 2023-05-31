#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <time.h>

char plazaName[100];
char date[20];
char collectorName[20];
char shiftID[20];
char vehicle_class[50];

int base_fare;
int shift_charge;
float vat;
int payable_amount;
int bike_count,cng_count,privateCar_count,microBus_count,miniBus_count,bus_count,truck_count;
int totalCollected;

void user_Login()
{
    char userID[20];
    char password[20];

    printf("Enter  your User ID: ");
    scanf("%s", userID);

    printf("Enter your Password: ");
    scanf("%s", password);

    if(strcmp(userID,"rakib")==0 && strcmp(password,"rakib")==0)
      {
        strcpy(collectorName,userID);
        printf("Login sucessfull.");
        clearConsole();
        display();
      }
    else if(strcmp(userID,"emon")==0 && strcmp(password,"emon")==0)
      {
        strcpy(collectorName,userID);
        printf("Login sucessfull.");
        clearConsole();
        display();
      }

    else if(strcmp(userID,"man")==0 && strcmp(password,"man")==0)
      {
        strcpy(collectorName,userID);
        printf("Login sucessfull.");
        clearConsole();
        display();
      }

    else
    {
      printf("Invalid UserId Or password!!\n");
      user_Login();
    }
}


void clearConsole()
{
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}


void dateTime()
{
    time_t currentTime = time(NULL);
    char currentDate[11];
    strftime(currentDate, sizeof(currentDate),"%d-%m-%Y", localtime(&currentTime));
    strcpy(date,currentDate);

    struct tm *localTime = localtime(&currentTime);
    int currentHour = localTime->tm_hour;

    if(currentHour >= 6 && currentHour < 14)
    {
        strcpy(shiftID,"Morning");
        shift_charge=7;
    }
    else if(currentHour >= 14 && currentHour < 22)
    {
        strcpy(shiftID,"Evening");
        shift_charge=7;
    }
    else
    {
        strcpy(shiftID,"Night");
        shift_charge=5;
    }
}


void display()
{
    dateTime();
    strcpy(plazaName,"     Podda Setu Toll Plaza");

    printf("%s\n", plazaName);
    printf("        Date:%s\n", date);
    printf("--------------------------------\n");
    printf("Collector Name: %s\n", collectorName);
    printf("Shift Id: %s\n", shiftID);
    printf("--------------------------------\n");

    vehicleList();
}


void vehicleList()
{
    printf("\nVehicle List          fare(BDT) \n");
    printf("1. Bike                 20 tk\n");
    printf("2. CNG Auto Rickshaw    40 tk\n");
    printf("3. Private Car          50 tk\n");
    printf("4. Micro Bus            60 tk\n");
    printf("5. Mini Bus             70 tk\n");
    printf("6. Bus                 120 tk\n");
    printf("7. Truck               150 tk\n");
    printf("--------------------------------\n");

    setVehicle();
}


void setVehicle()
{
   int choice;

   printf("Select a vehicle: ");
    scanf("%d",&choice);

    if(choice==1)
    {
        strcpy(vehicle_class,"Bike");
        base_fare=20;
        bike_count++;
        printf("Bike selected.\n");
    }
    else if(choice==2)
    {
        strcpy(vehicle_class,"CNG Auto Rickshaw");
        base_fare=40;
        cng_count++;
        printf("CNG Auto Rickshaw selected.\n");
    }
    else if(choice==3)
    {
        strcpy(vehicle_class,"Private Car");
        base_fare=50;
        privateCar_count++;
        printf("Private Car selected.\n");
    }
    else if(choice==4)
    {
        strcpy(vehicle_class,"Micro Bus");
        base_fare=60;
        microBus_count++;
        printf("Micro Bus selected.\n");
    }
    else if(choice==5)
    {
        strcpy(vehicle_class,"Mini Bus");
        base_fare=70;
        miniBus_count++;
        printf("Mini Bus selected.\n");
    }
    else if(choice==6)
    {
        strcpy(vehicle_class,"Bus");
        base_fare=120;
        bus_count++;
        printf("Bus selected.\n");
    }
    else if(choice==7)
    {
        strcpy(vehicle_class,"Truck");
        base_fare=150;
        truck_count++;
        printf("Truck selected.\n");
    }
    else
    {
        printf("\nInvalid Vehicle!!\n");
        setVehicle();
    }
    printToken();
}


void printToken()
{
    printf("\nPress 'P' to print token: ");
    char print;
    scanf("%s", &print);

     if(print=='P'||print=='p')
     {
         clearConsole();
         calculateToll();
         Token();
     }
     else
        printToken();
}


void calculateToll()
{
    vat = base_fare*(0.05);
    payable_amount= round(base_fare+shift_charge+vat);

    totalCollected = totalCollected+payable_amount;
}


void Token()
{
    printf("\n-------------Token-------------\n");
    printf("-------------------------------\n");
    printf("\n%s\n", plazaName);
    printf("        Date:%s\n", date);
    printf("--------------------------------\n");
    printf("  Collector Name: %s\n", collectorName);
    printf("  Shift ID: %s\n", shiftID);
    printf("  Vehicle Class: %s\n", vehicle_class);
    printf("  Fare: \n");
    printf("      Base fare   :  %i tk\n", base_fare);
    printf("      Shift charge:   %i tk\n", shift_charge);
    printf("      Vat (5%%)    : %.1f tk\n", vat);
    printf("--------------------------------\n");
    printf("  Payable (round) : %i Taka\n", payable_amount);
    printf("  Thank you, have a nice trip.\n");

    tollContinue();
}


void tollContinue()
{
    printf("\nContinue[Y/N]: ");
    char con;
    scanf("%s", &con);

    if(con=='Y'||con=='y')
         {
             clearConsole();
             display();
         }
    else if(con=='N'||con=='n')
        logout();
    else
        tollContinue();
}


void logout()
{
    printf("\nPress 'L' to LogOut: ");
    char press;
    scanf("%s", &press);

    if(press=='L'||press=='l')
    {
        clearConsole();
        summeryReport();
    }

    else
        logout();
}


void summeryReport()
{
    printf("\n--------------Summery Report-------------\n");
    printf("------------------------------------------\n");
    printf("\n%s\n", plazaName);
    printf("        Date:%s\n", date);
    printf("--------------------------------\n");
    printf("  Collector Name: %s\n", collectorName);
    printf("  Shift ID: %s\n", shiftID);
    printf("  Summery: \n");
    printf("       Bike                 : %i\n",bike_count);
    printf("       CNG Auto Rickshaw    : %i\n",cng_count);
    printf("       Private Car          : %i\n",privateCar_count);
    printf("       Micro Bus            : %i\n",microBus_count);
    printf("       Mini Bus             : %i\n",miniBus_count);
    printf("       Bus                  : %i\n",bus_count);
    printf("       Truck                : %i\n",truck_count);
    printf("--------------------------------\n");
    printf("Total Collected amount: %i Taka\n",totalCollected);
}


int main() {

    user_Login();
    return 0;
}

