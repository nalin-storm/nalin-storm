/*
  ==================================================================================================================

    dsp.h
    Created: 21 Sep 2020 9:47:23am
    Author:  Nalin Storms

    DESCRIPTION: A C .h file that includes both function declarations and implementations used in
                 the Digital Signal Processing and Analysis course offered at Northeastern
                 University.
 
                 Students must put all of their code for projects in this file. The code must use
                 only ANSI-C and have no dependencies. Students will be submitting this file
                 for each project deliverable, adding to it as the course progresses.

  ==================================================================================================================
*/

#pragma once

#include "AnalysisDisplay.h"
#include "Spectrogram.h"
#include "time.h"
//#include <debugapi.h>
#include <windows.h>
#include <complex.h>

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
#define     DSP_ERR_UNKNOWN_SAMPLERATE      1007
#define     FADE_TYPE_LINEAR                  10 
#define     FADE_TYPE_EQUALPOWER              11 
#define     FADE_TYPE_SSHAPE                  12
#define     DSP_FILTERTYPE_LPF                13
#define     DSP_FILTERTYPE_HPF                14
#define     UnsignedToFloat(u)         (((double)((long)(u - 2147483647L - 1))) + 2147483648.0)

static const double pi = 3.14159265358979323846;
static const double twopi = (3.14159265358979323846 * 2);

#pragma mark FUNCTION_DECLARATIONS

//.................................................................................................................. dsp_reverse
// FUNCTION:    dsp_reverse(float *iAudioPtr, int iNumSamples, float *oAudioPtr);
// DESCRIPTION: Reverses an audio file, swapping the first sample with the last sample, the second sample with the
// second to last sample, etc.
// PARAMS:
//      float*  iAudioPtr
//      int     iNumSamples
//      float*  oAudioPtr
// RETURNS: DSP_INVALID_PARAMETER, DSP_SUCCESS, DSP_NULL_POINTER
//
int dsp_reverse(float* iAudioPtr, int iNumSamples, float* oAudioPtr);

//.................................................................................................................. dsp_reverse
// FUNCTION:    dsp_gainChange(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float dbChange);
// DESCRIPTION: This function scales an audio file by a specified dB value. The function converts the dB scalar to
// an amplitude scalar and multiplies each sample value by the amplitude scalar.
// PARAMS:
//      float*  iAudioPtr
//      int     iNumSamples
//      float*  oAudioPtr
//      float   dbChange
// RETURNS: DSP_NULL_POINTER, DSP_ERR_DBRANGE, DSP_INVALID_PARAMETER, DSP_SUCCESS
//
int dsp_gainChange(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float dbChange);

//.................................................................................................................. dsp_reverse
// FUNCTION:    dsp_normalize(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float dBThreshold)
// DESCRIPTION: This function normalizes an audio file to any dB Threshold. The dB threshold is preset to
// 0 so running this function will normalize the audio to the maximum dB value.
// PARAMS:
//      float*  iAudioPtr
//      int     iNumSamples
//      float*  oAudioPtr
//      float   dBThreshold
// RETURNS: DSP_NULL_POINTER, DSP_ERR_DBRANGE, DSP_INVALID_PARAMETER, DSP_SUCCESS
//
int dsp_normalize(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float dBThreshold);

//.................................................................................................................. dsp_fadeIn
// FUNCTION: dsp_fadeIn(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int durationInMS, int sampleRate, short fadeType)
// DESCRIPTION: The purpose of this function is to fade in an audio file given the duration of the fade in MS 
// and the type of fade (linear fade, equal power fade, or S-curve fade.) fadeType 10 selects linear fade,
// fadeType 11 selects equal power fade, and fadeType 12 selects S-curve fade. The S-curve fade is based on 
// a cosine wave.
// PARAMS:
//      float*  iAudioPtr
//      int     iNumSamples
//      float*  oAudioPtr
//      int     durationInMS
//      int     sampleRate
//      short   fadeType   
// RETURNS:  DSP_INVALID_PARAMETER, DSP_NULL_POINTER, DSP_SUCCESS
//
int dsp_fadeIn(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int durationInMS, int sampleRate, short fadeType);

//.................................................................................................................. dsp_fadeIn
// FUNCTION: dsp_fadeOut(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int durationInMS, int sampleRate, short fadeType)
// DESCRIPTION: The purpose of this function is to fade out an audio file given the duration of the fade in MS 
// and the type of fade (linear fade, equal power fade, or S-curve fade.) fadeType 10 selects linear fade,
// fadeType 11 selects equal power fade, and fadeType 12 selects S-curve fade. The S-curve fade is based on 
// a cosine wave.
// PARAMS:
//      float*  iAudioPtr
//      int     iNumSamples
//      float*  oAudioPtr
//      int     durationInMS
//      int     sampleRate
//      short   fadeType  
// RETURNS: DSP_INVALID_PARAMETER, DSP_NULL_POINTER, DSP_SUCCESS
//
int dsp_fadeOut(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int durationInMS, int sampleRate, short fadeType);

//.................................................................................................................. dsp_simpleSinewave
// FUNCTION: dsp_simpleSinewave(float *oAudioPtr, int nSamples, float freq, float amp, int sampleRate);
// DESCRIPTION: This function generates a basic sine wave given a frequency, amplitude threshold (in dB),
// total number of samples, and a sample rate. The function fills in the total number of samples for the sine 
// wave at the desired frequency. 
// PARAMS:
//      float*  oAudioPtr 
//      int     nSamples (Any positive number that != 0)
//      float   freq (Any positive number greater than 0, less than sample rate divided by 2)
//      float   amp (dB gain change value that's a negative value or 0, greater than -100)
//      int     sampleRate (must equal 44100 or 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with freq value
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_DBRANGE             = Error with dB value (amp)
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
//
int dsp_simpleSinewave(float* oAudioPtr, int nSamples, float freq, float amp, int sampleRate);

//.................................................................................................................. dsp_simpleSquarewave
// FUNCTION: dsp_simpleSquarewave(float *oAudioPtr, int nSamples, float freq, float amp, int sampleRate);
// DESCRIPTION: This function generates a basic square wave given a frequency, amplitude threshold (in dB),
// total numeber of samples, and a sample rate. The function splits each cycle in half, setting one half of
// the cycle to be -1 and the other half to be 1. 
// PARAMS:
//      float*  oAudioPtr 
//      int     nSamples (Any positive number that != 0)
//      float   freq (Any positive number greater than 0, less than sample rate divided by 2)
//      float   amp (dB gain change value that's a negative value or 0, greater than -100)
//      int     sampleRate (must equal 44100 or 48000) 
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with freq value
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_DBRANGE             = Error with dB value (amp)
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int dsp_simpleSquarewave(float* oAudioPtr, int nSamples, float freq, float amp, int sampleRate);

//.................................................................................................................. dsp_simpleTrianglewave
// FUNCTION: dsp_TriangleSinewave(float *oAudioPtr, int nSamples, float freq, float amp, int sampleRate);
// DESCRIPTION: This function generates a basic triangle wave given a frequency, amplitude threshold (in dB),
// total numeber of samples, and a sample rate. The function splits each cycle into four sections. The function
// then uses the same equation from linear fadein/fadeout to achieve a linear increase from 0 to 1, a linear decrease
// from 1 to -1, and a linear increase from -1 back to 0
// PARAMS:
//      float*  oAudioPtr 
//      int     nSamples (Any positive number that != 0)
//      float   freq (Any positive number greater than 0, less than sample rate divided by 2)
//      float   amp (dB gain change value that's a negative value or 0, greater than -100)
//      int     sampleRate (must equal 44100 or 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with freq value
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_DBRANGE             = Error with dB value (amp)
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
//
int dsp_simpleTrianglewave(float* oAudioPtr, int nSamples, float freq, float amp, int sampleRate);

//.................................................................................................................. dsp_rampSinewave
// FUNCTION: dsp_rampSinewave(float *oAudioPtr, int nSamples, float startingFreq, float endingFreq, float gain_dB, int sampleRate)
// DESCRIPTION: This function creates a sine wave that gradually ramps from a given starting
// frequency and ends at a given ending frequency.
// PARAMS:
//      float*  oAudioPtr 
//      int     nSamples (Any positive number that != 0)
//      float   startingFreq (any positive number greater than 0, less than the sample rate divided by 2)
//      float   endingFreq   (any positive number greater than 0, less than the sample rate divided by 2)
//      float   amp (dB gain change value that's a negative value or 0, greater than -100)
//      int     sampleRate (must equal 44100 or 48000)
// RETURNS: 
//          DSP_INVALID_PARAMETER       = Error with EndingFreq
//          DSP_INVALID_PARAMETER       = Error with startingFreq
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_DBRANGE             = Error with dB range (gain_dB)
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
//
int dsp_rampSinewave(float* oAudioPtr, int nSamples, float startingFreq, float endingFreq, float gain_dB, int sampleRate);

