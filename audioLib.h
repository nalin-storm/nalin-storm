//
//  audioLib.h
//  VERSION: 1.0
//
//  Created by Mike Frengel on 1/22/21.
//
//  A library of C utility functions useful when working with audio.
//
//.........................................................................................................


#ifndef audioLib_h
#define audioLib_h

#include <stdio.h>
#include <math.h>

#endif /* audioLib_h */

#define     MAX_8BIT        127
#define     MAX_16BIT       32767
#define     MAX_24BIT       8388607
#define     MAX_32BIT       2147483647

#define     DSP_SUCCESS                        0
#define     DSP_NULL_POINTER                1000
#define     DSP_INVALID_PARAMETER           1001
#define     DSP_ERR_UNKNOWN_BITDEPTH        1002
#define     DSP_ERR_DBRANGE                 1003
#define     DSP_ERR_AMPRANGE                1004
#define     DSP_ERR_AMPINF                  1005
#define     DSP_ERR_UNDEFINED               1006


//.................................  FUNCTION DECLARATIONS  ...............................................

//.........................................................................................................
// FUNCTION:    ampTodB(float amp, int bitDepth, int *error);
// DESCRIPTION: Converts a linear amplitude value to the corresponding decibel in the defined
//              bit depth. 0 dB is considered max amp and decibels are measured as negative from 0.
// PARAMS:
// - amp        a signed value within the range of the specified bit depth
// - bitDepth   valid bit depths: 0, 8, 16, 24, 32. 0 signifies use of -1.0 to 1.0 (canonical format)
// - *error     pointer to an int, used to return error codes.
//
// RETURNS:     a valid decibel result or 0 on error. NOTE: 0 is also a valid result, so error code
//              must be checked.
//
float ampTodB(float amp, int bitDepth, int *error);

//.........................................................................................................
//
//  add function documentation here...
//
float dBToAmp(float dB, int bitDepth, int *error);
