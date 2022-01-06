#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME  "Assignment4_butt.bin"
typedef struct {
    int id;
    char title[45];
    char author[45];
    char note[100];
} book;

//validates the name of book, author,and note
//allows spaces to be used in names, author, and note
//takes input aslong as new line is entered
//purpose is for error checking and allowing spaces in names

int isValid(const char *name) {
    int validName = 1;
    int length = 0;
    int index = 0;
    length = strlen(name);
    for (index = 0; index < length; ++index) {
        if (!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' ')) {
            validName = 0;
            break;
        }
    }
    return validName;
}




/*void listbook(){



}*/
// Add books in list
void addBook() {

    //create a structure for empty book
    //create file pointer
    book bookinfo = {0};
    FILE *fp = NULL;
    int status = 0;

    //opens file
    //assignment4_butt.txt
    // if cannot find file,
    //prints file cannot be opened

    fp = fopen(FILE_NAME, "ab+");
    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

//asks user for input into book structure
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tBook ID NO  = ");
    scanf("%d", &bookinfo.id);
    fflush(stdin);

    //read book name as string from user
    //if invalid returns error prompt
    printf("\n\t\t\tBook Name  = ");
    fgets(bookinfo.title, 45, stdin);
    status = isValid(bookinfo.title);
    if (!status) {
        printf("\n\t\t\tName contain invalid character. Please enter again.");
    }

    //read author name as string from user
    //if invalid returns error prompt
    printf("\n\t\t\tAuthor Name  = ");
    fgets(bookinfo.author, 45, stdin);
    status = isValid(bookinfo.author);
    if (!status) {
        printf("\n\t\t\tName contain invalid character. Please enter again.");
    }

    //read book name as string from user
    //if invalid returns error prompt
    printf("\n\t\t\tBook note  = ");
    fgets(bookinfo.note, 100, stdin);
    status = isValid(bookinfo.note);
    if (!status) {
        printf("\n\t\t\tNote contain invalid character. Please enter again.");
    }

    //writes everything to the assignment_butt.txt file
    //in the order of the members of bookinfo
    //
    fwrite(&bookinfo, sizeof(bookinfo), 1, fp);
    //closes file
    fclose(fp);

}

//function to view books
void viewBooks() {

    int found = 0;
    char bookName[45] = {0};
    book bookinfo = {0};
    FILE *fp = NULL;
    int status = 0;

    //opens file
    //if not opened, returns error prompt
    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    //while loop to read lines until end of file
    //read a pointer to book info
    //# of bytes to be read specified by sizeof bookinfo structure
    //read from pointer to assignment_butt.txt file
    while (fread(&bookinfo, sizeof(bookinfo), 1, fp)) {

        printf("\n\t\t\tID:\t  %d", bookinfo.id);
        printf("\n\n\t\t\tTitle:\t  %s", bookinfo.title);
        printf("\n\t\t\tAuthor:\t  %s", bookinfo.author);
        printf("\n\t\t\tNote:\t  %s", bookinfo.note);
        printf("=====================================================");
        found = 1;
    }

    //closes file
    fclose(fp);

    //if no records are found (found = 0) prints no record
    if (!found) {
        printf("\n\t\t\tNo Record");
    }
    //flush standard input to permanent memory
    fflush(stdin);


}

void deleteBook() {
    int found = 0;
    int bookDelete = 0;

    book bookinfo = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    tmpFp = fopen("tmp.bin", "wb");
    if (tmpFp == NULL) {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }

/*
    fread(&fp, 100, 1, fp);
    fwrite(&fp, 100, 1, tmpFp);
*/


    printf("\n\t\t\tEnter Book ID NO. for delete:");
    scanf("%d", &bookDelete);

    while (fread(&bookinfo, sizeof(bookinfo), 1, fp)) {
        printf("Read ok\n");
        if (bookinfo.id != bookDelete) {
            fwrite(&bookinfo, sizeof(bookinfo), 1, tmpFp);
        } else {
            found = 1;
        }
    }

    (found) ? printf("\n\t\t\tRecord deleted successfully.....") : printf("\n\t\t\tRecord not found");

    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin", FILE_NAME);

}

/*void searchbook(){
 * printf("== Enter book ID to search ( 1 - 100 ):");

}*/

void searchBookid() {
    int found = 0;
    char bookid[100] = {0};
    book bookinfo = {0};
    FILE *fp = NULL;
    int status = 0;
    int id;

    //open file
    //if error while opening
    //display error prompt
    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    //prompt user to enter book id as a string to search
    //flush input to memory
    //change ID string to id integer
    printf("\n\n\t\t\tEnter Book ID to search:");
    fflush(stdin);
    fgets(bookid, 100, stdin);
    id = atoi(bookid);

    //while loop to read lines until end of file
    //read a pointer to book info
    //# of bytes to be read specified by sizeof bookinfo structure
    //read from pointer to assignment_butt.txt file
    while (fread(&bookinfo, sizeof(bookinfo), 1, fp))

        //if id integer matches a book id within the file,
        //print the book
    {
        if (id == bookinfo.id) {
            found = 1;
            break;
        }

    }

    //if the book is found
    // prints the book
    if (found) {
        printf("\n\t\t\tBook id = %u\n", bookinfo.id);
        printf("\t\t\tBook name = %s", bookinfo.title);
        printf("\t\t\tBook authorName = %s", bookinfo.author);
        printf("\t\t\tBook authorName = %s", bookinfo.note);

        //if book is not found, prints no record
    } else {
        printf("\n\t\t\tNo Record");
    }

    //close the file
    fclose(fp);

}


//function to print the menu
//prompt when program is executed
void printmenu() {
    printf("====== MAIN ======\n"
           "0 - Exit Program\n"
           "1 - List all Books\n"
           "2 - Add a New Book\n"
           "3 - Delete a Book\n"
           "4 - Search a Book by ID\n"
           "==================\n");
}

void textFile(FILE *readPtr);

void deleteRecord(FILE *fPtr);

void newRecord(FILE *fPtr);

int main(void) {

    int choice = 1;

    while (choice != 0) {
        printmenu();
        printf("Enter your choice:\n");
        scanf("%d", &choice);

        //switch loop for each possible input as a case
        switch (choice) {

            case 0:
                printf("== Thank You, Bye-Bye!");
                break;
            case 1:
                viewBooks();//display list
                break;
            case 2:
                addBook(); //add new book
                break;
            case 3:
                //delete book
                deleteBook();
                break;
            case 4:
                searchBookid();
                //search for book id
                break;
        }
    }
}
