#include <cairomm/context.h>
#include <gdkmm/general.h>  // set_source_pixbuf()
#include <giomm/resource.h>
#include <glibmm/fileutils.h>

#include <iostream>

#include "clockarea.h"

MyArea::MyArea() : m_radius(0.42), m_line_width(0.05) {
  try {
    image_bg = Gdk::Pixbuf::create_from_resource("/dev/stsdc/gadget_clock/images/body.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_sec = Gdk::Pixbuf::create_from_resource("/dev/stsdc/gadget_clock/images/seconds.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_min = Gdk::Pixbuf::create_from_resource("/dev/stsdc/gadget_clock/images/minutes.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_hou = Gdk::Pixbuf::create_from_resource("/dev/stsdc/gadget_clock/images/hours.png");
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

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &MyArea::on_timeout), 1000);
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));

  // Set the draw function.
  // set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea() {}

bool MyArea::on_timeout() {
  // force our program to redraw the entire clock.
  queue_draw();
  return true;
}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height) {
  if (!image_bg)
    return;

  // Draw the image in the middle of the drawing area, or (if the image is
  // larger than the drawing area) draw the middle part of the image.

  // cr->paint();

  Gdk::Cairo::set_source_pixbuf(cr, image_bg, (width - image_bg->get_width()) / 2, (height - image_bg->get_height()) / 2);
  cr->paint();
  cr->save();

  // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
  // the center of the window
  // cr->scale(width, height);
  cr->translate(100, 100);
  cr->set_line_width(m_line_width);

  // cr->save();
  // cr->paint();

  // cr->restore();
  // cr->arc(0, 0, m_radius, 0, 2 * M_PI);
  // cr->save();
  // cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
  // cr->fill_preserve();
  // cr->restore();
  // cr->stroke_preserve();
  // cr->clip();

  // clock ticks
  // for (int i = 0; i < 12; i++) {
  //   double inset = 0.05;

  //   cr->save();
  //   cr->set_line_cap(Cairo::Context::LineCap::ROUND);

  //   if (i % 3 != 0) {
  //     inset *= 0.8;
  //     cr->set_line_width(0.03);
  //   }

  //   cr->move_to(
  //       (m_radius - inset) * cos(i * M_PI / 6),
  //       (m_radius - inset) * sin(i * M_PI / 6));
  //   cr->line_to(
  //       m_radius * cos(i * M_PI / 6),
  //       m_radius * sin(i * M_PI / 6));
  //   cr->stroke();
  //   cr->restore(); /* stack-pen-size */
  // }

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

