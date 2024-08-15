//==============================================================================
//
// Title:       wav_handling.h
// Purpose:     A short description of the interface.
//
// Created on:  16/08/2024 at 00:37:27 by Reshef Schachter.
// Copyright:   Afeka College of Engineering. All Rights Reserved.
//
//==============================================================================

#ifndef __wav_handling_H__
#define __wav_handling_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
        
#define HEADER_SIZE 44 //the wav header size is 44 Bytes long

//==============================================================================
// Types

typedef unsigned char byte; //since im going to use this a lot i might as well give it an easier name to use.

// these useful unions if i want to easily refer to these values in
// some times as an int or sometimes as a byte.
union int_data {
  int int_value;
  byte int_bytes[4];
};
union short_data {
  short short_value;
  byte short_bytes[2];
};

// A struct to contain the values of the wav file header
struct header_struct {
  char chunk_id[4];                   // usually: "RIFF". Marks the file as a riff file. Characters are each 1 byte long.
  union int_data chunk_size;          // Size of the overall file - 8 bytes, in bytes (32-bit integer). Typically, you’d fill this in after creation.
  char format[4];                     // File Type Header. For our purposes, it always equals “WAVE”.
  char subchunk1_id[4];               // = "fmt ". Format chunk marker. Includes trailing null
  union int_data subchunk1_size;      // Length of format data as listed above
  union short_data audio_format;      // Type of format (1 is PCM) - 2 byte integer
  union short_data num_channels;      // Number of Channels - 2 byte integer
  union int_data sample_rate;         // Sample Rate in Hz - 32 byte integer.
  union int_data byte_rate;           // (Sample Rate * BitsPerSample * Channels) / 8.
  union short_data block_align;       // (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo
  union short_data bits_per_sample;   // Bits per sample
  char subchunk2_id[4];               // = "data". “data” chunk header. Marks the beginning of the data section.
  union int_data subchunk2_size;      // Size of the data section.
};

//==============================================================================
// Global functions

int DLLIMPORT Define_Your_Functions_Here (int x);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __wav_handling_H__ */
