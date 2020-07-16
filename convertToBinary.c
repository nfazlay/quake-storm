#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFSIZE 600

int main() {
    unsigned short int numberOfNaturalDisasters;
    char *eventTypes[21] = {"Flood", "Drought", "Heat Event", "Cold Event", "Storm Surge", "Storms and Severe Thunderstorms", "Storm - Unspecified / Other", "Winter Storm", "Geomagnetic Storm", "Hurricane / Typhoon / Tropical Storm", "Tornado", "Tsunami", "Avalanche", "Landslide", "Earthquake", "Volcano", "Wildfire", "Epidemic", "Pandemic" , "Infestation", "\n"};



    FILE *fz;
    // Open the file for reading only
    fz = fopen("CDD2.csv", "r");
    if (!fz ){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    FILE *fw;
    // Open a new file for writing only
    fw = fopen("CDD2.bin", "w");
    if (!fw) {
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    int check = 1;
    unsigned short int check2 = 0;

    char sbuffer[BUFFSIZE];
    fscanf(fz, "%[^\n]s", sbuffer);
    //printf("%s\n", sbuffer);
    fgetc(fz);

    while(!feof(fz)){
        check++;
        //getting category//
        char ccategory[200] = "";
        fscanf(fz, "%[^,]s", ccategory);
        //printf("Category: %s\n", ccategory);
        fgetc(fz);
        char ggroup[200] = "";
        fscanf(fz, "%[^,]s", ggroup);
        //printf("Group: %s\n", ggroup);
        fgetc(fz);
        if((strcmp(ccategory, "Disaster") == 0 ) && (strcmp(ggroup, "Natural") == 0 )){
            //printf("something");
            check2++;
        }
       else {
            fscanf(fz, "%[^\n]s", sbuffer);
            fgetc(fz);
        }
    }
    fwrite(&check2, sizeof(unsigned short int), 1, fw);

    fclose(fz);

    FILE *fr;
    // Open the file for reading only
    fr = fopen("CDD2.csv", "r");
    if (!fr) {
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    

    char buffer[BUFFSIZE];
    fscanf(fr, "%[^\n]s", buffer);
    //printf("%s\n", buffer);
    fgetc(fr);

    while(!feof(fr)){
        //getting category//
        char category[200] = "";
        fscanf(fr, "%[^,]s", category);
        //printf("Category: %s\n", category);
        fgetc(fr);
        char group[200] = "";
        fscanf(fr, "%[^,]s", group);
        //printf("Group: %s\n", group);
        fgetc(fr);
        if((strcmp(category, "Disaster") == 0 ) && (strcmp(group, "Natural") == 0 )){
            //printf("something");
            //getting subgroup//
            char subgroup[200] = "";
            fscanf(fr, "%[^,]s", subgroup); 
            fgetc(fr);        
            //printf("Subgroup: %s\n", subgroup);
            fwrite(subgroup, sizeof(char), 1, fw);
            //getting type//
            char type[80] = "";
            fscanf(fr, "%[^,]s", type); 
            fgetc(fr);
            //printf("Type: %s", type);
            int typeIndex = 0;
            for (typeIndex = 0; typeIndex < 20; typeIndex++){
                if (strcmp(type,*(eventTypes+typeIndex)) == 0){
                    //printf("%s", eventTypes+typeIndex);
                    break;
                }
            } 
            typeIndex++;
            char typeItem = (char)typeIndex;
            //printf(" %u\n", typeItem);
            fwrite(&typeItem, sizeof(char), 1, fw);

            //IGNORING place//
            char place[300] = "";
            fscanf(fr, "%[^,]s", place); 
            fgetc(fr);

            //IGNORING start date//
            char startdate[200] = "";
            fscanf(fr, "%[^,]s", startdate); 
            fgetc(fr);

            //getting fatalities, injured, evacuated//
            //printf("%d\n", check);
            char fatalities[200] = "";
            fscanf(fr, "%[^,]s", fatalities); 
            fgetc(fr);

            int fatal;
            fatal = atoi(fatalities);
            fwrite(&fatal, sizeof(int), 1, fw);
            //printf("fatalities: %d\n", fatal);

            //grtting injured
            char injured[200] = "";
            fscanf(fr, "%[^,]s", injured); 
            fgetc(fr);
            int inj;
            inj = atoi(injured);
            fwrite(&inj, sizeof(int), 1, fw);
            //printf("injured: %d\n", inj);

            //getting evacuated
            char evacuated[200] = "";
            fscanf(fr, "%[^,]s", evacuated); 
            fgetc(fr);
            int evac;
            evac = atoi(evacuated);
            fwrite(&evac, sizeof(int), 1, fw);
            //printf("evacuated: %d\n", evac);


            //ignoring next 10//
            for (int i = 0; i < 10; i++){
                char ignored0[200] = "";
                fscanf(fr, "%[^,]s", ignored0);
                fgetc(fr);
            }


            //getting utility-people affected//
            char utility[400] = "";
            fscanf(fr, "%[^,]s", utility); 
            fgetc(fr);
            //printf("Utility-people affected: %s\n", utility);
            int util;
            util = atoi(utility);
            fwrite(&util, sizeof(int), 1, fw);

            //getting magnitude//
            char magnitude[80]= "";
            fscanf(fr, "%[^\n]s", magnitude); 
            fgetc(fr);
            float magntd = atof(magnitude);
            if(typeIndex == 15){
                fwrite(&magntd, sizeof(float), 1, fw);
            }
            

            //printf("ending\n\n");
        }
        else {
            fscanf(fr, "%[^\n]s", buffer);
            fgetc(fr);
        }
        //fgetc(fr);
    }
    //close read file//
    fclose(fr);

    //close write file//
    fclose(fw);


    return(0);



}
 
