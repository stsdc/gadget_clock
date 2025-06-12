#include <iostream>

#include "clock.h"

GadgetClock::GadgetClock() {
  set_title("DrawingArea");
  set_default_size(200, 200);
  set_decorated(false);

  auto provider = Gtk::CssProvider::create();
  provider->load_from_resource("/dev/stsdc/gadget_clock/styles/main.css");
  this->get_style_context()->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

  m_box.append(clockarea);

  // Sets the margin around the button.
  m_button.set_label("asdad");
  m_button.set_margin(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &GadgetClock::on_button_clicked));

  // m_box.append (m_button);

  auto grabbingarea = Gtk::WindowHandle();
  grabbingarea.set_child(m_box);

  set_child(grabbingarea);
}

GadgetClock::~GadgetClock() {
}

void GadgetClock::on_button_clicked() {
  std::cout << "Hello World" << std::endl;
}

