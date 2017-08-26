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
]

add_global_arguments(am_cppflags, language: 'cpp')

subdir('src')