//.................................................................................................................. dsp_additiveSquarewave
// FUNCTION: dsp_additiveSquarewave(float *oAudioPtr, int nSamples, float freq, float gain_dB, int sampleRate)
// DESCRIPTION: This function generates a square wave using additive synthesis of sine waves
// of odd harmonics.
// PARAMS: 
//      float*  oAudioPtr 
//      int     nSamples (Any positive number that != 0)
//      float   freq (Any positive number greater than 0, less than sample rate divided by 2)
//      float   amp (dB gain change value that's a negative value or 0, greater than -100)
//      int     sampleRate (must equal 44100 or 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with freq
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_DBRANGE             = Error with dB range (gain_dB)
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
//
int dsp_additiveSquarewave(float* oAudioPtr, int nSamples, float freq, float gain_dB, int sampleRate);

//.................................................................................................................. dsp_additiveTrianglewave
// FUNCTION: dsp_additiveTrianglewave(float *oAudioPtr, int nSamples, float freq, float gain_dB, int sampleRate)
// DESCRIPTION: This function generates a triangle wave using additive synthesis of sine waves 
// of odd harmonics.
// PARAMS:
//      float*  oAudioPtr 
//      int     nSamples (Any positive number that != 0)
//      float   freq (Any positive number greater than 0, less than sample rate divided by 2)
//      float   amp (dB gain change value that's a negative value or 0, greater than -100)
//      int     sampleRate (must equal 44100 or 48000) 
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with freq
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_DBRANGE             = Error with dB range (gain_dB)
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
//
int dsp_additiveTrianglewave(float* oAudioPtr, int nSamples, float freq, float gain_dB, int sampleRate);

//.................................................................................................................. dsp_tremolo
// FUNCTION: dspa_tremolo(float *iAudioPtr, int iNumSamples, float* oAudioPtr, float lfoStartRate, float lfoEndRate, float lfoDepth, int sampleRate)
// DESCRIPTION: This program generates an lfo that gradually increases or decreases
// to a specificed start and end frequency. The program then multiplies any input signal
// by the lfo to generate tremolo. The lfo is also shifted to the positive domain
// so the input signal is only multiplied by positive numbers
// PARAMS:
//      float*  iAudioPtr (input audio pointer)
//      int     iNumSamples (Any positive number that is greater than or equal to 2, value is set by input audio.)
//      float*  oAudioPtr (output audio pointer)
//      float   lfoStartRate (Frequency value between 0 and 20 Hz)(Cannot equal zero)
//      float   lfoEndRate (Frequency value between 0 and 20 Hz)(Cannot equal zero)
//      float   lfoDepth (percent value 0 to 100)(Cannot equal zero)
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with lfoEndRate 
//          DSP_INVALID_PARAMETER       = Error with lfoStartRate
//          DSP_INVALID_PARAMETER       = Error with lfoDepth
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int dsp_tremolo(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float lfoStartRate, float lfoEndRate, float lfoDepth, int sampleRate);

//.................................................................................................................. dsp_ampModulation
// FUNCTION: dsp_ampModulation(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float modFrequency, float modAmplitude, int sampleRate);
// DESCRIPTION: This function provides amplitude modulation to any input signal. 
// The program generates an lfo that acts as the modulator, shifts that lfo to the
// positive domain, then multiplies the input (carrier) signal by the modulating signal.
// PARAMS:
//      float*  iAudioPtr (input audio pointer)
//      int     iNumSamples (Any positive number that is greater than or equal to 2, value is set by input audio.)
//      float*  oAudioPtr (output audio pointer)
//      float   modFrequency (Frequency value between 0 and 40 Hz)(Cannot equal zero)
//      float   modAmplitude (Amplitude decimal value between 0 and 1)(Cannot equal zero)
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with modFrequency 
//          DSP_INVALID_PARAMETER       = Error with modAmplitude
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int dsp_ampModulation(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float modFrequency, float modAmplitude, int sampleRate);

//.................................................................................................................. dsp_ringModulation
// FUNCTION: dsp_ringModulation(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float modFrequency, float modAmplitude, int sampleRate);
// DESCRIPTION: This function provides ring modulation to any input signal. The function
// does this my generating an lfo that acts as the modulating signal, then multiplies
// it with the carrier signal to generate a ring modulated signal.
// PARAMS:
//      float*  iAudioPtr (input audio pointer)
//      int     iNumSamples (Any positive number that is greater than or equal to 2, value is set by input audio.)
//      float*  oAudioPtr (output audio pointer)
//      float   modFrequency (Frequency value between 0 and 40 Hz)(Cannot equal zero)
//      float   modAmplitude (Amplitude decimal value between 0 and 1)(Cannot equal zero)
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with modFrequency 
//          DSP_INVALID_PARAMETER       = Error with modAmplitude
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int dsp_ringModulation(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float modFrequency, float modAmplitude, int sampleRate);

//.................................................................................................................. fir_lpf
// FUNCTION: fir_lpf(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, double cutoff, int firSize, int sampleRate);
// DESCRIPTION: This function generates an FIR filter, truncates it by multiplying it with
// the blackman window function to make it a finite length, then multiplies it by the input signal
// to apply the low pass filter generated to the input signal. The result is sent to oAudioPtr.
// PARAMS:
//      float*  iAudioPtr (input audio pointer)
//      int     iNumSamples (Any positive number that is greater than or equal to 2, value is set by input audio.)
//      float*  oAudioPtr (output audio pointer)
//      int     oNumSamples (unused)
//      double  cutoff (cutoff frequency at which the FIR LPF will begin to attenuate frequnecies. Function attenuates all frequencies below cutoff.)
//              valid inputs are 5 to half of the sample rate.
//      int     firSize (The size of each bin that will be attenuated.)
//              Valid inputs are 8 to 2048 (to prevent excess incorrect attenuation at the end of the file).
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with cutoff 
//          DSP_INVALID_PARAMETER       = Error with firSize
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int fir_lpf(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, double cutoff, int firSize, int sampleRate);

//.................................................................................................................. sinc
// FUNCTION: sinc(const double x);
// DESCRIPTION: This function generates a simple sinc function, used for FIR and IIR filtering. 
// sinc function is sine(x)/x and when x = 0, y = 1;
// PARAMS:
//      const double    x = x value of the sinc function
// RETURNS:  y value for the specified x value.
//         
double sinc(const double x);

//.................................................................................................................. amp_response
// FUNCTION: amp_response(float* oAudioPtr, int nSamples, int freqnum, int sampleRate)
// DESCRIPTION: This function determines the amplitude response for arbitrary frequencies by generating
// many sine waves and passing them through an FIR LPF. After being passed through an FIR LPF, the function 
// measures the maximum amplitues of the output. Doing this generates an amplitude response. 
// PARAMS:
//      float*  oAudioPtr (output audio pointer, used to generate sine waves)
//      int     nSamples  (length of the sine wave in samples, valid range is any integer greater than 2.
//      int     freqnum   (number of frequencies to be calculated for amp response.
//                        (valid ranges are 2 to half the sample rate (nyquist) so that maximum percision is 
//                        an increment of 1 Hz for each frequency included in the amplitude response.)
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with freqnum 
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int amp_response(float* oAudioPtr, int nSamples, int freqnum, int sampleRate);

//.................................................................................................................. fir_bandstop
// FUNCTION: fir_bandstop(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, float lowerEdgeInHZ, float upperEdgeInHz, int firSize, int sampleRate);
// DESCRIPTION: 
// PARAMS:
//      float*  iAudioPtr (input audio pointer)
//      int     iNumSamples (number of samples in input)
//      float*  oAudioPtr (output audio pointer)
//      int     oNumSamples  
//      float   lowerEdgeInHz (frequency value greater than 0 and less than upperEdgeInHz)
//      float   upperEdgeInHz (frequency value greater than lowerEdgeInHz and less than Nyquist value
//      int     firSize (Size of each bin that will be attenuated. Must be less than the total number of samples divided by 2 and greater than 8 
//                      to prevent the program from freezing.
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_INVALID_PARAMETER       = Error with oNumSamples 
//          DSP_INVALID_PARAMETER       = Error with lowerEdgeInHz 
//          DSP_INVALID_PARAMETER       = Error with upperEdgeInHz
//          DSP_INVALID_PARAMETER       = Error with firSize   
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int fir_bandstop(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, float lowerEdgeInHZ, float upperEdgeInHz, int firSize, int sampleRate);

//.................................................................................................................. amp_response_fft
// FUNCTION: amp_response_fft(double* ir, int firSize, int fftSize, int sampleRate)
// DESCRIPTION: 
// PARAMS:
//      double* ir
//      int     firSize
//      int     fftSize
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with firSize 
//          DSP_INVALID_PARAMETER       = Error with fftSize
//          DSP_NULL_POINTER            = Error with ir
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
void amp_response_fft(double* ir, int firSize, int fftSize, int sampleRate);

