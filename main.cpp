#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class subscription{
    public:
    float processingFee;
    float serviceFee;
    int numOfServices;
    int numOfPremChannels;
    float premChannelsFee;
    char customer_type;
    int maxServicesWithNoAddCost;
    float additionalCost;

    subscription(float pFee, float sFee, int numOfS, int pChannels, float pChannelsFee, char cType, float addCost, int maxNoCost){
        processingFee = pFee;
        serviceFee = sFee;
        numOfServices = numOfS;
        numOfPremChannels = pChannels;
        premChannelsFee = pChannelsFee;
        customer_type = cType;
        additionalCost = addCost;
        maxServicesWithNoAddCost = maxNoCost;
    }

    float getCost(){
        float amountDue = 0;
        amountDue += processingFee + premChannelsFee * numOfPremChannels;
        if(numOfServices > maxServicesWithNoAddCost){
            int numOfExtraServices = numOfServices - maxServicesWithNoAddCost;
            amountDue += maxServicesWithNoAddCost * serviceFee + numOfExtraServices * additionalCost;
        } else{
            amountDue += numOfServices * serviceFee;
        }
        return amountDue;
    }
};

char* readLine(char* buffer, int bufferSize){
    printf(">");
    return fgets(buffer, bufferSize-1, stdin);
}

int main(){
    cout<<("You should adder the customers in the following form:\n");
    cout<<("PIN PASSWORD NUM_OF_PREMCHANELS CUSTOMER_TYPE NUM_OF_BASIC_SERVICES\n\n");
    cout<<("For customer type use the letter B for buisness customer, else H for home customers.\n");
    cout<<("For home customers you do not need to add NUM_OF_BASIC_SERVICES, as they only get one phone line by default.\n\n");
    cout<<("Here is an input example:\n");
    cout<<("34 my_pass123 3 B 2\n\n");
    cout<<("You can start entering customers and their plan cost will be returned.\n");
    cout<<("Type exit to stop the program:");
    cout<<(">");

    char* d = " \n\t\r";
    char line[500]; // I expect the user wont write more than 500 characters
    int lineSize = 500;

    while(readLine(line, lineSize)){
        int customerPin, premChannels, basicServices;
        char* customerPass, *customerType;
        
        if(line == NULL) break;

        char* token = strtok(line, d);
        if(strcmp(token, "exit")) break;

        customerPin = atoi(token);
        customerPass = strtok(NULL, d);
        premChannels = atoi(strtok(NULL, d));
        customerType = strtok(NULL, d);

        if(strcmp(customerType, "B") == 0){
            basicServices = atoi(strtok(NULL, d));
        } else{
            basicServices = 1;
        }

        float pFee, sFee, pChannelsFee, addCost;
        int maxNoCost;
        char cType;
        if(strcmp(customerType, "B") == 0){
            cType = 'B';
            pFee = 15; sFee = 75; pChannelsFee = 50;
            addCost = sFee + 5; maxNoCost = 10;
        } else{
            cType = 'R';
            pFee = 4.5; sFee = 20.5; pChannelsFee = 7.5;
            addCost = pFee;
            maxNoCost = 0; // doesn't matter
        }
    
        subscription newSubscription(pFee, sFee, basicServices, premChannels, pChannelsFee, cType, addCost, maxNoCost);
        cout<<("amountDue = %f\n", newSubscription.getCost());
    }

    cout<<"\nNext, I want you to input 5 grades. Avarage grade will be calculated. Then all grades bellow avarage will be printed.\n";

    return 0;
}