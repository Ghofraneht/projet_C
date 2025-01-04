#include "patient.h"
#include <stdio.h>
#include <string.h>

void afficher_patient(Patient p) {
    printf("Patient: %s, Age: %d\n", p.nom, p.age);
}

void ajouter_patient(Patient *p, int id, const char *nom, int age) {
    p->id = id;
    strcpy(p->nom, nom);
    p->age = age;
}

void modifier_patient(Patient *p, const char *nouveau_nom, int nouveau_age) {
    strcpy(p->nom, nouveau_nom);
    p->age = nouveau_age;
}

void supprimer_patient(Patient *p) {
    p->id = 0;
    strcpy(p->nom, "");
    p->age = 0;
}
