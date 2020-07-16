#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFSIZE 600


/* typedef struct{
    char eventType[50];
    int amount;
}event; */

struct Node {
    char eventType[200];
    int data;
    struct Node *next;
};

/* Function to insert a node at the beginning of a linked list */
void insert(struct Node **head, int data, char *event); 
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start); 

/*function to free list*/
void freeList(struct Node *listItem);

int main() {
    int fatalities = 0;
    int injured = 0;
    int evacuated = 0;
    int utilities = 0;
    char *eventTypes[21] = {"Flood", "Drought", "Heat Event", "Cold Event", "Storm Surge", "Storms and Severe Thunderstorms", "Storm - Unspecified / Other", "Winter Storm", "Geomagnetic Storm", "Hurricane / Typhoon / Tropical Storm", "Tornado", "Tsunami", "Avalanche", "Landslide", "Earthquake", "Volcano", "Wildfire", "Epidemic", "Pandemic" , "Infestation", "\0"};
    int fatalArray[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int evacArray[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int numberOfTimes[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float quackTude = 0;

    FILE *fr;
    // Open the file for reading only
    fr = fopen("CDD2.bin", "r");
    if (!fr ){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    //readin the first unsigned short int
    unsigned short int numberOfOccurances;
    fread(&numberOfOccurances, sizeof(unsigned short int), 1, fr);
    printf("Number of occurances: %u\n", numberOfOccurances );

    for(int i = 0; i < numberOfOccurances; i++){
        char category;
        fread(&category , sizeof(char), 1, fr );
        //printf("category: %c\n", category);

        char type;
        fread(&type , sizeof(char), 1, fr );
        int index = (int)(type);
        index--;
        //printf("%d\n", index);
        numberOfTimes[index] = numberOfTimes[index] +1;

        //printf("type: %u\n", type);
        //printf("type in int: %d\n", index);

        //read fatalities
        int fatal = 0;
        fread(&fatal , sizeof(int), 1, fr );
        fatalities += fatal;
        fatalArray[index] += fatal;
        //printf("fatalities: %d\n", fatal);

        //read injured
        int injd = 0;
        fread(&injd , sizeof(int), 1, fr );
        injured += injd;
        //printf("injured: %d\n", injd);

        //read evacuated
        int evac= 0;
        fread(&evac , sizeof(int), 1, fr );
        evacuated += evac;
        evacArray[index] += evac;
        //printf("evacuated: %d\n", evac);

        //read utilities
        int util;
        fread(&util , sizeof(int), 1, fr );
        //printf("%d ", util);
        utilities += util;
        //printf("Utilities: %d\n", util);

        //read earthQuake magnitude
        if(index == 14){
            float magntd= 0;;
            fread(&magntd , sizeof(float), 1, fr );
            if(magntd > quackTude){
                quackTude = magntd;
            }
            //printf("Magnitude: %f\n\n", magntd);
        }
    }

    //printing fatalities, injured, evacuated, utilities
    printf("Total Fatalities: %d\n\n", fatalities);
    printf("Total Injured: %d\n\n", injured);
    printf("Total Evacuated: %d\n\n", evacuated);
    printf("Total  utilities/affected: %d\n\n", utilities);
    int maximum = 0;
    int index;
    for(int i = 0; i<20; i++){
        if(fatalArray[i]>maximum){
            maximum = fatalArray[i];
            index = i;
        }
    }
    printf("Max fatality is %d for Type: %s\n\n", maximum, eventTypes[index]);
    
    int max = 0;
    int ind;
    for(int i = 0; i<20; i++){
        if(evacArray[i]>max){
            max = evacArray[i];
            ind = i;
        }
    }
    printf("Max evacuation is %d for Type: %s\n\n", max, eventTypes[ind]);
    printf("Max earthquake magnitude: %0.2f\n\n", quackTude);


    /*for(int i =0; i< 20; i++){
        printf("%d) Event Type: %s\n", i, *(eventTypes+i));
        printf("Number of Times: %d\n\n", numberOfTimes[i]);
    }*/

    struct Node *head = NULL;


    printf("A list (sorted from highest to lowest) showing the 20 types of disasters and how many times each type occurred: \n");
    for (int i = 0; i < 20; i++){
        insert(&head, numberOfTimes[i], *(eventTypes+i));
    }

    printList(head);

    printf("\n");

    freeList(head);

    fclose(fr);
}


/* Function to insert a node in descendeing order */
void insert(struct Node **head, int data, char *event) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node)); 
    strcpy((newNode->eventType), event);
    newNode->data = data; 
    if(*head == NULL){ 
        *head = newNode;
        return;
    }
    else{
        if((*head)->data < newNode->data){
            newNode->next = *head;
            *head = newNode;
            return;
        }
        else{
            struct Node *current = *head;
            while(1){
                if(current->next == NULL){
                    current->next = newNode;
                    break;
                }
                else if(current->next->data < newNode->data){
                    struct Node *temp = current->next;
                    current->next = newNode;
                    newNode->next = temp;
                    break;
                }
                else{
                    current = current->next;
                }
            }
        }
    }
} 
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start) 
{ 
    struct Node *temp = start;
    int count = 0;
    while (temp!=NULL) {
        if (count == 0){
            printf("{%s -> ", temp->eventType);
            count = 1;
        }
        else{
            printf("%s -> ", temp->eventType);
        }
        if(temp->next != NULL){ 
            if(temp->data == 1 || temp->data == 0){
                printf("%d time, ", temp->data);
            }
            else{
                printf("%d times, ", temp->data);
            }
        }
        else{
            if(temp->data == 1 || temp->data == 0){
                printf("%d time}, ", temp->data);
            }
            else{
                printf("%d times}, ", temp->data);
            }
        }
        temp = temp->next; 
    } 
}


/*function to free list(from textbook)*/
void freeList(struct Node *listItem) {
    struct Node *nextItem;

    while(listItem != NULL) {
        nextItem = listItem->next;
        free(listItem);
        listItem = nextItem;
    }
}

