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

GetNewValues encoder;

bool InitInputHandler() {
  initscr();
  noecho();
  cbreak();
  nodelay(stdscr, TRUE);
  curs_set(0);

  return true;
}

bool ReadUserInput() {
  int ch;
  printw("Set the throttle! \n");
  printw("Current throttle setting: ");

  for (;;) {
    if ((ch = getch()) == ERR) {
      // No user input
    } else {
      mvaddch(1, 26, ch);
        encoder.getNewValues(&ch);
    }
    usleep(5);
  }

  return true;
}

bool ExitInputHandler() {
  endwin();
  return true;
}

