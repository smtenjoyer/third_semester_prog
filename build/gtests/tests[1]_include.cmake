if(EXISTS "C:/Users/user/Desktop/2laba/build/gtests/tests[1]_tests.cmake")
  include("C:/Users/user/Desktop/2laba/build/gtests/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
