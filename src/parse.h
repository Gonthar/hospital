//
// Created by maciek on 27.07.16.
//

#ifndef HOSPITAL_PARSE_H
#define HOSPITAL_PARSE_H

#define MAX_LINE_SIZE 1000
#define NUM_OF_VALID_COMMANDS 5

typedef enum CommandType{
    NEW_DISEASE_ENTER_DESCRIPTION,
    NEW_DISEASE_COPY_DESCRIPTION,
    CHANGE_DESCRIPTION,
    PRINT_DESCRIPTION,
    DELETE_PATIENT_DATA,
    INVALID_COMMAND
}CommandType;

typedef struct Command{
    enum CommandType type;
    char arg1[MAX_LINE_SIZE];
    char arg2[MAX_LINE_SIZE];
    char arg3[MAX_LINE_SIZE];
}Command;

Command * fetchCommand();
char * readLine();
Command * parseCommand(char * line);

#endif //HOSPITAL_PARSE_H