//..................................................................................................... fft_fir
// FUNCTION: fft_fir(int fftSize, float lo_freq, float hi_freq, double* out_ir, int sampleRate)
// DESCRIPTION: This function is used to specify a filter's frequency response in the frequency domain. It then
// performs an IFFT to create a time-domain impulse response. This function uses the JUCE FFT library and also
// shifts the IR, but does not window it.
// PARAMS:
//      int     fftSize     the size of the FFT (must be >=firSize)
//      float   lo_freq     the lower edge of the passband
//      float   hi_freq     the upper edge of the passband
//      double* out_ir      pointer to the output buffer where impulse response is written.
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with fftSize 
//          DSP_INVALID_PARAMETER       = Error with lo_freq 
//          DSP_INVALID_PARAMETER       = Error with hi_freq 
//          DSP_NULL_POINTER            = Error with out_ir
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int fft_fir(int fftSize, float lo_freq, float hi_freq, double* out_ir, int sampleRate);

//..................................................................................................... iir_bpf
// FUNCTION: iir_bpf(float* iAudioPtr, int iNumSamples, float* oAudioPtr, double cutoff, double bandwidth, int sampleRate);
// DESCRIPTION: This function filters any input audio signal with an Infinite Impulse Response Bandpass filter. 
// The function generates coefficients necessary to calculate the filtered signal using a center frequency
// and a bandwidth value in hertz. The function then generates and computes a bandpass filter over the input audio
// signal. 
// PARAMS:
//      float*  iAudioPtr   Input audio pointer
//      int     iNumSamples input number of samples (any number greater than or equal to 2, set by input audio)
//      float*  oAudioPtr   Output audio pointer
//      double  cutoff      Value in Hz greater than 1 to Nyquist frequency
//      double  bandwidth   Value in Hz greater than 1 to Nyquist frequency
//      NOTE: cutoff minus bandwidth must be greater than or equal to 0 and cutoff plus bandwidth must be less than or equal to the Nyquist
//      int     sampleRate (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with iNumSamples 
//          DSP_INVALID_PARAMETER       = Error with cutoff 
//          DSP_INVALID_PARAMETER       = Error with bandwidth 
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int iir_bpf(float* iAudioPtr, int iNumSamples, float* oAudioPtr, double cutoff, double bandwidth, int sampleRate);

//..................................................................................................... bpf_amp_response
// FUNCTION: bpf_amp_response(float centerFreqHz, float bandwidthHz, float analysis_freq, int sampleRate);
// DESCRIPTION: This function performs direct evaluation to get an amplitude and phase response for any given 
// frequency after being passed through an IIR BPF. The function uses the Z transform and imaginary numbers
// to calculate the magnitude and phase by finding the real and imaginary parts of any given frequency coming out of the BPF
// PARAMS:
//      float   centerFreqHz        (Any integer greater than 1 and less than the nyquist)
//      float   bandwidthHz         (Any integer greater than 1, centerFreq - bandwidth must be > 0, & centerFreq + bandwidth must be < nyquist)
//      float   analysis_freq       (Any integer between 2 and the nyquist)
//      int     sampleRate          (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with centerFreqHz
//          DSP_INVALID_PARAMETER       = Error with bandwidthHz 
//          DSP_INVALID_PARAMETER       = Error with analysis_freq
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
float bpf_amp_response(float centerFreqHz, float bandwidthHz, float analysis_freq, int sampleRate);

//..................................................................................................... biquad_filter
// FUNCTION: biquad_filter(float* iAudioPtr, int iNumSamples, float* oAudioPtr, double cutoffHz, double Q, short filterType, int sampleRate);
// DESCRIPTION: This function is a biquad filter that independently filters each channel of an input signal,
// iAudioPtr, with a second order recursive filter with coefficients calculated from the inputs.
// PARAMS:
//      float*  iAudioPtr           Input audio pointer
//      int     iNumSamples         input number of samples (any number greater than or equal to 2, set by the input audio)
//      float*  oAudioPtr           Output audio pointer
//      double  cutoffHz            Value in Hz greater than 1, less than or equal to the Nyquist frequency
//      double  Q                   Decimal value from 0.0 - 1.0
//      short   filterType          Sets the filter type to a high pass or low pass filter (DSP_FILTERTYPE_HPF or DSP_FILTERTYPE_LPF)
//      int     sampleRate          global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000
// RETURNS:  
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_INVALID_PARAMETER       = Error with curoffHz
//          DSP_INVALID_PARAMETER       = Error with Q  
//          DSP_INVALID_PARAMETER       = Error with filterType
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int biquad_filter(float* iAudioPtr, int iNumSamples, float* oAudioPtr, double cutoffHz, double Q, short filterType, int sampleRate);

//..................................................................................................... biquad_amp_response
// FUNCTION: int biquad_amp_response(double cutoffHz, double Q, short filterType, int freqnum, int sampleRate)
// DESCRIPTION: This function performs an amplitude response for the biquad filter created in the previous
// function. This function generates a list of magnitudes at various frequencies and the frequencies are 
// determined by freqnum, the number of desired calculated magnitudes for the amplitude response of the biquad filter.
// PARAMS:
//      double  cutoffHz            Value in Hz greater than 1, less than or equal to the Nyquist frequency
//      double  Q                   Decimal value from 0.0 - 1.0
//      short   filterType          Sets the filter type to a high pass or low pass filter (DSP_FILTERTYPE_HPF or DSP_FILTERTYPE_LPF)
//      int     freqnum             number of frequencies to be calculated for amp response.Valid ranges are 2 to half the sample rate
//                                  (nyquist) so that maximum percision is an increment of 1 Hz for each frequency included in the amplitude response.
//      int     sampleRate          (global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000)
// RETURNS:  
//          DSP_INVALID_PARAMETER       = Error with cutoffHz
//          DSP_INVALID_PARAMETER       = Error with Q 
//          DSP_INVALID_PARAMETER       = Error with filterType
//          DSP_INVALID_PARAMETER       = Error with freqnum
//          DSP_ERR_UNKOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int biquad_amp_response(double cutoffHz, double Q, short filterType, int sampleRate, int freqnum);

//..................................................................................................... dsp_pitchChange
// FUNCTION: dsp_pitchChange(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, float pitchRatio, int sampleRate);
// DESCRIPTION: This function effectively increases or decreases the pitch of an input audio signal limited to one octave in either direction.
// The amount the pitch is shifted is determined by pitchRatio. The function does this by converting the pitchRatio to a fraction, multiplying the 
// input audio by the numerator (inserting 0's at new samples), then dividing the audio by the denominator.
// PARAMS:
//      float*  iAudioPtr           Input audio pointer
//      int     iNumSamples         input number of samples (any number greater than or equal to 2, set by the input audio)
//      float*  oAudioPtr           Output audio pointer
//      int     oNumSamples         Output number of samples determined by pitchRatio. (Must equal iNumSamples * pitchRatio)!!
//      float   pitchRatio          Valid inputs are: 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5
//      int     sampleRate          global variable _sampleRate is passed in to this value. Must equal 44100 ot 48000
// RETURNS:  
//          DSP_NULL_POINTER            = Error with iAudioPtr
//          DSP_NULL_POINTER            = Error with oAudioPtr
//          DSP_INVALID_PARAMETER       = Error with iNumSamples
//          DSP_INVALID_PARAMETER       = Error with oNumSamples
//          DSP_INVALID_PARAMETER       = Error with pitchRatio 
//          DSP_ERR_UNKNOWN_SAMPLERATE   = Error with sampleRate
//          DSP_SUCCESS                 = No errors, function worked successfully
int dsp_pitchChange(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, float pitchRatio, int sampleRate);

//.................................................................................................................. swap2Bytes
short swap2Bytes(unsigned char* bytes);

//.................................................................................................................. swap4Bytes
int swap4Bytes(unsigned char* bytes);

//.................................................................................................................. convertFromIeeeExtended
int convertFromIeeeExtended(unsigned char* bytes);


#pragma mark FUNCTION_IMPLEMENTATIONS

int swap4Bytes(unsigned char* bytes)
{
    return ((int)bytes[3] << 0) | ((int)bytes[2] << 8) | ((int)bytes[1] << 16) | ((int)bytes[0] << 24);
}

short swap2Bytes(unsigned char* bytes)
{
    return (int)bytes[1] | (int)bytes[0] << 8;
}

int convertFromIeeeExtended(unsigned char* bytes)
{
    double    f;
    int    expon;
    unsigned long hiMant, loMant;

    expon = ((bytes[0] & 0x7F) << 8) | (bytes[1] & 0xFF);
    hiMant = ((unsigned long)(bytes[2] & 0xFF) << 24)
        | ((unsigned long)(bytes[3] & 0xFF) << 16)
        | ((unsigned long)(bytes[4] & 0xFF) << 8)
        | ((unsigned long)(bytes[5] & 0xFF));
    loMant = ((unsigned long)(bytes[6] & 0xFF) << 24)
        | ((unsigned long)(bytes[7] & 0xFF) << 16)
        | ((unsigned long)(bytes[8] & 0xFF) << 8)
        | ((unsigned long)(bytes[9] & 0xFF));

    if (expon == 0 && hiMant == 0 && loMant == 0)
    {
        f = 0;
    }
    else
    {
        if (expon == 0x7FFF)
        {    /* Infinity or NaN */
            f = HUGE_VAL;
        }
        else {
            expon -= 16383;
            f = ldexp(UnsignedToFloat(hiMant), expon -= 31);
            f += ldexp(UnsignedToFloat(loMant), expon -= 32);
        }
    }

    if (bytes[0] & 0x80)
        return -f;
    else
        return f;
}

