/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "propertydialog.h"
#include <sstream>

namespace workflow::gui {
wxBEGIN_EVENT_TABLE(PropertyDialog, wxDialog)
wxEND_EVENT_TABLE()

PropertyDialog::PropertyDialog(wxWindow *parent, bool new_prop)
 : wxDialog(parent, wxID_ANY, "Application Property Dialog" ,
             wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
  auto *group = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                               wxDefaultPosition,
                              wxDefaultSize, new_prop ? 0 : wxTE_READONLY,
                              wxTextValidator( wxFILTER_EMPTY |
                                               wxFILTER_ALPHANUMERIC, &group_));
  group->SetMinSize({20 * 10, -1});
  auto *sep = new wxStaticText(this, wxID_ANY, L"/");
  auto *leaf = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                               wxDefaultSize, new_prop ? 0 : wxTE_READONLY,
                               wxTextValidator( wxFILTER_ALPHANUMERIC |
                                                   wxFILTER_SPACE, &leaf_));
  leaf->SetMinSize({20 * 10, -1});

  auto *value = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                              wxDefaultPosition, wxDefaultSize, 0,
                              wxTextValidator(wxFILTER_NONE, &value_));
  value->SetMinSize({50 * 10, -1});

  auto *save_button_ = new wxButton(this, wxID_OK,
                                    wxGetStockLabel(wxID_SAVE,
                                                    wxSTOCK_FOR_BUTTON));
  auto *cancel_button_ = new wxButton(this, wxID_CANCEL,
                                      wxGetStockLabel(wxID_CANCEL,
                                                      wxSTOCK_FOR_BUTTON));

  auto *key_label = new wxStaticText(this, wxID_ANY, L"Key:");
  auto *value_label = new wxStaticText(this, wxID_ANY, L"Value:");


  int label_width = 100;
  label_width = std::max(label_width, key_label->GetBestSize().GetX());
  label_width = std::max(label_width, value_label->GetBestSize().GetX());

  key_label->SetMinSize({label_width, -1});
  value_label->SetMinSize({label_width, -1});


  auto *key_sizer = new wxBoxSizer(wxHORIZONTAL);
  key_sizer->Add(key_label, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
  key_sizer->Add(group, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
  key_sizer->Add(sep, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
  key_sizer->Add(leaf, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

  auto *value_sizer = new wxBoxSizer(wxHORIZONTAL);
  value_sizer->Add(value_label, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
  value_sizer->Add(value, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);


  auto *system_sizer = new wxStdDialogButtonSizer();
  system_sizer->AddButton(save_button_);
  system_sizer->AddButton(cancel_button_);
  system_sizer->Realize();

  auto *cfg_box = new wxStaticBoxSizer(wxVERTICAL, this,
                                       L"Property Configuration");
  cfg_box->Add(key_sizer, 0, wxALIGN_LEFT | wxALL, 1);
  cfg_box->Add(value_sizer, 0, wxALIGN_LEFT | wxALL, 1);

  auto *main_sizer = new wxBoxSizer(wxVERTICAL);
  main_sizer->Add(cfg_box, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 4);
  main_sizer->Add(system_sizer, 0,
                  wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxLEFT | wxRIGHT, 10);

  SetSizerAndFit(main_sizer);
  if (new_prop) {
    save_button_->SetDefault();
  } else {
    cancel_button_->SetDefault();
  }

}

void PropertyDialog::Key(const std::string &key) {
  auto sep = key.find('/');
  if (sep == std::string::npos) {
    group_ = wxString::FromUTF8(key);
    leaf_.Empty();
  } else {
    const auto group = key.substr(0, sep);
    ++sep;
    const auto leaf = key.substr(sep);
    group_ = wxString::FromUTF8(group);
    leaf_ = wxString::FromUTF8(leaf);
  }
}

std::string PropertyDialog::Key() {
  group_.Trim(true).Trim(false);
  leaf_.Trim(true).Trim(false);

  auto group = group_.utf8_string();
  auto leaf = leaf_.utf8_string();

  std::ostringstream temp;
  temp << group;
  if (!leaf.empty()) {
    temp << "/" << leaf;
  }
  return temp.str();
}

void PropertyDialog::Value(const std::string &value) {
  value_ = wxString::FromUTF8(value);
}

std::string PropertyDialog::Value() {
  value_.Trim(true).Trim(false);
  return value_.utf8_string();
}

}  // namespace workflow::gui