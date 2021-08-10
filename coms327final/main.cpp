#include "candy.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {

    //Opens a the file to read
    FILE * f;
    f = fopen(argv[1], "r");

    //Creates a vector to store all of the candies
    vector<candy *> candyV;

    /**
     * This while loop goes through and reads the file.
     * It looks for the start line and then take in all of the input in the order it should be in
     */
    while(!feof(f)) {
        char start[50];
        fgets(start, sizeof(start), f);
        strtok(start, "\n");

        //This will keep iterating through until it sees the keyword of START then starts taking the inputs it needs
        //for each type of candy
        if (strcmp(start, "START") == 0) {
            //Gets the name of of the candy from the file
            char name[50];
            fgets(name, sizeof(name), f);
            strtok(name, "\n");

            //Gets the candy type of of the candy from the file
            char candytype[50];
            fgets(candytype, sizeof(candytype), f);
            strtok(candytype, "\n");

            //Error for if the candy type isn't valid
            if (strcmp(candytype, "chocolate") != 0 && strcmp(candytype, "caramel") != 0 && strcmp(candytype, "jelly") != 0
                    && strcmp(candytype, "hard") != 0) {
                printf("%s does not have a valid candy type. The candy type of %s is %s\n", name, name, candytype);
                return 1;
            }

            //Gets the price type of of the candy from the file
            char pricetype[50];
            fgets(pricetype, sizeof(pricetype), f);
            strtok(pricetype, "\n");

            //Error for if the price type isn't valid
            if (strcmp(pricetype, "piece") != 0 && strcmp(pricetype, "pound") != 0) {
                printf("%s does not have a valid price type. The candy type of %s is %s\n", name, name, pricetype);
                return 1;
            }

            //Gets the price of of the candy from the file
            char price[50];
            fgets(price, sizeof(price), f);
            strtok(price, "\n");

            //Gets the color of of the candy from the file
            char color[50];
            fgets(color, sizeof(color), f);
            strtok(color, "\n");

            //Handles errors for when the color is out of bounds
            if (atoi(color) > 9 || atoi(color) < 0) {
                printf("%s is out of the bounds 0 though 9\n", name);
                return 1;
            }

            //Handles errors for the colors based on their types
            //Chocolate and caramel can be any color between 0 and 9
            //If is it jelly, then the color should be greater than 0 so if it is 0 then throw an error
            //If it is hard, then the color should be greater than 0 so if it is 0 then throw an error
            if (strcmp(candytype, "jelly") == 0 && atoi(color) == 0) {
                printf("%s does not have a valid color\n", name);
                return 1;
            } else if (strcmp(candytype, "hard") == 0 && atoi(color) == 0) {
                printf("%s does not have a valid color\n", name);
                return 1;
            }

            //Gets the amount of of the candy from the file
            char amount[50];
            fgets(amount, sizeof(amount), f);
            strtok(amount, "\n");

            //Gets the calories of of the candy from the file
            char calories[50];
            fgets(calories, sizeof(calories), f);
            strtok(calories, "\n");

            //If statement for both types of candy
            if (strcmp(pricetype, "piece") == 0) {
                //Creates the candy and it is a piece type
                candy * c = new piece(name, candytype, atof(price), atoi(color), atof(amount), atof(calories));

                //Throws an error for items with a matching name. This is because they should be the same item and only
                //input once (occuring on the input file once)
                for(int i = 0; i < candyV.size(); i++) {
                    if (c->getName() == candyV.at(i)->getName()) {
                        printf("There are two items with the same name of %s\n", name);
                        printf("They should be separate items with different name. \n");
                        printf("If they are the same item, they should only be on the list once. \n");
                        return 1;
                    }
                }

                //Adds this candy to the candyV vector
                candyV.push_back(c);
            } else if (strcmp(pricetype, "pound") == 0) {
                //Creates a candy and it is the pound type
                candy * c = new pound(name, candytype, atof(price), atoi(color), atof(amount), atof(calories));

                //Throws an error for items with a matching name. This is because they should be the same item and only
                //counted once (occuring on the input file once)
                for(int i = 0; i < candyV.size(); i++) {
                    if (c->getName() == candyV.at(i)->getName()) {
                        printf("There are two items with the same name of %s\n", name);
                        printf("They should be separate items with different name. \n");
                        printf("If they are the same item, they should only be on the list once. \n");
                        return 1;
                    }
                }

                //Adds this candy to the candyV vector
                candyV.push_back(c);
            }
        }
    }

    //Creates an array of candy that will be sorted in the end
    //The lower on the sorted array, the higher the price of that candy
    candy * cSorted[candyV.size()];

    //This is an array of ints that tell us if the item has already been added to the sorted list
    int * canUse = new int[candyV.size()];

    //Sets all items in the canUse array to 0. When the item can be added it is a 0
    //and when it has been added it becomes a 1
    for (int i = 0; i < candyV.size(); i++) {
        canUse[i] = 0;
    }

    //For loop that goes through all the candy and finds the largest price that hasn't been added to cSorted
    //and then adds the candy of the next largest price
    for (int i = 0; i < candyV.size(); i++) {
        float largest = 0;
        int largestIndex = 0;
        for (int j = 0; j < candyV.size(); j++) {
            if (canUse[j] == 0 && candyV.at(j)->totalPrice() > largest) {
                largest = candyV.at(j)->totalPrice();
                largestIndex = j;
            }
        }

        //Adds that candy to cSorted and sets its use to 1 so it won't be used again
        cSorted[i] = candyV.at(largestIndex);
        canUse[largestIndex] = 1;
    }

    //Prints out the info of all the candies sorted by price
    for (int i = 0; i < candyV.size(); i++) {
        cSorted[i]->getInfo();
    }

    //Creates a total variable and then adds all the totals to that variable
    float total = 0;
    for (int i = 0; i < candyV.size(); i++) {
        total += candyV.at(i)->totalPrice();
    }

    //A spacer line and then a line that prints out the total of all the candy in the store
    printf("\n");
    printf("The total of all the candy in all the store is: $%.2f\n", total);

    //Creates all the ints of the types that are possible of the candies.
    int jellys = 0;
    int caramels = 0;
    int chocolates = 0;
    int hards = 0;

    //Goes through and adds 1 to each type depending on the type of candy of each
    for (int i = 0; i < candyV.size(); i++) {
        if (candyV.at(i)->getCandyType() == "jelly") {
            jellys += 1;
        } else if (candyV.at(i)->getCandyType() == "caramel") {
            caramels += 1;
        } else if (candyV.at(i)->getCandyType() == "chocolate") {
            chocolates += 1;
        } else if (candyV.at(i)->getCandyType() == "hard") {
            hards += 1;
        }
    }

    //Break line and then outputs the number of jelly, caramel, chocolate and hard candies
    printf("\n");
    if (jellys == 1) {
        printf("There is %d jelly candy\n", jellys);
    } else {
        printf("There are %d jelly candies\n", jellys);
    }
    if (caramels == 1) {
        printf("There is %d caramel candy\n", caramels);
    } else {
        printf("There are %d caramel candies\n", caramels);
    }
    if (chocolates == 1) {
        printf("There is %d chocolate candy\n", chocolates);
    } else {
        printf("There are %d chocolate candies\n", chocolates);
    }
    if (hards == 1) {
        printf("There is %d hard candy\n", hards);
    } else {
        printf("There are %d hard candies\n", hards);
    }

    return 0;
}
