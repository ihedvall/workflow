/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <wx/wx.h>
#include <wx/treelist.h>
namespace workflow::gui {

class GeneralPanel : public wxPanel {
 public:
  explicit GeneralPanel(wxWindow* parent);
  void Update() override;
 private:
  wxTreeListCtrl *list_ = nullptr;
  wxImageList image_list_;

  void RedrawPropertyList();
  void OnUpdateNewProperty(wxUpdateUIEvent& event);
  void OnUpdateSingleProperty(wxUpdateUIEvent& event);
  void OnNewProperty(wxCommandEvent& event);
  void OnEditProperty(wxCommandEvent& event);
  void OnRightClick(wxTreeListEvent& event);
  void OnDoubleClick(wxTreeListEvent& event);

  [[nodiscard]] std::string GetSelectedPropertyKey() const;
  void SelectItem(const std::string& key);
  wxDECLARE_EVENT_TABLE();
};

}  // namespace workflow::gui
