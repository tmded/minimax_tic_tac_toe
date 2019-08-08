//
// Created by mdavies4 on 07/07/2019.
//

#include "curses_game.hpp"
#include "curses_wrapper.hpp"
#include "../common_tools/common_tools.hpp"
#include "../minimax_algorithm/minimax_algorithm.hpp"
#include <iostream>
#include <curses.h>
#include <unistd.h>

int main_game_curses();
int checkwin_curses(std::vector<char> square,char team);
std::string board_curses(std::vector<char> square,int aiplayer);


curses_wrapper curses;



int main_game_curses()
{
    int ai_player =1;
    int player = 1;
    int choice;
    int i;
    std::vector<char> square = {'1','2','3','4','5','6','7','8','9'};
    curses.clear_screen();
    std::string minimax_logo="  __  __ _       _                      \n"
                             " |  \\/  (_)     (_)                     \n"
                             " | \\  / |_ _ __  _ _ __ ___   __ ___  __\n"
                             " | |\\/| | | '_ \\| | '_ ` _ \\ / _` \\ \\/ /\n"
                             " | |  | | | | | | | | | | | | (_| |>  < \n"
                             " |_|  |_|_|_| |_|_|_| |_| |_|\\__,_/_/\\_\\\n"
                             "                                        \n"
                             "\n"
                             "  _______ _        _______           _______         \n"
                             " |__   __(_)      |__   __|         |__   __|        \n"
                             "    | |   _  ___     | | __ _  ___     | | ___   ___ \n"
                             "    | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\\n"
                             "    | |  | | (__     | | (_| | (__     | | (_) |  __/\n"
                             "    |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___|\n"
                             "                                                     \n"
                             "\n"
                             "  _____             ___           _           ___ __  _ ___ \n"
                             " |_   _|__ _ __    |   \\ __ ___ _(_)___ ___  |_  )  \\/ / _ \\\n"
                             "   | |/ _ \\ '  \\   | |) / _` \\ V / / -_|_-<   / / () | \\_, /\n"
                             "   |_|\\___/_|_|_|  |___/\\__,_|\\_/|_\\___/__/  /___\\__/|_|/_/ \n"
                             "                                                            \n"
                             "\n"
                             "Press enter to start.";
    curses.get_int(minimax_logo);
    std::string question="\n"
                         "\n"
                         " __   __                          ____  \n"
                         " \\ \\ / /                         / __ \\ \n"
                         "  \\ V /          ______         | |  | |\n"
                         "   > <          |______|        | |  | |\n"
                         "  / . \\                         | |__| |\n"
                         " /_/ \\_\\                         \\____/ \n"
                         "                                        \n"
                         "                                        \n"
                         "Which Team would you like to play on?"
                         "\n\n"
                         "X moves first."
                         "\n\nEnter your choice now:";
    std::string question_reasked="\n"
                         "\n"
                         " __   __                          ____  \n"
                         " \\ \\ / /                         / __ \\ \n"
                         "  \\ V /          ______         | |  | |\n"
                         "   > <          |______|        | |  | |\n"
                         "  / . \\                         | |__| |\n"
                         " /_/ \\_\\                         \\____/ \n"
                         "                                        \n"
                         "                                        \n"
                         "Which Team would you like to play on?"
                         "\n\n"
                         "X moves first."
                         "\n\nSorry you must enter either X or O."
                         "\n\nEnter your choice now:";
    curses.clear_screen();
    std::string team_choice = (curses.get_string(question));
    while (team_choice != std::to_string('X') and team_choice != std::to_string('x') and team_choice != std::to_string('O') and team_choice != std::to_string('o')){
        curses.clear_screen();
        team_choice = (curses.get_string(question_reasked));}
    if (team_choice == std::to_string('X') or team_choice == std::to_string('x')){
        ai_player = 2;
    }
    else if (team_choice == std::to_string('O') or team_choice == std::to_string('o')){
        ai_player =1;
    }
    curses.clear_screen();
    char mark;
    char mark_e;
    do
    {
        player=(player%2)?1:2;
        curses.clear_screen();
        std::string message = (board_curses(square,ai_player)+ "Player "+std::to_string(player)+ ", enter a number:  ");

//        choice = curses.get_int(message);
        mark=(player == 1) ? 'X' : 'O';
        mark_e =(player==1) ? 'O' : 'X';
//        curses.middle_print(reinterpret_cast<const char *>(mark));
        if (player == ai_player)
            choice = choice_minimax(checkwin_curses, square, mark, mark_e);
        else choice = curses.get_int(message);

        if (choice == 1 && square[0] == '1')

            square[0] = mark;
        else if (choice == 2 && square[1] == '2')

            square[1] = mark;
        else if (choice == 3 && square[2] == '3')

            square[2] = mark;
        else if (choice == 4 && square[3] == '4')

            square[3] = mark;
        else if (choice == 5 && square[4] == '5')

            square[4] = mark;
        else if (choice == 6 && square[5] == '6')

            square[5] = mark;
        else if (choice == 7 && square[6] == '7')

            square[6] = mark;
        else if (choice == 8 && square[7] == '8')

            square[7] = mark;
        else if (choice == 9 && square[8] == '9')

            square[8] = mark;
        else
        {
            curses.clear_screen();
            std::string M =("Invalid move press enter to re-enter.");

            player--;
            curses.get_int(M);
        }
        i=checkwin_curses(square,mark);

        player++;
    }while(i==-1);
    board_curses(square,ai_player);
    if(i==1){
        curses.clear_screen();
        curses.get_int(board_curses(square,ai_player)+"Player "+std::to_string(--player)+" win "+"\n Press enter to close.");}
    else
        curses.get_int(board_curses(square,ai_player)+"Game draw \n press enter to close.");
    curses.close_screen();
    return 0;
}

