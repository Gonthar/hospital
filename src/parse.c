//
// Created by maciek on 27.07.16.
//

#include "parse.h"

static const char * types[] = {
        "NEW_DISEASE_ENTER_DESCRIPTION",
        "NEW_DISEASE_COPY_DESCRIPTION",
        "CHANGE_DESCRIPTION",
        "PRINT_DESCRIPTION",
        "DELETE_PATIENT_DATA",
        "INVALID_COMMAND"
};

static char* readLine(){
    char * line = malloc(sizeof(char) * MAX_LINE_SIZE);
    int c;
    int i = 0;

    while(c != fgetc(stdin) != EOF && c != '\n'){
        line[i++] = (char)c;
    }
    return line;
}

enum CommandType determineCommandType(char * line){
    for(int i = 0; i < NUM_OF_VALID_COMMANDS; ++i){
        if(strcmp(line, types[i]) == 0){
            break;
        }
    }
    return ((enum CommandType) i);
}

Command * parseCommand(char * line){
    Command * command;
    char *type;

    type = strtok(line, " ");
    command->type = determineCommandType(type);
    switch (command->type) {
        case NEW_DISEASE_ENTER_DESCRIPTION: {
            command->arg1 = strtok(NULL, " ");
            command->arg2 = strtok(NULL, "\n");
        }
        case NEW_DISEASE_COPY_DESCRIPTION: {
            command->arg1 = strtok(NULL, " ");
            command->arg2 = strtok(NULL, "\n");
        }
        case CHANGE_DESCRIPTION: {
            command->arg1 = strtok(NULL, " ");
            command->arg2 = strtok(NULL, " ");
            command->arg3 = strtok(NULL, "\n");
        }
        case PRINT_DESCRIPTION: {
            command->arg1 = strtok(NULL, " ");
            command->arg2 = strtok(NULL, "\n");
        }
        case DELETE_PATIENT_DATA: {
            command->arg1 = strtok(NULL, "\n");
        }
        case INVALID_COMMAND: printError();
        default: printError(); assert(NULL);
    }
    return command;
}

Command * fetchCommand(){
    char * line = readLine();
    return parseCommand(line);
}