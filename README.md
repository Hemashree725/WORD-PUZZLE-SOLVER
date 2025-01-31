# WORD-PUZZLE-SOLVER
 The Word Puzzle Solver is a console-based game where players unscramble jumbled words to earn points and progress through different difficulty levels. The game includes user registration, login, and score tracking to maintain player progress.
 

 **Key Features:**
1) User Authentication
~Players must register and log in before playing.
~Password validation ensures strong security.

2) Game Levels & Word Selection
~Three difficulty levels: Easy, Medium, and Hard.
~Each level has a predefined set of words that get scrambled.

3) Gameplay Mechanics
~Players are presented with a scrambled word and must guess the correct word.
~They have 5 attempts per word.
~Correct answers earn 10 points and advance the player to the next level.
~Players can retry or change the difficulty if they fail.

4) Score & Progress Tracking
~Player scores are saved in a progress file.
~Leaderboards are maintained for each difficulty level.
~Scores are ranked to determine top players.

5) Random Word Scrambling
~The game shuffles words uniquely to ensure unpredictability.


**Files Used in the Project:**
1) user_data.txt
~Stores registered user credentials (username and password).
~Used in registration (register_user()) and login (login_user()).

2) user_progress.txt
~Stores user progress (username and score).
~Used in saving progress (save_user_data(), update_user_progress()) and loading progress (load_user_data()).

3) easy_leaderboard.txt
~Stores scores of players who played in Easy mode.
~Used in updating and ranking (update_leaderboard(), assign_ranks_and_save()).

4) medium_leaderboard.txt
~Stores scores of players who played in Medium mode.
~Used in updating and ranking (update_leaderboard(), assign_ranks_and_save()).

5) hard_leaderboard.txt
~Stores scores of players who played in Hard mode.
~Used in updating and ranking (update_leaderboard(), assign_ranks_and_save()).

**Operations Performed on These Files:**
--Read (r): Loading user credentials, progress, and leaderboard data.
--Write (w): Updating user progress and ranking players in the leaderboard.
--Append (a): Saving new user credentials and adding scores to leaderboards.


**Step-by-Step Working of the Project:**

1. Program Initialization
>The game starts with a welcome message.
>The player is asked to register or log in.

2. User Registration & Login
Registration (register_user())
>The player enters a username and password (validated for security).
>The credentials are stored in user_data.txt.
>The user’s score is initialized to 0 and saved in user_progress.txt.

Login (login_user())
>The player enters existing credentials.
>The program verifies them from user_data.txt.
>If successful, the user’s saved score is retrieved from user_progress.txt.

3. Game Setup
>The player chooses a difficulty level:
*Easy
*Medium
*Hard
>Based on the choice, a predefined set of words is selected.

4. Gameplay (gameplay())
>A random word from the chosen level is scrambled using jumbleWord().
>The scrambled word is displayed, and the player gets 5 attempts to guess the correct word.
>If the guess is correct:
*10 points are awarded.
*The player moves to the next word.
*Score is saved in user_progress.txt.
>If all 5 attempts fail:
*The player can retry, change difficulty, or quit.

5. Score & Leaderboard Handling
>At the end of the game, the player’s score is updated in the respective leaderboard file:
*easy_leaderboard.txt (Easy Mode)
*medium_leaderboard.txt (Medium Mode)
*hard_leaderboard.txt (Hard Mode)
>The leaderboard is sorted to rank players (assign_ranks_and_save()).

6. Exiting the Game
>The player can choose to play again or exit.
>The final message thanks the player for playing.


**[Main Functions & Their Roles]:-**

Function Name                             |                               	Purpose
>main()                                   |              	Handles user login, level selection, and game loop.
>register_user()                          |              	Registers new users with validated passwords.
>login_user()                             |              	Authenticates users from stored data.
>load_user_data()                         |              	Retrieves user progress from file.
>save_user_data()                         |              	Saves user progress (score) to file.
>update_user_progress()	                  |               Updates user progress when they finish a game.
>user_choice()                            |              	Takes user input for difficulty level.
>Game_Rules()                             |              	Displays game rules.
>jumbleWord()                             |              	Scrambles words for the game.
>gameplay()	                              |               Core game logic—handles word guessing and scoring.
>update_leaderboard()	                    |               Updates leaderboard file with user scores.
>assign_ranks_and_save()                  |              	Sorts and ranks players in the leaderboard.



 
