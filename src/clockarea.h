#ifndef CLOCKAREA_H
#define CLOCKAREA_H

#include <gdkmm/pixbuf.h>
#include <glibmm/main.h>
#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>

#include <cmath>

class ClockArea : public Gtk::DrawingArea {
 public:
  ClockArea();
  virtual ~ClockArea();

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

#endif  // CLOCKAREA_H

