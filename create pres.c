#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char medication_name[100];
    int dosage;
    int frequency;
    int duration;
} Medication;

typedef struct {
    char symptoms[100];
    char findings[100];
    char diagnosis[100];
    Medication *medication;
    int medication_count;
} Prescription;

typedef struct {
    long id;
    char name[30];
    char date_of_birth[11];
    double weight;
    char mobile_number[15];
    Prescription *prescription;
    int prescription_count;
} PatientDetails;


int main() {
    long id;
    printf("Enter patient ID to add prescription: ");
    scanf("%ld", &id);

    char file_name[50];
    sprintf(file_name, "%ld.dat", id);

    FILE *fp = fopen(file_name, "rb+");
    if (fp == NULL) {
        printf("Patient file not found.\n");
        return 1;
    }

    PatientDetails patient;
    fread(&patient, sizeof(PatientDetails), 1, fp);

    Prescription new_prescription;
    printf("Enter symptoms: ");
    getchar();
    fgets(new_prescription.symptoms, 100, stdin);
    new_prescription.symptoms[strcspn(new_prescription.symptoms, "\n")] = '\0';

    printf("Enter findings: ");
    fgets(new_prescription.findings, 100, stdin);
    new_prescription.findings[strcspn(new_prescription.findings, "\n")] = '\0';

    printf("Enter diagnosis: ");
    fgets(new_prescription.diagnosis, 100, stdin);
    new_prescription.diagnosis[strcspn(new_prescription.diagnosis, "\n")] = '\0';

    printf("Enter number of medications: ");
    scanf("%d", &new_prescription.medication_count);

    new_prescription.medication = (Medication *)malloc(new_prescription.medication_count * sizeof(Medication));

    for (int i = 0; i < new_prescription.medication_count; i++) {
        printf("Medication #%d name: ", i + 1);
        getchar();
        fgets(new_prescription.medication[i].medication_name, 100, stdin);
        new_prescription.medication[i].medication_name[strcspn(new_prescription.medication[i].medication_name, "\n")] = '\0';

        printf("Dosage: ");
        scanf("%d", &new_prescription.medication[i].dosage);
        printf("Frequency: ");
        scanf("%d", &new_prescription.medication[i].frequency);
        printf("Duration: ");
        scanf("%d", &new_prescription.medication[i].duration);
    }

    fseek(fp, 0, SEEK_END);

    fwrite(&new_prescription, sizeof(Prescription), 1, fp);
    fwrite(new_prescription.medication, sizeof(Medication), new_prescription.medication_count, fp);

    patient.prescription_count += 1;
    fseek(fp, 0, 0);
    fwrite(&patient, sizeof(PatientDetails), 1, fp);

    printf("New prescription added successfully.\n");

    fclose(fp);
    free(new_prescription.medication);
    return 0;
}
