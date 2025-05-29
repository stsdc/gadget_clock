#include "clockarea.h"
#include <cairomm/context.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <giomm/resource.h>
#include <glibmm/fileutils.h>
#include <iostream>

MyArea::MyArea() {
  try {
    m_image = Gdk::Pixbuf::create_from_resource(
        "/dev/stsdc/gadget_clock/images/body.png");
  } catch (const Gio::ResourceError &ex) {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  // Show at least a quarter of the image.
  if (m_image) {
    set_content_width(m_image->get_width() / 2);
    set_content_height(m_image->get_height() / 2);
  }

  // Set the draw function.
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea() {}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width,
                     int height) {
  if (!m_image)
    return;

  // Draw the image in the middle of the drawing area, or (if the image is
  // larger than the drawing area) draw the middle part of the image.
  Gdk::Cairo::set_source_pixbuf(cr, m_image, (width - m_image->get_width()) / 2,
                                (height - m_image->get_height()) / 2);
  cr->paint();
}

