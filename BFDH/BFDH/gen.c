//./gen 10 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int generate_id()
{
    int r = (unsigned int)rand();
    if (r > 1000) r %= 1000;
    if (r < 100) r += 100;
    return r;
}

int generate_int(int n)
{
    return ((int)rand() % n / 2) + 1;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr,"\nERROR, must be 2 args: number of machines, number of generations\n");
        exit(1);
    }
    
    int n = atoi(argv[1]);
    int count = atoi(argv[2]);
    
    FILE *file;
    file = fopen("data", "w");
    
    srand(time(NULL));
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %d %d\n", generate_id(), generate_int(n), generate_int(n));
    }
    fprintf(file, "END\n\nid mach time\n\n");
    
    return 0;
}
