#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notebook.h"

#define STOCK_FILE "notebooks.dat"
#define INPUT_SIZE 64

/* Removes the trailing newline from a string read with fgets. */
static void removeTrailingNewline(char *text)
{
    size_t length = strlen(text);

    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    }
}

/* Clears the remaining characters from stdin when the input is too long. */
static void discardRemainingInput(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        /* Discard characters until the end of the line. */
    }
}

/* Reads one line of text safely. */
static int readLine(const char *prompt, char *buffer, size_t bufferSize)
{
    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(buffer, bufferSize, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL) {
        discardRemainingInput();
    }

    removeTrailingNewline(buffer);

    return 1;
}

/* Reads a yes/no answer and returns 1 for yes, 0 for no. */
static int askYesNo(const char *prompt)
{
    char answer[INPUT_SIZE];

    while (1) {
        if (!readLine(prompt, answer, sizeof(answer))) {
            return 0;
        }

        if (answer[0] == 'y' || answer[0] == 'Y') {
            return 1;
        }

        if (answer[0] == 'n' || answer[0] == 'N') {
            return 0;
        }

        printf("\n**** Please enter Y or N ****\n\n");
    }
}

/* Shows the main menu and returns the selected option. */
char showMenu(void)
{
    char option[INPUT_SIZE];

    printf("**********************\n");
    printf("* Notebook Inventory *\n");
    printf("**********************\n\n");

    printf("  1 - INSERT notebook\n");
    printf("  2 - REMOVE notebook\n");
    printf("  3 - UPDATE notebook data\n");
    printf("  4 - SHOW notebook list sorted by PRICE\n");
    printf("  5 - SHOW notebook list sorted by BRAND\n");
    printf("  6 - SHOW notebook list sorted by PROCESSOR\n");
    printf("  7 - SHOW notebook list filtered by BRAND\n");
    printf("  8 - SHOW notebook list filtered by PROCESSOR\n");
    printf("  0 - EXIT application\n");

    readLine("\n  Choose an option: ", option, sizeof(option));

    return option[0];
}

/* Loads the notebook inventory from a binary file. */
static void loadInventory(struct NotebookList *notebookList)
{
    FILE *file;

    if (notebookList == NULL) {
        return;
    }

    initializeList(notebookList);

    file = fopen(STOCK_FILE, "rb");

    if (file == NULL) {
        return;
    }

    if (fread(notebookList, sizeof(struct NotebookList), 1, file) != 1) {
        initializeList(notebookList);
    }

    fclose(file);

    if (notebookList->count > MAX) {
        notebookList->count = MAX;
    }
}

/* Saves the notebook inventory to a binary file. */
static int saveInventory(struct NotebookList *notebookList)
{
    FILE *file;

    if (notebookList == NULL) {
        printf("\nInvalid notebook list.\n");
        return 0;
    }

    file = fopen(STOCK_FILE, "wb");

    if (file == NULL) {
        printf("\nCould not open the inventory file for writing.\n");
        return 0;
    }

    if (fwrite(notebookList, sizeof(struct NotebookList), 1, file) != 1) {
        printf("\nCould not save the inventory file.\n");
        fclose(file);
        return 0;
    }

    fclose(file);

    printf("\n**** The inventory file was saved successfully ****\n");

    return 1;
}

/* Prints a sorted copy of the notebook list without changing the original list. */
static void printSortedNotebookList(struct NotebookList *notebookList,
                                    int (*comparisonFunction)(const void *, const void *))
{
    struct NotebookList sortedList;

    if (notebookList == NULL) {
        printf("\nInvalid notebook list.\n");
        return;
    }

    if (notebookList->count < 2) {
        printf("\nAt least two notebooks are required to sort the list.\n\n");
        return;
    }

    sortedList = *notebookList;

    qsort(sortedList.items,
          sortedList.count,
          sizeof(struct Notebook),
          comparisonFunction);

    printNotebookList(&sortedList);
}

int main(void)
{
    struct NotebookList notebookList;
    struct Notebook notebook;
    int foundIndex;
    int inventoryChanged = 0;
    char option;
    char code[CODE_SIZE];
    char brand[INPUT_SIZE];
    char processor[INPUT_SIZE];
    unsigned previousCount;

    loadInventory(&notebookList);

    do {
        option = showMenu();

        switch (option) {
            case '1':
                previousCount = notebookList.count;

                addNotebook(&notebookList, notebook);

                if (notebookList.count > previousCount) {
                    inventoryChanged = 1;
                }

                break;

            case '2':
                printf("\n\n**** Remove Notebook ****\n\n");

                readLine("Enter the notebook code: ", code, sizeof(code));

                foundIndex = findNotebookByCode(&notebookList, code);

                if (foundIndex < 0) {
                    printf("\n\n**** Notebook does not exist ****\n\n");
                } else {
                    char confirmationPrompt[INPUT_SIZE];

                    snprintf(confirmationPrompt,
                             sizeof(confirmationPrompt),
                             "\nDelete notebook %s? (y/n): ",
                             code);

                    if (askYesNo(confirmationPrompt)) {
                        removeNotebook(&notebookList, code);
                        printf("\n\n**** Notebook removed ****\n\n");
                        inventoryChanged = 1;
                    }
                }

                break;

            case '3':
                printf("\n\n**** Update Notebook ****\n\n");

                readLine("Enter the notebook code: ", code, sizeof(code));

                foundIndex = findNotebookByCode(&notebookList, code);

                if (foundIndex < 0) {
                    printf("\n\n**** Notebook does not exist ****\n\n");
                } else {
                    char confirmationPrompt[INPUT_SIZE];

                    snprintf(confirmationPrompt,
                             sizeof(confirmationPrompt),
                             "\nUpdate notebook %s? (y/n): ",
                             code);

                    if (askYesNo(confirmationPrompt)) {
                        updateNotebook(&notebookList, code);
                        printf("\n\n**** Notebook data updated ****\n\n");
                        inventoryChanged = 1;
                    }
                }

                break;

            case '4':
                printSortedNotebookList(&notebookList, compareByPrice);
                break;

            case '5':
                printSortedNotebookList(&notebookList, compareByBrand);
                break;

            case '6':
                printSortedNotebookList(&notebookList, compareByProcessor);
                break;

            case '7':
                printf("\n\n--- Enter the notebook brand ---\n\n");

                readLine("Brand: ", brand, sizeof(brand));

                printNotebooksByBrand(&notebookList, brand);
                break;

            case '8':
                printf("\n\n--- Enter the notebook processor ---\n\n");

                readLine("Processor: ", processor, sizeof(processor));

                printNotebooksByProcessor(&notebookList, processor);
                break;

            case '0':
                if (inventoryChanged) {
                    if (askYesNo("\nInventory changed. Do you want to save the changes? (y/n): ")) {
                        saveInventory(&notebookList);
                    } else {
                        printf("\nChanges were not saved.\n");
                    }
                }

                break;

            default:
                printf("\n\n**** Invalid input ****\n\n");
                break;
        }

    } while (option != '0');

    printf("\n");

    return 0;
}