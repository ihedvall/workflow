/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "workflow/genericworkflowserver.h"

#include <ods/odsfactory.h>
#include <workflow/itaskfactory.h>
using namespace ods;

namespace workflow {

GenericWorkflowServer::GenericWorkflowServer() {
  const auto& ods_factory = OdsFactory::Instance();
  AddTaskFactory(ods_factory);
}


}  // namespace workflow