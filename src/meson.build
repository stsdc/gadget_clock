gadget_clock_sources = [
  'clock.cpp',
  'clockarea.cpp',
  'main.cpp',
]

gadget_clock_deps = [
	dependency('gtkmm-4.0'),
]

executable('com.github.stsdc.gadget_clock', gadget_clock_sources,
images_gresource,
styles_gresource,
  dependencies: gadget_clock_deps,
  install: true,
)

