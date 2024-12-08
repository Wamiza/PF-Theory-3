#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeInventory(char ***speciesSupplies, int *numSupplies, int numSpecies);
void addSupplies(char ***speciesSupplies, int *numSupplies, int speciesIndex);
void updateSupply(char ***speciesSupplies, int *numSupplies, int speciesIndex);
void removeSpecies(char ***speciesSupplies, int **numSupplies, int *numSpecies, int speciesIndex);
void displayInventory(char **species, char ***speciesSupplies, int *numSupplies, int numSpecies);

int main() {
    int numSpecies, choice;
    char **species = NULL;
    char ***speciesSupplies = NULL;
    int *numSupplies = NULL;

    printf("Enter the number of species: ");
    scanf("%d", &numSpecies);
    getchar(); // Clear newline character

    species = (char **)malloc(numSpecies * sizeof(char *));
    for (int i = 0; i < numSpecies; i++) {
        species[i] = (char *)malloc(50 * sizeof(char));
    }

    for (int i = 0; i < numSpecies; i++) {
        printf("Enter the name of species %d: ", i + 1);
        fgets(species[i], 50, stdin);
        species[i][strcspn(species[i], "\n")] = '\0';
    }

    speciesSupplies = (char ***)malloc(numSpecies * sizeof(char **));
    numSupplies = (int *)calloc(numSpecies, sizeof(int));
    initializeInventory(speciesSupplies, numSupplies, numSpecies);

    do {
        printf("\n--- Pets in Heart Inventory ---\n");
        printf("1. Add Supplies\n");
        printf("2. Update Supply\n");
        printf("3. Remove Species\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                int speciesIndex;
                printf("Enter the species index (1 to %d): ", numSpecies);
                scanf("%d", &speciesIndex);
                getchar();
                if (speciesIndex < 1 || speciesIndex > numSpecies) {
                    printf("Invalid species index!\n");
                } else {
                    addSupplies(speciesSupplies, numSupplies, speciesIndex - 1);
                }
                break;
            }
            case 2: {
                int speciesIndex;
                printf("Enter the species index (1 to %d): ", numSpecies);
                scanf("%d", &speciesIndex);
                getchar();
                if (speciesIndex < 1 || speciesIndex > numSpecies) {
                    printf("Invalid species index!\n");
                } else {
                    updateSupply(speciesSupplies, numSupplies, speciesIndex - 1);
                }
                break;
            }
            case 3: {
                int speciesIndex;
                printf("Enter the species index to remove (1 to %d): ", numSpecies);
                scanf("%d", &speciesIndex);
                getchar();
                if (speciesIndex < 1 || speciesIndex > numSpecies) {
                    printf("Invalid species index!\n");
                } else {
                    removeSpecies(&speciesSupplies, &numSupplies, &numSpecies, speciesIndex - 1);
                    free(species[speciesIndex - 1]);
                    for (int i = speciesIndex - 1; i < numSpecies - 1; i++) {
                        species[i] = species[i + 1];
                    }
                    numSpecies--;
                }
                break;
            }
            case 4:
                displayInventory(species, speciesSupplies, numSupplies, numSpecies);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    for (int i = 0; i < numSpecies; i++) {
        for (int j = 0; j < numSupplies[i]; j++) {
            free(speciesSupplies[i][j]);
        }
        free(speciesSupplies[i]);
        free(species[i]);
    }
    free(speciesSupplies);
    free(species);
    free(numSupplies);

    return 0;
}

void initializeInventory(char ***speciesSupplies, int *numSupplies, int numSpecies) {
    for (int i = 0; i < numSpecies; i++) {
        speciesSupplies[i] = NULL;
        numSupplies[i] = 0;
    }
}

void addSupplies(char ***speciesSupplies, int *numSupplies, int speciesIndex) {
    int newSupplies;
    printf("Enter the number of supplies to add: ");
    scanf("%d", &newSupplies);
    getchar(); // Clear newline character

    // Reallocate memory for the new supplies
    speciesSupplies[speciesIndex] = (char **)realloc(speciesSupplies[speciesIndex], 
                                                     (numSupplies[speciesIndex] + newSupplies) * sizeof(char *));
    for (int i = numSupplies[speciesIndex]; i < numSupplies[speciesIndex] + newSupplies; i++) {
        speciesSupplies[speciesIndex][i] = (char *)malloc(50 * sizeof(char));
        printf("Enter supply name: ");
        fgets(speciesSupplies[speciesIndex][i], 50, stdin);
        speciesSupplies[speciesIndex][i][strcspn(speciesSupplies[speciesIndex][i], "\n")] = '\0'; // Remove newline
    }

    // Update the count of supplies
    numSupplies[speciesIndex] += newSupplies;
}

void updateSupply(char ***speciesSupplies, int *numSupplies, int speciesIndex) {
    int supplyIndex;
    printf("Enter the supply index to update (1 to %d): ", numSupplies[speciesIndex]);
    scanf("%d", &supplyIndex);
    getchar();
    if (supplyIndex < 1 || supplyIndex > numSupplies[speciesIndex]) {
        printf("Invalid supply index!\n");
    } else {
        printf("Enter the new supply name: ");
        fgets(speciesSupplies[speciesIndex][supplyIndex - 1], 50, stdin);
        speciesSupplies[speciesIndex][supplyIndex - 1][strcspn(speciesSupplies[speciesIndex][supplyIndex - 1], "\n")] = '\0';
    }
}

void removeSpecies(char ***speciesSupplies, int **numSupplies, int *numSpecies, int speciesIndex) {
    for (int i = 0; i < (*numSupplies)[speciesIndex]; i++) {
        free((*speciesSupplies)[speciesIndex][i]);
    }
    free((*speciesSupplies)[speciesIndex]);
    for (int i = speciesIndex; i < *numSpecies - 1; i++) {
        (*speciesSupplies)[i] = (*speciesSupplies)[i + 1];
        (*numSupplies)[i] = (*numSupplies)[i + 1];
    }
    *speciesSupplies = (char ***)realloc(*speciesSupplies, (*numSpecies - 1) * sizeof(char **));
    *numSupplies = (int *)realloc(*numSupplies, (*numSpecies - 1) * sizeof(int));
    (*numSpecies)--;
}

void displayInventory(char **species, char ***speciesSupplies, int *numSupplies, int numSpecies) {
    printf("\n--- Inventory ---\n");
    for (int i = 0; i < numSpecies; i++) {
        printf("Species: %s\n", species[i]);
        printf("Supplies: ");
        for (int j = 0; j < numSupplies[i]; j++) {
            printf("%s ", speciesSupplies[i][j]);
        }
        printf("\n");
    }
}
