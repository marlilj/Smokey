#include "../include/canio.hpp"

#include <linux/can/raw.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

SocketCan::SocketCan(const std::string &can_interface,
                     int32_t read_timeout_ms) {
  m_interface = can_interface;
  m_read_timeout_ms = read_timeout_ms;
  m_status = this->open();
}

SocketCanStatus SocketCan::open() {
  /* open socket */
  if ((m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
    perror("socket");
    return STATUS_SOCKET_CREATE_ERROR;
  }
  int mtu, enable_canfd = 1;
  struct sockaddr_can addr;
  struct ifreq ifr;

  strncpy(ifr.ifr_name, m_interface.c_str(), IFNAMSIZ - 1);
  ifr.ifr_name[IFNAMSIZ - 1] = '\0';
  ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);

  if (!ifr.ifr_ifindex) {
    perror("if_nametoindex");
    return STATUS_INTERFACE_NAME_TO_IDX_ERROR;
  }

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  struct timeval tv;
  tv.tv_sec = 0; /* 30 Secs Timeout */
  tv.tv_usec =
      m_read_timeout_ms * 1000;  // Not init'ing this can cause strange errors
  setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv,
             sizeof(struct timeval));

  if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    return STATUS_BIND_ERROR;
  }
  return STATUS_OK;
}

SocketCanStatus SocketCan::write(const CanFrame &msg) {
  struct can_frame frame;
  memset(&frame, 0, sizeof(frame)); /* init CAN FD frame, e.g. LEN = 0 */
  // convert CanFrame to can_frame
  frame.can_id = msg.id;
  frame.can_dlc = msg.len;
  memcpy(frame.data, msg.data, msg.len);

  /* send frame */
  if (::write(m_socket, &frame, static_cast<int>(CAN_MTU))
        != static_cast<int>(CAN_MTU)) {
    perror("write");
    return STATUS_WRITE_ERROR;
  }
  return STATUS_OK;
}

SocketCanStatus SocketCan::read(CanFrame &msg) {
  struct can_frame frame;

  // Read in a CAN frame
  auto num_bytes = ::read(m_socket, &frame, CAN_MTU);
  if (num_bytes != CAN_MTU && num_bytes != CAN_MTU) {
    // perror("Can read error");
    return STATUS_READ_ERROR;
  }

  msg.id = frame.can_id;
  msg.len = frame.can_dlc;
  memcpy(msg.data, frame.data, frame.can_dlc);
  return STATUS_OK;
}

SocketCanStatus SocketCan::close() {
  ::close(m_socket);
  return STATUS_OK;
}

const std::string &SocketCan::interfaceName() const { return m_interface; }

const SocketCanStatus &SocketCan::getStatus() const { return m_status; }

SocketCan::~SocketCan() { close(); }

