catch_lib = subproject('catch2').get_variable('catch2_with_main_dep')

test_sources = files(
  'linux-random-test.cpp',
  'pseudo-random-test.cpp'
)

test_suite = executable(
  'brutucs-test',
  test_sources + sources,
  dependencies : catch_lib,
  include_directories : '../src/random'
)

test('Brutucs tests', test_suite)
