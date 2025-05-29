#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();

protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

  Glib::RefPtr<Gdk::Pixbuf> m_image;
};

#endif // GTKMM_EXAMPLE_MYAREA_H
