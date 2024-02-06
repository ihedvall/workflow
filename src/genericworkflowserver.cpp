/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "workflow/genericworkflowserver.h"

#include <ods/odsfactory.h>
#include <workflow/irunnerfactory.h>
using namespace ods;

namespace workflow {

GenericWorkflowServer::GenericWorkflowServer() {
  const auto& ods_factory = OdsFactory::Instance();
  AddRunnerFactory(ods_factory);
}


}  // namespace workflow