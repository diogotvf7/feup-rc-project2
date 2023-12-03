#include <stdio.h>
#include <stdlib.h>

#include "download.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <url>\n", argv[0]);
        exit(1);
    }

    return download(argv[1]);
}