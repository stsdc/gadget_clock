#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <gtkmm.h>

#include <iostream>

#include "settingsrow.h"  

class SettingsWindow : public Gtk::Window {
 public:
  SettingsWindow();

 private:
  // Signal handlers
  void on_apply_clicked();
  void on_cancel_clicked();
  void on_theme_changed();

  void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);

  void on_row_activated(Gtk::ListBoxRow* row);



  void populate_settings_list();
  SettingsRow* get_settings_row_by_skin_id(const std::string& skin_id);

  // Member widgets
  Gtk::Button m_apply_button;
  Gtk::Button m_cancel_button;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::ListBox settingsListBox;
  Gtk::ListView m_ListView;
  Glib::RefPtr<Gtk::StringList> m_StringList;
  Gtk::Box m_VBox;
};

#endif

