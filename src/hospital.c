//
// Created by maciek on 27.07.16.
//

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "structure.h"
#include "messages.h"

static const char * types[] = {
        "NEW_DISEASE_ENTER_DESCRIPTION",
        "NEW_DISEASE_COPY_DESCRIPTION",
        "CHANGE_DESCRIPTION",
        "PRINT_DESCRIPTION",
        "DELETE_PATIENT_DATA",
        "INVALID_COMMAND"
};

int main(int argc, char *argv[]){
    bool v = false;

    if(argc > 1){
        if(strcmp(argv[1], "-v") == 0){
            v = true;
        }else{
            wrongArgument();
            return 1;
        }
    }

    DiseaseList * dlist = initialiseDiseaseList();
    PatientList * plist = initialisePatientList();

    Command * command = fetchCommand();
    while(command != NULL){
        switch(command->type){
            case NEW_DISEASE_ENTER_DESCRIPTION: {
                newDiseaseEnterDescription(command->arg1, command->arg2, dlist, plist);
                break;
            }
            case NEW_DISEASE_COPY_DESCRIPTION: {
                newDiseaseCopyDescription(command->arg1, command->arg2, plist);
                break;
            }
            case CHANGE_DESCRIPTION: {
                changeDescription(command->arg1, command->arg2, command->arg3, dlist, plist);
                break;
            }
            case PRINT_DESCRIPTION: {
                printDescription(command->arg1, command->arg2, plist);
                break;
            }
            case DELETE_PATIENT_DATA: {
                deletePatientData(command->arg1, plist, dlist);
                break;
            }
            case INVALID_COMMAND: {
                printError();
                break;
            }
            default: {
                assert(NULL);
            }
        }

        if(v){
            fprintf(stderr, "DESCRIPTIONS: %d\n", dlist->size);
        }
        free(command);
        command = fetchCommand();
    }
    freePatientList(plist, dlist);
    freeDiseaseList(dlist);
    return 0;
};