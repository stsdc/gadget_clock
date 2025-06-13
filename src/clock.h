#ifndef GTKMM_EXAMPLE_GadgetClock_H
#define GTKMM_EXAMPLE_GadgetClock_H

#include <gtkmm.h>

#include "clockarea.h"

class GadgetClock : public Gtk::Window {
 public:
  GadgetClock();
  ~GadgetClock() override;

 protected:
  // Signal handlers:
  void on_button_clicked();

  // Member widgets:
  Gtk::Button m_button;
  Gtk::Box m_box;
  ClockArea clockarea;
};

#endif