int dsp_reverse(float *iAudioPtr, int iNumSamples, float *oAudioPtr)
{
    int result = DSP_SUCCESS;

    if (iNumSamples <= 0) {
        result = DSP_INVALID_PARAMETER;}
    else if (iAudioPtr == NULL) {
        result = DSP_NULL_POINTER;}
    else if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //This for loop reverses every sample and assigns it to the output Audio Buffer.
        //i represents the sample number.
        for (int i = 0; i < iNumSamples; i++) {

            //Setting the output pointer to the opposite 
            //sample read from the input pointer
            oAudioPtr[i] = iAudioPtr[iNumSamples - i - 1];
        };

        return result;
    };
}

int dsp_gainChange(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float dbChange) {
    
    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (iNumSamples <= 0) {
        result = DSP_INVALID_PARAMETER;}
    else if (iAudioPtr == NULL) {
        result = DSP_NULL_POINTER;}
    else if (dbChange > 0) {
        result = DSP_ERR_DBRANGE;}
    else if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (dbChange / 20)));

        //For loop multiplies each sample by the amplitude scalar.
        for (int i = 0; i < iNumSamples; i++) {
            oAudioPtr[i] = iAudioPtr[i] * ampscale;
        };

        return result;
    };
};

int dsp_normalize(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float dBThreshold) {

    int result = DSP_SUCCESS;

    //Variable stores maximum read sample
    float maxamp = 0;

    //Error checking function inputs
    if (iNumSamples <= 0) {
        result = DSP_INVALID_PARAMETER;}
    else if (iAudioPtr == NULL) {
        result = DSP_NULL_POINTER;}
    else if (dBThreshold > 0) {
        result = DSP_ERR_DBRANGE;}
    else if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Formula for converting dBThreshold to Amplitude Threshold. Storing as ampthresh.
        float ampthresh = (powf(10, (dBThreshold / 20)));

        //For loop finds the largest sample and stores it under variable maxamp
        for (int i = 0; i < iNumSamples; i++) {
            if (iAudioPtr[i] >= maxamp) {
                maxamp = iAudioPtr[i];
            };
        };

        float multiplier = ampthresh / maxamp;
        //For loop scales each sample by ampthresh/maxamp.
        for (int i = 0; i < iNumSamples; i++) {
            oAudioPtr[i] = iAudioPtr[i] * multiplier;
        };

        return result;
    };
};

int dsp_fadeIn(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int durationInMS, int sampleRate, short fadeType) {

    int result = 0;
    float durationInSamples = sampleRate * (durationInMS / 1000.0000);
    //Converting from duration of fade in MS to duration of fade in total samples

    //Error checking function inputs
    if (iNumSamples <= 0) {
        result = DSP_INVALID_PARAMETER;}
    else if (iAudioPtr == NULL) {
        result = DSP_NULL_POINTER;}
    else if (durationInSamples > (iNumSamples/2)) {
        result = DSP_INVALID_PARAMETER;}
    else if (durationInSamples <= 0) {
        result = DSP_INVALID_PARAMETER;}
    else if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;}
    else if (sampleRate != 8000 && sampleRate != 11025 && sampleRate != 16000 && sampleRate != 22050 && sampleRate != 44100 && sampleRate != 48000 && sampleRate != 88200 && sampleRate != 96000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        float multiplier = 0;

        switch (fadeType)
        {
        case 10: 
            //Linear fade
            for (int i = 0; i < durationInSamples; i++) {
                multiplier = (i / durationInSamples);
                oAudioPtr[i] = iAudioPtr[i] * multiplier;
            };

            for (int i = durationInSamples; i < iNumSamples; i++) {
                oAudioPtr[i] = iAudioPtr[i];
            };
            break;

        case 11:
            //Equal Power fade
            for (int i = 0; i < durationInSamples; i++) {
                multiplier = sqrt(i / durationInSamples);
                oAudioPtr[i] = iAudioPtr[i] * multiplier;
            };

            for (int i = durationInSamples; i < iNumSamples; i++) {
                oAudioPtr[i] = iAudioPtr[i];
            };
            break;

        case 12:
            //S-curve fade (based on cosine wave)
            float x = 0;
            for (int i = 0; i < durationInSamples; i++) {
                x = (i / durationInSamples);
                //Based on equation of cosine that reaches max at x = 1
//and oscillates from 0 to 1, centered at 0.5
multiplier = ((0.5 * cos((pi * x) - pi)) + 0.5);
oAudioPtr[i] = iAudioPtr[i] * multiplier;
            };

            for (int i = durationInSamples; i < iNumSamples; i++) {
                oAudioPtr[i] = iAudioPtr[i];
            };
            break;
        };

        return result;
    };
};

int dsp_fadeOut(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int durationInMS, int sampleRate, short fadeType) {

    int result = 0;
    float durationInSamples = sampleRate * (durationInMS / 1000.0000);
    //Converting from duration of fade in MS to duration of fade in total samples

    //Error checking function inputs
    if (iNumSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (iAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (durationInSamples > (iNumSamples / 2)) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (durationInSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (sampleRate != 8000 && sampleRate != 11025 && sampleRate != 16000 && sampleRate != 22050 && sampleRate != 44100 && sampleRate != 48000 && sampleRate != 88200 && sampleRate != 96000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        float multiplier = 0;
        int fadestart = iNumSamples - durationInSamples;

        switch (fadeType)
        {
        case 10:
            //Linear fade
            for (int i = fadestart; i < iNumSamples; i++) {
                multiplier = ((iNumSamples - i) / durationInSamples);
                oAudioPtr[i] = iAudioPtr[i] * multiplier;
            };

            for (int i = 0; i < fadestart; i++) {
                oAudioPtr[i] = iAudioPtr[i];
            }
            break;

        case 11:
            //Equal Power fade
            for (int i = fadestart; i < iNumSamples; i++) {
                multiplier = sqrt((iNumSamples - i) / durationInSamples);
                oAudioPtr[i] = iAudioPtr[i] * multiplier;
            };

            for (int i = 0; i < fadestart; i++) {
                oAudioPtr[i] = iAudioPtr[i];
            };
            break;

        case 12:
            //S-curve fade (based on cosine wave)
            float x = 0;

            for (int i = fadestart; i < iNumSamples; i++) {
                x = ((iNumSamples - i) / durationInSamples);
                //Based on equation of cosine that reaches max at x = 1
                //and oscillates from 0 to 1, centered at 0.5
                multiplier = ((0.5 * cos((pi * x) - pi)) + 0.5);
                oAudioPtr[i] = iAudioPtr[i] * multiplier;
            };

            for (int i = 0; i < fadestart; i++) {
                oAudioPtr[i] = iAudioPtr[i];
            };
            break;
        };

        return result;
    };
};

int dsp_simpleSinewave(float* oAudioPtr, int nSamples, float freq, float amp, int sampleRate) {

    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (amp > 0 || amp < -100) {
        result = DSP_ERR_DBRANGE;
    }
    else if (freq <= 0 || freq >= (sampleRate / 2) || nSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (amp / 20)));


        //Calculates the phase increment.
        float phase = 0.0;
        float phaseincrement = ((twopi * freq) / sampleRate);
        int p = 0;

        //Infinite loop that exits when reached max number of samples.
        for (p; p < nSamples; p++) {

            //Assigns the sample to the specified amplitude multiplied by the scalar value.
            oAudioPtr[p] = (sinf(phase) * ampscale);
            //increments phase
            phase += phaseincrement;

        };
        return result;
    }
};

int dsp_simpleSquarewave(float* oAudioPtr, int nSamples, float freq, float amp, int sampleRate) {

    int result = DSP_SUCCESS;


    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (amp > 0 || amp < -100) {
        result = DSP_ERR_DBRANGE;
    }
    else if (freq <= 0 || freq >= (sampleRate / 2) || nSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        // frequency = cycles/second
        // sample rate = samples/second
        // nSamples = total num samples
        // totalcycles = nSamples / samplespercycle
       
        //Formula calculates number of samples per every cycle.
        float sampspercycle = int(sampleRate / freq);

        int totalcycles = nSamples / sampspercycle;

        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (amp / 20)));
        float negampscale = ampscale * -1;

        //number of samples in half of a cycle calculated to determine
        //when signal switches from 1 to -1 and -1 to 1 for square wave.
        int halfsampspercycle = (sampspercycle / 2);
        int startsamp = 0;

        for (int c = 0; c < totalcycles; c++) {
            startsamp = sampspercycle * c;

            //For loop sets first half of cycle to 1 
            for (int i = startsamp; i < (startsamp + halfsampspercycle); i++) {
                oAudioPtr[i] = ampscale;
            };

            //For loop sets second half of cycle to -1
            for (int i = (startsamp + halfsampspercycle); i < (startsamp + sampspercycle); i++) {
                oAudioPtr[i] = negampscale;
            };
        };

        return result;
    }
    
};

