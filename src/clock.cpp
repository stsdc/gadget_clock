#include <iostream>

#include "clock.h"

void GadgetClock::on_label_pressed(int /* n_press */, double x, double y) {
  const Gdk::Rectangle rect(x, y, 1, 1);
  m_MenuPopup.set_pointing_to(rect);
  m_MenuPopup.popup();
}

void GadgetClock::on_menu_file_popup_generic() {
  std::cout << "A popup menu item was selected." << std::endl;
}

GadgetClock::GadgetClock(const Glib::RefPtr<Gtk::Application>& app) {
  set_title("DrawingArea");
  set_default_size(200, 200);
  set_decorated(false);

  auto provider = Gtk::CssProvider::create();
  provider->load_from_resource("/com/github/stsdc/gadget_clock/styles/main.css");
  this->get_style_context()->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

  m_box.append(clockarea);

  m_refGesture = Gtk::GestureClick::create();
  m_refGesture->set_button(GDK_BUTTON_SECONDARY);
  m_refGesture->signal_pressed().connect(sigc::mem_fun(*this, &GadgetClock::on_label_pressed));
  m_box.add_controller(m_refGesture);

  auto refActionGroup = Gio::SimpleActionGroup::create();

  refActionGroup->add_action("edit", sigc::mem_fun(*this, &GadgetClock::on_menu_file_popup_generic));
  refActionGroup->add_action("process", sigc::mem_fun(*this, &GadgetClock::on_menu_file_popup_generic));
  refActionGroup->add_action("remove", sigc::mem_fun(*this, &GadgetClock::on_menu_file_popup_generic));

  insert_action_group("examplepopup", refActionGroup);

  Glib::ustring ui_info =
      "<interface>"
      "  <menu id='menu-examplepopup'>"
      "    <section>"
      "      <item>"
      "        <attribute name='label' translatable='yes'>Edit</attribute>"
      "        <attribute name='action'>examplepopup.edit</attribute>"
      "      </item>"
      "      <item>"
      "        <attribute name='label' translatable='yes'>Process</attribute>"
      "        <attribute name='action'>examplepopup.process</attribute>"
      "      </item>"
      "      <item>"
      "        <attribute name='label' translatable='yes'>Remove</attribute>"
      "        <attribute name='action'>examplepopup.remove</attribute>"
      "      </item>"
      "    </section>"
      "  </menu>"
      "</interface>";

  // Set accelerator keys:
  app->set_accel_for_action("examplepopup.edit", "<Primary>e");
  app->set_accel_for_action("examplepopup.process", "<Primary>p");
  app->set_accel_for_action("examplepopup.remove", "<Primary>r");

  m_refBuilder = Gtk::Builder::create();

  try {
    m_refBuilder->add_from_string(ui_info);
  } catch (const Glib::Error& ex) {
    std::cerr << "building menus failed: " << ex.what();
  }

  // Get the menu:
  auto gmenu = m_refBuilder->get_object<Gio::Menu>("menu-examplepopup");
  if (!gmenu)
    g_warning("GMenu not found");

  m_MenuPopup.set_parent(m_box);
  m_MenuPopup.set_menu_model(gmenu);
  m_MenuPopup.set_has_arrow(false);

  auto grabbingarea = Gtk::WindowHandle();
  grabbingarea.set_child(m_box);

  set_child(grabbingarea);
}

GadgetClock::~GadgetClock() {
  m_MenuPopup.unparent();
}

