#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<io.h>
#define MAX_QUESTION_LENGTH 200
d
// Function to display the question;
void displayQuestion(char Qustions[], char options[MAX_QUESTION_LENGTH]){
    puts(Qustions);
    puts(options);
}

// Function to set record;
void save_record(char username[], char user_reg[], int score){
    FILE* pr;
    pr = fopen("record.text", "a");
    if (pr == NULL){
        printf("error!");
    }

    fprintf(pr, "\n");
    fprintf(pr, "Username:");
    fputs(username, pr);
    fprintf(pr, "Reg no:");
    fputs(user_reg, pr);
    fprintf(pr, "Total Score:");
    fprintf(pr, "%d", score);
    fprintf(pr, "\n");
    fclose(pr);
}

int main(){
    // Display Welcome Message
    printf("--------------------------------------------------------------------------\n");
    char welcome[] = "Welcome to DSU Quiz Game";
    for(int i=0; i<strlen(welcome); i++){
        printf("  %c", welcome[i]);
        fflush(stdout);
        Sleep(100);
    }
    printf("\n--------------------------------------------------------------------------\n");

    FILE* ptr;
    char filename[] = "Qustion.text";
    char Questions[MAX_QUESTION_LENGTH];
    char option[MAX_QUESTION_LENGTH];
    char originalAnswer[MAX_QUESTION_LENGTH/2];
    char username[MAX_QUESTION_LENGTH];
    char user_reg[MAX_QUESTION_LENGTH];
    char userAnswer, confirm;
    int repty = 0;
    int score = 0;

    ptr = fopen(filename, "r");
    if (ptr == NULL){
        printf("Error!\nI have not questions");
        printf("\nfile %s is not found", filename);
        return 1;
    }

    // Taking user information
    printf("Enter your name:");
    fgets(username, MAX_QUESTION_LENGTH/2, stdin);
    printf("Enter your reg number:");
    fgets(user_reg, MAX_QUESTION_LENGTH/2, stdin);

    // Confirmation
    printf("\n");
    printf("Press S for start:");
    scanf("%c", &confirm);
    printf("\n");

    // Game start
    if(confirm == 's' || confirm == 'S'){
        do {
            // Display Welcome Message again when he/she wants to play again
            if (repty == 1){
                printf("-----------------------------------------------------------------------------------------\n");
                char welcome[] = "Welcome Back to DSU Quiz Game";
                for(int i=0; i<strlen(welcome); i++){
                    printf("  %c", welcome[i]);
                    fflush(stdout);
                    Sleep(100);
                }
                printf("\n-----------------------------------------------------------------------------------------\n");
            }
            rewind(ptr);
            ptr = fopen(filename, "r");

            if (ptr == NULL) {
                printf("Error!\nI have not questions");
                printf("\nfile %s is not found", filename);
            }

            while (fgets(Questions, MAX_QUESTION_LENGTH, ptr) != NULL) { // Qustion reading from file
                fgets(option, MAX_QUESTION_LENGTH, ptr);// Option reading from file
                fgets(originalAnswer, MAX_QUESTION_LENGTH / 2, ptr);// Right Answer reading from file
                printf("\n");

                displayQuestion(Questions, option);// Display the qustion and option

                printf("Enter your Answer(A-D):");
                scanf(" %c", &userAnswer);// Taking answer from user

                userAnswer = toupper(userAnswer);// If user put a small alphabet, this function changes it to upper

                if (userAnswer == 'A' || userAnswer == 'B' || userAnswer == 'C' || userAnswer == 'D') {
                    if (userAnswer == originalAnswer[0]) {
                        printf("RIGHT Answer!\n");
                        score++;
                    } else {
                        printf("WRONG Answer\nThe right answer is %s\n", originalAnswer);
                    }
                } else {
                    printf("Invalid option Enter A-D\n");
                    fseek(ptr, -(strlen(Questions) + strlen(option) + strlen(originalAnswer)), SEEK_CUR);
                }
            }
            fclose(ptr);

            save_record(username, user_reg, score);

            printf("Congratulations! You have passed the test. Your total score is %d\n", score);

            printf("Do you want to play again? Type '1' for Yes and '0' for No: ");
            scanf("%d", &repty);
            score = 0;
            system("cls");
        } while (repty == 1);
    } else {
        printf("Start Again\n");
    }
    printf("Thank you");

    getche();
    return 0;
}
