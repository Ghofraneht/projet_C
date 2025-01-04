#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int ID;
    char nom[50];
    char specialite[50];
    char adresse[100];
    char numero_telephone[20];
} Docteur;

typedef struct {
    int ID;
    char nom[50];
    int age;
    char adresse[100];
    char numero_telephone[20];
} Patient;

// Fonctions utilitaires pour valider les entrées
int valider_id() {
    int id;
    printf("Saisir l'ID : ");
    scanf("%d", &id);
    getchar();
    while (id <= 0) {
        printf("ID invalide. Veuillez entrer un entier positif : ");
        scanf("%d", &id);
        getchar();
    }
    return id;
}

void valider_numero(char *numero) {
    int valide = 0;
    while (!valide) {
        printf("Saisir le numéro de téléphone : ");
        fgets(numero, 20, stdin);
        numero[strcspn(numero, "\n")] = '\0';

        valide = 1;
        for (int i = 0; numero[i] != '\0'; i++) {
            if (!isdigit(numero[i])) {
                valide = 0;
                printf("Le numéro doit contenir uniquement des chiffres.\n");
                break;
            }
        }
    }
}

// Fonctions CRUD pour les docteurs
void Ajouter_docteur(Docteur **docteurs, int *total) {
    *docteurs = realloc(*docteurs, (*total + 1) * sizeof(Docteur));
    Docteur *nouveau = &(*docteurs)[*total];

    nouveau->ID = valider_id();
    printf("Saisir le nom : ");
    fgets(nouveau->nom, sizeof(nouveau->nom), stdin);
    printf("Saisir la spécialité : ");
    fgets(nouveau->specialite, sizeof(nouveau->specialite), stdin);
    printf("Saisir l'adresse : ");
    fgets(nouveau->adresse, sizeof(nouveau->adresse), stdin);
    valider_numero(nouveau->numero_telephone);

    // Supprimer le '\n' des entrées utilisateur
    nouveau->nom[strcspn(nouveau->nom, "\n")] = '\0';
    nouveau->specialite[strcspn(nouveau->specialite, "\n")] = '\0';
    nouveau->adresse[strcspn(nouveau->adresse, "\n")] = '\0';

    (*total)++;
}

void Afficher_liste_docteurs(Docteur *docteurs, int total) {
    if (total == 0) {
        printf("Aucun docteur trouvé.\n");
        return;
    }
    printf("\n--- Liste des docteurs ---\n");
    for (int i = 0; i < total; i++) {
        printf("ID : %d\nNom : %s\nSpécialité : %s\nAdresse : %s\nNuméro de téléphone : %s\n\n",
               docteurs[i].ID, docteurs[i].nom, docteurs[i].specialite, docteurs[i].adresse, docteurs[i].numero_telephone);
    }
}

void Modifier_docteur(Docteur *docteurs, int total, int id) {
    for (int i = 0; i < total; i++) {
        if (docteurs[i].ID == id) {
            printf("Saisir le nouveau nom : ");
            fgets(docteurs[i].nom, sizeof(docteurs[i].nom), stdin);
            printf("Saisir la nouvelle spécialité : ");
            fgets(docteurs[i].specialite, sizeof(docteurs[i].specialite), stdin);
            printf("Saisir la nouvelle adresse : ");
            fgets(docteurs[i].adresse, sizeof(docteurs[i].adresse), stdin);
            valider_numero(docteurs[i].numero_telephone);

            docteurs[i].nom[strcspn(docteurs[i].nom, "\n")] = '\0';
            docteurs[i].specialite[strcspn(docteurs[i].specialite, "\n")] = '\0';
            docteurs[i].adresse[strcspn(docteurs[i].adresse, "\n")] = '\0';
            printf("Modification effectuée.\n");
            return;
        }
    }
    printf("Aucun docteur avec cet ID.\n");
}

void Supprimer_docteur(Docteur **docteurs, int *total, int id) {
    for (int i = 0; i < *total; i++) {
        if ((*docteurs)[i].ID == id) {
            for (int j = i; j < *total - 1; j++) {
                (*docteurs)[j] = (*docteurs)[j + 1];
            }
            (*docteurs) = realloc(*docteurs, (*total - 1) * sizeof(Docteur));
            (*total)--;
            printf("Docteur supprimé.\n");
            return;
        }
    }
    printf("Aucun docteur avec cet ID.\n");
}

// Fonctions CRUD pour les patients
void Ajouter_patient(Patient **patients, int *total) {
    *patients = realloc(*patients, (*total + 1) * sizeof(Patient));
    Patient *nouveau = &(*patients)[*total];

    nouveau->ID = valider_id();
    printf("Saisir le nom : ");
    fgets(nouveau->nom, sizeof(nouveau->nom), stdin);
    printf("Saisir l'âge : ");
    scanf("%d", &nouveau->age);
    getchar();
    printf("Saisir l'adresse : ");
    fgets(nouveau->adresse, sizeof(nouveau->adresse), stdin);
    valider_numero(nouveau->numero_telephone);

    nouveau->nom[strcspn(nouveau->nom, "\n")] = '\0';
    nouveau->adresse[strcspn(nouveau->adresse, "\n")] = '\0';

    (*total)++;
}

void Afficher_liste_patients(Patient *patients, int total) {
    if (total == 0) {
        printf("Aucun patient trouvé.\n");
        return;
    }
    printf("\n--- Liste des patients ---\n");
    for (int i = 0; i < total; i++) {
        printf("ID : %d\nNom : %s\nÂge : %d\nAdresse : %s\nNuméro de téléphone : %s\n\n",
               patients[i].ID, patients[i].nom, patients[i].age, patients[i].adresse, patients[i].numero_telephone);
    }
}

