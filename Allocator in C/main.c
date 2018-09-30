#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    unsigned char* container;
    size_t size;
} arena_t;


typedef struct
{
    size_t next_block;
    size_t prev_block;
    size_t size;
    unsigned char data[0];
} __attribute__((packed)) arena_block_t;


arena_block_t* interpret_block(arena_t* arena, size_t offset)
{
    return (arena_block_t*)(arena->container + offset);
}


arena_block_t* interpret_block_user(arena_t* arena, size_t offset)
{
    return (arena_block_t*)(arena->container + offset - sizeof(arena_block_t));
}


size_t block_to_offset(arena_t* arena, arena_block_t* block)
{
    return (unsigned char*)block - arena->container;
}


void initialize(arena_t* arena, size_t n)
{
    arena->container =(unsigned char *)malloc(n*sizeof(unsigned char));
    arena->size = n;
}


void finalize(arena_t* arena)
{
    free(arena->container);
}


void dump(arena_t* arena)
{
    size_t k, i;

    for(k = 0 ; k < arena->size ; k += 16)
    {
        printf("%08X\t", k);

        for(i = 0 ; i < 16 && k + i < arena->size; ++i)
        {
            printf("%02X ", *(arena->container + k + i));

            if(i == 7)
                printf(" ");
        }
        printf("\n");
    }

    printf("%08X\n", arena->size);
}


size_t alloc(arena_t* arena, size_t n)
{
    arena_block_t* first_block = (arena_block_t*)(arena->container);

    /* initial allocation */
    if(first_block->next_block == 0)
    {
        arena_block_t* new_block = (arena_block_t*)(arena->container + sizeof(size_t));
        new_block->prev_block = 0;
        new_block->next_block = 0;
        new_block->size = sizeof(arena_block_t) + n;

        first_block->next_block = block_to_offset(arena, new_block);

        return new_block->data - arena->container;
    }

    /* start allocation */
    arena_block_t* second_block = interpret_block(arena, first_block->next_block);
    if(block_to_offset(arena, second_block) - sizeof(size_t) >= n + sizeof(arena_block_t))
    {
        arena_block_t* new_block = (arena_block_t*)(arena->container + sizeof(size_t));
        new_block->prev_block = block_to_offset(arena, first_block);
        new_block->next_block = block_to_offset(arena, second_block);
        new_block->size = sizeof(arena_block_t) + n;

        first_block->next_block = block_to_offset(arena, new_block);
        second_block->prev_block = block_to_offset(arena, new_block);

        return new_block->data - arena->container;
    }

    /* middle allocation */
    arena_block_t* left_block = second_block;
    arena_block_t* right_block = interpret_block(arena, left_block->next_block);
    while(left_block->next_block != 0)
    {
        if(block_to_offset(arena, right_block) - block_to_offset(arena, left_block) - left_block->size >= n + sizeof(arena_block_t))
        {
            arena_block_t* new_block = (arena_block_t*)(arena->container + block_to_offset(arena, left_block) + left_block->size);
            new_block->prev_block = block_to_offset(arena, left_block);
            new_block->next_block = block_to_offset(arena, right_block);
            new_block->size = sizeof(arena_block_t) + n;

            left_block->next_block = block_to_offset(arena, new_block);
            right_block->prev_block = block_to_offset(arena, new_block);

            return new_block->data - arena->container;
        }

        left_block = right_block;
        right_block = interpret_block(arena, left_block->next_block);
    }

    /* end allocation */
    arena_block_t* current_block = left_block;
    if(arena->size >= block_to_offset(arena, current_block) + current_block->size + n + sizeof(arena_block_t))
    {
        arena_block_t* new_block = (arena_block_t*)(arena->container + block_to_offset(arena, current_block) + current_block->size);
        new_block->prev_block = block_to_offset(arena, current_block);
        new_block->next_block = 0;
        new_block->size = sizeof(arena_block_t) + n;

        current_block->next_block = block_to_offset(arena, new_block);

        return new_block->data - arena->container;
    }

    return 0;
}


void free_block(arena_t* arena, size_t pos)
{
    arena_block_t* current_block = interpret_block_user(arena, pos);
    arena_block_t* prev_block = interpret_block(arena, current_block->prev_block);
    arena_block_t* next_block = interpret_block(arena, current_block->next_block);

    prev_block->next_block = block_to_offset(arena, next_block);
    if(block_to_offset(arena, next_block) != 0)
    {
        next_block->prev_block = block_to_offset(arena, prev_block);
    }
}


void fill(arena_t* arena, size_t start, size_t n, unsigned char val)
{
    unsigned char* i;
    for(i = arena->container + start ; i < arena->container + start + n; ++i)
        *i = val;
}


void show_free(arena_t* arena)
{
    size_t nr = 0;
    arena_block_t* first_block = interpret_block(arena, 0);
    arena_block_t* block = interpret_block(arena, first_block->next_block);
    arena_block_t* last_block = first_block;
    size_t total = arena->size - sizeof(size_t);
    size_t last_block_end = sizeof(size_t);
    while(block_to_offset(arena, block) != 0)
    {
        if(block_to_offset(arena, block) != last_block_end)
        {
            nr++;
        }
        last_block_end = block_to_offset(arena, block) + block->size;

        total -= block->size;
        last_block = block;
        block = interpret_block(arena, block->next_block);
    }
    if(block_to_offset(arena, last_block) + last_block->size < arena->size)
        nr++;
    printf("%d blocks (%d bytes) free\n", nr, total);
}


