#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gdkmm/pixbuf.h>
#include <glibmm/main.h>
#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>

#include <cmath>

class MyArea : public Gtk::DrawingArea {
 public:
  MyArea();
  virtual ~MyArea();

 protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

  bool on_timeout();

  double m_radius;
  double m_line_width;

  Glib::RefPtr<Gdk::Pixbuf> image_bg;
  Glib::RefPtr<Gdk::Pixbuf> image_sec;
  Glib::RefPtr<Gdk::Pixbuf> image_min;
  Glib::RefPtr<Gdk::Pixbuf> image_hou;
};

#endif  // GTKMM_EXAMPLE_MYAREA_H

