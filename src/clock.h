#ifndef GadgetClock_H
#define GadgetClock_H

#include <gtkmm.h>
#include <memory>

#include "clockarea.h"
#include "settingswindow.h"

class GadgetClock : public Gtk::Window {
 public:
  GadgetClock(const Glib::RefPtr<Gtk::Application>& app);
  ~GadgetClock() override;

 protected:
  Gtk::Box m_box;
  Gtk::PopoverMenu m_MenuPopup;
  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gtk::GestureClick> m_refGesture;

  // Signals
  void on_label_pressed(int n_press, double x, double y);
  void on_contextmenu_settings();
  void on_contextmenu_close();

  ClockArea clockarea;
  SettingsWindow settingswindow;
};

#endif

