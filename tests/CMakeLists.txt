add_executable(cmakeresources-demo-test main.t.cc)
target_link_libraries(cmakeresources-demo-test PUBLIC gtest gmock gtest_main)

foreach(it RANGE 15)
    add_test(
        NAME cmakeresources-demo-test-${it}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/Debug/cmakeresources-demo-test
    )
    set_property(TEST cmakeresources-demo-test-${it} PROPERTY
        RESOURCE_GROUPS "portoffset:1"
    )
endforeach()
