#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc,char* argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    if(argc>=3 && check_operation_type(argv[1][1])==e_encode)
    {
        
        if( read_and_validate_encode_args(argv, &encInfo)==e_failure)
        {
            printf("\n-------- SAMPLE INPUTS --------\n");
            printf("\n./a.out -e source_file.bmp secret_file.txt [output_file.bmp]\n");
            printf("./a.out -d source_file.bmp [output_file(.bmp .py .txt )]\n");
            printf("\n");
            
            return 0;
        }
        
        if(do_encoding(&encInfo)==e_failure)
        {
            printf("Error: Failed to do Encoding\n");
            return 0;
        }
        printf("\nEncoding is Done.\n");
        printf("\n");
        return 0;
            
        
    }
    else if(check_operation_type(argv[1][1])==e_decode)
    {
        if(read_and_validate_decode_args(argv, &decInfo)==e_failure)
        {
            printf("\n-------- SAMPLE INPUTS --------\n");
            printf("\n./a.out -e source_file.bmp secret_file.txt [output_file.bmp]\n");
            printf("./a.out -d source_file.bmp [output_file(.bmp .py .txt)]\n");
            printf("\n");
            return 0;
           // return e_failure;
        }
        
            
        if(do_decoding(&decInfo)==e_failure)
        {
            printf("Error: Failed to do decoding \n");
            return 0;

        }
        printf("\nDecoding is done.\n");
        printf("\n");
        return 0;
    
    }
    else
    {
        printf("\nInvalid input\n");
        printf("\n-------- SAMPLE INPUTS --------\n");
        printf("\n./a.out -e source_file.bmp secret_file.txt [output_file.bmp]\n");
        printf("./a.out -d source_file.bmp [output_file(.bmp .py .txt)]\n");
        printf("\n");
        return 0;
    }

   

    
    return 0;
}
OperationType check_operation_type(char opt)
{
    if(opt=='e')
        return e_encode;
    else if(opt=='d')
        return e_decode;
    else
        return e_unsupported;

}