#include <gtkmm.h>
#include <glibmm/main.h>

class SettingsRow : public Gtk::ListBoxRow {
 public:
  SettingsRow(const Glib::ustring& title, const Glib::ustring& subtitle, const Glib::ustring& skin_id);
  Glib::ustring* skin_id;

 private: 
  Gtk::Label* title_label;
  Gtk::Label* subtitle_label;

    void set_title(const Glib::ustring& title);
    void set_subtitle(const Glib::ustring& subtitle);
};