int dsp_simpleTrianglewave(float* oAudioPtr, int nSamples, float freq, float amp, int sampleRate) {

    int result = DSP_SUCCESS;


    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (amp > 0 || amp < -100) {
        result = DSP_ERR_DBRANGE;
    }
    else if (freq <= 0 || freq >= (sampleRate / 2) || nSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        // frequency = cycles/second
        // sample rate = samples/second
        // nSamples = total num samples
        // totalcycles = nSamples / samplespercycle

        //Formula calculates number of samples per every cycle.
        float sampspercycle = int(sampleRate / freq);

        int totalcycles = nSamples / sampspercycle;

        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (amp / 20)));

        float multiplier = 0;
        int startsamp = 0;
        
        float halfsampspercycle = int(sampspercycle / 2);
        float fourthsampspercycle = int(halfsampspercycle / 2);
 
        for (int c = 0; c < totalcycles; c++) {
            startsamp = sampspercycle * c;
           
            for (int i = 0; i < fourthsampspercycle; i++) {
                multiplier = (i / fourthsampspercycle);
                oAudioPtr[startsamp + i] = (ampscale * multiplier);
            };

            for (int x = 0; x < fourthsampspercycle; x++) {
                multiplier = ((fourthsampspercycle - x) / fourthsampspercycle);
                oAudioPtr[startsamp + int(fourthsampspercycle) + x] = (ampscale * multiplier);
            };

            for (int w = 0; w < fourthsampspercycle; w++) {
                multiplier = (w / fourthsampspercycle);
                oAudioPtr[startsamp + int(halfsampspercycle) + w] = (-1 * ampscale * multiplier);
            };
            
            for (int z = 0; z < fourthsampspercycle; z++) {
                multiplier = ((fourthsampspercycle - z) / fourthsampspercycle);
                oAudioPtr[startsamp + int(halfsampspercycle) + int(fourthsampspercycle) + z] = (-1 * ampscale * multiplier);
            };
        };

        return result;
    }
};

int dsp_additiveTrianglewave(float* oAudioPtr, int nSamples, float freq, float gain_dB, int sampleRate) {
    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (gain_dB > 0 || gain_dB < -100) {
        result = DSP_ERR_DBRANGE;
    }
    else if (freq <= 0 || freq >= (sampleRate / 2) || nSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }


    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (gain_dB / 20)));

        float maxharmonicnum = 1;
        int i = 0;
        float s = 1;
        float h = 1.0;
        float maxfreq = (maxharmonicnum * freq);
        float phaseincrement = ((twopi * freq) / sampleRate);
        float phase = 0.0;

        //Calculates the maximum harmonic allowed based on sample rate and sets it to maxharmonicnum
        while (maxfreq < (sampleRate / 2)) {
            maxfreq = (maxharmonicnum * freq);
            maxharmonicnum += 2;
        }

        //Sets all samples in output buffer to 0
        for (i = 0; i < nSamples; i++) {
            oAudioPtr[i] = 0;
        };

        //This is to prevent accidental aliasing
        maxharmonicnum = maxharmonicnum - 2;

        for (h = 1; h <= maxharmonicnum; h += 2) {
            //Resets s variable that flips the sign of hval for every other harmonic

            //Reset phase and phase incrementor since restarting at sample 0
            phase = 0.0;
            phaseincrement = ((twopi * (freq * h)) / sampleRate);

            for (i = 0; i < nSamples; i++) {
                //harmonic value is added to previous, summing
                oAudioPtr[i] += ((ampscale) * (1.0 / h) * (sinf(phase)) * (powf(-1, s)) * (1.0 / (s * s)));

                //Increment the phase
                phase += phaseincrement;
            };
            //Increment the exponent for -1, flipping the sign after every other harmonic
            s++;
        };
        return result;
    }
};

int dsp_additiveSquarewave(float* oAudioPtr, int nSamples, float freq, float gain_dB, int sampleRate) {

    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (gain_dB > 0 || gain_dB < -100) {
        result = DSP_ERR_DBRANGE;
    }
    else if (freq <= 0 || freq >= (sampleRate / 2) || nSamples <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (gain_dB / 20)));

        float maxharmonicnum = 1;
        float h = 1.0;
        float maxfreq = (maxharmonicnum * freq);
        float phaseincrement = ((twopi * freq) / sampleRate);
        float phase = 0.0;
        int p = 0;
        int i = 0;
        
        //Calculates the maximum harmonic allowed based on sample rate and sets it to maxharmonicnum
        while (maxfreq < (sampleRate / 2)) {
            maxfreq = (maxharmonicnum * freq);
            maxharmonicnum+=2;
        }
    
        //This is to prevent accidental aliasing
        maxharmonicnum = maxharmonicnum - 2;

        //for loop sets all samples in output audio buffer to 0
        for (i = 0; i < nSamples; i++) {
            oAudioPtr[i] = 0;
        };

        //nested for loop goes through each harmonic first, calculating the sample values and adding
        //them to the previous sample values stored in the output audio buffer.
        for (h = 1; h <= maxharmonicnum; h += 2) {
            phase = 0.0;
            phaseincrement = ((twopi * (freq * h)) / sampleRate);

            for (p = 0; p < nSamples; p++) {
                oAudioPtr[p] += ((1.0 / h) * (sinf(phase)) * ampscale);    
                phase += phaseincrement;
            };
        };
        return result;
    }
};

int dsp_rampSinewave(float* oAudioPtr, int nSamples, float startingFreq, float endingFreq, float gain_dB, int sampleRate) {
    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (gain_dB > 0 || gain_dB < -100) {
        result = DSP_ERR_DBRANGE;
    }
    else if (startingFreq <= 0 || startingFreq >= (sampleRate / 2) || nSamples <= 0 || endingFreq <= 0 || endingFreq >= (sampleRate / 2)) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
       
        //Formula for converting dB to amplitude
        float ampscale = (powf(10, (gain_dB / 20)));
    
        //Calculates how much the freq needs to increment to reach the endingFreq
        float currentfreq = startingFreq;
        float freqincrement = ((endingFreq - startingFreq) / nSamples);

        //Calculates the phase increment for every sample given the new "currentfreq".
        float phase = 0.0;
        float phaseincrement = ((twopi * currentfreq) / sampleRate);
        int p = 0;

        //Infinite loop that exits when reached max number of samples.
        for (p; p < nSamples; p++) {

            oAudioPtr[p] = (sinf(phase)*ampscale);

            //Calculates new phase increment given new currentfreq and increments the phase.
            phaseincrement = ((twopi * currentfreq) / sampleRate);
            phase += phaseincrement;
            
            //Sets a new currentfreq for the next sample then repeats.
            currentfreq += freqincrement;
        };
        return result;
    }


};

int dsp_tremolo(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float lfoStartRate, float lfoEndRate, float lfoDepth, int sampleRate) {
    int result = 0;

    //Error checking function inputs
    if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (iNumSamples < 2 || lfoStartRate <= 0 || lfoEndRate <= 0 || lfoStartRate > 20 || lfoEndRate > 20 || lfoDepth < 0 || lfoDepth > 100) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Copy ramp sine function to generate LFO (< 20 Hz)
        float currentfreq = lfoStartRate;
        float freqincrement = ((lfoEndRate - lfoStartRate) / iNumSamples);
        float phase = 0.0;
        float phaseincrement = ((twopi * currentfreq) / sampleRate);
        int p = 0;

        //Creates new buffer for LFO, stored under lfo
        float* lfo;
        lfo = oAudioPtr;
        
        for (p; p < iNumSamples; p++) {
            lfo[p] = (sinf(phase));
            phaseincrement = ((twopi * currentfreq) / sampleRate);
            phase += phaseincrement;
            currentfreq += freqincrement;
        };

        //multiply LFO by 0.5, then shift everything up by 0.5
        //Then scales the lfo by the lfoDepth and flips all the samples (sample = 1 - sample).
        //This is so the lfo suppresses from max amp, NOT pulsing amplitude from 0
        p = 0;
        for (p; p < iNumSamples; p++) {
            lfo[p] = (1 - (((lfo[p] * 0.5) + 0.5) * (lfoDepth / 100)));
        };

        //Multiply input audio buffer by the lfo
        p = 0;
        for (p; p < iNumSamples; p++) {
            oAudioPtr[p] = iAudioPtr[p]*lfo[p];
        };
   
        return result;
    }
};

