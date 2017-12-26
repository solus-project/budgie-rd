project(
    'budgie-rd',
    ['cpp'],
    version: '0.0.0',
    license: [
        'LGPL-2.1',
    ],
    default_options: [
        'cpp_std=c++11',
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

# Global dirs
prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
sessiondir = join_paths(datadir, 'budgie-session')
sessiondir_desktop = join_paths(sessiondir, 'desktop')
libdir = get_option('libdir')

# Single top level plugin tree defined at build time
budgie_plugin_dir = join_paths(libdir, meson.project_name(), 'plugins')

add_global_arguments(am_cppflags, language: 'cpp')
compiler = meson.get_compiler('cpp')

qt5 = import('qt5')
qt_min_version = '>= 5.9.1'
dep_qtwidgets = dependency('Qt5Widgets', version: qt_min_version)
dep_qml = dependency('Qt5Quick', version: qt_min_version)
dep_qml_controls = dependency('Qt5QuickControls2', version: qt_min_version)

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

# Write config.h now
config_h = configure_file(
     configuration: cdata,
     output: 'config.h',
)
config_h_dir = include_directories('.')

subdir('src')
