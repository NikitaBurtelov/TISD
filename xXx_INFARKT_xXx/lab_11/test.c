#include "my_snprintf.h"

int main(void)
{
    char buffer[100], buffer1[100];
    long cx, cx1;

    cx = my_snprintf(buffer1,  100, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", -600, -30000000000,
                    (short)-12, 8, 83123, (short)8, 160301, 155555555, (short)17, 'c', "cccasdsaw1e");

    cx1 = snprintf  (buffer, 100, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", -600, -30000000000,
                    (short)-12, 8, 83123, (short)8, 160301, 155555555, (short)17, 'c', "cccasdsaw1e");

    if(strcmp(buffer, buffer1) || cx1 != cx)
    {
        printf("Test #1\n Expected:\n%s\n Real:\n%s\n strcmp value %d, (cx;cx1) == (%ld,%ld) , return code -1\n",  buffer, buffer1, strcmp(buffer, buffer1), cx,cx1);
        return -1;
    }

    cx = my_snprintf(buffer1, 50, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", -600, -30000000000,
                  (short)-12, 8, 83123, (short)8, 160301, 155, (short)17, 'c', "cccasdsaw1e");

    cx1 = snprintf(buffer, 50, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", -600, -30000000000,
                   (short)-12, 8, 83123, (short)8, 160301, 155, (short)17, 'c', "cccasdsaw1e");

    if(strcmp(buffer, buffer1) || cx1 != cx)
    {
        printf("Test #2\n Expected:\n%s\n Real:\n%s\n strcmp value %d, (cx;cx1) == (%ld,%ld) , return code -1\n",  buffer, buffer1, strcmp(buffer, buffer1), cx,cx1);
        return -1;
    }

    cx = my_snprintf(buffer1,  100, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", 600, 30000000000,
                    (short)12, 8, 83123, (short)8, 160301, 155, (short)17, 'c', "cccasdsaw1e");

    cx1 = snprintf  (buffer, 100, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", 600, 30000000000,
                    (short)12, 8, 83123, (short)8, 160301, 155, (short)17, 'c', "cccasdsaw1e");

    if(strcmp(buffer, buffer1) || cx1 != cx)
    {
        printf("Test #3\n Expected:\n%s\n Real:\n%s\n strcmp value %d, (cx;cx1) == (%ld,%ld) , return code -1\n",  buffer, buffer1, strcmp(buffer, buffer1), cx,cx1);
        return -1;
    }

    cx = my_snprintf(buffer1, 50, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", 600, 30000000000,
                  (short)12, 8, 83123, (short)8, 160301, 155, (short)17, 'c', "cccasdsaw1e");

    cx1 = snprintf(buffer, 50, "Hi, here are %d,%ld,%hd,%o,%o,%o,%x,%x,%x,%c,%s!", 600, 30000000000,
                   (short)12, 8, 83123, (short)8, 160301, 155, (short)17, 'c', "cccasdsaw1e");

    if(strcmp(buffer, buffer1) || cx1 != cx)
    {
        printf("Test #4\n Expected:\n%s\n Real:\n%s\n strcmp value %d, (cx;cx1) == (%ld,%ld) , return code -1\n",  buffer, buffer1, strcmp(buffer, buffer1), cx,cx1);
        return -1;
    }

    printf("Return code 0\n");
    return 0;
}
