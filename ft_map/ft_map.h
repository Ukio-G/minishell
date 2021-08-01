#ifndef MINIRT_FT_MAP_H
#define MINIRT_FT_MAP_H

#include "ft_vector.h"

typedef enum e_ft_vector_errors t_ft_map_error ;

typedef struct s_ft_map
{
    t_ft_vector values;
    t_ft_vector keys;

    t_ft_map_error error;
    void * iterator;
} t_ft_map;

void ft_map_init(t_ft_map * map, size_t element_size);
void ft_map_add(t_ft_map * map, char * key, void * value);
void *ft_map_at(t_ft_map * map, char * key);

#endif //MINIRT_FT_MAP_H
