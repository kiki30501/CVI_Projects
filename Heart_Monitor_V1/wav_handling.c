/*=============================================================================================*/

#include "wav_handling.h"

/*=============================================================================================*/

static int data_offset = 0;

/*=============================================================================================*/

wav_header DLLSTDCALL get_wav_header_from_file(FILE *fp) // Assumes the system is little endian
{
    wav_header wav;
    fread(&wav, HEADER_SIZE, 1, fp);
    wav.file_size.int_value += 8;
    if (is_extended_RIFF(wav))
    {
        data_offset = find_data_chunk(fp, wav);
        if (data_offset == -1)
            printf("darn");
        fseek(fp, HEADER_SIZE + data_offset, SEEK_SET);
        fread(&wav.subchunk2_id, 4, 1, fp);
        fread(&wav.subchunk2_size, 4, 1, fp);
    }
    else data_offset = 0;
    return wav;
}

/*=============================================================================================*/

byte * DLLSTDCALL read_wav_data(FILE *fp, wav_header wav, byte *data)
{
    unsigned int buff_size = wav.subchunk2_size.int_value;
    fseek(fp, HEADER_SIZE + data_offset, SEEK_SET);
    fread(data, buff_size, 1, fp);
    return data;
}

/*=============================================================================================*/

void DLLSTDCALL free_wav_data(wav_file wav)
{
    free(wav.data);
    return;
}

/*=============================================================================================*/

wav_file DLLSTDCALL get_wav_from_file(FILE *fp, wav_header wav_head)
{
    wav_file wav;
    wav.header = wav_head;
    wav.data = (short_data *) malloc(wav_head.subchunk2_size.int_value);
    read_wav_data(fp, wav_head, (byte *) wav.data);
    return wav;
}

/*=============================================================================================*/

BOOL is_extended_RIFF(wav_header header)
{
    // Checks if the file is an EXTENDED RIFF file. meaning it has additional chunks.
    return memcmp(header.subchunk2_id, "data", 4);
}

/*=============================================================================================*/

int find_data_chunk(FILE *fp, wav_header header)
{
    // Finds the data chuck in the file and returns the offset from the beginning of the file.
    // If the file is an extended RIFF file, we need to create an offset for the data chuck location.
    char test_list[5];
    memcpy (test_list, header.subchunk2_id, 4);
    test_list[4] = '\0';
  
    if (strcmp("LIST", test_list) == 0)
        return header.subchunk2_size.int_value;
    else
    {
        fseek(fp, 0, SEEK_SET);
        char chunk_id[4];
        int chunk_size;
        while (fread(chunk_id, 4, 1, fp) == 1)
        {
            fread(&chunk_size, 4, 1, fp);
            if (chunk_id == "data")
                return ftell(fp);
            fseek(fp, header.block_align.short_value, SEEK_CUR);
        }
    }
    return -1; // could not find the data chunk
}

/*=============================================================================================*/