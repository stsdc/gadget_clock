#ifndef GadgetClock_H
#define GadgetClock_H

#include <gtkmm.h>

#include "clockarea.h"

class GadgetClock : public Gtk::Window {
 public:
  GadgetClock();
  ~GadgetClock() override;

 protected:
  Gtk::Box m_box;
  ClockArea clockarea;
};

#endif

