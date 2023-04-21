/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
#include <wx/wx.h>
#pragma once
namespace workflow::gui {

class PropertyDialog : public wxDialog  {
 public:
 PropertyDialog(wxWindow* parent, bool new_prop);

  void Key(const std::string& key);
  [[nodiscard]] std::string Key();

  void Value(const std::string& value);
  [[nodiscard]] std::string Value();

 private:

  wxString group_;
  wxString leaf_;
  wxString value_;
  wxDECLARE_EVENT_TABLE();
};

}  // namespace workflow::gui
