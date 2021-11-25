
/*
 * Copyright (C) 2021 - Volvo Car Corporation
 */

#include "canio.hpp"

int main() {
  SocketCan socket_can("vcan0");
  if (socket_can.getStatus() == STATUS_OK) {
    for (int j = 0; j < 20000; ++j) {
      CanFrame fr;

      while (socket_can.read(fr) == STATUS_OK) {
        printf(
            "len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x "
            "%02x  \n",
            fr.len, fr.id, fr.data[0], fr.data[1], fr.data[2], fr.data[3],
            fr.data[4], fr.data[5], fr.data[6], fr.data[7]);
      }
    }
  } else {
    printf("Cannot open can socket!");
  }
  return 0;

}
