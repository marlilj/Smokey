/**
 * Copyright (C) - Volvo Car Corporation
 *
 * All Rights Reserved
 *
 * LEGAL NOTICE:  All information (including intellectual and technical concepts) contained herein
 * is, and remains the property of or licensed to Volvo Car Corporation.
 * This information is proprietary to Volvo Car Corporation and may be covered by patents or patent
 * applications. This information is protected by trade secret or copyright law. Dissemination of
 * this information or reproduction of this material is strictly forbidden unless prior written
 * permission is obtained from Volvo Car Corporation.
 *
 * This file was generated fri Nov 12 11:07:24 2021
 */

//////////////////////////////////////////////////
// Dependencies

#ifndef INTERFACETOCANENCODER_HPP  // NOLINT
#define INTERFACETOCANENCODER_HPP

#include <ncurses.h>
#include <string>
#include <iostream>

class SendNewValues {
 private:
 public:
    int16_t sendNewValues(int16_t value_to_can_encoder);
};

#endif  // INTERFACETOCANENCODER_HPP // NOLINT