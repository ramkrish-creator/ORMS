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

typedef struct {
    char mobile_number[15];
    long id;
} phoneNumber;

int main() {
    PatientDetails new_patient;
    new_patient.prescription = NULL;
    new_patient.prescription_count = 0;

    
    FILE *all_records = fopen("all_patients.dat", "rb");
    if (all_records != NULL) {
        fseek(all_records, 0, SEEK_END);
        long size = ftell(all_records) / sizeof(PatientDetails);
        new_patient.id = size + 1001;
        fclose(all_records);
    } else {
        new_patient.id = 1001;
    }

    printf("Enter patient name: ");
    fgets(new_patient.name, sizeof(new_patient.name), stdin);
    new_patient.name[strcspn(new_patient.name, "\n")] = '\0';

    printf("Enter date of birth (YYYY-MM-DD): ");
    fgets(new_patient.date_of_birth, sizeof(new_patient.date_of_birth), stdin);
    new_patient.date_of_birth[strcspn(new_patient.date_of_birth, "\n")] = '\0';

    printf("Enter weight (in kg): ");
    scanf("%lf", &new_patient.weight);
    getchar(); 

    printf("Enter mobile number: ");
    fgets(new_patient.mobile_number, sizeof(new_patient.mobile_number), stdin);
    new_patient.mobile_number[strcspn(new_patient.mobile_number, "\n")] = '\0';

    phoneNumber new_phone;
    new_phone.id = new_patient.id;
    strcpy(new_phone.mobile_number, new_patient.mobile_number);

    FILE *phone_file = fopen("phone_number.dat", "ab");
    if (phone_file == NULL) {
        perror("Failed to open phone_number.dat");
        return 1;
    }
    fwrite(&new_phone, sizeof(phoneNumber), 1, phone_file);
    fclose(phone_file);

    printf("\nPatient created successfully!\n");
    printf("ID: %ld\n", new_patient.id);
    printf("Name: %s\n", new_patient.name);
    printf("DOB: %s\n", new_patient.date_of_birth);
    printf("Weight: %.2f kg\n", new_patient.weight);
    printf("Mobile: %s\n", new_patient.mobile_number);
    printf("Prescriptions: %d\n", new_patient.prescription_count);

    all_records = fopen("all_patients.dat", "ab");
    if (all_records == NULL) {
        perror("Failed to open all_patients.dat");
        return 1;
    }
    fwrite(&new_patient, sizeof(PatientDetails), 1, all_records);
    fclose(all_records);

    char filename[30];
    sprintf(filename, "%ld.dat", new_patient.id);

    FILE *user_file = fopen(filename, "wb");
    if (user_file == NULL) {
        perror("Failed to create individual patient file");
        return 1;
    }
    fwrite(&new_patient, sizeof(PatientDetails), 1, user_file);
    fclose(user_file);

    return 0;
}
