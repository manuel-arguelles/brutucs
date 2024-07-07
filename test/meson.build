catch_lib = subproject('catch2').get_variable('catch2_with_main_dep')

openssl_dep = dependency('openssl', method : 'pkg-config')

test_sources = files(
  'linux-random-test.cpp',
  'pseudo-random-test.cpp',
  'base58-test.cpp',
  'p2pkh-address-generator-test.cpp',
  'mocks/mock-random.cpp'
)

incdir = include_directories(
  '../src/random',
  '../src/base58',
  '../src/address'
)

test_suite = executable(
  'brutucs-test',
  test_sources + sources,
  dependencies : [catch_lib, openssl_dep],
  include_directories : incdir
)

test('Brutucs tests', test_suite)