void show_usage(arena_t* arena)
{
    size_t nr = 0, fr = 0;
    arena_block_t* first_block = interpret_block(arena, 0);
    arena_block_t* block = interpret_block(arena, first_block->next_block);
    arena_block_t* last_block = first_block;
    size_t total = sizeof(size_t);
    size_t total_user = 0;
    size_t last_block_end = sizeof(size_t);
    while(block_to_offset(arena, block) != 0)
    {
        if(block_to_offset(arena, block) != last_block_end)
        {
            fr++;
        }
        last_block_end = block_to_offset(arena, block) + block->size;

        nr++;
        total += block->size;
        total_user += block->size - sizeof(arena_block_t);
        last_block = block;
        block = interpret_block(arena, block->next_block);
    }

    if(block_to_offset(arena, last_block) + last_block->size < arena->size)
        fr++;

    printf("%d blocks (%d bytes) used\n",  nr, total_user);
    printf("%d%% efficiency\n", 100 * total_user / total);

    if(nr)
        printf("%d%% fragmentation\n", 100 * (fr-1)/nr);
    else printf("0%% fragmentation\n");
}


void show_allocations(arena_t* arena)
{
    size_t last_block_end = sizeof(size_t);
    arena_block_t* first_block = interpret_block(arena, 0);
    arena_block_t* block = interpret_block(arena, first_block->next_block);
    arena_block_t* last_block = first_block;

    printf("OCCUPIED %d bytes\n", sizeof(size_t));

    while(block_to_offset(arena, block) != 0)
    {
        if(block_to_offset(arena, block) != last_block_end)
        {
            printf("FREE %d bytes\n", block_to_offset(arena, block) - last_block_end);
        }

        printf("OCCUPIED %d bytes\n", block->size);

        last_block_end = block_to_offset(arena, block) + block->size;
        last_block = block;
        block = interpret_block(arena, block->next_block);
    }

    if(block_to_offset(arena, last_block) == 0)
    {
        printf("FREE %d bytes\n", arena->size - sizeof(size_t));
    }
    else
    {
        if(block_to_offset(arena, last_block) + last_block->size < arena->size)
        {
            printf("FREE %d bytes\n", arena->size - block_to_offset(arena, last_block) - last_block->size);
        }
    }
}


void show_map(arena_t* arena, size_t length)
{
    printf("%d\n", length);

    size_t last_block_end = sizeof(size_t);
    arena_block_t* first_block = interpret_block(arena, 0);
    arena_block_t* block = interpret_block(arena, first_block->next_block);
    arena_block_t* last_block = first_block;

    size_t current_character = 0;
    size_t k = 0;

    for(k = 0 ; k < sizeof(size_t) ; ++k)
    {
        printf("*");
        current_character++;

        if(current_character % length == 0)
            printf("\n");
    }

    while(block_to_offset(arena, block) != 0)
    {
        if(block_to_offset(arena, block) != last_block_end)
        {
            for(k = 0 ; k < block_to_offset(arena, block) - last_block_end; ++k)
            {
                printf(".");
                current_character++;

                if (current_character % length == 0)
                    printf("\n");
            }
        }

        for(k = 0 ; k < block->size ; ++k)
        {
            printf("*");
            current_character++;

            if(current_character % length == 0)
                printf("\n");
        }

        last_block_end = block_to_offset(arena, block) + block->size;
        last_block = block;
        block = interpret_block(arena, block->next_block);
    }

    if(block_to_offset(arena, last_block) == 0)
    {
        for(k = 0 ; k < arena->size - sizeof(size_t) ; ++k)
        {
            printf(".");
            current_character++;

            if(current_character % length == 0)
                printf("\n");
        }
    }
    else
    {
        if(block_to_offset(arena, last_block) + last_block->size < arena->size)
        {
            for(k = 0 ; k < arena->size - block_to_offset(arena, last_block) - last_block->size ; ++k)
            {
                printf(".");
                current_character++;

                if(current_character % length == 0)
                    printf("\n");
            }
        }
    }
    printf("\n");
}


int main()
{
    arena_t arena = {0};
    char s[30];
    while(fgets(s, 30, stdin)!=NULL)
    {
        char cmd[32];
        sscanf(s, "%s", cmd);
        size_t offset = strlen(cmd);

        if(!strcmp(cmd, "INITIALIZE"))
        {
            size_t n;
            sscanf(s + offset, "%d", &n);
            initialize(&arena, n);
        }
        else if(!strcmp(cmd, "FINALIZE"))
        {
            finalize(&arena);

            return 0;
        }
        else if(!strcmp(cmd, "DUMP"))
        {
            dump(&arena);
        }
        else if(!strcmp(cmd, "ALLOC"))
        {
            size_t n;
            sscanf(s + offset, "%d", &n);
            printf("%d\n", alloc(&arena, n));
        }
        else if(!strcmp(cmd, "FILL"))
        {
            size_t start, n, value;
            sscanf(s + offset, "%d %d %d", &start, &n, &value);
            fill(&arena, start, n, value);
        }
        else if(!strcmp(cmd, "FREE"))
        {
            size_t start;
            sscanf(s + offset, "%d", &start);
            free_block(&arena, start);
        }
        else if(!strcmp(cmd, "SHOW"))
        {
            sscanf(s + offset, "%s", cmd);
            if(!strcmp(cmd, "FREE"))
                show_free(&arena);
            else if(!strcmp(cmd, "USAGE"))
                show_usage(&arena);
            else if(!strcmp(cmd, "ALLOCATIONS"))
                show_allocations(&arena);
            else if(!strcmp(cmd, "MAP"))
            {
                offset += strlen(cmd);
                offset += 2;

                size_t length;
                sscanf(s + offset, "%d", &length);
                show_map(&arena, length);
            }
        }
    }
    return 0;
}
