#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>  // For reading directory entries

#define MAX_LENGTH 100

// Structure to hold patient appointment information
struct Appointment {
    char patient_id[MAX_LENGTH];
    char name[MAX_LENGTH];
    char date[MAX_LENGTH];
    char time[MAX_LENGTH];
    char doctor[MAX_LENGTH];
};

// Function to save the appointment
void save_appointment(const char *patient_id, const char *name, const char *date, const char *time, const char *doctor) {
    FILE *file;
    char filename[MAX_LENGTH];
    struct Appointment appointment;

    snprintf(filename, sizeof(filename), "%s_%s.dat", doctor, patient_id);
    file = fopen(filename, "ab");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    strncpy(appointment.patient_id, patient_id, sizeof(appointment.patient_id) - 1);
    strncpy(appointment.name, name, sizeof(appointment.name) - 1);
    strncpy(appointment.date, date, sizeof(appointment.date) - 1);
    strncpy(appointment.time, time, sizeof(appointment.time) - 1);
    strncpy(appointment.doctor, doctor, sizeof(appointment.doctor) - 1);

    fwrite(&appointment, sizeof(struct Appointment), 1, file);
    fclose(file);

    printf("Appointment saved successfully with Doctor %s.\n", doctor);
}

// Function to list all appointments for a doctor
void list_appointments(const char *doctor) {
    DIR *d;
    struct dirent *dir;
    char filename[MAX_LENGTH];
    struct Appointment appointment;

    d = opendir(".");
    if (!d) {
        perror("Unable to open directory");
        return;
    }

    printf("\n--- Appointments for Doctor %s ---\n", doctor);
    while ((dir = readdir(d)) != NULL) {
        if (strstr(dir->d_name, doctor) == dir->d_name) { // starts with "DrA" or "DrB"
            FILE *file = fopen(dir->d_name, "rb");
            if (file) {
                while (fread(&appointment, sizeof(struct Appointment), 1, file)) {
                    printf("Patient ID: %s\n", appointment.patient_id);
                    printf("Name     : %s\n", appointment.name);
                    printf("Date     : %s\n", appointment.date);
                    printf("Time     : %s\n", appointment.time);
                    printf("---------\n");
                }
                fclose(file);
            }
        }
    }
    closedir(d);
}

int main() {
    int choice;
    char name[MAX_LENGTH], patient_id[MAX_LENGTH], date[MAX_LENGTH], time[MAX_LENGTH];
    char doctor_choice[MAX_LENGTH], doctor[MAX_LENGTH];

    printf("1. Add Appointment\n2. View Appointments by Doctor\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();  // Clear newline

    printf("Select Doctor (Enter A or B): ");
    fgets(doctor_choice, sizeof(doctor_choice), stdin);
    doctor_choice[strcspn(doctor_choice, "\n")] = 0;

    if (strcmp(doctor_choice, "A") == 0 || strcmp(doctor_choice, "a") == 0)
        strcpy(doctor, "DrA");
    else if (strcmp(doctor_choice, "B") == 0 || strcmp(doctor_choice, "b") == 0)
        strcpy(doctor, "DrB");
    else {
        printf("Invalid doctor selection.\n");
        return 1;
    }

    if (choice == 1) {
        printf("Enter Patient ID: ");
        fgets(patient_id, sizeof(patient_id), stdin);
        patient_id[strcspn(patient_id, "\n")] = 0;

        printf("Enter Patient Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter Appointment Date (YYYY-MM-DD): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = 0;

        printf("Enter Time Slot (e.g., 08:00 AM): ");
        fgets(time, sizeof(time), stdin);
        time[strcspn(time, "\n")] = 0;

        save_appointment(patient_id, name, date, time, doctor);
    } else if (choice == 2) {
        list_appointments(doctor);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

