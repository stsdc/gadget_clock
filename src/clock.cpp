#include "clock.h"
#include <iostream>

GadgetClock::GadgetClock ()
{
  set_title ("DrawingArea");
  set_default_size (300, 200);

  m_box.append (m_area);

  // Sets the margin around the button.
  m_button.set_label ("asdad");
  m_button.set_margin (10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked ().connect (sigc::mem_fun (*this,
                                                     &GadgetClock::on_button_clicked));

  m_box.append (m_button);

  set_child (m_box);
}

GadgetClock::~GadgetClock ()
{
}

void
GadgetClock::on_button_clicked ()
{
  std::cout << "Hello World" << std::endl;
}

