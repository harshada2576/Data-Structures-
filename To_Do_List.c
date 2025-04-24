/*The Personal To-Do List with Categories is a C program that manages tasks . Users can add, view (all or by category), 
mark as completed, or delete tasks, stored in a linked list. It uses structs (`Task`, `ToDoList`), 
dynamic memory (`malloc`, `free`), string handling (`strncpy`, `strcmp`), pointers, loops, conditionals.The menu-driven app 
ensures safe input and memory cleanup. It teaches linked lists.
Uses Singly lisked list
*/
//Harshada Avhad
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for maximum lengths of task description and category
#define MAX_DESC 100  // Maximum length for task description
#define MAX_CAT 50    // Maximum length for category name

// Structure to represent a Task
// Each task has a description, category, completion status, and a pointer to the next task
typedef struct Task {
    char description[MAX_DESC];  // Task description (e.g., "Buy groceries")
    char category[MAX_CAT];      // Category name (e.g., "Personal")
    int completed;              // Completion status (0 = pending, 1 = completed)
    struct Task* next;          // Pointer to the next task in the linked list
} Task;

// Structure to represent the To-Do List
// Contains a pointer to the head of the linked list of tasks
typedef struct ToDoList {
    Task* head;                 // Pointer to the first task in the list
} ToDoList;

// Function: createToDoList
// Purpose: Allocates memory for a new To-Do List and initializes it with an empty list
// Returns: Pointer to the newly created To-Do List
ToDoList* createToDoList() {
    ToDoList* list = (ToDoList*)malloc(sizeof(ToDoList)); // Allocate memory for the list
    if (list == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed!\n");
        return NULL;
    }
    list->head = NULL; // Initialize the list as empty
    return list;
}

// Function: createTask
// Purpose: Creates a new task with the given description and category
// Parameters:
//   - description: The task description
//   - category: The category to which the task belongs
// Returns: Pointer to the newly created Task
Task* createTask(char* description, char* category) {
    Task* newTask = (Task*)malloc(sizeof(Task)); // Allocate memory for the new task
    if (newTask == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // Copy description and category, ensuring null-termination
    strncpy(newTask->description, description, MAX_DESC - 1);
    newTask->description[MAX_DESC - 1] = '\0';
    strncpy(newTask->category, category, MAX_CAT - 1);
    newTask->category[MAX_CAT - 1] = '\0';
    newTask->completed = 0; // Initialize task as not completed
    newTask->next = NULL;   // Initialize next pointer as NULL
    return newTask;
}

// Function: addTask
// Purpose: Adds a new task to the end of the To-Do List
// Parameters:
//   - list: Pointer to the To-Do List
//   - description: The task description
//   - category: The category of the task
void addTask(ToDoList* list, char* description, char* category) {
    Task* newTask = createTask(description, category); // Create a new task
    if (list->head == NULL) { // If the list is empty
        list->head = newTask; // Set the new task as the head
    } else {
        Task* current = list->head; // Start at the head
        while (current->next != NULL) { // Traverse to the end of the list
            current = current->next;
        }
        current->next = newTask; // Link the new task at the end
    }
    printf("Task added: %s (Category: %s)\n", description, category);
}

// Function: viewTasks
// Purpose: Displays all tasks or tasks in a specific category
// Parameters:
//   - list: Pointer to the To-Do List
//   - category: The category to filter by (NULL to show all tasks)
void viewTasks(ToDoList* list, char* category) {
    Task* current = list->head; // Start at the head
    int found = 0; // Flag to track if any tasks are found
    printf("\nTo-Do List:\n");
    while (current != NULL) {
        // Show task if category is NULL (all tasks) or matches the specified category
        if (category == NULL || strcmp(current->category, category) == 0) {
            printf("- %s [%s] (%s)\n", current->description, current->category,
                   current->completed ? "Completed" : "Pending");
            found = 1;
        }
        current = current->next; // Move to the next task
    }
    if (!found) {
        // Print message if no tasks are found
        printf("No tasks found %s.\n", category ? "in this category" : "");
    }
}

// Function: markCompleted
// Purpose: Marks a task as completed based on its description
// Parameters:
//   - list: Pointer to the To-Do List
//   - description: The description of the task to mark as completed
void markCompleted(ToDoList* list, char* description) {
    Task* current = list->head; // Start at the head
    while (current != NULL)
//The strcmp function in C is used to compare two strings. It’s declared in the string.h header and stands for string compare.
	 {
        if (strcmp(current->description, description) == 0) { // Match task by description
            current->completed = 1; // Mark as completed
            printf("Task marked as completed: %s\n", description);
            return;
        }
        current = current->next; // Move to the next task
    }
    printf("Task not found: %s\n", description); // Task not found
}

// Function: deleteTask
// Purpose: Deletes a task from the list based on its description
// Parameters:
//   - list: Pointer to the To-Do List
//   - description: The description of the task to delete
void deleteTask(ToDoList* list, char* description) {
    Task* current = list->head; // Start at the head
    Task* prev = NULL; // Keep track of the previous task
    while (current != NULL) {
        if (strcmp(current->description, description) == 0) { // Match task by description
            if (prev == NULL) { // If the task is the head
                list->head = current->next; // Update head to next task
            } else {
                prev->next = current->next; // Bypass the current task
            }
            printf("Task deleted: %s\n", description);
            free(current); // Free the task's memory
            return;
        }
        prev = current; // Update previous pointer
        current = current->next; // Move to the next task
    }
    printf("Task not found: %s\n", description); // Task not found
}

// Function: freeToDoList
// Purpose: Frees all memory allocated for the To-Do List and its tasks
// Parameters:
//   - list: Pointer to the To-Do List
void freeToDoList(ToDoList* list) {
    Task* current = list->head; // Start at the head
    while (current != NULL) {
        Task* temp = current; // Store current task
        current = current->next; // Move to next task
        free(temp); // Free current task
    }
    free(list); // Free the list itself
}

// Function: main
// Purpose: Entry point of the program, provides a menu-driven interface
//          for managing the To-Do List
int main() {
    ToDoList* list = createToDoList(); // Initialize the To-Do List
    int choice; // Store user's menu choice
    char description[MAX_DESC]; // Buffer for task description
    char category[MAX_CAT]; // Buffer for category name

    while (1) { // Main loop for the menu
        // Display menu options
        printf("\nPersonal To-Do List Manager\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. View Tasks by Category\n");
        printf("4. Mark Task as Completed\n");
        printf("5. Delete Task\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer
        if(choice==6)
        break;

        switch (choice) {
            case 1: // Add a new task
                printf("Enter task description: ");
                fgets(description, MAX_DESC, stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline
                printf("Enter category: ");
                fgets(category, MAX_CAT, stdin);
                category[strcspn(category, "\n")] = 0; // Remove newline
                addTask(list, description, category);
                break;
            case 2: // View all tasks
                viewTasks(list, NULL);
                break;
            case 3: // View tasks by category
                printf("Enter category: ");
                fgets(category, MAX_CAT, stdin);
                category[strcspn(category, "\n")] = 0; // Remove newline
                viewTasks(list, category);
                break;
            case 4: // Mark a task as completed
                printf("Enter task description to mark as completed: ");
                fgets(description, MAX_DESC, stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline
                markCompleted(list, description);
                break;
            case 5: // Delete a task
                printf("Enter task description to delete: ");
                fgets(description, MAX_DESC, stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline
                deleteTask(list, description);
                break;
            //
	            default: // Handle invalid input
                printf("Invalid choice. Try again.\n");
    			return 0;
        }
    }
}
