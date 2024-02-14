catch_lib = subproject('catch2').get_variable('catch2_with_main_dep')

test_sources = files(
  'linux-random-test.cpp',
  'pseudo-random-test.cpp',
  'base58-test.cpp'
)

incdir = include_directories(
  '../src/random',
  '../src/base58'
)
test_suite = executable(
  'brutucs-test',
  test_sources + sources,
  dependencies : catch_lib,
  include_directories : incdir
)

test('Brutucs tests', test_suite)
