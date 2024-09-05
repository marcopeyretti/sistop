
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "builtin.h"
#include <unistd.h>

       int chdir(const char *path);

static bool invrep_cmd(scommand self){
    return self!=NULL;
}
static bool invrep_pipe (pipeline self){
    return self != NULL;
}

bool builtin_is_internal(scommand cmd){
    assert(invrep_cmd(cmd));
    char *cd="cd",*help="help",*exit="exit";
        char *com= scommand_front(cmd);
    if(com==cd || com==help || com==exit) return true;
    return false;
}


bool builtin_alone(pipeline p){
    assert(invrep_pipe(p));
    if(pipeline_length(p)==1 && builtin_is_internal(pipeline_front(p))) return true;
    return false;
}

    

/*
 * Indica si el pipeline tiene solo un elemento y si este se corresponde a un
 * comando interno.
 *
 * REQUIRES: p != NULL
 *
 * ENSURES:
 *
 * builtin_alone(p) == pipeline_length(p) == 1 &&
 *                     builtin_is_internal(pipeline_front(p))
 *
 *
 */

void builtin_run(scommand cmd){
    assert(builtin_is_internal(cmd));
    char *cd="cd",*help="help",*exit="exit";
    char *com= scommand_front(cmd);
    if(com==cd){
        scommand_pop_front(cmd);
        char *READ = scommand_to_string(cmd);
        chdir(READ);
    }
    else if(com==help){
        printf("\t\t MYBASH\n");
        printf("Autores: \nMarco Peyretti\n Valentin Luna\n Lucas Cuadrado\n Ludmila Cassano\n");
        printf("Comandos Internos:\n cd:permite el movimiento entre directorios\n help:da informacion util sobre el shell\n exit:cierra el shell\n");
    }
    else if(com==exit){
        system(exit);
    }
}
/*
 * Ejecuta un comando interno
 *
 * REQUIRES: {builtin_is_internal(cmd)}
 *
 */
