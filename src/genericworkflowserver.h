/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <workflow/workflowserver.h>

namespace workflow {

class GenericWorkflowServer : public WorkflowServer {
 public:
  GenericWorkflowServer();
  [[nodiscard]] std::unique_ptr<IRunner> CreateRunner(
      const IRunner& source) override;
  void CreateDefaultTemplates() override;
};

}  // namespace workflow
