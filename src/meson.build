gadget_clock_sources = [
  'clock.cpp',
  'main.cpp',
]

gadget_clock_deps = [
	dependency('gtkmm-4.0'),
	# dependency('gtksourceviewmm-3.0'),
	# dependency('zlib'),
	# dependency('fontconfig'),
	# dependency('gdk-x11-3.0', required : false),
	# dependency('jsoncpp')
]

executable('gadget_clock', gadget_clock_sources,
  dependencies: gadget_clock_deps,
  install: true,
)