int dsp_ampModulation(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float modFrequency, float modAmplitude, int sampleRate) {
    int result = 0;

    //Error checking function inputs
    if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (iNumSamples < 2 || modFrequency <= 0 || modFrequency > 40 || modAmplitude > 1 || modAmplitude <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Copy ramp sine function to generate low freq modulator signal (< 20 Hz)
        float currentfreq = modFrequency;
        float phase = 0.0;
        float phaseincrement = ((twopi * currentfreq) / sampleRate);
        int p = 0;

        //Creates new buffer for modulator, stored under ampmod
        float* ampmod;
        ampmod = oAudioPtr;

        for (p; p < iNumSamples; p++) {
            ampmod[p] = (sinf(phase));
            phaseincrement = ((twopi * currentfreq) / sampleRate);
            phase += phaseincrement;
        };

        //Multiplies the modulator by 0.5 then shifts up by 0.5
        //so the signal is completely positive
        p = 0;
        for (p; p < iNumSamples; p++) {
            ampmod[p] = (1 - ((ampmod[p] * 0.5) + 0.5))* modAmplitude;
        }; 

        //Multiply modulator signal by the carrier signal to produce
        //amplitude modulated signal
        p = 0;
        for (p; p < iNumSamples; p++) {
            oAudioPtr[p] = (iAudioPtr[p] * ampmod[p]);
        };
        free(ampmod);
        return result;
    }
};

int dsp_ringModulation(float* iAudioPtr, int iNumSamples, float* oAudioPtr, float modFrequency, float modAmplitude, int sampleRate) {
    int result = 0;

    //Error checking function inputs
    if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (iNumSamples < 2 || modFrequency <= 0 || modFrequency > 40 || modAmplitude > 1 || modAmplitude <= 0) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        //Copy ramp sine function to generate low freq modulator
        float currentfreq = modFrequency;
        float phase = 0.0;
        float phaseincrement = ((twopi * currentfreq) / sampleRate);
        int p = 0;

        //Creates new buffer for ring modulator signal, stored under ringmod
        float* ringmod;
        ringmod = oAudioPtr;

        for (p; p < iNumSamples; p++) {
            ringmod[p] = (sinf(phase));
            phaseincrement = ((twopi * currentfreq) / sampleRate);
            phase += phaseincrement;
        };

        //Multiplies modulator signal by modulator amplitude
        p = 0;
        for (p; p < iNumSamples; p++) {
            ringmod[p] = ((ringmod[p])*modAmplitude);
        };

        // 
        p = 0;
        for (p; p < iNumSamples; p++) {
            oAudioPtr[p] = ((iAudioPtr[p]) * ringmod[p]);
        };
        free(ringmod);
        return result;
    }
};

double sinc(const double x)
{
    if (x == 0) {
        return 1;
    }
    else {
        return float(sin(x) / x);
    }
}

int fir_lpf(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, double cutoff, int firSize, int sampleRate) {
    int result = 0;

    //Error checking function inputs
    if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (iNumSamples < 2 || cutoff <= 5 || cutoff > (sampleRate / 2.0) || firSize > (iNumSamples / 2.0) || firSize <= 8) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
            return result;
    }

    else {

        //Creates SINC Impulse response and limits it with Blackman Window Function
        //to create windowed impulse response.
        double cf = cutoff / sampleRate;        // cf valid range here is 0.0 to 0.5
        int k;
        int i;
        int j;
        int firShift = (firSize / 2.0);

        //Allocate memory for SINC impulse response, blackman window function, and windowed impulse response.
        //All functions are the size of the firSize.
        double* IR = (double*)malloc(firSize * sizeof(double));
        double* Blackman = (double*)malloc(firSize * sizeof(double));
        double* WIR = (double*)malloc(firSize * sizeof(double));

        for (i = 0; i < firSize; i++) {
            k = i - firShift;
            IR[i] = 2 * cf * sinc(twopi * cf * k);
            Blackman[i] = 0.42 - 0.5 * cos((twopi * i) / (firSize)) + 0.08 * cos(2.0 * ((twopi * i) / (firSize)));
            WIR[i] = IR[i] * Blackman[i];
        }
        
        //Convolve the WIR with Input signal and store result sample value under accum
        double accum;
        for (i = 0; i < iNumSamples; i++) {

            accum = 0;
            for (j = 0; j < firSize; j++) {
                if (i + j <= iNumSamples) {
                    accum += WIR[j] * iAudioPtr[i + j];
                }
                else {
                    accum = 0;
                };
            }
            oAudioPtr[i] = accum;
        }

        char str[256];
        for (i = 0; i < firSize; i++) {
            sprintf_s(str, sizeof(str), "i = %d, WIR = %f, IR = %f, Blackamn = %f \n", i, WIR[i], IR[i], Blackman[i]);
            OutputDebugStringA(str);
        }

        //Freeing memory for Blackman windowed function, sinc impulse response, and windowed impulse response.
        free(Blackman);
        free(IR);
        free(WIR);
        return result;
    };

}

int amp_response(float* oAudioPtr, int nSamples, int freqnum, int sampleRate) {
    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (freqnum <= 2 || freqnum >= (sampleRate / 2) || nSamples < 2) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        int f;      //frequency of sine wave 
        int p;      //sample number (used and reset multiple times)
        int nyquist = (sampleRate / 2);
        int freqinc = (nyquist / freqnum);
        int ampsample = 0;
        int sampspercycle;

        float maxamp;
        float phase;
        float phaseincrement;
        //Buffer to store all the recorded maxamp values for each sine wave freq after being passed through the FIR LPF
        float* maxampbuffer = (float*)malloc(freqnum * sizeof(float));

        //Loop to generate sine wave at every freq of increment "freqinc"
        for (f = 1; f < nyquist; f += freqinc) {

            //Calculates samples per cycle (so we don't need to go through each cycle)
            sampspercycle = (sampleRate / f);

            //Calculates the phase increment.
            phase = 0.0;
            phaseincrement = ((twopi * f) / sampleRate);
            p = 0;

            //Generates sine wave
            for (p; p < sampspercycle; p++) {
                //Assigns the sample to the specified amplitude multiplied by the scalar value.
                oAudioPtr[p] = sinf(phase);
                //increments phase
                phase += phaseincrement;
            };

            //CHANGE LPF CUTOFF FREQ AND BIN SIZE HERE!!!!
            //
            //Filters sine wave and replaces it in same buffer (oAudioPtr)
            result = fir_lpf(oAudioPtr, nSamples, oAudioPtr, nSamples, 1000, 128, sampleRate);

            //Check fir_lpf had no errors
            if (result != DSP_SUCCESS) {
                return result;
            }

            //Resets maxamp value for each new freq
            maxamp = 0;

            //Finds and stores maxamp of filtered sine wave. Only need to check half of a cycle to find maxamp
            for (p = 0; p <= (sampspercycle/2); p++) {
                if (oAudioPtr[p] >= maxamp) {
                    maxamp = oAudioPtr[p];
                }
            }

            //Store maxamp value in maxampbuffer
            maxampbuffer[ampsample] = maxamp;
            ampsample++;
        }

        //Printf for some reason doesn't work on windows
        //Found this online to print frequency and maxamp value to output window
        char str[256];
        ampsample = 0;
        for (f = 1; f < nyquist; f += freqinc) {
            sprintf_s(str, sizeof(str), "frequency = %d, maxamp = %f \n", f, maxampbuffer[ampsample]);
            OutputDebugStringA(str);
            ampsample++;
        }

        //To test on mac:
        ampsample = 0;
        for (f = 1; f < nyquist; f += freqinc) {
            printf("frequency = %d, maxamp = %f \n", f, maxampbuffer[ampsample]);
            ampsample++;
        }
        return result;
    }
}

