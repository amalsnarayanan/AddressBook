#include <stdio.h>
#include "contact.h"
#include<stdlib.h>
#include "file.h"

int main()
 {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n======================================== ADDRESS BOOK MENU =================================================\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. save contact\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                    exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
    
       return 0;
}
