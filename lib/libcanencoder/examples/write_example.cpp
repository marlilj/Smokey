/*
 * Copyright (C) 2021 - Volvo Car Corporation
 */

#include "canio.hpp"

int main() {
  SocketCan socket_can("vcan0");
  if (socket_can.getStatus() == STATUS_OK) {
    for (int j = 0; j < 20000; ++j) {
      CanFrame cf_to_write;

      cf_to_write.id = 123;
      cf_to_write.len = 8;
      for (int i = 0; i < 8; ++i) cf_to_write.data[i] = j & (254);
      auto write_sc_status = socket_can.write(cf_to_write);
      if (write_sc_status != STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n",
               int32_t(write_sc_status));
      else
        printf("Message was written to the socket \n");
    }
  } else {
    printf("Cannot open can socket!");
  }
  return 0;
}
