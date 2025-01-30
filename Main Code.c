#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 10
#define MAX_LENGTH 80
#define DATABASE_FILE "user_data.txt"
#define PROGRESS_FILE "user_progress.txt"
#define EASY_LEADERBOARD "easy_leaderboard.txt"
#define MEDIUM_LEADERBOARD "medium_leaderboard.txt"
#define HARD_LEADERBOARD "hard_leaderboard.txt"

// User struct to store username, password, and score
struct user_details {
    char username[20];
    char password[20];
    int score;
};

// Function Prototypes
int user_choice();
void Game_Rules();
void jumbleWord(char *word);
int gameplay(char userchoicewords[MAX_WORDS][MAX_LENGTH], struct user_details *u);
int register_user();
int login_user(struct user_details *u);
void save_user_data(struct user_details u);
int load_user_data(struct user_details *u);
int validate_password(char *password);
void update_leaderboard(const char *level_file, struct user_details u);
void assign_ranks_and_save(const char *level_file);
void update_user_progress(struct user_details *u);

int main() {
    int choice, play_again;
    struct user_details u;
    char Easy[MAX_WORDS][MAX_LENGTH] = {"BUS", "BALL", "RIVER", "CLOUD", "APPLE", "BUTTER", "PENCIL", "ANIMAL", "BOTTLE", "NATURE"};
    char Medium[MAX_WORDS][MAX_LENGTH] = {"GRASS", "WHALE", "CANDLE", "GIRAFFE", "DOLPHIN", "PYRAMID", "PENGUIN", "FOREST", "CUSHION", "JOURNAL"};
    char Hard[MAX_WORDS][MAX_LENGTH] = {"CRYSTAL", "FIREWORK", "ICEBERG", "DUNGEON", "MEADOWS", "LANTERNS", "CITADEL", "HARMONY", "SNOWFLAKE", "SANCTUARY"};
    char userchoicewords[MAX_WORDS][MAX_LENGTH] = {""};

    printf("WELCOME TO WORD SCRAMBLE GAME!!!\n");

    printf("Choose an option:\n");
    printf("1. Register\n2. Login\n");
    scanf("%d", &choice);

    if (choice == 1) {
        if (!register_user()) {
            printf("Registration failed.\n");
            return 1;
        }
    } else if (choice == 2) {
        if (!login_user(&u)) {
            printf("Login failed.\n");
            return 1;
        }
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    load_user_data(&u);

    do {
        do {
            choice = user_choice();
            switch (choice) {
                case 1:
                    memcpy(userchoicewords, Easy, sizeof(Easy));
                    printf("YOU HAVE CHOSEN EASY LEVEL! LET'S START!\n");
                    break;
                case 2:
                    memcpy(userchoicewords, Medium, sizeof(Medium));
                    printf("YOU HAVE CHOSEN MEDIUM LEVEL! LET'S START!\n");
                    break;
                case 3:
                    memcpy(userchoicewords, Hard, sizeof(Hard));
                    printf("YOU HAVE CHOSEN HARD LEVEL! LET'S START!\n");
                    break;
                default:
                    printf("Invalid choice! Please choose again.\n");
                    break;
            }
        } while (choice != 1 && choice != 2 && choice != 3);

        srand(time(NULL));
        Game_Rules();
        play_again = gameplay(userchoicewords, &u);

        if (play_again == 1) {
            continue;
        } else {
            // Update leaderboard based on the difficulty level
            if (choice == 1) {
                update_leaderboard(EASY_LEADERBOARD, u);
                assign_ranks_and_save(EASY_LEADERBOARD);
            } else if (choice == 2) {
                update_leaderboard(MEDIUM_LEADERBOARD, u);
                assign_ranks_and_save(MEDIUM_LEADERBOARD);
            } else if (choice == 3) {
                update_leaderboard(HARD_LEADERBOARD, u);
                assign_ranks_and_save(HARD_LEADERBOARD);
            }
        }
    } while (play_again == 2);

    printf("THANK YOU FOR PLAYING! SEE YOU AGAIN!\n");
}

int user_choice() {
    int choice;
    printf("PRESS '1' FOR EASY LEVEL\n");
    printf("PRESS '2' FOR MEDIUM LEVEL\n");
    printf("PRESS '3' FOR HARD LEVEL\n");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2 && choice != 3) {
        printf("CHOOSE CORRECT OPTION\n");
        return -1;
    }
    return choice;
}

void jumbleWord(char *word) {
    int length, i, j;
    char temp;
    char *initial = strdup(word);
    length = strlen(word);
    do {
        for (i = length - 1; i > 0; i--) {
            j = rand() % (i + 1);
            temp = word[i];
            word[i] = word[j];
            word[j] = temp;
        }
    } while (strcmp(word, initial) == 0);
    free(initial);
}

void Game_Rules() {
    printf("\n-INSTRUCTIONS-\n");
    printf("1. YOU WILL BE GIVEN A JUMBLE WORD TO SOLVE.\n");
    printf("2. YOU WILL HAVE 5 ATTEMPTS TO GUESS THE CORRECT WORD.\n");
    printf("3. ENTER ALL YOUR GUESS IN UPPERCASE ONLY.\n");
    printf("4. IF YOU GUESS CORRECTLY, YOU WILL MOVE TO NEXT LEVEL AND EARN 10 POINTS.\n");
    printf("5. TRY TO SOLVE ALL 10 WORDS GIVEN IN YOUR CHOSEN LEVEL.\n\n");
    printf("--------------GOOD LUCK------------------\n");
}

