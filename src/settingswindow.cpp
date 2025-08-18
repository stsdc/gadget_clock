#include "settingswindow.h"

SettingsWindow::SettingsWindow() : m_VBox(Gtk::Orientation::VERTICAL) {
  set_title("Settings");
  set_default_size(400, 300);
  set_destroy_with_parent(true);
  set_hide_on_close();

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  settingsListBox = Gtk::ListBox();
  settingsListBox.set_selection_mode(Gtk::SelectionMode::SINGLE);

  populate_settings_list();

  auto settings = Gio::Settings::create("io.github.stsdc.gadget_clock");
  Glib::ustring skin = settings->get_string("current-skin");
  g_debug("SW Current skin: %s", skin.c_str());

  SettingsRow* settings_row = get_settings_row_by_skin_id(skin);
  auto row_to_select = settings_row ? settings_row : settingsListBox.get_row_at_index(0);
  if (row_to_select) {
    settingsListBox.select_row(*row_to_select);
  }


  // Connect row activated signal
  settingsListBox.signal_row_activated().connect(
      sigc::mem_fun(*this, &SettingsWindow::on_row_activated));

  m_VBox.append(m_ScrolledWindow);
  m_ScrolledWindow.set_child(settingsListBox);

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

void SettingsWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item) {
  auto pos = list_item->get_position();
  std::cout << "on_bind_name: position = " << pos << std::endl;
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(m_StringList->get_string(pos));
}

void SettingsWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item) {
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void SettingsWindow::on_row_activated(Gtk::ListBoxRow* row) {
  SettingsRow* settings_row = dynamic_cast<SettingsRow*>(row);
  if (settings_row) {
    g_debug ("Selected skin: %s", settings_row->skin_id->c_str());

    auto settings = Gio::Settings::create("io.github.stsdc.gadget_clock");
    settings->set_string("current-skin", settings_row->skin_id->c_str());
    // Handle activation here
  } else {
    std::cerr << "Activated row is not a SettingsRow!" << std::endl;
  }
}

void SettingsWindow::populate_settings_list() {
  SettingsRow* row1 = Gtk::make_managed<SettingsRow>("Bell & Ross BR 01-94", "Ramon Fernandez (2009)", "br-01-94");
  SettingsRow* row2 = Gtk::make_managed<SettingsRow>("Panerai", "Jimking", "panerai-luminor-1");
  settingsListBox.append(*row1);
  settingsListBox.append(*row2);
}

SettingsRow* SettingsWindow::get_settings_row_by_skin_id(const std::string& skin_id) {
  int index = 0;
  SettingsRow* settings_row;
  while ((settings_row = dynamic_cast<SettingsRow*>(settingsListBox.get_row_at_index(index)))) {
    if (settings_row->skin_id && settings_row->skin_id->c_str() == skin_id) {
      return settings_row;
    }
    index++;
  }
  return nullptr;
}
