#include <iostream>

#include "clock.h"

GadgetClock::GadgetClock() {
  set_title("DrawingArea");
  set_default_size(200, 200);
  set_decorated(false);

  auto provider = Gtk::CssProvider::create();
  provider->load_from_resource("/com/github/stsdc/gadget_clock/styles/main.css");
  this->get_style_context()->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

  m_box.append(clockarea);

  auto grabbingarea = Gtk::WindowHandle();
  grabbingarea.set_child(m_box);

  set_child(grabbingarea);
}

GadgetClock::~GadgetClock() {
}

