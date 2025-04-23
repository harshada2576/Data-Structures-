#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// Function to clear the input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Structures
typedef struct Pdata {
	char name[50], disease[50];
	int age, id;
} Pdata;

typedef struct Patient {
	Pdata data;
	struct Patient *next;
} Patient;

typedef struct Doctor {
	char name[50];
	Patient* patient;
	struct Doctor* next;
} Doctor;

typedef struct Hospital {
	char name[50];
	Doctor* d;
	struct Hospital* next;
} Hospital;

// Init Functions
Patient* initP(int id, char* name, int age) {
	Patient* newP = (Patient*) malloc(sizeof(Patient));
	newP->data.id = id;
	strcpy(newP->data.name, name);
	newP->data.age = age;
	newP->next = NULL;
	return newP;
}
Doctor* initD(const char* name) {
	Doctor* newD = (Doctor*) malloc(sizeof(Doctor));
	strcpy(newD->name, name);
	newD->patient = NULL;
	newD->next = NULL;
	return newD;
}
Hospital* initH(const char* name) {
	Hospital* newH = (Hospital*) malloc(sizeof(Hospital));
	strcpy(newH->name, name);
	newH->d = NULL;
	newH->next = NULL;
	return newH;
}

// Memory Cleanup
void freePatient(Patient* patient) {
	free(patient);
}
void freeDoctor(Doctor* doctor) {
	Patient* temp = doctor->patient;
	while (temp != NULL) {
		Patient* next = temp->next;
		freePatient(temp);
		temp = next;
	}
	free(doctor);
}
void freeHospital(Hospital* hospital) {
	Doctor* temp = hospital->d;
	while (temp != NULL) {
		Doctor* next = temp->next;
		freeDoctor(temp);
		temp = next;
	}
	free(hospital);
}

// Add Functions
void addPtoD(Doctor *doctor, Patient *newp) {
	if (doctor->patient == NULL) {
		doctor->patient = newp;
	} else {
		Patient *temp = doctor->patient;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newp;
	}
}
void addDtoH(Hospital* hospital, Doctor* newD) {
	if (hospital->d == NULL) {
		hospital->d = newD;
	} else {
		Doctor* temp = hospital->d;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newD;
	}
}
void addH(Hospital** Hlist, Hospital* newH) {
	if (*Hlist == NULL) {
		*Hlist = newH;
	} else {
		Hospital* temp = *Hlist;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newH;
	}
}

// Print Functions
void pPofD(Doctor *doctor) {
	Patient *temp = doctor->patient;
	while (temp != NULL) {
		printf("Patient ID: %d, Name: %s, Age: %d\n", temp->data.id, temp->data.name, temp->data.age);
		temp = temp->next;
	}
}
void pDofH(Hospital* hospital) {
	Doctor* temp = hospital->d;
	while (temp != NULL) {
		printf("Doctor: %s\n", temp->name);
		pPofD(temp);
		temp = temp->next;
	}
}
void pH(Hospital** Hlist) {
	Hospital* temp = *Hlist;
	if (temp == NULL) {
		printf("No Hospitals.\n");
	} else {
		while (temp != NULL) {
			printf("Hospital: %s\n", temp->name);
			temp = temp->next;
		}
	}
}

// Patient Operations
void editP(Doctor* doctor) {
	int id;
	printf("Enter the patient ID to edit: ");
	scanf("%d", &id);

	Patient* temp = doctor->patient;
	while (temp != NULL && temp->data.id != id)
		temp = temp->next;

	if (temp != NULL) {
		printf("Editing patient %d\n", id);
		printf("Enter new name: ");
		scanf(" %49[^\n]", temp->data.name);
		printf("Enter new age: ");
		scanf("%d", &temp->data.age);
		printf("Patient updated successfully!\n");
	} else {
		printf("Patient not found.\n");
	}
}
void deleteP(Doctor* doctor) {
	int id;
	printf("Enter the patient ID to delete: ");
	scanf("%d", &id);

	Patient* temp = doctor->patient;
	Patient* prev = NULL;

	while (temp != NULL && temp->data.id != id) {
		prev = temp;
		temp = temp->next;
	}

	if (temp != NULL) {
		if (prev == NULL) {
			doctor->patient = temp->next;
		} else {
			prev->next = temp->next;
		}
		free(temp);
		printf("Patient %d deleted successfully!\n", id);
	} else {
		printf("Patient not found.\n");
	}
}
void searchPatientByName(Doctor* doctor) {
	char name[50];
	printf("Enter the patient's name to search: ");
	scanf(" %49[^\n]", name);

	Patient* temp = doctor->patient;
	int found = 0;
	while (temp != NULL) {
		if (strcmp(temp->data.name, name) == 0) {
			printf("Patient found: ID: %d, Name: %s, Age: %d\n",
				temp->data.id, temp->data.name, temp->data.age);
			found = 1;
		}
		temp = temp->next;
	}
	if (!found) {
		printf("No patient with that name found.\n");
	}
}
void viewPatientInfo(Doctor* doctor) {
	int id;
	printf("Enter the patient ID to view: ");
	scanf("%d", &id);

	Patient* temp = doctor->patient;
	while (temp != NULL && temp->data.id != id)
		temp = temp->next;

	if (temp != NULL) {
		printf("Patient ID: %d\nName: %s\nAge: %d\n",
			   temp->data.id, temp->data.name, temp->data.age);
	} else {
		printf("Patient not found.\n");
	}
}

