#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <gtkmm.h>
#include <iostream>

class SettingsWindow : public Gtk::Window {
 public:
  SettingsWindow();

 private:
  // Signal handlers
  void on_apply_clicked();
  void on_cancel_clicked();
  void on_theme_changed();

  // Member widgets
  Gtk::Button m_apply_button;
  Gtk::Button m_cancel_button;
};

#endif

