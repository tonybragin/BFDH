//./BFDH 10 data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_size;

struct listnode {
    int mach;
    int time;
    int id;
    
    struct listnode *next;
};

struct listnode *hashtab[];

void hashtab_init(struct listnode **hashtab)
{
    int i;
    for (i = 0; i <= hash_size; i++) {
        hashtab[i] = NULL;
    }
}

struct listnode *hashtab_add(struct listnode **hashtab, int mach, int time, int id)
{
    struct listnode *node;
    
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->mach = mach;
        node->time = time;
        node->id = id;
        node->next = hashtab[mach];
        hashtab[mach] = node;
        return node;
    }
    
    return NULL;
}

struct listnode *hashtab_lookup(struct listnode **hashtab, int mach)
{
    struct listnode *node = hashtab[mach];
    
    if (node != NULL) {
        return node;
    }
    
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, int mach)
{
    struct listnode *node = hashtab[mach];
    struct listnode *new_head = node->next;
    hashtab[mach] = new_head;
    free(node);
    
}

struct listnode *lookup_insert(struct listnode **hashtab, int left_mach)
{
    struct listnode *node;
    
    for (; left_mach > 0; left_mach--) {
        node = hashtab_lookup(hashtab, left_mach);
        if (node != NULL) {
            return node;
        }
    }
    
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"\nERROR, must be 2 args: number of machines, name of file with data\n");
        exit(1);
    }
    
    hash_size = atoi(argv[1]);
    int mach, time, id;
    int max_time = 0, now_time, now_mach, left_mach;
    int count = 0;

    FILE *data, *schedule;
    data = fopen(argv[2], "r");
    schedule = fopen("schedule", "w");

    hashtab_init(hashtab);
    struct listnode *node = NULL;
    
    while (fscanf(data, "%d %d %d", &id, &mach, &time)){
        node = hashtab_add(hashtab, mach, time, id);
        count++;
    }
    fclose(data);
    
    while (count > 0) {
        left_mach = hash_size;
        now_time += max_time;
        max_time = 0;
        now_mach = 0;
        int f = 0;
        
        while (f != 1) {
            node = lookup_insert(hashtab, left_mach);
            if (node != NULL) {
                count--;
                fprintf(schedule, "%d %d %d %d %d\n", node->id, now_time, now_time + node->time, now_mach, now_mach + node->mach - 1);
                if (node->time > max_time) max_time = node->time;
                now_mach += node->mach;
                left_mach = hash_size - now_mach;
                hashtab_delete(hashtab, node->mach);
            }
            else f = 1;
        }
    }
    
    fprintf(schedule, "END\n\nid time_start time_end mach_start mach_end\n");
    fclose(schedule);
        
    return 0;
}
