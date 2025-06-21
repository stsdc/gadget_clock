#include "clock.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("io.github.stsdc.gadget_clock");

  //Shows the window and returns when it is closed.
  return app->make_window_and_run<GadgetClock>(argc, argv);
}

