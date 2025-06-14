gnome = import('gnome')
i18n = import('i18n')

images_gresource = gnome.compile_resources(
    'gresource_images', 'images/images.gresource.xml',
    source_dir: 'images',
    c_name: 'as1'
)

styles_gresource = gnome.compile_resources(
    'gresource_styles',
    'styles/styles.gresource.xml',
    source_dir: 'styles',
    c_name: 'as2'
)

icon_sizes = ['32', '48', '64', '128']

foreach i : icon_sizes
    install_data(
        join_paths('icons', i + '.svg'),
        install_dir: join_paths(get_option('datadir'), 'icons', 'hicolor', i + 'x' + i, 'apps'),
        rename: meson.project_name() + '.svg'
    )
    install_data(
        join_paths('icons', i + '.svg'),
        install_dir: join_paths(get_option('datadir'), 'icons', 'hicolor', i + 'x' + i + '@2', 'apps'),
        rename: meson.project_name() + '.svg'
    )
endforeach

i18n.merge_file(
    input: 'gadget_clock.desktop.in',
    output: meson.project_name() + '.desktop',
    po_dir: join_paths(meson.source_root(), 'po', 'extra'),
    type: 'desktop',
    install: true,
    install_dir: get_option('datadir') / 'applications'
)

i18n.merge_file(
    input: 'gadget_clock.metainfo.xml.in',
    output: meson.project_name() + '.metainfo.xml',
    po_dir: meson.source_root() / 'po' / 'extra',
    type: 'xml',
    install: true,
    install_dir: get_option('datadir') / 'metainfo',
)