int gameplay(char userchoicewords[MAX_WORDS][MAX_LENGTH], struct user_details *u) {
    int i, number;
    char word[MAX_LENGTH];
    int MAX_ATTEMPTS = 5;
    char temp[MAX_WORDS][MAX_LENGTH];
    for (int j = 0; j < MAX_WORDS; j++) {
        strcpy(temp[j], userchoicewords[j]);
    }
    for (i = 0; i < MAX_WORDS; i++) {
        MAX_ATTEMPTS = 5;
        jumbleWord(userchoicewords[i]);
        printf("LEVEL %d :\n", i + 1);
        printf("\n%s\n", userchoicewords[i]);
        while (MAX_ATTEMPTS > 0) {
            printf("ENTER YOUR GUESS:\n");
            scanf("%s", word);
            if (strcmp(word, temp[i]) == 0) {
                printf("\nCORRECT GUESS!!\nYOU HAVE PASSED LEVEL %d\n", i + 1);
                u->score += 10;
                save_user_data(*u);
                if (i == MAX_WORDS - 1) {
                    printf("CONGRATULATIONS YOU HAVE COMPLETED ALL 10 LEVELS OF THIS DIFFICULTY!\n");
                }
                break;
            } else {
                printf("\nWRONG ANSWER, %d ATTEMPTS LEFT\n", MAX_ATTEMPTS - 1);
                MAX_ATTEMPTS--;
            }
        }
        if (MAX_ATTEMPTS == 0) {
            printf("ALL YOUR ATTEMPTS ARE OVER!!\n");
            printf("YOU WANNA CONTINUE THE GAME?\n");
            printf("\nCHOICE 1: RETRY THE LEVEL AND CONTINUE PLAYING\nPRESS '1' \n");
            printf("\nCHOICE 2: CHANGE THE DIFFICULTY LEVEL AND CONTINUE PLAYING\nPRESS '2' \n");
            printf("\nCHOICE 3: QUIT!\nPRESS '3' \n");
            scanf("%d", &number);
            if (number == 1) {
                printf("\nRETRY THE LEVEL %d:\n", i + 1);
                i--;
                continue;
            }
            return number;
        }
    }
    return 2;
}

int register_user() {
    struct user_details u;
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    printf("Enter your desired username: ");
    scanf("%s", u.username);

    char password[MAX_LENGTH];
    printf("Enter a password (must contain uppercase, lowercase, and special characters): ");
    scanf("%s", password);
    if (!validate_password(password)) {
        printf("Password must contain uppercase, lowercase, and special characters.\n");
        fclose(file);
        return 0;
    }
    strcpy(u.password, password);

    u.score = 0;
    fprintf(file, "%s %s\n", u.username, u.password);
    fclose(file);
    save_user_data(u);
    return 1;
}

int login_user(struct user_details *u) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char username[MAX_LENGTH], password[MAX_LENGTH];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s", u->username, u->password) != EOF) {
        if (strcmp(u->username, username) == 0 && strcmp(u->password, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    printf("Invalid username or password.\n");
    fclose(file);
    return 0;
}

void save_user_data(struct user_details u) {
    FILE *file = fopen(PROGRESS_FILE, "a");
    if (file == NULL) {
        printf("Error saving progress.\n");
        return;
    }
    fprintf(file, "%s %d\n", u.username, u.score);
    fclose(file);
}

int load_user_data(struct user_details *u) {
    FILE *file = fopen(PROGRESS_FILE, "r");
    if (file == NULL) {
        printf("Error loading progress.\n");
        return 0;
    }
    while (fscanf(file, "%s %d", u->username, &u->score) != EOF) {
        if (strcmp(u->username, u->username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int validate_password(char *password) {
    int has_upper = 0, has_lower = 0, has_special = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (ispunct(password[i])) has_special = 1;
    }
    return has_upper && has_lower && has_special;
}

void update_leaderboard(const char *level_file, struct user_details u) {
    FILE *file = fopen(level_file, "a");
    if (file == NULL) {
        printf("Error opening leaderboard file.\n");
        return;
    }
    fprintf(file, "%s %d\n", u.username, u.score);
    fclose(file);
}

void assign_ranks_and_save(const char *level_file) {
    FILE *file = fopen(level_file, "r");
    if (file == NULL) {
        printf("Error opening leaderboard file.\n");
        return;
    }
    struct user_details users[MAX_WORDS];
    int count = 0;
    while (fscanf(file, "%s %d", users[count].username, &users[count].score) != EOF) {
        count++;
    }
    fclose(file);

    // Sort users by score
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (users[i].score < users[j].score) {
                struct user_details temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    // Save sorted leaderboard
    file = fopen(level_file, "w");
    if (file == NULL) {
        printf("Error opening leaderboard file.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", users[i].username, users[i].score);
    }
    fclose(file);
}

void update_user_progress(struct user_details *u) {
    FILE *file = fopen(PROGRESS_FILE, "w");
    if (file == NULL) {
        printf("Error updating progress.\n");
        return;
    }
    fprintf(file, "%s %d\n", u->username, u->score);
    fclose(file);
}
