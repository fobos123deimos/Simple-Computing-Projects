#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TEXT_SIZE 32
#define CODE_SIZE 16

/*
 * Stores the attributes of one notebook in stock.
 * The code is generated from the first character of the brand,
 * the model, the processor, the screen size, and the RAM amount.
 */
struct Notebook {
    char brand[TEXT_SIZE];
    char model[TEXT_SIZE];
    char processor[TEXT_SIZE];
    int storage;
    int ram;
    double screenSize;
    char inputOutput[TEXT_SIZE];
    char operatingSystem[TEXT_SIZE];
    int price;
    char code[CODE_SIZE];
};

/*
 * Stores the notebook list and keeps track of how many notebooks are registered.
 */
struct NotebookList {
    unsigned count;
    struct Notebook items[MAX];
};

/* Clears the remaining characters from the input buffer. */
void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        /* Discard characters until the end of the line. */
    }
}

/* Removes the trailing newline from a string read with fgets. */
static void removeNewline(char *text)
{
    size_t length = strlen(text);

    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    }
}

/* Reads a non-empty text value safely. */
static int readText(const char *prompt, char *buffer, size_t bufferSize)
{
    do {
        printf("%s", prompt);

        if (fgets(buffer, bufferSize, stdin) == NULL) {
            return 0;
        }

        removeNewline(buffer);

        if (buffer[0] == '\0') {
            printf("Empty value. Try again.\n");
        }
    } while (buffer[0] == '\0');

    return 1;
}

/* Reads an integer value safely. */
static int readInteger(const char *prompt, int *value)
{
    char line[TEXT_SIZE];
    char extraCharacter;

    while (1) {
        if (!readText(prompt, line, sizeof(line))) {
            return 0;
        }

        if (sscanf(line, "%d %c", value, &extraCharacter) == 1) {
            return 1;
        }

        printf("Invalid value. Enter an integer number.\n");
    }
}

/* Reads a floating-point value safely. */
static int readDouble(const char *prompt, double *value)
{
    char line[TEXT_SIZE];
    char extraCharacter;

    while (1) {
        if (!readText(prompt, line, sizeof(line))) {
            return 0;
        }

        if (sscanf(line, "%lf %c", value, &extraCharacter) == 1) {
            return 1;
        }

        printf("Invalid value. Enter a decimal number.\n");
    }
}

/* Reads a yes/no answer and returns 1 for yes, 0 for no. */
static int readYesNo(const char *prompt)
{
    char answer[TEXT_SIZE];

    while (1) {
        if (!readText(prompt, answer, sizeof(answer))) {
            return 0;
        }

        if (answer[0] == 'y' || answer[0] == 'Y') {
            return 1;
        }

        if (answer[0] == 'n' || answer[0] == 'N') {
            return 0;
        }

        printf("Invalid command. Enter y or n.\n");
    }
}

/* Initializes an empty notebook list. */
void initializeList(struct NotebookList *list)
{
    if (list != NULL) {
        list->count = 0;
    }
}

/* Converts the first character of a string to uppercase. */
static char firstUppercaseCharacter(const char *text)
{
    if (text == NULL || text[0] == '\0') {
        return 'X';
    }

    return (char)toupper((unsigned char)text[0]);
}

/* Generates the notebook code automatically from its main identifying fields. */
static void generateCode(struct Notebook *notebook)
{
    if (notebook == NULL) {
        return;
    }

    snprintf(notebook->code,
             sizeof(notebook->code),
             "%c%c%c%.1f%d",
             firstUppercaseCharacter(notebook->brand),
             firstUppercaseCharacter(notebook->model),
             firstUppercaseCharacter(notebook->processor),
             notebook->screenSize,
             notebook->ram);
}

/* Prints one notebook in tabular format. */
void printNotebook(struct Notebook notebook)
{
    printf("%-12s %-12s %-12s %-12d %-8d %-12.1f %-14s %-18s %-8d %-12s",
           notebook.brand,
           notebook.model,
           notebook.processor,
           notebook.storage,
           notebook.ram,
           notebook.screenSize,
           notebook.inputOutput,
           notebook.operatingSystem,
           notebook.price,
           notebook.code);
}

/* Adds one notebook to the list if there is available space. */
void insertNotebook(struct NotebookList *list, struct Notebook notebook)
{
    if (list == NULL) {
        printf("\nInvalid list.\n");
        return;
    }

    if (list->count >= MAX) {
        printf("\nStock is full. The notebook could not be inserted.\n");
        return;
    }

    list->items[list->count++] = notebook;
}

/* Prints all notebooks currently stored in the list. */
void printNotebookList(struct NotebookList *list)
{
    unsigned index;

    if (list == NULL) {
        printf("\nInvalid list.\n");
        return;
    }

    printf("\n\n-------------------------------- Notebook List --------------------------------\n");
    printf("%-12s %-12s %-12s %-12s %-8s %-12s %-14s %-18s %-8s %-12s\n",
           "BRAND",
           "MODEL",
           "PROCESSOR",
           "STORAGE",
           "RAM",
           "SCREEN",
           "IN/OUT",
           "OS",
           "PRICE",
           "CODE");

    for (index = 0; index < list->count; index++) {
        printNotebook(list->items[index]);
        printf("\n");
    }

    printf("\n");
}

