project('io.github.stsdc.gadget_clock', ['cpp', 'c'],
          version: '0.5.1',
    meson_version: '>= 1.0.0',
  default_options: [ 'warning_level=2', 'werror=false', 'cpp_std=c++17', ],
)

subdir('data')
subdir('src')

gnome.post_install(
    glib_compile_schemas: true,
    gtk_update_icon_cache: true
)