int fir_bandstop(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, float lowerEdgeInHz, float upperEdgeInHz, int firSize, int sampleRate) {
    int result = DSP_SUCCESS;

    //Error checking function inputs
    if (oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    else if (iNumSamples <= 2 || oNumSamples < 2 || lowerEdgeInHz >= upperEdgeInHz || lowerEdgeInHz <= 0 || upperEdgeInHz >= (sampleRate/2) || firSize >(iNumSamples / 2.0) || firSize <= 8) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        int i;
        int j;
        int k;
        int firShift = (firSize / 2.0);
        double cfL = lowerEdgeInHz / sampleRate;        // cf for LPF
        double cfH = upperEdgeInHz / sampleRate;        // cf for HPF
        int fftsize = 512;
        int binSize = fftsize / 2;
        //double* fft_ir = (double*)malloc(fftsize * sizeof(double));

        //Allocate memory for IR and WIR for both HPF and LPF and memory for Blackman window
        //All functions are the size of the firSize.
        double* IRL = (double*)malloc(firSize * sizeof(double));
        double* IRH = (double*)malloc(firSize * sizeof(double));
        double* Blackman = (double*)malloc(firSize * sizeof(double));
        double* WIRL = (double*)malloc(firSize * sizeof(double));
        double* WIRH = (double*)malloc(firSize * sizeof(double));

        //Generating sinc impulse response. fft_fir doesn't work
        for (i = 0; i < firSize; i++) {
            k = i - firShift;
            IRL[i] = 2 * cfL * sinc(twopi * cfL * k);

            //Converting IR from LPF to HPF by multiplying by (-1)  and using upperEdgeInHz cf
            IRH[i] = -2 * cfH * sinc(twopi * cfH * k);
            Blackman[i] = 0.42 - 0.5 * cos((twopi * i) / (firSize)) + 0.08 * cos(2.0 * ((twopi * i) / (firSize)));

            //Two separate windowed impulse responses, one for LPF one for HPF
            WIRL[i] = Blackman[i] * IRL[i];
            WIRH[i] = Blackman[i] * IRH[i];
        }

        //Adding 1 to center value of IR for HPF to complete the conversion from LPF to HPF
        WIRH[(firSize / 2)] += 1;

        //Commented out because fft_fir function does not work.
        //Cannot figure out why it doesn't work
        /*
        //Generate FFT impulse Response
        fft_fir(fftsize, lowerEdgeInHz, upperEdgeInHz, IR, sampleRate);

        //Generate blackman window to window the impulse response
        for (i = 0; i < firSize; i++) {
            Blackman[i] = 0.42 - 0.5 * cos((twopi * i) / (firSize)) + 0.08 * cos(2.0 * ((twopi * i) / (firSize)));
            WIR[i] = IR[i] * Blackman[i];
        }
        */

        char str[256];
        for (i = 0; i < firSize; i++) {
            sprintf_s(str, sizeof(str), "i = %d, WIRL = %f, WIRH = %f \n", i, WIRL[i], WIRH[i]);
            OutputDebugStringA(str);
        }

        //Convolve both WIR's with Input signal and store result sample values under accum and accum2
        double accum;
        double accum2;
        for (i = 0; i < iNumSamples; i++) {
            accum = 0;
            accum2 = 0;
            for (j = 0; j < firSize; j++) {
                if (i + j <= iNumSamples) {

                    //Simotaneously convolves WIR for LPF and WIR for HPF with input signal. 
                    //Adds both accum values at the ned

                    accum += WIRL[j] * iAudioPtr[i + j];
                    accum2 += WIRH[j] * iAudioPtr[i + j];
                }
                else {
                    accum = 0;
                };
            }
            oAudioPtr[i] = accum + accum2;
        }

        //Freeing memory for Blackman windowed function, 2 IR's and 2 WIR's
        free(Blackman);
        free(IRH);
        free(IRL);
        free(WIRH);
        free(WIRL);
        //free(fft_fir);
        return result;
    }
}

int fft_fir(int fftSize, float lo_freq, float hi_freq, double* out_ir, int sampleRate)
{
    int result = DSP_SUCCESS;
    int i;
    int numBins = fftSize / 2;
    int nyquist = sampleRate / 2;
    float binWidth = nyquist / numBins;

    std::vector<std::complex<float>> inputFrame(fftSize);
    std::vector<std::complex<float>> outputFrame(fftSize);

    // CREATE THE FREQ RESPONSE HERE. REMEMBER TO MIRROR EVERYTHING UP THE THE NYQUIST
    // ON THE OTHER SIDE, UP TO SAMPLE RATE

    float binEdge = 0;
    for (i = 0; i < numBins; i++) {
        binEdge = (i + 1) * binWidth;       //Upper edge of the bin (in Hz)
        if (binEdge < lo_freq) {
            inputFrame[i].real(1.0);
            inputFrame[fftSize - 1].real(1.0);
        }
        else {
            inputFrame[i].real(0.0);
            inputFrame[fftSize - i].real(0.0);
        }
    }

    for (i = 0; i < fftSize; i++) {
        inputFrame[i].imag(0.0);
    }

    // PERFORM THE IFFT
    //
    juce::dsp::FFT fft(log2(fftSize)); // the (#) is fftOrder. It's the exponent that 2 is raised to. 2^7 = 128, 2^8 = 256, etc...
    fft.perform(inputFrame.data(), outputFrame.data(), true); // this is an IFFT. When the last param is false it's an FFT.

    // pack amplitude and phase into arrays
    double* fftIR = (double*)malloc(fftSize * sizeof(double));
    for (i = 0; i < fftSize; i++)
    {
        fftIR[i] = (outputFrame[i].real());
        //printf("%d  %f\n", i, fftIR[i]);
    }

    // At this point, the IR is mirrored around the NYQUIST, with the peak of the sinc function at time 0.
    // It's like this: A B C D D C B A
    // we need to move the second half of the array before the first
    // we want this: D C B A A B C D
    for (i = 0; i < fftSize; i++) {
        if (i < (fftSize / 2)) {
            out_ir[i] = fftIR[i + (fftSize / 2)];
        }
        else {
            out_ir[i] = fftIR[i - (fftSize / 2)];
        }
    }
    return result;
}

void amp_response_fft(double* ir, int firSize, int fftSize, int sampleRate)
{
    //firSize needs to be limited to powers of 2
    //ir developed through sinc function

    int nyquist = sampleRate / 2;
    int numBins = fftSize / 2;
    float binWidth = nyquist / numBins;
    int i;

    // CREATE ARRAYS FOR COMPLEX VALUES (REAL+IMAG)
    //
    std::vector<std::complex<float>> inputFrame(fftSize);
    std::vector<std::complex<float>> outputFrame(fftSize);

    // Pack impulse response (ir) into complex data type for fft
    //
    for (i = 0; i < fftSize; i++)
    {
        if (i < firSize)               // original IR size can be smaller than frame size of fft analysis
            inputFrame[i] = ir[i];
        else
            inputFrame[i] = 0.0;
    }

    // PERFORM THE FFT
    //
    juce::dsp::FFT fft(log2(fftSize));  // fft wants the power of two... e.g. 9 (2^9 = 512) - must match frameSize
    fft.perform(inputFrame.data(), outputFrame.data(), false);

    // CONVERT FROM POLAR TO RECTANGULAR COORDINATED TO GET MAGNITUDE AND PHASE
    //
    float m = 0;
    float p = 0;
    for (i = 0; i < numBins; i++)
    {
        // this looks more complex then it is. it's just the math of triangles
        // remember, the real part is the x axis and the imaginary is the y axis
        // we get the magnitude by using the pythagorean theorum: c = sqrt(a^2 + b^2)
        // since we know sides a (real) and b (imaginary) of the triangle, we can use the tangent to computer the angle
        m = sqrt((outputFrame[i].real() * outputFrame[i].real()) + (outputFrame[i].imag() * outputFrame[i].imag()));
        p = atan(outputFrame[i].imag() / outputFrame[i].real());

        printf("bin %d  freq: %f  m: %f p: %f\n", i, i * binWidth, m, p);
    }
}

int iir_bpf(float* iAudioPtr, int iNumSamples, float* oAudioPtr, double cutoff, double bandwidth, int sampleRate) {
    int result = 0;
    int nyquist = (sampleRate / 2);

    //Error checking function inputs
    if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    } 
    else if (iNumSamples < 2 || cutoff <= 1 || cutoff > nyquist  || bandwidth <= 1 || ((cutoff - bandwidth) < 0) || ((cutoff + bandwidth) > nyquist)) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        int i;

        //Converting cutoff frequency and bandwidth to decimals between 0 and 0.5
        float decimalcutoff = cutoff / sampleRate;
        float decimalBW = bandwidth / sampleRate;

        //Calculating all coefficients and R and K values
        float R = 1 - 3 * (decimalBW);
        float K = ((1 - (2 * R * cos(2 * pi * decimalcutoff)) + (R * R)) / (2 - (2 * cos(2 * pi * decimalcutoff))));
        float a0 = 1 - K;
        float a1 = (2 * (K - R) * cos(2 * pi * decimalcutoff));
        float a2 = ((R * R) - K);
        float b1 = (2 * R * cos(2 * pi * decimalcutoff));
        float b2 = -(R * R);

        for (i = 0; i < iNumSamples; i++) {
            //If statement accounts for samples written that don't exist.
            if (i <= 3 || i >= (iNumSamples - 3)) {
                oAudioPtr[i] = 0;
            }

            //Formula from The Scientist and Engineer's Guide to DSP
            else {
                oAudioPtr[i] = (a0 * iAudioPtr[i]) + (a1 * iAudioPtr[i - 1]) + (a2 * iAudioPtr[i - 2]) + (b1 * oAudioPtr[i - 1]) + (b2 * oAudioPtr[i - 2]);
            }
            
            if (oAudioPtr[i] > 1.0) {
                oAudioPtr[i] = 1.0;
            }
        }
        return result;
    }

}

