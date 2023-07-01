/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "../include/workflow/genericworkflowserver.h"

#include <ods/odsfactory.h>

using namespace ods;

namespace workflow {

GenericWorkflowServer::GenericWorkflowServer() {
  OdsFactory::CreateDefaultTemplateTask(*this);
}

std::unique_ptr<IRunner> GenericWorkflowServer::CreateRunner(const IRunner& source) {
  auto db_task = OdsFactory::CreateTemplateTask(source);
  if (db_task) {
    return db_task;
  }
  return WorkflowServer::CreateRunner(source);
}

void GenericWorkflowServer::CreateDefaultTemplates() {

  WorkflowServer::CreateDefaultTemplates();
}


}  // namespace workflow