// Menu
void menu() {
	printf("\n===== Hospital Patient Record System =====\n");
	printf("1. Add new Hospital\n");
	printf("2. Add new Doctor to Hospital\n");
	printf("3. Add new Patient to Doctor\n");
	printf("4. View List of Hospitals\n");
	printf("5. Select Hospital\n");
	printf("6. View Doctors in Hospital\n");
	printf("7. Select Doctor\n");
	printf("8. View Waiting List of Patients under Doctor\n");
	printf("9. View Patients under Doctor\n");
	printf("10. View Patient Information by ID\n");
	printf("11. Edit Patient Information\n");
	printf("12. Delete Patient\n");
	printf("13. Search Patient by Name\n");
	printf("14. Exit\n");
	printf("==========================================\n");
}

// Main
int main() {
	Hospital* Hlist = NULL;
	int choice;
	char name[50];
	int id, age;

	Patient* patient;
	Doctor* doctor = NULL;
	Hospital* hospital = NULL;

	while (1) {
		menu();
		printf("Enter your choice: ");
		if (scanf("%d", &choice) != 1) {
			clearInputBuffer();
			printf("Invalid input. Please enter a number.\n");
			continue;
		}
		clearInputBuffer();

		switch (choice) {
			case 1:
				printf("Enter hospital name: ");
				scanf(" %49[^\n]", name);
				hospital = initH(name);
				addH(&Hlist, hospital);
				printf("Hospital %s added.\n", name);
				break;
			case 2:
				if (Hlist == NULL) {
					printf("No hospitals available.\n");
					break;
				}
				printf("Enter hospital name to add doctor: ");
				scanf(" %49[^\n]", name);
				hospital = Hlist;
				while (hospital != NULL && strcmp(hospital->name, name) != 0)
					hospital = hospital->next;
				if (hospital == NULL) {
					printf("Hospital not found.\n");
					break;
				}
				printf("Enter doctor name: ");
				scanf(" %49[^\n]", name);
				addDtoH(hospital, initD(name));
				printf("Doctor added to %s.\n", hospital->name);
				break;
			case 3:
				if (hospital == NULL || hospital->d == NULL) {
					printf("Select a hospital and ensure it has doctors.\n");
					break;
				}
				printf("Enter doctor name: ");
				scanf(" %49[^\n]", name);
				doctor = hospital->d;
				while (doctor != NULL && strcmp(doctor->name, name) != 0)
					doctor = doctor->next;
				if (doctor == NULL) {
					printf("Doctor not found.\n");
					break;
				}
				printf("Enter patient ID: ");
				scanf("%d", &id);
				printf("Enter patient name: ");
				scanf(" %49[^\n]", name);
				printf("Enter patient age: ");
				scanf("%d", &age);
				addPtoD(doctor, initP(id, name, age));
				printf("Patient added to Dr. %s.\n", doctor->name);
				break;
			case 4:
				pH(&Hlist);
				break;
			case 5:
				printf("Enter hospital name to select: ");
				scanf(" %49[^\n]", name);
				hospital = Hlist;
				while (hospital != NULL && strcmp(hospital->name, name) != 0)
					hospital = hospital->next;
				if (hospital)
					printf("Hospital %s selected.\n", hospital->name);
				else
					printf("Hospital not found.\n");
				break;
			case 6:
				if (!hospital) {
					printf("Select a hospital first.\n");
					break;
				}
				pDofH(hospital);
				break;
			case 7:
				if (!hospital) {
					printf("Select a hospital first.\n");
					break;
				}
				printf("Enter doctor name to select: ");
				scanf(" %49[^\n]", name);
				doctor = hospital->d;
				while (doctor != NULL && strcmp(doctor->name, name) != 0)
					doctor = doctor->next;
				if (doctor)
					printf("Doctor %s selected.\n", doctor->name);
				else
					printf("Doctor not found.\n");
				break;
			case 8:
			case 9:
				if (!doctor) {
					printf("Select a doctor first.\n");
					break;
				}
				pPofD(doctor);
				break;
			case 10:
				if (!doctor) {
					printf("Select a doctor first.\n");
					break;
				}
				viewPatientInfo(doctor);
				break;
			case 11:
				if (!doctor) {
					printf("Select a doctor first.\n");
					break;
				}
				editP(doctor);
				break;
			case 12:
				if (!doctor) {
					printf("Select a doctor first.\n");
					break;
				}
				deleteP(doctor);
				break;
			case 13:
				if (!doctor) {
					printf("Select a doctor first.\n");
					break;
				}
				searchPatientByName(doctor);
				break;
			case 14:
				printf("Exiting...\n");
				while (Hlist != NULL) {
					Hospital* next = Hlist->next;
					freeHospital(Hlist);
					Hlist = next;
				}
			default:
				printf("Invalid choice.\n");
		}
	}
	return 0;
}

