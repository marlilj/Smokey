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
#include "input_handler.hpp"
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

  return kSuccess;
}

bool InputHandler::ReadUserInput(GetNewValues &get_new_values) {
  int ch;
  printw("Set the throttle! \n");
  // printw("Current throttle setting: \n");
  printw("Current input: \n");

  while (SmokeyInputData.shutdown == 0) {
    if ((ch = getch()) == ERR) {
      // No user input.throttle
    } else if ( (48 <= ch) && (ch <= 57) ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.throttle = (ch-48)*10;
    } else if ( ch == 112 || ch == 110 || ch == 100 || ch == 114 ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.gear = ch;
    } else if ( ch == 115 && !SmokeyInputData.start ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.start = 1;
    } else if ( ch == 115 && SmokeyInputData.start ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.start = 0;
    } else if ( ch == 98 && !SmokeyInputData.breaking ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.breaking = 1;
        SmokeyInputData.throttle = 0;
    } else if ( ch == 98 && SmokeyInputData.breaking ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.breaking = 0;
    } else if ( ch == 113 && !SmokeyInputData.shutdown ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.shutdown = 1;
        SmokeyInputData.start = 0;
    } else if ( ch == 113 && SmokeyInputData.shutdown ) {
        mvaddch(1, 26, ch);
        SmokeyInputData.shutdown = 0;
        SmokeyInputData.start = 1;
    }
    get_new_values.getNewValues(SmokeyInputData);
    usleep(5);
  }
  usleep(100000);
  SmokeyInputData.gear = 0;
  SmokeyInputData.start = 0;
  // Sending multiple times to make sure message is sent
  for (size_t i = 0; i < 10 ; i++) {
    get_new_values.getNewValues(SmokeyInputData);
    usleep(10000);
  }

  return kSuccess;
}

bool InputHandler::ExitInputHandler() {
  endwin();

  return kSuccess;
}

bool InputHandler::GracefulShutdown() {
  bool error_code = kFailure;
  // Delete stuff!
  error_code = kSuccess;
  return error_code;
}
