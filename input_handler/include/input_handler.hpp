
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
#ifndef INPUT_HANDLER_INCLUDE_INPUT_HANDLER_HPP_
#define INPUT_HANDLER_INCLUDE_INPUT_HANDLER_HPP_

#include "smokey_data.hpp"
#include "../../can_encoder/include/interface_from_input_handler.hpp"

class InputHandler {
 private:
 public:
    Payload_t SmokeyInputData;
    bool InitInputHandler();
    bool ReadUserInput(GetNewValues &get_new_values); // NOLINT 
    bool ExitInputHandler();
};

#endif  // INPUT_HANDLER_INCLUDE_INPUT_HANDLER_HPP_

