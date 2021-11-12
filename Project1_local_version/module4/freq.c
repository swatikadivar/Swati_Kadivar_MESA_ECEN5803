#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int freq_detect(int *data, int size) //size = 999
{
    printf("size = %d\n", size);
    bool is_pos = false;
    int i = 0;
    int zero_cross = 0;
    if(data[0] < 0x7FFF)
    {
        is_pos = true;
    }
    
    while(size--) {
        int value = data[++i];
        if(is_pos && value > 0x7FFF)
        {
            is_pos = false;
            zero_cross++;
        }
        else if(!is_pos && value < 0x7FFF)
        {
            is_pos = true;
            zero_cross++;
        }
    }
    
    printf("freq*2 = %d\n", zero_cross);
    
    return (zero_cross/2);
    
}

int main()
{
    FILE * file;
    const char *filename = "ECEN5803Data3.txt";
    file = fopen( filename , "r");
    char line[7];
    int num[1000];
    int *p = num;
    int j = 0;

    while (fgets((line), 128, file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        num[j++] = (int)strtol(line, NULL, 16);
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);
    
    for(int i = 0; i < 1000; i++)
    {
        printf("id:%d, num:%d\n", i, num[i]); 
    }
    
    int freq = freq_detect(num, 999);
    printf("freq = %d\n", freq);

    return 0;
}