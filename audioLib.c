//
//  audioLib.c
//
//  Created by Mike Frengel on 1/22/21.
//  Edited by Nalin Storm on 1/23/23

#include "audioLib.h"
#include "math.h"
#include <stdio.h>



//...................................................................................................... ampTodB
float ampTodB(float amp, int bitDepth, int *error)
{
    int maxamp=0;
    // While loop sets the maximum amplitude based on the bit depth
    while (1){
        if (bitDepth==8){
            maxamp+=MAX_8BIT;
            break;
        }
        else if (bitDepth==16){
            maxamp+=MAX_16BIT;
            break;
        }
        else if (bitDepth==24){
            maxamp+=MAX_24BIT;
            break;
        }
        else if (bitDepth==32){
            maxamp+=MAX_32BIT;
            break;
        }
        else {
            printf("\nBit Depth Invalid, please try another value:");
            scanf("%d",&bitDepth);
        }
    }

    //Formula for converting amplitude to dB. Returns the answer under "*error".
    float answer = 20 * log10f(amp / maxamp);
    *error = round(answer);
    return (*error);
}
//...................................................................................................... dBToAmp
float dBToAmp(float dB, int bitDepth, int *error)
{
    int maxamp = 0;
    // While loop sets the maximum amplitude based on the bit depth
    while (1){
        if (bitDepth==8){
            maxamp+=MAX_8BIT;
            break;
        }
        else if (bitDepth==16){
            maxamp+=MAX_16BIT;
            break;
        }
        else if (bitDepth==24){
            maxamp+=MAX_24BIT;
            break;
        }
        else if (bitDepth==32){
            maxamp+=MAX_32BIT;
            break;
        }
        else {
            printf("\n\nBit Depth Invalid, please try another value:");
            scanf("%d",&bitDepth);
        }
    }

    //Formula for converting dB to amplitude. Reutnrs the answer under "*error".
    float answer = (maxamp*powf(10, (dB / 20)));
    *error = round(answer);
    return (*error);
}

int main() {

    int choice = 0;
    //Infinite while loop that exits when User decides to end the program.
    while (1){
        //Following lines show the main menu.Add choice numbers for future functions.
        if (choice ==0){
            printf("\n\nHello, Welcome to Nalin's Audio Library\n"
                   "Please type a program number then hit enter:\n\n"
                   "1: Amplitude to dB Converter\n2: dB to Amplitude Converter\n"
                   "3: Exit Nalin's Audio Library\nSelection:");
            scanf("%d",&choice);
        }

        if (choice == 1){
            int bitDepth;
            int amp;
            int dB;
            printf("\nAmplitude to dB Converter\n"
                   "Please type bit depth value (8, 16, 24, 32):");
            scanf("%d",&bitDepth);
            printf("Please type Amplitude value:");
            scanf("%d",&amp);

            ampTodB(amp, bitDepth, &dB);
            printf("New value in dB: %d", dB);
            //Choice 0 represents the main menu.
            choice = 0;
        }

        else if (choice == 2){
            int bitDepth;
            int amp;
            int dB;
            printf("\ndB to Amplitude Converter\n"
                   "Please type bit depth value (8, 16, 24, 32):");
            scanf("%d",&bitDepth);
            printf("Please type dB value:");
            scanf("%d",&dB);

            dBToAmp(dB, bitDepth, &amp);
            printf("Converted Amplitude Value: %d", amp);
            choice =0;
        }

        else if (choice == 3){
            printf("\n\nThank you for using my program, Goodbye!\n");
            break;
        }

        else {
            while(1){
                printf("Selection invalid, please try again:");
                scanf("%d",&choice);
                //Add choice for future functions.
                if (choice == 1 || choice == 2 || choice == 3){
                    break;
                }
            }
        }
    }
}