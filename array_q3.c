#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_TEAMS 10
#define SQUAD_SIZE 25

// using struct to store DOB of teammate 
typedef struct {
    int D , M , Y;
} date_p;

// using struct for teammate information 
typedef struct {
    char name[25];            // name variable can have 25 characters 
    int kitNumber;            // kit number fro 1 to 99 
    char club[30];            // club name can have 30 characters 
    date_p dob;               // DOB 
    char position[20];        // position of the player with 20 characters 
} player_p;

// Struct for team information
typedef struct {
    char name[20];            // name of the team with 20 characters 
    player_p players[SQUAD_SIZE]; // an array that contains all the players 
    int no_of_players;           // no. of players in the team 
} team_p;

// an array that contains all the teams 
team_p teams[NUM_TEAMS];
int no_of_teams = 0; // counting the number of teams 

//  pre defined function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(const char message[]);

int main() {
    int option;

    
    while (1) {
    display_menu();
    printf("Select your option: ");
    scanf("%d", &option);

    if (option == 1) {
        enroll_club();
    } else if (option == 2) {
        add_player();
    } else if (option == 3) {
        search_update();
    } else if (option == 4) {
        display_club_statistics();
    } else if (option == 5) {
        printf("Quitting the code.\n");
        return 0;
    } else {
        handle_error("You have selected the wrong option, quitting the code.");
        return 0;
    }
 }

}

// displaying the menu 
void display_menu() {
    printf("\n '''''MANAGING OFFICIALS OF THE SPORT''''' \n 1. Enrolling  the club \n 2. Add Player\n 3. Search and Update Player\n 4. Display Club records\n 5. quit\n");
   
}

// adding a new club 
void enroll_club() {
    if (no_of_teams >= NUM_TEAMS) {
        handle_error("not able to enroll anymore clubs. Max size reached .");
        return;
    }

    printf("type the  club name: ");
    getchar(); 
    fgets(teams[no_of_teams].name, 21, stdin);
    teams[no_of_teams].name[strcspn(teams[no_of_teams].name, "\n")] = '\0'; 
    teams[no_of_teams].no_of_players = 0;

    no_of_teams++;
    printf("the typed Club is added correctly!\n");
}

// adding player to a club 
void add_player() {
    // checking if there is a club avaiable 
    if (no_of_teams == 0) {
        handle_error("you dont have any clubs yet , first add some clubs ");
        return;
    }

    // dislaying all the clubs for the user to choose 
    printf("select the club that you want to add the player to \n");
    for (int i = 0; i < no_of_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }
    
    // taking the users choice 
    int club_choice;
    scanf("%d", &club_choice);

    // checking is the user chose correct option , and if theres no error 
    if (club_choice < 1 || club_choice > no_of_teams) {
        handle_error("wrong choice , please select theplayer from the list ");
        return;
    }
    club_choice--;

    // checking if anymore players can be added 
    if (teams[club_choice].no_of_players >= SQUAD_SIZE) {
        handle_error("this team is full , please try some other team ");
        return;
    }

    
    player_p new_player;

    // asking the new players name 
    printf("type the name of the new player  ");
    getchar(); 
    fgets(new_player.name, 26, stdin);
    new_player.name[strcspn(new_player.name, "\n")] = '\0'; 

    // asking the new players kit number 
    printf("what is the kit number of  %s  (Choose between 1 and 99) ", new_player.name);
    scanf("%d", &new_player.kitNumber);

    // checking if the same player is not added already 
    for (int i = 0; i < teams[club_choice].no_of_players; i++) {
        if (teams[club_choice].players[i].kitNumber == new_player.kitNumber ||
            strcasecmp(teams[club_choice].players[i].name, new_player.name) == 0) {
            handle_error("sorry , there is already a player with that name or kit number ");
            return;
        }
    }

    // asking the players position 
    printf("which position does %s play? ", new_player.name);
    getchar(); 
    fgets(new_player.position, 20, stdin);
    new_player.position[strcspn(new_player.position, "\n")] = '\0'; 

    // asking the players DOB 
    printf("what is the date of birth of  %s  (Please enter as DD MM YYYY) ", new_player.name);
    scanf("%d %d %d", &new_player.dob.D, &new_player.dob.M, &new_player.dob.Y);

    // adding the new player to the team 
    strcpy(new_player.club, teams[club_choice].name);
    teams[club_choice].players[teams[club_choice].no_of_players++] = new_player;

    printf("great  %s has been added to %s. sucessfully \n", new_player.name, new_player.club);
}

