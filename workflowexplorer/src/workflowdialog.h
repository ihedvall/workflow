/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/

#pragma once
#include <wx/wx.h>
#include <workflow/workflow.h>
namespace workflow::gui {

class WorkflowDialog : public wxDialog {
 public:
  WorkflowDialog(wxWindow* parent, Workflow& workflow );

  bool TransferDataToWindow() override;
  bool TransferDataFromWindow() override;
 private:
  Workflow& workflow_;
  wxString name_;
  wxString description_;
  wxString event_;
  wxDECLARE_EVENT_TABLE();
};


}  // namespace workflow::gui
