#include "visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void menu(void) {
  system("cls");
  int choice;
  printf("Welcome to the Candy Game !\n");
  printf("1. Rules\n");
  printf("2. New Game\n");  
  printf("3. Load Game\n");
  printf("4. Exit\n");
  scanf("%d",choice);  
  if (choice == 1) {
      rules();
  } else if (choice == 2) {
      NewGame();
  } else if (choice == 3) {
      Chargegame();
  } else {
      leave();
  }
}

void rules(void) {
    system("cls");
    printf("Here are the rules of the Candy Game...\n");
    // Add more detailed rules here
    printf("Press any key to return to the menu.\n");
    getch();
    menu();
}
void leave(void) {
    system("cls");
    printf("Thank you for playing the Candy Game! Goodbye!\n");
    exit(0);
}
void NewGame(void) {
    system("cls");
    printf("Starting a new game...\n");
    // Initialize game state here
    printf("Press any key to return to the menu.\n");
    getch();
    menu();
}

void Chargegame(void) {
    system("cls");
    printf("Loading a saved game...\n");
    // Load game state here
    printf("Press any key to return to the menu.\n");
    getch();
    menu();
}

