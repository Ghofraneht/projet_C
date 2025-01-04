#ifndef PATIENT_H
#define PATIENT_H

typedef struct {
    int id;
    char nom[100];
    int age;
} Patient;

void afficher_patient(Patient p);
void ajouter_patient(Patient *p, int id, const char *nom, int age);
void modifier_patient(Patient *p, const char *nouveau_nom, int nouveau_age);
void supprimer_patient(Patient *p);
#endif
