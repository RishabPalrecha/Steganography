#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"


/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    //printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    //printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}


Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
   char *dot=strchr(argv[2],'.');
   if(dot == NULL || strcmp(dot,".bmp") != 0)
   {
    printf("Error : Source file should be .bmp file\n");
    return e_failure;
   }
   encInfo -> src_image_fname = argv[2];

   encInfo -> secret_fname = argv[3];

   if(argv[4]==NULL)
    {                     
        encInfo -> stego_image_fname = "output.bmp";
    }
    else
    {
       char *dot1 = strchr(argv[4],'.');     

        if(dot1 == NULL || (strcmp(dot1,".bmp") != 0)){
            printf("Error : Output file must be .bmp file\n");
            return e_failure;
        }

        encInfo->stego_image_fname = argv[4];
    }

    if(open_files(encInfo) == e_failure){
        printf("File not opened\n");
        return e_failure;
    }
    
    return e_success;
}


Status do_encoding(EncodeInfo *encInfo)
{
    /*

        -> call check_capacity(encInfo) == e_failure
            if yes,print error ,return e_failure;

         -> call copy_bmp_header(src_file,dest_file) == e_success
            -> if not,print error msg,return e_failure;

        -> Call encode_magic_string(MAGIC_STRING,encInfo) == e_failure
            ->if yes,print error msg,return e_failure
        
        -> call encode_secret_file_size()
    
    
    
    
    */

}


Status check_capacity(EncodeInfo *encInfo)
{
    /*
        -> store in structure member as image_capacity = call get_image_size_for_bmp(encodeInfo -> fptr_src_image)
        
        -> call get_file_size(encode -> fptr_secret)
            -> size_secret_file = get_file_size()

        -> check((14 + size_secret_file) * 8) > image_capacity
            ->return e_failure

       
        return e_success;
    
    */

    encInfo -> image_capacity = get_image_size_for_bmp(encInfo ->  fptr_src_image);

    encInfo -> size_secret_file = get_file_size(encInfo -> fptr_secret);

    if ( ((14 + encInfo->size_secret_file) * 8) > encInfo -> image_capacity)
    {
        printf("Error : Secret file size is bigger than .bmp file\n");
        return e_failure;
    }

    return e_success;

}

uint get_file_size(FILE *fptr)
{
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);

}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    /*
    -> move file pointers to SEEK_SET position using rewind
    -> declare a buffer of 54 bytes
    ->Read from src_file & store 54bytes in a buffer
    -> Write to dest_file 
    -> Validate the 

    ->return e_success 
    */
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    /*
    ->declare a buffer of 8 bytes
    ->LOOp for strlen(magic_string) 2 times
    -> read 8 bytes from source file into buffer

    encode_byte_to_lsb(magic_string[1],buffer)
    write the encoded buff to output_file

    -> return e_success
    
    */

}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    /*
        for(int i=7;i>=0;i++)
        {
            ->get the ith bit ,check if it is  set or not
                -> if set, set the LSB of image_buffer[]
                -> if clear,clear the LSB of image_buffer[]
        }
    
    
    
    */

}



Status encode_secret_file_extn_size(EncodeInfo *encInfo)
{
    /*
    -> char *dot=strchr(secret_file,'.')
    ->strcpy(extn_secret_file,dot);
    -> declare buffer for 32 bytes
    -> read 32 bytes from src_file to buff
    ->call encode_size_to_lsb
    
    */

}

Status encode_size_to_lsb( FILE *fptr_src_image, FILE *fptr_stego_image)
{

}