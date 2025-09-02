#include "settingsrow.h"

SettingsRow::SettingsRow(const Glib::ustring& title, const Glib::ustring& subtitle,
                         const Glib::ustring& skin_id) : title_label(Gtk::make_managed<Gtk::Label>(title)),
                                                         subtitle_label(Gtk::make_managed<Gtk::Label>(subtitle)) {
  set_margin(5);

  // Initialize skin_id
  this->skin_id = new Glib::ustring(skin_id);

  // Create the main container
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
  box->set_margin(10);

  // Create title label
  title_label->set_halign(Gtk::Align::START);
  title_label->set_markup("<b>" + Glib::Markup::escape_text(title) + "</b>");

  // Create subtitle label
  subtitle_label = Gtk::make_managed<Gtk::Label>(subtitle);
  subtitle_label->set_halign(Gtk::Align::START);
  subtitle_label->add_css_class("dim-label");
  subtitle_label->set_ellipsize(Pango::EllipsizeMode::END);

  // Add labels to box
  box->append(*title_label);
  box->append(*subtitle_label);

  // Set the box as the child widget
  set_child(*box);
}

void SettingsRow::set_title(const Glib::ustring& title) {
  title_label->set_markup("<b>" + Glib::Markup::escape_text(title) + "</b>");
}

void SettingsRow::set_subtitle(const Glib::ustring& subtitle) {
  subtitle_label->set_text(subtitle);
};
