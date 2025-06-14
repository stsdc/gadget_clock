#include <cairomm/context.h>
#include <gdkmm/general.h>  // set_source_pixbuf()
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

#include <iostream>

#include "clockarea.h"

ClockArea::ClockArea() : m_radius(0.42), m_line_width(0.05) {

    this->set_tooltip_text("Artwork by Ramon Fernandez (2009)");

  try {
    image_bg = Gdk::Pixbuf::create_from_resource("/com/github/stsdc/gadget_clock/images/body.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_sec = Gdk::Pixbuf::create_from_resource("/com/github/stsdc/gadget_clock/images/seconds.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_min = Gdk::Pixbuf::create_from_resource("/com/github/stsdc/gadget_clock/images/minutes.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_hou = Gdk::Pixbuf::create_from_resource("/com/github/stsdc/gadget_clock/images/hours.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  // Show at least a quarter of the image.
  if (image_bg) {
    set_content_width(image_bg->get_width());
    set_content_height(image_bg->get_height());
  }

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &ClockArea::on_timeout), 1000);
  set_draw_func(sigc::mem_fun(*this, &ClockArea::on_draw));
}

ClockArea::~ClockArea() {}

bool ClockArea::on_timeout() {
  // force our program to redraw the entire clock.
  queue_draw();
  return true;
}

void ClockArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height) {
  if (!image_bg)
    return;

  cr->set_source_rgba(0, 0, 0, 0.0);
  cr->rectangle(0, 0, 512, 128);
  cr->fill();
  cr->save();

  Gdk::Cairo::set_source_pixbuf(cr, image_bg, 0, 0);
  cr->paint();
  cr->save();

  cr->translate(100, 100);
  cr->set_line_width(m_line_width);

  // store the current time
  time_t rawtime;
  time(&rawtime);
  struct tm *timeinfo = localtime(&rawtime);

  // compute the angles of the indicators of our clock
  double minutes = timeinfo->tm_min * M_PI / 30;
  double hours = timeinfo->tm_hour * M_PI / 6;
  double seconds = timeinfo->tm_sec * M_PI / 30;

  cr->save();
  cr->set_line_cap(Cairo::Context::LineCap::ROUND);

  // draw the minutes hand
  cr->save();
  cr->rotate(minutes);
  cr->translate(-100, -100);
  Gdk::Cairo::set_source_pixbuf(cr, image_min, 0, 0);
  cr->paint();

  cr->restore();

  // draw the hours hand
  cr->save();
  cr->rotate(hours);
  cr->translate(-100, -100);
  Gdk::Cairo::set_source_pixbuf(cr, image_hou, 0, 0);
  cr->paint();

  cr->restore();

  // draw the seconds hand
  cr->save();
  cr->rotate(seconds);
  cr->translate(-100, -100);
  Gdk::Cairo::set_source_pixbuf(cr, image_sec, 0, 0);
  cr->paint();

  cr->restore();
}