// updating players information 
void search_update() {
    char searchName[26];
    int kitNumber, available = 0;

    printf("Search by:\n1. Name\n2. Kit Number\nEnter option: "); 
    int option;
    scanf("%d", &option);

    if (option == 1) {
        printf("Type the player's name: ");
        getchar();      // Clear input buffer
        fgets(searchName, 26, stdin);
        searchName[strcspn(searchName, "\n")] = '\0';

        for (int i = 0; i < no_of_teams; i++) {
            for (int j = 0; j < teams[i].no_of_players; j++) {
                if (strcasecmp(teams[i].players[j].name, searchName) == 0) {
                    available = 1;
                    printf("the player is found in team  %s\n", teams[i].name);
                    printf("Kit Number: %d, Position: %s, DOB: %02d-%02d-%04d\n",
                           teams[i].players[j].kitNumber, teams[i].players[j].position,
                           teams[i].players[j].dob.D, teams[i].players[j].dob.M,
                           teams[i].players[j].dob.Y);
                    
                    // display the menu to edit player information 
                    printf("which of the player details would you like to  update?\n");
                    printf("1. Name\n2. Kit Number\n3. Position\n4. DOB\nEnter option: ");
                    int update_option;
                    scanf("%d", &update_option);

                    switch (update_option) {
                        case 1: 
                            printf("Enter the new name: ");
                            getchar();
                            fgets(teams[i].players[j].name, 26, stdin);
                            teams[i].players[j].name[strcspn(teams[i].players[j].name, "\n")] = '\0';
                            printf("Name updated successfully!\n");
                            break;
                        case 2:
                            printf("type the new kit number (1-99): ");
                            scanf("%d", &teams[i].players[j].kitNumber);
                            printf("Kit number updated successfully!\n");
                            break;
                        case 3:
                            printf("type the new position: ");
                            getchar();
                            fgets(teams[i].players[j].position, 20, stdin);
                            teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = '\0';
                            printf("Position updated successfully!\n");
                            break;
                        case 4:
                            printf("type  the new DOB (DD MM YYYY): ");
                            scanf("%d %d %d", &teams[i].players[j].dob.D,
                                  &teams[i].players[j].dob.M,
                                  &teams[i].players[j].dob.Y);
                            printf("DOB updated successfully!\n");
                            break;
                        default:
                            printf("your choice is invalid !\n");
                            break;
                    }
                    return; // quiting after updating using player name 
                }
            }
        }
    } else if (option == 2) {
        printf("Enter the kit number: ");
        scanf("%d", &kitNumber);

        for (int i = 0; i < no_of_teams; i++) {
            for (int j = 0; j < teams[i].no_of_players; j++) {
                if (teams[i].players[j].kitNumber == kitNumber) {
                    available = 1;
                    printf("Player found in team %s\n", teams[i].name);
                    printf("Name: %s, Position: %s, DOB: %02d-%02d-%04d\n",
                           teams[i].players[j].name, teams[i].players[j].position,
                           teams[i].players[j].dob.D, teams[i].players[j].dob.M,
                           teams[i].players[j].dob.Y);

                    // displaying the options to update the player information 
                    printf("What changes would you like to make ?\n");
                    printf("1. Name\n2. Kit Number\n3. Position\n4. DOB\nEnter option: ");
                    int update_option;
                    scanf("%d", &update_option);

                    switch (update_option) {
                        case 1:
                            printf("Enter the new name: ");
                            getchar();
                            fgets(teams[i].players[j].name, 26, stdin);
                            teams[i].players[j].name[strcspn(teams[i].players[j].name, "\n")] = '\0';
                            printf("Name updated successfully!\n");
                            break;
                        case 2:
                            printf("Enter the new kit number (1-99): ");
                            scanf("%d", &teams[i].players[j].kitNumber);
                            printf("Kit number updated successfully!\n");
                            break;
                        case 3:
                            printf("Enter the new position: ");
                            getchar();
                            fgets(teams[i].players[j].position, 20, stdin);
                            teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = '\0';
                            printf("Position updated successfully!\n");
                            break;
                        case 4:
                            printf("Enter the new DOB (DD MM YYYY): ");
                            scanf("%d %d %d", &teams[i].players[j].dob.D,
                                  &teams[i].players[j].dob.M,
                                  &teams[i].players[j].dob.Y);
                            printf("DOB updated successfully!\n");
                            break;
                        default:
                            printf("Invalid option!\n");
                            break;
                    }
                    return; // quiting after updating using kit number 
                }
            }
        }
    }

    if (!available) {
        handle_error("Player not found.");
    }
}


// displaying the clubs records 
void display_club_statistics() {
    printf("\n''''' Club Records '''''\n");
    for (int i = 0; i < no_of_teams; i++) {
        printf("Club: %s\n", teams[i].name);
        printf("no. of Players: %d\n", teams[i].no_of_players);
        for (int j = 0; j < teams[i].no_of_players; j++) {
            player_p p = teams[i].players[j];
            printf("  Name: %s, Kit: %d, Position: %s, DOB: %02d-%02d-%04d\n",
                   p.name, p.kitNumber, p.position, p.dob.D, p.dob.M, p.dob.Y);
        }
    }
}

// Error handling function 
void handle_error(const char message[]) {
    printf("Error: %s\n", message)
    ;
}
