project('brutucs', 'cpp',
       version : '0.0.1',
       license : 'GPL-2.1-or-later',
       meson_version : '>= 0.59.0',
       default_options : ['warning_level=3', 'werror=true', 'cpp_std=c++17'])

main_sources = []
sources = []

subdir('src')
subdir('test')

executable('brutucs', sources + main_sources)