float bpf_amp_response(float centerFreqHz, float bandwidthHz, float analysis_freq, int sampleRate) {
    int result = 0;
    int nyquist = sampleRate / 2;

    //Error checking function inputs
    if (centerFreqHz <= 1 || centerFreqHz > nyquist || bandwidthHz <= 1 || ((centerFreqHz - bandwidthHz) < 0) ||
        ((centerFreqHz + bandwidthHz) > nyquist) || (analysis_freq < 2) || (analysis_freq >= nyquist)) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }
    if (result != DSP_SUCCESS) {
        return result;
    }

    else {

        int p = 0;      //sample number (used and reset multiple times)
        int nyquist = (sampleRate / 2);
        int sampspercycle = (sampleRate / analysis_freq);

        float maxamp = 0;
        float phase = 0.0;
        float phaseincrement = ((twopi * analysis_freq) / sampleRate);
        int size = (3 * sampspercycle);

        //Buffer to store all the recorded maxamp values for each sine wave freq after being passed through the FIR LPF
        float* oAudioPtr = (float*)malloc(size * sizeof(float));

        //Generates sine wave
        for (p; p < size; p++) {
            //Assigns the sample to the specified amplitude multiplied by the scalar value.
            oAudioPtr[p] = sinf(phase);
            //increments phase
            phase += phaseincrement;
        };

        //Filters sine wave and replaces it in same buffer (oAudioPtr)
        result = iir_bpf(oAudioPtr, size, oAudioPtr, centerFreqHz, bandwidthHz, sampleRate);

        //Check fir_lpf had no errors
        if (result != DSP_SUCCESS) {
            return result;
        }

        //Finds and stores maxamp of filtered sine wave. Only need to check half of a cycle to find maxamp
        for (p = 0; p <= (sampspercycle/2); p++) {
            if (oAudioPtr[p] >= maxamp) {
                maxamp = oAudioPtr[p];
            }
        }

        //Printf for some reason doesn't work on windows
        //Found this online to print frequency and maxamp value to output window
        char str[256];
        sprintf_s(str, sizeof(str), "frequency = %f, maxamp = %f \n", analysis_freq, maxamp);
        OutputDebugStringA(str);

        free(oAudioPtr);

        return result;
    }

}

int biquad_filter(float* iAudioPtr, int iNumSamples, float* oAudioPtr, double cutoffHz, double Q, short filterType, int sampleRate) {
    int result = 0;
    int nyquist = sampleRate / 2;

    //Error checking function inputs
    if (cutoffHz <= 1 || cutoffHz > nyquist || Q < 0 || Q > 1 || iNumSamples < 2) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }
    else if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        int i;
        //Second Order filter Design:

        float a0, a1, a2;
        float thetaC = twopi * (cutoffHz / sampleRate);
        float K = tanf(thetaC / 2.0);
        float W = K * K;
        float alpha = (1 + K) / (Q + W);

        //Denomiator for both LPF and HPF
        float b0 = 1.0;
        float b1 = 2.0 * ((W - 1) / alpha);
        float b2 = ((1 - K) / (Q + W)) / alpha;
     
        if (filterType == DSP_FILTERTYPE_LPF) {
            //Numerator for LPF
            a0 = W / alpha;
            a1 = 2.0 * W / alpha;
            a2 = a0;
        }
        else if (filterType == DSP_FILTERTYPE_HPF) {
            //Numerator for HPF
            a0 = (1.0 / alpha);
            a1 = -2.0 / alpha;
            a2 = a0;
        }
        else {
            result = DSP_INVALID_PARAMETER;
            return result;
        }

        for (i = 0; i < iNumSamples; i++) {
            oAudioPtr[i] = (b0 * iAudioPtr[i]) +
                (a1 * iAudioPtr[i - 1]) +
                (a2 * iAudioPtr[i - 2]) -
                (b1 * iAudioPtr[i - 1]) -
                (b2 * iAudioPtr[i - 2]);

            if (oAudioPtr[i] > 1) {
                oAudioPtr[i] = 1;
            }
        }

        return result;
    }

}

int biquad_amp_response(double cutoffHz, double Q, short filterType, int freqnum, int sampleRate) {
    int result = DSP_SUCCESS;
    int nyquist = (sampleRate / 2);

    //Error checking function inputs
    if (cutoffHz <= 1 || cutoffHz > nyquist || Q < 0 || Q > 1 || filterType != DSP_FILTERTYPE_HPF || filterType != DSP_FILTERTYPE_LPF || freqnum < 2 || freqnum > nyquist) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }

    if (result != DSP_SUCCESS) {
        return result;
    }
    else {
        int p;      //sample number (used and reset multiple times)
        int f;      //Frequency value incremented by value determined by freqnum

        int freqinc = (nyquist / freqnum);
        int ampsample = 0;
        int sampspercycle;

        float maxamp;
        float phase;
        float phaseincrement;
        //Buffer to store all the recorded maxamp values for each sine wave freq after being passed through the FIR LPF
        float* maxampbuffer = (float*)malloc(freqnum * sizeof(float));
        
        //Loop to generate sine wave at every freq of increment "freqinc"
        for (f = 1; f < nyquist; f += freqinc) {

            //Calculates samples per cycle (so we don't need to go through each cycle)
            sampspercycle = (sampleRate / f);

            //Allocate memory for 1 cycle of sine wave at specified frequency (f)
            float* oAudioPtr = (float*)malloc(sampspercycle * sizeof(float));

            //Calculates the phase increment.
            phase = 0.0;
            phaseincrement = ((twopi * f) / sampleRate);

            //Generates sine wave
            for (p = 0; p < sampspercycle; p++) {
                //Assigns the sample to the specified amplitude multiplied by the scalar value.
                oAudioPtr[p] = sinf(phase);
                //increments phase
                phase += phaseincrement;
            };

            //Filters sine wave and replaces it in same buffer (oAudioPtr)
            result = biquad_filter(oAudioPtr, sampspercycle, oAudioPtr, cutoffHz, Q, filterType, sampleRate);

            //Check biquad_filter had no errors
            if (result != DSP_SUCCESS) {
                return result;
            }

            //Resets maxamp value for each new freq
            maxamp = 0;

            //Finds and stores maxamp of filtered sine wave. Only need to check half of a cycle to find maxamp
            for (p = 0; p <= (sampspercycle/2); p++) {
                if (oAudioPtr[p] >= maxamp) {
                    maxamp = oAudioPtr[p];
                }
            }

            //Store maxamp value in maxampbuffer
            maxampbuffer[ampsample] = maxamp;
            ampsample++;
            free(oAudioPtr);
        }

        //Printf for some reason doesn't work on windows
        //Found this online to print frequency and maxamp value to output window
        char str[256];
        ampsample = 0;
        for (f = 1; f < nyquist; f += freqinc) {
            sprintf_s(str, sizeof(str), "frequency = %d, maxamp = %f \n", f, maxampbuffer[ampsample]);
            OutputDebugStringA(str);
            ampsample++;
        }

        //To test on mac:
        ampsample = 0;
        for (f = 1; f < nyquist; f += freqinc) {
            printf("frequency = %d, maxamp = %f \n", f, maxampbuffer[ampsample]);
            ampsample++;
        }
        free(maxampbuffer);
        return result;
    }

}

int dsp_pitchChange(float* iAudioPtr, int iNumSamples, float* oAudioPtr, int oNumSamples, float pitchRatio, int sampleRate) {
    int result = 0;
    int nyquist = sampleRate / 2;

    //Error checking function inputs
    if (iNumSamples <= 1 || oNumSamples <= 1 || oNumSamples != (iNumSamples * pitchRatio)) {
        result = DSP_INVALID_PARAMETER;
    }
    else if (sampleRate != 44100 && sampleRate != 48000) {
        result = DSP_ERR_UNKNOWN_SAMPLERATE;
    }
    else if (iAudioPtr == NULL || oAudioPtr == NULL) {
        result = DSP_NULL_POINTER;
    }
    if (result != DSP_SUCCESS) {
        return result;
    }

    else {
        int p;
        int j;
        int num;
        int dem;

        if (pitchRatio == float(0.5)) {
            num = 2;
            dem = 3;
        }
        else if(pitchRatio == float(0.6)) {
            num = 3;
            dem = 5;
        }
        else if (pitchRatio == float(0.7)) {
            num = 7;
            dem = 10;
        }
        else if (pitchRatio == float(0.8)) {
            num = 4;
            dem = 5;
        }
        else if (pitchRatio == float(0.9)) {
            num = 9;
            dem = 10;
        }
        else if (pitchRatio == float(1.0)) {
            num = 1;
            dem = 1;
        }
        else if (pitchRatio == float(1.1)) {
            num = 11;
            dem = 10;
        }
        else if (pitchRatio == float(1.2)) {
            num = 6;
            dem = 5;
        }
        else if (pitchRatio == float(1.3)) {
            num = 13;
            dem = 10;
        }
        else if (pitchRatio == float(1.4)) {
            num = 7;
            dem = 5;
        }
        else if (pitchRatio == float(1.5)) {
            num = 3;
            dem = 2;
        }
        else {
            result = DSP_INVALID_PARAMETER;
            return result;
        }

        int tempsize = iNumSamples * num;
        float* temp = (float*)malloc(tempsize * sizeof(float));
        
        //Initialize temp buffer with all zeros
        j = 0;
        for (j = 0; j < tempsize; j++) {
            temp[j] = 0;
        }

        //Multiply audio by numerator
        p = 0;
        for (j = 0; j < iNumSamples; j++) {
            temp[p] = iAudioPtr[j];
            p += num;
        }
        
        //Then divide audio by denominator
        p = 0;
        for (j = 0; j < oNumSamples; j++) {
            oAudioPtr[j] = temp[p];
            p += dem;
        }

        free(temp);
        return result;
    }
}



// ADD OTHER DSP FUNCTIONS HERE...




