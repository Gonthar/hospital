//
// Created by maciek on 20.08.16.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "messages.h"


DiseaseList* initialiseDiseaseList(){
    DiseaseList* list = malloc(sizeof(DiseaseList));
    list->first = malloc(sizeof(Disease));
    list->first->prev = NULL;
    list->first->next = NULL;
    list->first->value = NULL;
    list->last = list->first;
    list->size = 0;
    return list;
}

PatientList* initialisePatientList(){ //first patient NULL initializes
    PatientList* list = malloc(sizeof(PatientList));
    list->first = malloc(sizeof(Patient));
    list->first->prev = NULL;
    list->first->next = NULL;
    list->first->history = NULL;
    list->last = list->first;
    list->size = 0;
    return list;
}

void freeDiseaseList(DiseaseList * list){
    Disease * tbfreed = list->last;
    while(list->last->prev != NULL){
        tbfreed = list->last;
        list->last = list->last->prev;
        free(tbfreed->value);
        free(tbfreed);
    }
    free(list->last); //dummy
    free(list);
}

void updateRefCounter(Disease * disease, DiseaseList * list){
    disease->reference_counter--;
    if(disease->reference_counter == 0){
        disease->prev->next = disease->next;
        if(disease->next != NULL){
            disease->next->prev = disease->prev;
        }
        if(list->last->value != NULL) {
            if (strcmp(list->last->value, disease->value) == 0) {
                list->last = list->last->prev;
            }
        }
        free(disease->value);
        free(disease);
        (list->size)--;
    }
}

void freePatientHistory(Patient * patient, DiseaseList * dlist){
    PatientHistory * history = patient->history;
    PatientHistory * tbdeleted;
    while(history != NULL){
        if(history->disease != NULL){
            updateRefCounter(history->disease, dlist);
        }
        tbdeleted = history;
        history = history->prev;
        free(tbdeleted);
    }
}

void freePatientList(PatientList * plist, DiseaseList * dlist){
    Patient * patient = plist->last;
    while(plist->last->prev != NULL){
        patient = plist->last;
        plist->last = plist->last->prev;
        freePatientHistory(patient, dlist);
        free(patient->name);
        free(patient);
    }
    free(plist->last); //dummy
    free(plist);
}

Disease * addNewDisease(DiseaseList * list, char* description){
    Disease * disease = malloc(sizeof(Disease));
    disease->value = malloc((strlen(description) + 1) * (sizeof(char)));
    strcpy(disease->value, description);
    disease->next = NULL;
    disease->prev = list->last;
    disease->reference_counter = 0;
    list->last->next = disease;
    list->last = disease;
    list->size++;
    return disease;
}

Patient * addNewPatient(PatientList* list, char* name, Disease* disease){
    Patient * patient = malloc(sizeof(Patient));
    patient->history = malloc(sizeof(PatientHistory));
    patient->name = malloc((strlen(name) + 1) * (sizeof(char)));
    strcpy(patient->name, name);
    patient->history->disease = disease;
    patient->history->prev = NULL;
    patient->disease_count = 1;
    patient->next = NULL;
    patient->prev = list->last;
    disease->reference_counter++;
    list->last->next = patient;
    list->last = patient;
    list->size++;
    return patient;
}

Patient * findPatient(PatientList* list, char* name){
    int i = 0;
    Patient * target = list->last;
    while(i < (list->size)){
        if(strcmp(name, target->name) == 0){
            return target;
        }else{
            ++i;
            target = target->prev;
        }
    }
    return NULL;
}

PatientHistory * findDisease(Patient * patient, char* n){
    int num = atoi(n);
    int i = patient->disease_count;
    PatientHistory * history = patient->history;
    if(i < num){
        return NULL;
    }
    while(i > num){
        i--;
        history = history->prev;
    }
    return history;
}

void addDiseaseToHistory(Patient * patient, Disease * disease){
    PatientHistory * new_disease = malloc(sizeof(PatientHistory));
    new_disease->disease = disease;
    new_disease->prev = patient->history;
    patient->history = new_disease;
    patient->disease_count++;
    disease->reference_counter++;
}

void newDiseaseEnterDescription(char* name, char* disease_description, DiseaseList * dlist, PatientList * plist){
    Disease* disease = addNewDisease(dlist, disease_description);
    Patient* patient = findPatient(plist, name);
    if(patient == NULL){
        addNewPatient(plist, name, disease);
    }else{
        addDiseaseToHistory(patient, disease);
    }
    ok();
}

void newDiseaseCopyDescription(char* name1, char* name2, PatientList * plist){
    Patient* patient2 = findPatient(plist, name2);
    if(patient2 == NULL || patient2->disease_count == 0) {
        printError(); return;
    }
    Disease * disease = patient2->history->disease;

    Patient * patient1 = findPatient(plist, name1);
    if(patient1 == NULL) {
        addNewPatient(plist, name1, disease);
    }else{
        addDiseaseToHistory(patient1, disease);
    }
    ok();
}

void changeDescription(char* name, char* n, char* disease_description, DiseaseList * dlist, PatientList * plist){
    Patient* patient = findPatient(plist, name);
    if(patient == NULL) {
        printError(); return;
    }else{
        PatientHistory* history = findDisease(patient, n);
        if(history == NULL) {
            printError(); return;
        }
        Disease* new_disease = addNewDisease(dlist, disease_description);
        new_disease->reference_counter++;
        updateRefCounter(history->disease, dlist);
        history->disease = new_disease;
    }
    ok();
}

void printDescription(char* name, char* n, PatientList * plist){
    Patient * patient = findPatient(plist, name);
    if(patient == NULL) {
        printError(); return;
    }else{
        PatientHistory * history = findDisease(patient, n);
        if(history == NULL){
            printError(); return;
        }else{
            printf("%s\n", history->disease->value);
        }
    }
}

void deletePatientData(char* name, PatientList * plist, DiseaseList * dlist){
    Patient * patient = findPatient(plist, name);
    if(patient == NULL) {
        printError(); return;
    }else{
        freePatientHistory(patient, dlist);
        patient->history = NULL;
        patient->disease_count = 0;
    }
    ok();
}