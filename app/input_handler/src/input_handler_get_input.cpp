/*
 * Copyright (C) 2021 - Volvo Car Corporation
 *
 * All Rights Reserved
 *
 * LEGAL NOTICE:  All information (including intellectual and technical concepts) contained herein
 * is, and remains the property of or licensed to Volvo Car Corporation.
 * This information is proprietary to Volvo Car Corporation and may be covered by patents or patent
 * applications. This information is protected by trade secret or copyright law. Dissemination of
 * this information or reproduction of this material is strictly forbidden unless prior written
 * permission is obtained from Volvo Car Corporation.
 */
#include "../include/input_handler.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <iostream>


bool InputHandler::InitInputHandler() {
  initscr();
  noecho();
  cbreak();
  nodelay(stdscr, TRUE);
  curs_set(0);

  return true;
}

bool InputHandler::ReadUserInput(GetNewValues &get_new_values) {
  int ch;
  printw("Set the throttle! \n");
  // printw("Current throttle setting: \n");
  printw("Current input: \n");

  for (;;) {
    if ((ch = getch()) == ERR) {
      // No user input.throttle
    } else if ( (48 <= ch) && (ch <= 57) ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.throttle = (ch-48)*10;
        get_new_values.getNewValues(SmokeyInputData);
    } else if ( ch == 112 || ch == 110 || ch == 100 || ch == 114 ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.gear = ch;
        get_new_values.getNewValues(SmokeyInputData);
    } else if ( ch == 115 && !SmokeyInputData.start ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.start = 1;
        get_new_values.getNewValues(SmokeyInputData);
    } else if ( ch == 115 && SmokeyInputData.start ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.start = 0;
        get_new_values.getNewValues(SmokeyInputData);
    }
    usleep(5);
  }

  return true;
}

bool InputHandler::ExitInputHandler() {
  endwin();
  return true;
}

