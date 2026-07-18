#include "contact.h"
#include<string.h>
#include<stdio.h>
#include <ctype.h>
#include "populate.h"
#include "file.h"
#include "sort.h"

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
   
   load_data_from_file(addressBook);
}

void listContacts(AddressBook *addressBook)
{
    
    int choice;

    printf("List the contacts based on \n1.Name\n2.Phone Number\n3.Email\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);

    sortaddress(addressBook, choice);

    printf("\n======================================== SORTED CONTACTS =================================================\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%15s%15s%30s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
       
    }
}

void createContact(AddressBook *addressBook)
{
    
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full! Maximum 100 contacts allowed.\n");
        return;
    }


    
    Contact new;
    printf("\nName of person : ");
    scanf(" %[^\n]",new.name);   
     for(int i = 0; new.name[i] != '\0'; i++)
    {
        if(isdigit(new.name[i]))
        {
            printf("Invalid name! Numbers are not allowed.\n");
            return;
        }
    }

    printf("Phone Number : ");
    scanf(" %[^\n]",new.phone);  
    if(strlen(new.phone) != 10)
    {
        printf("Invalid phone number! Must contain exactly 10 digits.\n");
        return;
    }
    for(int i = 0; new.phone[i] != '\0'; i++)
    {
        if(!isdigit(new.phone[i]))
        {
            printf("Invalid phone number! Only digits allowed.\n");
            return;
        }
    }


    printf("Email : ");
    scanf(" %[^\n]",new.email);  
    int at_found = 0, dot_found = 0;

    for(int i = 0; new.email[i] != '\0'; i++)
    {
        if(new.email[i] == '@')
            at_found = 1;
        if(new.email[i] == '.')
            dot_found = 1;
    }

    if(!at_found || !dot_found)
    {
        printf("Invalid email! Must contain '@' and '.'.\n");
        return;
    }

    addressBook->contacts[addressBook->contactCount] = new ;
    addressBook->contactCount++ ;
    printf("Contact successfully added");
    
    
}

void searchContact(AddressBook *addressBook)
{
    char buffer[50];
    int choice;
    printf("how do you want to search?\n");
    printf("1.Name\n2.Phone Number\n3.Email\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1 :  
        printf("Enter the name you want to search : ");
        scanf(" %[^\n]",buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, buffer))
            {
                printf("Contact found successfully\n");
                printf("%20s%15s%35s\n",addressBook->contacts[i].name ,addressBook->contacts[i].phone ,addressBook->contacts[i].email);
            }
        }
        break;

        case 2 :  
        printf("Enter the phone number you want to search : ");
        scanf(" %[^\n]",buffer);
        for(int i = 0; i< addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].phone, buffer))
            {
                printf("Contact found successfully\n");
                printf("%20s%15s%35s\n",addressBook->contacts[i].name ,addressBook->contacts[i].phone ,addressBook->contacts[i].email);
            }
        }
        break;

        case 3 :  
        printf("Enter the email you want to search : ");
        scanf(" %[^\n]",buffer);
        for(int i = 0; i< addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email, buffer))
            {
                printf("Contact found successfully\n");
                printf("%20s%15s%35s\n",addressBook->contacts[i].name ,addressBook->contacts[i].phone ,addressBook->contacts[i].email);
            }
        }
        break;

        default :
        printf("Enter valid input\n");
        break;
    }
}

void editContact(AddressBook *addressBook)
{
    char buffer[50];
    printf("Enter the contact you want to edit : ");
    scanf(" %[^\n]", buffer);
    for (int i = 0; i < addressBook->contactCount ; i++)
    {
        if(strcasestr(addressBook->contacts[i].name, buffer))
        {
            printf("Editing contact : %s\n",addressBook->contacts[i].name);
            printf("Enter new name : \n");
            scanf(" %[^\n]", addressBook->contacts[i].name);
            printf("Enter new phone number : \n");
            scanf(" %[^\n]", addressBook->contacts[i].phone);
            printf("Enter new email : \n");
            scanf(" %[^\n]", addressBook->contacts[i].email);
            printf("Contact successfully edited\n");
            return ;
        }
    }

    printf("Contact does not exist\n");
}

void deleteContact(AddressBook *addressBook)
{
    char buffer[50];
    printf("Enter the contact you want to delete : ");
    scanf(" %[^\n]", buffer);
    for (int i = 0; i < addressBook->contactCount ; i++)
    {
        if(strcasestr(addressBook->contacts[i].name, buffer))
        {
            for (int j = i ; j < addressBook->contactCount-1 ; j++ )
            {
                  addressBook->contacts[j] = addressBook->contacts[j + 1] ;
            }
            addressBook->contactCount-- ;
            printf("Contact deleted successfully\n");
            return ;
        }
    } 
    printf("Contact is not found\n") ;
}

void sortaddress(AddressBook *addressBook, int choice)
{
    int i, j;
    Contact temp;

    for (i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            int result = 0;

            switch (choice)
            {
                case 1:
                    result = strcmp(addressBook->contacts[j].name,
                                    addressBook->contacts[j + 1].name);
                    break;

                case 2:
                    result = strcmp(addressBook->contacts[j].phone,
                                    addressBook->contacts[j + 1].phone);
                    break;

                case 3:
                    result = strcmp(addressBook->contacts[j].email,
                                    addressBook->contacts[j + 1].email);
                    break;

                default:
                    printf("Invalid choice\n");
                    return;
            }

            if (result > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}
