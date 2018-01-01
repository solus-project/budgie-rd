project(
    'budgie-rd',
    ['cpp'],
    version: '0.0.0',
    license: [
        'LGPL-2.1',
    ],
    default_options: [
        'cpp_std=c++17',
    ],
)

am_cppflags = [
    '-fstack-protector',
    '-pedantic',
    '-Wundef',
    '-Werror-implicit-function-declaration',
    '-Wformat',
    '-Wformat-security',
    '-Werror=format-security',
    '-Wconversion',
    '-Wunused-variable',
    '-Wunreachable-code',
    '-Wall',
    '-W',
    '-fPIC',
]

add_global_arguments(am_cppflags, language: 'cpp')
compiler = meson.get_compiler('cpp')

path_prefix = get_option('prefix')
path_sysconfdir = join_paths(path_prefix, get_option('sysconfdir'))
path_datadir = join_paths(path_prefix, get_option('datadir'))
path_bindir = join_paths(path_prefix, get_option('bindir'))
path_libdir = join_paths(path_prefix, get_option('libdir'))

path_plugin_dir = join_paths(path_libdir, meson.project_name(), 'plugins')

qt5 = import('qt5')
qt_min_version = '>= 5.9.1'
dep_qtwidgets = dependency('Qt5Widgets', version: qt_min_version)
dep_qtcore = dependency('Qt5Core', version: qt_min_version)
dep_qml = dependency('Qt5Quick', version: qt_min_version)
dep_qml_controls = dependency('Qt5QuickControls2', version: qt_min_version)

dep_qt_compositor = dependency('Qt5WaylandCompositor', version: qt_min_version)

kf5_components_needed = [
    'WindowSystem',
]

kf5_deps = []

foreach kde_component: kf5_components_needed
    dep_tmp_lib = compiler.find_library('KF5' + kde_component)
    dep_tmp_kf5 = declare_dependency(
        dependencies: [
            dep_tmp_lib,
        ],
        include_directories: [
            include_directories('/usr/include/KF5/K' + kde_component),
        ],
    )
    kf5_deps += dep_tmp_kf5
endforeach

# Get configuration bits together
cdata = configuration_data()
cdata.set_quoted('PACKAGE_VERSION', meson.project_version())
cdata.set_quoted('PACKAGE_NAME', meson.project_name())
cdata.set_quoted('BUDGIE_PLUGIN_DIRECTORY', path_plugin_dir)

# Write config.h now
config_h = configure_file(
     configuration: cdata,
     output: 'config.h',
)
config_h_dir = include_directories('.')

subdir('src')

report = [
    '    Build configuration:',
    '    ====================',
    '',
    '    prefix:                                 @0@'.format(path_prefix),
    '    datadir:                                @0@'.format(path_datadir),
    '    sysconfdir:                             @0@'.format(path_sysconfdir),
    '    bindir:                                 @0@'.format(path_bindir),
    '    libdir:                                 @0@'.format(path_libdir),
    '    plugins:                                @0@'.format(path_plugin_dir),
]

# Output some stuff to validate the build config
message('\n\n\n' + '\n'.join(report) + '\n\n')
