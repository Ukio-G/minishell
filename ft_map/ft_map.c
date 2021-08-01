#include "ft_map/ft_map.h"

void ft_map_init(t_ft_map * map, size_t element_size)
{
    ft_vector_init(&map->values, element_size);
    ft_vector_init(&map->keys, sizeof(char*));
}

void ft_map_add(t_ft_map * map, char * key, void * value)
{
    char * key_allocated;
    size_t key_length;

    key_length = ft_strlen(key);
    if (key_length == 0)
        return;
    key_allocated = malloc(key_length);
    if (!key_allocated)
    {
        map->error = MALLOC_ERROR;
        print_error("ft_map key malloc failed");
        return;
    }
    ft_memcpy(key_allocated, key, key_length);
    ft_vector_add(&map->keys, &key_allocated);
    if (ft_vector_get_error(&map->keys) == MALLOC_ERROR)
    {
        free(key_allocated);
        return;
    }
    ft_vector_add(&map->values, value);
    if (ft_vector_get_error(&map->values) == MALLOC_ERROR)
    {
        free(key_allocated);
        return;
    }
}


void * ft_map_at(t_ft_map * map, char * key)
{
    int cntr;
    t_ft_pair v_key;

    v_key = ft_vector_find_str(&map->keys, key);
    if (v_key.second == 0)
        return 0;
    return ft_vector_at(&map->values, (size_t)v_key.first);
}