void Modifier_patient(Patient *patients, int total, int id) {
    for (int i = 0; i < total; i++) {
        if (patients[i].ID == id) {
            printf("Saisir le nouveau nom : ");
            fgets(patients[i].nom, sizeof(patients[i].nom), stdin);
            printf("Saisir le nouvel âge : ");
            scanf("%d", &patients[i].age);
            getchar();
            printf("Saisir la nouvelle adresse : ");
            fgets(patients[i].adresse, sizeof(patients[i].adresse), stdin);
            valider_numero(patients[i].numero_telephone);

            patients[i].nom[strcspn(patients[i].nom, "\n")] = '\0';
            patients[i].adresse[strcspn(patients[i].adresse, "\n")] = '\0';
            printf("Modification effectuée.\n");
            return;
        }
    }
    printf("Aucun patient avec cet ID.\n");
}

void Supprimer_patient(Patient **patients, int *total, int id) {
    for (int i = 0; i < *total; i++) {
        if ((*patients)[i].ID == id) {
            for (int j = i; j < *total - 1; j++) {
                (*patients)[j] = (*patients)[j + 1];
            }
            (*patients) = realloc(*patients, (*total - 1) * sizeof(Patient));
            (*total)--;
            printf("Patient supprimé.\n");
            return;
        }
    }
    printf("Aucun patient avec cet ID.\n");
}

// Fonctions pour gérer les fichiers
void Charger_docteurs(Docteur **docteurs, int *total, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    while (!feof(file)) {
        *docteurs = realloc(*docteurs, (*total + 1) * sizeof(Docteur));
        Docteur *nouveau = &(*docteurs)[*total];
        fscanf(file, "%d;%49[^;];%49[^;];%99[^;];%19[^\n]\n", &nouveau->ID, nouveau->nom, nouveau->specialite, nouveau->adresse, nouveau->numero_telephone);
        (*total)++;
    }

    fclose(file);
}

void Sauvegarder_docteurs(Docteur *docteurs, int total, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < total; i++) {
        fprintf(file, "%d;%s;%s;%s;%s\n", docteurs[i].ID, docteurs[i].nom, docteurs[i].specialite, docteurs[i].adresse, docteurs[i].numero_telephone);
    }

    fclose(file);
}

void Charger_patients(Patient **patients, int *total, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    while (!feof(file)) {
        *patients = realloc(*patients, (*total + 1) * sizeof(Patient));
        Patient *nouveau = &(*patients)[*total];
        fscanf(file, "%d;%49[^;];%d;%99[^;];%19[^\n]\n", &nouveau->ID, nouveau->nom, &nouveau->age, nouveau->adresse, nouveau->numero_telephone);
        (*total)++;
    }

    fclose(file);
}

void Sauvegarder_patients(Patient *patients, int total, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < total; i++) {
        fprintf(file, "%d;%s;%d;%s;%s\n", patients[i].ID, patients[i].nom, patients[i].age, patients[i].adresse, patients[i].numero_telephone);
    }

    fclose(file);
}

int main() {
    Docteur *docteurs = NULL;
    Patient *patients = NULL;
    int total_docteurs = 0, total_patients = 0;
    const char *fichier_docteurs = "docteurs.txt";
    const char *fichier_patients = "patients.txt";

    Charger_docteurs(&docteurs, &total_docteurs, fichier_docteurs);
    Charger_patients(&patients, &total_patients, fichier_patients);

    int choix;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Ajouter un docteur\n");
        printf("2. Afficher la liste des docteurs\n");
        printf("3. Modifier un docteur\n");
        printf("4. Supprimer un docteur\n");
        printf("5. Ajouter un patient\n");
        printf("6. Afficher la liste des patients\n");
        printf("7. Modifier un patient\n");
        printf("8. Supprimer un patient\n");
        printf("9. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                Ajouter_docteur(&docteurs, &total_docteurs);
                break;
            case 2:
                Afficher_liste_docteurs(docteurs, total_docteurs);
                break;
            case 3: {
                int id;
                printf("Saisir l'ID du docteur à modifier : ");
                scanf("%d", &id);
                getchar();
                Modifier_docteur(docteurs, total_docteurs, id);
                break;
            }
            case 4: {
                int id;
                printf("Saisir l'ID du docteur à supprimer : ");
                scanf("%d", &id);
                getchar();
                Supprimer_docteur(&docteurs, &total_docteurs, id);
                break;
            }
            case 5:
                Ajouter_patient(&patients, &total_patients);
                break;
            case 6:
                Afficher_liste_patients(patients, total_patients);
                break;
            case 7: {
                int id;
                printf("Saisir l'ID du patient à modifier : ");
                scanf("%d", &id);
                getchar();
                Modifier_patient(patients, total_patients, id);
                break;
            }
            case 8: {
                int id;
                printf("Saisir l'ID du patient à supprimer : ");
                scanf("%d", &id);
                getchar();
                Supprimer_patient(&patients, &total_patients, id);
                break;
            }
            case 9:
                Sauvegarder_docteurs(docteurs, total_docteurs, fichier_docteurs);
                Sauvegarder_patients(patients, total_patients, fichier_patients);
                printf("Données sauvegardées. Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 9);

    free(docteurs);
    free(patients);
    return 0;
}
