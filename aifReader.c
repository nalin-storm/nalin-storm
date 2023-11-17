//
//  main.c
//  AIFF File Reader
//
//  Created by Nalin Storm on 1/25/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "aifReader.h"


int main(int argc, const char * argv[])
{
    //Edit file path if you want to test different aif file.

    char *file_path = "C:/Users/nalin/OneDrive - Northeastern University/Documents/Northeastern/Digital Signal Processing/StormNalinProject1b/clarine.aif";
    FILE *filePtr = fopen(file_path,"r");
    FILE *file_ptr = filePtr;
    int result = 0;

    if(file_ptr == NULL)
    {
        printf("error opening file %s\n", file_path);
        result = -1;
    }
    else
    {
        // Define variables that we'll be reusing throughout the function.
        //
        int chunkSize = 0;              // AIFF Spec defines this as long 32-bit. Nowadays, int is 32-bit
        char chunkID[5];                // Four bytes/chars used to identify the chunk
        unsigned char sizeBuffer[4];    // This will be used to hold 32-bit values, one byte at a time. Doing
        // this because we need to swap the bytes. They are big endian in aiff.
        unsigned int numSampleFrames = 0;

        // INSPECT FILE TO ENSURE THAT IT IS AIFF.
        //
        chunkID[0] = (char)fgetc(file_ptr);
        chunkID[1] = (char)fgetc(file_ptr);
        chunkID[2] = (char)fgetc(file_ptr);
        chunkID[3] = (char)fgetc(file_ptr);
        chunkID[4] = '\0';
        if(0 == strcmp(chunkID, "FORM") )
        {
            printf("---------------- FORM Chunk ----------------\n");
            sizeBuffer[0] = fgetc(file_ptr);
            sizeBuffer[1] = fgetc(file_ptr);
            sizeBuffer[2] = fgetc(file_ptr);
            sizeBuffer[3] = fgetc(file_ptr);
            chunkSize = swap4Bytes(sizeBuffer);
            printf("chunkSize = %d\n", chunkSize);

            char formType[5];
            formType[0] = (char)fgetc(file_ptr);
            formType[1] = (char)fgetc(file_ptr);
            formType[2] = (char)fgetc(file_ptr);
            formType[3] = (char)fgetc(file_ptr);
            formType[4] = '\0';
            printf("Form Type: %c%c%c%c\n", formType[0], formType[1], formType[2], formType[3]);
            if(0 != strcmp(formType, "AIFF") && 0 != strcmp(formType, "AIFC"))
            {
                printf("error: file is not .aif.\n");
                exit(0);
            }
            else
            {
                char nextc = (char)fgetc(file_ptr);

                while(nextc != EOF){
                    chunkID[0] = nextc;
                    chunkID[1] = (char)fgetc(file_ptr);
                    chunkID[2] = (char)fgetc(file_ptr);
                    chunkID[3] = (char)fgetc(file_ptr);
                    chunkID[4] = '\0';
                    if(0 == strcmp(chunkID, "COMM") ) {
                        printf("---------------- COMM Chunk ----------------\n");

                        //No (char) character cast because we want Bytes here, not characters
                        sizeBuffer[0] = fgetc(file_ptr);
                        sizeBuffer[1] = fgetc(file_ptr);
                        sizeBuffer[2] = fgetc(file_ptr);
                        sizeBuffer[3] = fgetc(file_ptr);
                        chunkSize = swap4Bytes(sizeBuffer);
                        printf("COMM chunkSize = %d\n", chunkSize);

                        unsigned char nChannelsBytes[2];
                        nChannelsBytes[0] = fgetc(file_ptr);
                        nChannelsBytes[1] = fgetc(file_ptr);
                        short numChannels = swap2Bytes(nChannelsBytes);
                        printf("Number of Channels = %d\n", numChannels);

                        unsigned char nFramesBytes[4];
                        nFramesBytes[0] = fgetc(file_ptr);
                        nFramesBytes[1] = fgetc(file_ptr);
                        nFramesBytes[2] = fgetc(file_ptr);
                        nFramesBytes[3] = fgetc(file_ptr);
                        numSampleFrames = swap4Bytes(nFramesBytes);
                        printf("Number of Sampled Frames = %d\n", numSampleFrames);

                        unsigned char bitDepthBytes[2];
                        bitDepthBytes[0] = fgetc(file_ptr);
                        bitDepthBytes[1] = fgetc(file_ptr);
                        short bitDepth = swap2Bytes(bitDepthBytes);
                        printf("bitDepth = %d\n", bitDepth);

                        unsigned char sampleRate[10];
                        sampleRate[0] = fgetc(file_ptr);
                        sampleRate[1] = fgetc(file_ptr);
                        sampleRate[2] = fgetc(file_ptr);
                        sampleRate[3] = fgetc(file_ptr);
                        sampleRate[4] = fgetc(file_ptr);
                        sampleRate[5] = fgetc(file_ptr);
                        sampleRate[6] = fgetc(file_ptr);
                        sampleRate[7] = fgetc(file_ptr);
                        sampleRate[8] = fgetc(file_ptr);
                        sampleRate[9] = fgetc(file_ptr);
                        int convsampleRate = convertFromIeeeExtended(sampleRate);
                        printf("Sample Rate = %d\n",convsampleRate);

                    }
                    else{
                        //If the chunkID does not equal COMM, continue to the next chunk
                        nextc = (char)fgetc(file_ptr);
                    }

                }
            }
        }
    }

    return 0;
}
