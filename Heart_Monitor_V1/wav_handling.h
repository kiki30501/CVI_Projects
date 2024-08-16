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
#include <stdio.h>
#include <ansi_c.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//==============================================================================
// Constants
        
#define HEADER_SIZE 44 //the wav header size is 44 Bytes long

//==============================================================================
// Types

typedef unsigned char byte; //since im going to use this a lot i might as well give it an easier name to use.

// these useful unions if i want to easily refer to these values in
// some times as an int or sometimes as a byte.
typedef union{
  int int_value;
  byte int_bytes[4];
} int_data;

typedef union{
  short short_value;
  byte short_bytes[2];
} short_data;

// A struct to contain the values of the wav file header
typedef struct {
  char riff_id[4];            // usually: "RIFF". Marks the file as a riff file. Characters are each 1 byte long.
  int_data file_size;         // Size of the overall file - 8 bytes, in bytes (32-bit integer). Typically, youd fill this in after creation.
  char description_header[4]; // File Type Header. For our purposes, it always equals the string "WAVE".
  char subchuck1_id[4];       // = "fmt ". Format chunk marker. Includes trailing null
  int_data subchunk1_size;    // Length of format data as listed above
  short_data audio_format;    // Type of format (1 is PCM) - 2 byte integer
  short_data num_channels;    // Number of Channels - 2 byte integer
  int_data sample_rate;       // Sample Rate in Hz - 32 byte integer.
  int_data byte_rate;         // (Sample Rate * BitsPerSample * Channels) / 8.
  short_data block_align;     // (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo
  short_data bits_per_sample; // Bits per sample
  char subchunk2_id[4];       // = "data". data chunk header. Marks the beginning of the data section.
  int_data subchunk2_size;    // Size of the data section.
} wav_header;

typedef struct {
  wav_header header;
  short_data *data;
} wav_file;


//==============================================================================
// Global functions

wav_header DLLSTDCALL get_wav_header_from_file(FILE *fp);
byte * DLLSTDCALL read_wav_data(FILE *fp, wav_header wav, byte *data);
void DLLSTDCALL free_wav_data(wav_file wav);
wav_file DLLSTDCALL get_wav_from_file(FILE *fp, wav_header wav_head);
BOOL is_extended_RIFF(wav_header header);
int find_data_chunk(FILE *fp, wav_header header);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __wav_handling_H__ */
