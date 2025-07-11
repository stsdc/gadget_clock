gadget_clock_sources = [
  'settingswindow.cpp',
  'clock.cpp',
  'clockarea.cpp',
  'main.cpp',
]

gadget_clock_deps = [
	dependency('gtkmm-4.0'),
]

executable('io.github.stsdc.gadget_clock', gadget_clock_sources,
images_gresource,
styles_gresource,
  dependencies: gadget_clock_deps,
  install: true,
)

