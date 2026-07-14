/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <wx/wx.h>
#include <workflow/parameter.h>

namespace workflow::gui {

class ParameterDialog : public wxDialog {
 public:
  ParameterDialog(wxWindow* parent, Parameter& parameter );

  bool TransferDataToWindow() override;
  bool TransferDataFromWindow() override;
 private:
  Parameter& parameter_;

  wxString name_;
  wxString display_name_;
  wxString description_;
  wxString data_type_;
  wxString unit_;
  wxString device_;
  wxString identity_;
  wxString signal_;
 wxDECLARE_EVENT_TABLE();
};

} // end namespace




