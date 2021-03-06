
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
#ifndef SMOKEYDATA_HPP  // NOLINT
#define SMOKEYDATA_HPP

#include <iostream>

const unsigned k_FrameIdUserInput = 1;
const unsigned k_FrameIdEmulator = 2;
typedef struct __attribute__((__packed__)) SmokeyPayload {
  uint8_t throttle = 0;
  uint8_t gear = 112;
  uint8_t start = 0;
  uint8_t breaking = 0;
  uint8_t shutdown = 0;
} Payload_t;

typedef struct __attribute__ ((__packed__)) EmulatorOutput {
  uint8_t speed;
  uint8_t gear;
  uint16_t rpm;
  uint8_t breaking;
  uint8_t shutdown;
  uint8_t pindle;
  uint8_t start;
} EmulatorOutput_t;

const bool kSuccess = false;
const bool kFailure = true;

#endif  // SMOKEYDATA_HPP // NOLINT