/*********************************************
    FUNCTION TO RETURN GAME STATUS
    1 FOR GAME IS OVER WITH RESULT
    -1 FOR GAME IS IN PROGRESS
    O GAME IS OVER AND NO RESULT
**********************************************/




int checkwin_curses(std::vector<char> square,char team)
{
    if (square[0] == square[1] && square[1] == square[2])
        if (square[0] == team){return 1;}
        else{return -1;}
    else if (square[3] == square[4] && square[4] == square[5])
        if (square[3] == team){return 1;}
        else{return -1;}
    else if (square[6] == square[7] && square[7] == square[8])
        if (square[6] == team){return 1;}
        else{return -1;}
    else if (square[0] == square[3] && square[3] == square[6])
        if (square[0] == team){return 1;}
        else{return -1;}
    else if (square[1] == square[4] && square[4] == square[7])
        if (square[1] == team){return 1;}
        else{return -1;}
    else if (square[2] == square[5] && square[5] == square[8])
        if (square[2] == team){return 1;}
        else{return -1;}
    else if (square[0] == square[4] && square[4] == square[8])
        if (square[0] == team){return 1;}
        else{return -1;}
    else if (square[2] == square[4] && square[4] == square[6])
        if (square[2] == team){return 1;}
        else{return -1;}
    else if (square[0] != '1' && square[1] != '2' && square[2] != '3'
             && square[3] != '4' && square[4] != '5' && square[5] != '6'
             && square[6] != '7' && square[7] != '8' && square[8] != '9')
        return 0;
    else
        return -1;
}


/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
********************************************************************/


std::string board_curses(std::vector<char> square,int aiplayer)
{
    curses.clear_screen();
    std::string board_string;
    board_string = "";
    board_string = board_string+ "\n\nTic Tac Toe\n\n";
    if (aiplayer==1){board_string = board_string+"AI Player (X) - Player 1 (O)" + "\n\n";}
    else board_string = board_string+"Player 1 (X)  -  AI Player (O)" + "\n\n";
    board_string = board_string+ "\n";

    board_string = board_string+ "     |     |     " + "\n";
    board_string = board_string+ "" + square[0] + "  |  " + square[1] + "  |  " + square[2] + "\n";

    board_string = board_string+ "_____|_____|_____" + "\n";
    board_string = board_string+ "     |     |     " + "\n";

    board_string = board_string+ "" + square[3] + "  |  " + square[4] + "  |  " + square[5] + "\n";

    board_string = board_string+ "_____|_____|_____" + "\n";
    board_string = board_string+ "     |     |     " + "\n";

    board_string = board_string+ "" + square[6] + "  |  " + square[7] + "  |  " + square[8] + "\n";

    board_string = board_string+ "     |     |     " + "\n" + "\n";
    return board_string;

}

/*******************************************************************
                END OF PROJECT
********************************************************************/