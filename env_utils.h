//
// Created by savinykh-n on 25.07.2021.
//

#ifndef MINISHELL_ENV_UTILS_H
#define MINISHELL_ENV_UTILS_H
# define INT_MIN_MINISHELL -2147483646

char * find_env_by_key(char * str);
int get_int_from_env(char *key);

char **copy_env(char **orig_env);
void update_env(char* key, char *value);
void remove_env(char *key);
void print_env(char** env);


#endif //MINISHELL_ENV_UTILS_H
