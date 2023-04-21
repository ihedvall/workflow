/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "generalpanel.h"
#include <wx/withimages.h>

#include <string>
#include <set>
#include "workflowexplorerid.h"
#include "workflowexplorer.h"
#include "propertydialog.h"

namespace {

// constexpr int kWorkflowBmp = 0;
// constexpr int kRunnerBmp = 1;
// constexpr int kEventBmp = 2;
// constexpr int kParameterBmp = 3;
// constexpr int kDeviceBmp = 4;
constexpr int kPropertyBmp = 5;

}

namespace workflow::gui {
wxBEGIN_EVENT_TABLE(GeneralPanel, wxPanel)
    EVT_UPDATE_UI(kIdNewProperty, GeneralPanel::OnUpdateNewProperty)
    EVT_MENU(kIdNewProperty, GeneralPanel::OnNewProperty)
    EVT_UPDATE_UI(kIdEditProperty, GeneralPanel::OnUpdateSingleProperty)
    EVT_MENU(kIdEditProperty, GeneralPanel::OnEditProperty)
    EVT_TREELIST_ITEM_CONTEXT_MENU(kIdGeneralList, GeneralPanel::OnRightClick)
    EVT_TREELIST_ITEM_ACTIVATED(kIdGeneralList, GeneralPanel::OnDoubleClick)
wxEND_EVENT_TABLE()

GeneralPanel::GeneralPanel(wxWindow *parent)
  : wxPanel(parent),
    image_list_(16, 16, false, 6),
    list_(new wxTreeListCtrl(this, kIdGeneralList, wxDefaultPosition,
                             {800, 600}, wxTL_SINGLE)) {
  image_list_.Add(wxBitmap("TREE_LIST", wxBITMAP_TYPE_BMP_RESOURCE));

  list_->SetImageList(&image_list_);
  list_->AppendColumn(L"Property Key");
  list_->AppendColumn(L"Value");


  auto *main_sizer = new wxBoxSizer(wxVERTICAL);
  main_sizer->Add(list_, 1, wxALIGN_LEFT | wxALL | wxEXPAND, 0);

  SetSizerAndFit(main_sizer);
}

void GeneralPanel::RedrawPropertyList() {
  wxBusyCursor wait;
  if (list_ == nullptr) {
    return;
  }

  std::set<std::string> selected_list;
  const auto root_item = list_->GetRootItem();
  for ( wxTreeListItem item = list_->GetFirstItem();
       item.IsOk();
       item = list_->GetNextItem(item) ) {
    const auto parent_item = list_->GetItemParent(item);
    if (parent_item != root_item) {
      continue;
    }
    if (list_->IsSelected(item)) {
      const auto name = list_->GetItemText(item).ToStdString();
      selected_list.emplace(name);
    }
  }

  list_->DeleteAllItems();

  const auto& app = wxGetApp();
  const auto& server = app.Server();
  const auto& prop_list = server.ApplicationProperties();
  for (const auto& itr : prop_list) {
    const auto& key = itr.first;
    const auto& value = itr.second;
    const auto item = list_->AppendItem(root_item,
                                        wxString::FromUTF8(key),
                                        kPropertyBmp,kPropertyBmp,
                                        nullptr);
    list_->SetItemText(item, 1, wxString::FromUTF8(value));
    const auto selected_itr = selected_list.find(key);
    if (selected_itr != selected_list.cend()) {
      list_->Select(item);
    }
  }
}

void GeneralPanel::Update() {
  wxWindow::Update();
  RedrawPropertyList();
}

std::string GeneralPanel::GetSelectedPropertyKey() const {
  if (list_ == nullptr) {
    return {};
  }
  const auto root_item = list_->GetRootItem();
  wxTreeListItems selection_list;
  list_->GetSelections(selection_list);
  std::set<std::string> key_list;
  for (const auto& item : selection_list) {
    const auto parent_item = list_->GetItemParent(item);
    if (parent_item == root_item) {
      const auto key = list_->GetItemText(item).ToStdString();
      key_list.emplace(key);
    }
  }
  if (key_list.size() != 1) {
    return {};
  }
  return *key_list.cbegin();
}

void GeneralPanel::SelectItem(const std::string& key) {
  if (list_ == nullptr) {
    return ;
  }
  const auto root_item = list_->GetRootItem();
  for ( wxTreeListItem item = list_->GetFirstItem();
       item.IsOk();
       item = list_->GetNextItem(item) ) {
    const auto parent_item = list_->GetItemParent(item);
    const auto name = list_->GetItemText(item).ToStdString();
    if (parent_item == root_item) {
      if (key == name) {
        list_->Select(item);
      } else {
        list_->Unselect(item);
      }
    }
  }
}

void GeneralPanel::OnUpdateNewProperty(wxUpdateUIEvent &event) {
  event.Enable(list_ != nullptr);
}

void GeneralPanel::OnUpdateSingleProperty(wxUpdateUIEvent &event) {
  event.Enable(!GetSelectedPropertyKey().empty());
}


void GeneralPanel::OnNewProperty(wxCommandEvent&) {
  if (list_ == nullptr) {
    return;
  }

  PropertyDialog dialog(this, true);
  const auto ret = dialog.ShowModal();
  if (ret != wxID_OK) {
    return;
  }
  const auto key = dialog.Key();
  const auto value = dialog.Value();

  auto& app = wxGetApp();
  auto& server = app.Server();
  auto& prop_list = server.ApplicationProperties();

  const auto exist = prop_list.find(key) != prop_list.cend();
  if (exist) {
    std::ostringstream msg;
    msg << "The name of the new property key needs to be unique." << std::endl;
    msg << "Key: " << key << std::endl;
    wxMessageBox(msg.str(), "Fail to Add Application Property",
                 wxCENTRE | wxICON_ERROR, this);
    return;
  }

  server.SetApplicationProperty(key, value);
  RedrawPropertyList();
  SelectItem(dialog.Key());
}

void GeneralPanel::OnEditProperty(wxCommandEvent&) {
  auto& app = wxGetApp();
  auto& server = app.Server();
  auto key = GetSelectedPropertyKey();
  auto value = server.GetApplicationProperty<std::string>(key);

  PropertyDialog dialog(this, false);
  dialog.Key(key);
  dialog.Value(value);

  const auto ret = dialog.ShowModal();
  if (ret != wxID_OK) {
    return;
  }
  server.SetApplicationProperty(dialog.Key(),dialog.Value());
  RedrawPropertyList();
}

void GeneralPanel::OnRightClick(wxTreeListEvent&) {
  wxMenu menu;

  menu.Append(kIdNewProperty, wxGetStockLabel(wxID_NEW));
  menu.Append(kIdEditProperty, wxGetStockLabel(wxID_EDIT));
  menu.AppendSeparator();
  menu.Append(kIdOpenLogFile, L"Open Log File");

  PopupMenu(&menu);
}

void GeneralPanel::OnDoubleClick(wxTreeListEvent& event) {
  const auto key = GetSelectedPropertyKey();
  if (!key.empty()) {
    OnEditProperty(event);
  }
}

}  // namespace workflow
