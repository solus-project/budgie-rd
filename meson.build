project(
    'budgie-rd',
    ['cpp'],
    version: '0.0.0',
    license: [
        'LGPL-2.1',
    ],
    default_options: [
        'cpp_std=c++1z',
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
]

add_global_arguments(am_cppflags, language: 'cpp')
compiler = meson.get_compiler('cpp')

qt5 = import('qt5')
qt_min_version = '>= 5.9.1'
dep_qtwidgets = dependency('Qt5Widgets', version: qt_min_version)
dep_qml = dependency('Qt5Quick', version: qt_min_version)

subdir('src')