/* Searches for a notebook by code and returns its index, or -1 if not found. */
int findNotebookByCode(struct NotebookList *list, const char *code)
{
    unsigned index;

    if (list == NULL || code == NULL) {
        return -1;
    }

    for (index = 0; index < list->count; index++) {
        if (strcmp(code, list->items[index].code) == 0) {
            return (int)index;
        }
    }

    return -1;
}

/* Searches for a notebook by brand and returns the first matching index. */
int findNotebookByBrand(struct NotebookList *list, const char *brand)
{
    unsigned index;

    if (list == NULL || brand == NULL) {
        return -1;
    }

    for (index = 0; index < list->count; index++) {
        if (strcmp(list->items[index].brand, brand) == 0) {
            return (int)index;
        }
    }

    return -1;
}

/* Searches for a notebook by processor and returns the first matching index. */
int findNotebookByProcessor(struct NotebookList *list, const char *processor)
{
    unsigned index;

    if (list == NULL || processor == NULL) {
        return -1;
    }

    for (index = 0; index < list->count; index++) {
        if (strcmp(list->items[index].processor, processor) == 0) {
            return (int)index;
        }
    }

    return -1;
}

/* Prints all notebooks that match the given brand. */
void printNotebooksByBrand(struct NotebookList *list, const char *brand)
{
    unsigned index;

    if (findNotebookByBrand(list, brand) == -1) {
        printf("\nThis brand is out of stock.\n");
        return;
    }

    printf("\n\n------------------------------ Notebooks by Brand ------------------------------\n");
    printf("%-12s %-12s %-12s %-12s %-8s %-12s %-14s %-18s %-8s %-12s\n",
           "BRAND",
           "MODEL",
           "PROCESSOR",
           "STORAGE",
           "RAM",
           "SCREEN",
           "IN/OUT",
           "OS",
           "PRICE",
           "CODE");

    for (index = 0; index < list->count; index++) {
        if (strcmp(list->items[index].brand, brand) == 0) {
            printNotebook(list->items[index]);
            printf("\n");
        }
    }

    printf("\n");
}

/* Prints all notebooks that match the given processor. */
void printNotebooksByProcessor(struct NotebookList *list, const char *processor)
{
    unsigned index;

    if (findNotebookByProcessor(list, processor) == -1) {
        printf("\nComputers with this processor are out of stock.\n");
        return;
    }

    printf("\n\n--------------------------- Notebooks by Processor -----------------------------\n");
    printf("%-12s %-12s %-12s %-12s %-8s %-12s %-14s %-18s %-8s %-12s\n",
           "BRAND",
           "MODEL",
           "PROCESSOR",
           "STORAGE",
           "RAM",
           "SCREEN",
           "IN/OUT",
           "OS",
           "PRICE",
           "CODE");

    for (index = 0; index < list->count; index++) {
        if (strcmp(list->items[index].processor, processor) == 0) {
            printNotebook(list->items[index]);
            printf("\n");
        }
    }

    printf("\n");
}

/* Comparison function used by qsort to sort notebooks by price. */
int compareByPrice(const void *firstNotebook, const void *secondNotebook)
{
    const struct Notebook *notebookOne = (const struct Notebook *)firstNotebook;
    const struct Notebook *notebookTwo = (const struct Notebook *)secondNotebook;

    if (notebookOne->price < notebookTwo->price) {
        return -1;
    }

    if (notebookOne->price > notebookTwo->price) {
        return 1;
    }

    return 0;
}

/* Comparison function used by qsort to sort notebooks by processor. */
int compareByProcessor(const void *firstNotebook, const void *secondNotebook)
{
    const struct Notebook *notebookOne = (const struct Notebook *)firstNotebook;
    const struct Notebook *notebookTwo = (const struct Notebook *)secondNotebook;

    return strcmp(notebookOne->processor, notebookTwo->processor);
}

/* Comparison function used by qsort to sort notebooks by brand. */
int compareByBrand(const void *firstNotebook, const void *secondNotebook)
{
    const struct Notebook *notebookOne = (const struct Notebook *)firstNotebook;
    const struct Notebook *notebookTwo = (const struct Notebook *)secondNotebook;

    return strcmp(notebookOne->brand, notebookTwo->brand);
}

/* Removes a notebook from the list by code and returns the removed record. */
struct Notebook removeNotebook(struct NotebookList *list, const char *code)
{
    int foundIndex;
    unsigned index;
    struct Notebook removedNotebook;

    memset(&removedNotebook, 0, sizeof(removedNotebook));

    if (list == NULL || code == NULL) {
        printf("\nInvalid list or code.\n");
        return removedNotebook;
    }

    foundIndex = findNotebookByCode(list, code);

    if (foundIndex == -1) {
        printf("\nNotebook not found.\n");
        return removedNotebook;
    }

    removedNotebook = list->items[foundIndex];

    for (index = (unsigned)foundIndex; index + 1 < list->count; index++) {
        list->items[index] = list->items[index + 1];
    }

