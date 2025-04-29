#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Structure to hold patient appointment information
struct Appointment {
    char patient_id[MAX_LENGTH];
    char name[MAX_LENGTH];
    char date[MAX_LENGTH];
    char time[MAX_LENGTH];
};

// Function to save the patient data in a binary .dat file
void save_appointment(const char *patient_id, const char *name, const char *date, const char *time) {
    FILE *file;
    char filename[MAX_LENGTH];
    struct Appointment appointment;

    // Create the filename using the patient ID
    snprintf(filename, sizeof(filename), "%s.dat", patient_id);

    // Open the file in append binary mode
    file = fopen(filename, "ab");

    // Check if file opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Fill the appointment struct with data
    strncpy(appointment.patient_id, patient_id, sizeof(appointment.patient_id) - 1);
    strncpy(appointment.name, name, sizeof(appointment.name) - 1);
    strncpy(appointment.date, date, sizeof(appointment.date) - 1);
    strncpy(appointment.time, time, sizeof(appointment.time) - 1);

    // Write the struct to the binary file
    fwrite(&appointment, sizeof(struct Appointment), 1, file);

    // Close the file
    fclose(file);

    printf("Appointment saved successfully.\n");
}

int main() {
    char name[MAX_LENGTH];
    char patient_id[MAX_LENGTH];
    char date[MAX_LENGTH];
    char time[MAX_LENGTH];

    // Get the input data from the user (simulating form data submission)
    printf("Enter Patient ID: ");
    fgets(patient_id, sizeof(patient_id), stdin);
    patient_id[strcspn(patient_id, "\n")] = 0; // Remove trailing newline

    printf("Enter Patient Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    printf("Enter Appointment Date (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0; // Remove trailing newline

    printf("Enter Time Slot (e.g., 08:00 AM): ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = 0; // Remove trailing newline

    // Save the appointment details in binary format
    save_appointment(patient_id, name, date, time);

    return 0;
}
