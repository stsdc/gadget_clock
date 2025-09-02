#include "clockarea.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>  // set_source_pixbuf()
#include <giomm/resource.h>
#include <giomm/settings.h>
#include <glibmm/fileutils.h>
#include <gtkmm/settings.h>

#include <iostream>

ClockArea::ClockArea() {
  // this->set_tooltip_text("Artwork by Ramon Fernandez (2009)");

  // Get current skin from GSettings
  auto settings = Gio::Settings::create("io.github.stsdc.gadget_clock");

  // don't need to use Glib::ustring here, for this key only ASCII characters are used
  // https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-basics-ustring.html
  std::string skin = settings->get_string("current-skin");

  g_info("CA Current skin: %s", skin.c_str());

  try {
    auto path = "/io/github/stsdc/gadget_clock/images/" + skin + "/body.png";
    image_bg = Gdk::Pixbuf::create_from_resource(path);

    scale_factor = 200.0 / image_bg->get_width();

    image_bg = image_bg->scale_simple(200, 200, Gdk::InterpType::BILINEAR);

  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_sec = Gdk::Pixbuf::create_from_resource("/io/github/stsdc/gadget_clock/images/" + skin + "/seconds.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_min = Gdk::Pixbuf::create_from_resource("/io/github/stsdc/gadget_clock/images/" + skin + "/minutes.png");
    image_min = image_min->scale_simple(200, 200, Gdk::InterpType::BILINEAR);
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  try {
    image_hou = Gdk::Pixbuf::create_from_resource("/io/github/stsdc/gadget_clock/images/" + skin + "/hours.png");
    image_hou = image_hou->scale_simple(200, 200, Gdk::InterpType::BILINEAR);
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  // Show at least a quarter of the image.
  if (image_bg) {
    set_content_width(200);
    set_content_height(200);
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
  cr->rectangle(0, 0, 200, 200);
  cr->fill();
  cr->save();

  Gdk::Cairo::set_source_pixbuf(cr, image_bg, 0, 0);
  cr->paint();
  cr->save();

  cr->translate(100, 100);

  // store the current time
  time_t rawtime;
  time(&rawtime);
  struct tm *timeinfo = localtime(&rawtime);

  // compute the angles of the indicators of our clock
  double minutes = timeinfo->tm_min * M_PI / 30;
  double hours = timeinfo->tm_hour * M_PI / 6;
  double seconds = timeinfo->tm_sec * M_PI / 30;


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
  if (!image_sec) {
      g_debug("No seconds image available.");
    return;
  }


  cr->save();
  cr->rotate(seconds);
  cr->translate(-100, -100);
  Gdk::Cairo::set_source_pixbuf(cr, image_sec, 0, 0);
  cr->paint();

  cr->restore();
}
