#include "settingswindow.h"

SettingsWindow::SettingsWindow() : m_VBox(Gtk::Orientation::VERTICAL) {
  set_title("Settings");
  set_default_size(400, 300);
  set_destroy_with_parent(true);
  set_hide_on_close();

  m_ScrolledWindow.set_child(m_ListView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  // Create the list model:
  m_StringList = Gtk::StringList::create({"Billy Bob", "Joey Jojo", "Rob McRoberts"});

  // Set list model and selection model.
  auto selection_model = Gtk::SingleSelection::create(m_StringList);
  selection_model->set_autoselect(false);
  selection_model->set_can_unselect(true);
  m_ListView.set_model(selection_model);
  m_ListView.add_css_class("data-table");

  // Add the factory for the ListView's single column.
  auto factory = Gtk::SignalListItemFactory::create();
  // factory->signal_setup().connect(sigc::mem_fun(*this, &SettingsWindow::on_setup_label));
  factory->signal_bind().connect(sigc::mem_fun(*this, &SettingsWindow::on_bind_name));
  m_ListView.set_factory(factory);

  m_VBox.append(m_ScrolledWindow);

  set_child(m_VBox);
}

// void SettingsWindow::on_apply_clicked() {
//     std::cout << "Settings applied!" << std::endl;
//     hide();
// }

// void SettingsWindow::on_cancel_clicked() {
//     std::cout << "Settings cancelled" << std::endl;
//     hide();
// }

// void SettingsWindow::on_theme_changed() {
//     std::cout << "Theme changed to: " << std::endl;
// }

void SettingsWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(m_StringList->get_string(pos));
}

