//
// Created by maciek on 20.08.16.
//

#ifndef HOSPITAL_STRUCTURE_H
#define HOSPITAL_STRUCTURE_H

typedef struct Disease{
    char* value;
    struct Disease* next;
    struct Disease* prev;
    int reference_counter;
}Disease;

typedef struct DiseaseList{
    struct Disease* first;
    struct Disease* last;
    int size;
}DiseaseList;

typedef struct PatientHistory{
    struct Disease* disease;
    struct PatientHistory* prev;
}PatientHistory;

typedef struct Patient{
    char* name;
    struct PatientHistory* history;
    struct Patient* next;
    struct Patient* prev;
    int disease_count;
}Patient;

typedef struct PatientList{
    struct Patient* first;
    struct Patient* last;
    int size;
}PatientList;

DiseaseList * initialiseDiseaseList();

PatientList * initialisePatientList();

void freeDiseaseList(DiseaseList * list);

void freePatientList(PatientList * plist, DiseaseList * dlist);

void newDiseaseEnterDescription(char* name, char* disease_description, DiseaseList * dlist, PatientList * plist);

void newDiseaseCopyDescription(char* name1, char* name2, PatientList * plist);

void changeDescription(char* name, char* n, char* disease_description, DiseaseList * dlist, PatientList * plist);

void printDescription(char* name, char* n, PatientList * plist);

void deletePatientData(char* name, PatientList * plist, DiseaseList * dlist);

#endif //HOSPITAL_STRUCTURE_H