    list->count--;

    return removedNotebook;
}

/* Checks whether a code already exists, ignoring one specific index. */
static int codeExistsExcept(struct NotebookList *list, const char *code, int ignoredIndex)
{
    unsigned index;

    if (list == NULL || code == NULL) {
        return 0;
    }

    for (index = 0; index < list->count; index++) {
        if ((int)index != ignoredIndex && strcmp(list->items[index].code, code) == 0) {
            return 1;
        }
    }

    return 0;
}

/* Updates only the notebook fields selected by the user. */
void updateNotebook(struct NotebookList *list, const char *code)
{
    int foundIndex;
    int codeFieldsChanged = 0;
    char previousCode[CODE_SIZE];

    if (list == NULL || code == NULL) {
        printf("\nInvalid list or code.\n");
        return;
    }

    foundIndex = findNotebookByCode(list, code);

    if (foundIndex == -1) {
        printf("\nNotebook not found.\n");
        return;
    }

    strncpy(previousCode, list->items[foundIndex].code, sizeof(previousCode));
    previousCode[sizeof(previousCode) - 1] = '\0';

    if (readYesNo("\nDo you want to update the brand? (y/n): ")) {
        readText("New brand: ", list->items[foundIndex].brand, sizeof(list->items[foundIndex].brand));
        codeFieldsChanged = 1;
    }

    if (readYesNo("\nDo you want to update the model? (y/n): ")) {
        readText("New model: ", list->items[foundIndex].model, sizeof(list->items[foundIndex].model));
        codeFieldsChanged = 1;
    }

    if (readYesNo("\nDo you want to update the processor? (y/n): ")) {
        readText("New processor: ", list->items[foundIndex].processor, sizeof(list->items[foundIndex].processor));
        codeFieldsChanged = 1;
    }

    if (readYesNo("\nDo you want to update the storage capacity? (y/n): ")) {
        readInteger("New storage capacity: ", &list->items[foundIndex].storage);
    }

    if (readYesNo("\nDo you want to update the RAM capacity? (y/n): ")) {
        readInteger("New RAM capacity: ", &list->items[foundIndex].ram);
        codeFieldsChanged = 1;
    }

    if (readYesNo("\nDo you want to update the screen size? (y/n): ")) {
        readDouble("New screen size: ", &list->items[foundIndex].screenSize);
        codeFieldsChanged = 1;
    }

    if (readYesNo("\nDo you want to update the input/output information? (y/n): ")) {
        readText("New input/output information: ",
                 list->items[foundIndex].inputOutput,
                 sizeof(list->items[foundIndex].inputOutput));
    }

    if (readYesNo("\nDo you want to update the operating system? (y/n): ")) {
        readText("New operating system: ",
                 list->items[foundIndex].operatingSystem,
                 sizeof(list->items[foundIndex].operatingSystem));
    }

    if (readYesNo("\nDo you want to update the price? (y/n): ")) {
        readInteger("New price: ", &list->items[foundIndex].price);
    }

    if (codeFieldsChanged) {
        generateCode(&list->items[foundIndex]);

        if (codeExistsExcept(list, list->items[foundIndex].code, foundIndex)) {
            strncpy(list->items[foundIndex].code, previousCode, sizeof(list->items[foundIndex].code));
            list->items[foundIndex].code[sizeof(list->items[foundIndex].code) - 1] = '\0';

            printf("\nThe new code already exists. The previous code was kept: %s\n", previousCode);
        } else {
            printf("\nCode updated automatically: %s\n", list->items[foundIndex].code);
        }
    }
}

/* Reads a new notebook from the user and adds it to the list. */
void addNotebook(struct NotebookList *list, struct Notebook newNotebook)
{
    if (list == NULL) {
        printf("\nInvalid list.\n");
        return;
    }

    if (list->count >= MAX) {
        printf("\nStock is full. The notebook could not be inserted.\n");
        return;
    }

    memset(&newNotebook, 0, sizeof(newNotebook));

    printf("\n\n--- Insert New Notebook ---\n");

    readText("Brand: ", newNotebook.brand, sizeof(newNotebook.brand));
    readText("Model: ", newNotebook.model, sizeof(newNotebook.model));
    readText("Processor: ", newNotebook.processor, sizeof(newNotebook.processor));
    readInteger("Storage capacity: ", &newNotebook.storage);
    readInteger("RAM capacity: ", &newNotebook.ram);
    readDouble("Screen size: ", &newNotebook.screenSize);
    readText("Input/output information: ", newNotebook.inputOutput, sizeof(newNotebook.inputOutput));
    readText("Operating system: ", newNotebook.operatingSystem, sizeof(newNotebook.operatingSystem));
    readInteger("Price: ", &newNotebook.price);

    generateCode(&newNotebook);

    if (findNotebookByCode(list, newNotebook.code) != -1) {
        printf("\n**** Existing notebook. Duplicated code: %s ****\n", newNotebook.code);
        return;
    }

    insertNotebook(list, newNotebook);

    printf("\nNotebook inserted successfully. Generated code: %s\n", newNotebook.code);
}