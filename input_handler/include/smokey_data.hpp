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

#ifndef INPUT_HANDLER_INCLUDE_SMOKEY_DATA_HPP_
#define INPUT_HANDLER_INCLUDE_SMOKEY_DATA_HPP_


typedef struct SmokeyPayload {
  int throttle;
  int gear;
}Payload_t;

#endif  // INPUT_HANDLER_INCLUDE_SMOKEY_DATA_HPP_