//
// Created by maciek on 27.07.16.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "parse.h"
#include "messages.h"

static const char * types[] = {
        "NEW_DISEASE_ENTER_DESCRIPTION",
        "NEW_DISEASE_COPY_DESCRIPTION",
        "CHANGE_DESCRIPTION",
        "PRINT_DESCRIPTION",
        "DELETE_PATIENT_DATA",
        "INVALID_COMMAND"
};

char * readLine(){
    char * line = malloc(100 * sizeof(char));
    char * line_old = line;
    size_t max_length = 100;
    size_t length = 0;
    char c;

    if(line == NULL){
        return NULL;
    }

    for(;;){
        c = fgetc(stdin);
        if(c == EOF){
            free(line);
            return NULL;
        }

        if(++length == max_length){
            char * line_new = realloc(line_old, max_length *= 2);
            if(line_new == NULL){
                free(line_old);
                return NULL;
            }
            line = line_new + (line - line_old);
            line_old = line_new;
        }

        if((*line++ = c) == '\n'){
            break;
        }
    }
    *line = '\0';

    //printf("%s", line_old);
    return line_old;
}

enum CommandType determineCommandType(char * line){
    int i;
    for(i = 0; i < NUM_OF_VALID_COMMANDS; ++i){
        if(strcmp(line, types[i]) == 0){
            return ((enum CommandType) i);
        }
    }
    free(line);
    return ((enum CommandType) NUM_OF_VALID_COMMANDS); //invalid command
}

Command * parseCommand(char * line){
    Command * command = malloc(sizeof(Command));
    char *type;
    char *tmp;

    type = strtok(line, " ");
    command->type = determineCommandType(type);
    switch(command->type){
        case NEW_DISEASE_ENTER_DESCRIPTION: {
            tmp = strtok(NULL, " ");
            strcpy(command->arg1, tmp);
            tmp = strtok(NULL, "\n");
            strcpy(command->arg2, tmp);
            break;
        }
        case NEW_DISEASE_COPY_DESCRIPTION: {
            tmp = strtok(NULL, " ");
            strcpy(command->arg1, tmp);
            tmp = strtok(NULL, "\n");
            strcpy(command->arg2, tmp);
            break;
        }
        case CHANGE_DESCRIPTION: {
            tmp = strtok(NULL, " ");
            strcpy(command->arg1, tmp);
            tmp = strtok(NULL, " ");
            strcpy(command->arg2, tmp);
            tmp = strtok(NULL, "\n");
            strcpy(command->arg3, tmp);
            break;
        }
        case PRINT_DESCRIPTION: {
            tmp = strtok(NULL, " ");
            strcpy(command->arg1, tmp);
            tmp = strtok(NULL, "\n");
            strcpy(command->arg2, tmp);
            break;
        }
        case DELETE_PATIENT_DATA: {
            tmp = strtok(NULL, "\n");
            strcpy(command->arg1, tmp);
            break;
        }
        case INVALID_COMMAND: printError(); break;
        default: printError(); assert(NULL);
    }
    free(line);
    return command;
}

Command * fetchCommand(){
    char * line = readLine();
    if(line == NULL){
        return NULL;
    }
    return parseCommand(line);
}