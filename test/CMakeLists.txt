configure_file(testdir.h.in ${CMAKE_CURRENT_BINARY_DIR}/testdir.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(testpunctuation testpunctuation.cpp)
target_link_libraries(testpunctuation Fcitx5::Core Fcitx5::Module::Punctuation)
add_dependencies(testpunctuation punctuation punctuation.conf.in-fmt)
add_test(NAME testpunctuation COMMAND testpunctuation)

add_executable(testcloudpinyin testcloudpinyin.cpp)
target_link_libraries(testcloudpinyin Fcitx5::Core Fcitx5::Module::CloudPinyin)
add_dependencies(testcloudpinyin cloudpinyin)

add_executable(testpinyinhelper testpinyinhelper.cpp)
target_link_libraries(testpinyinhelper Fcitx5::Core Fcitx5::Module::PinyinHelper)
add_dependencies(testpinyinhelper pinyinhelper pinyinhelper.conf.in-fmt)
add_test(NAME testpinyinhelper COMMAND testpinyinhelper)

add_subdirectory(addon)
add_subdirectory(inputmethod)
add_executable(testpinyin testpinyin.cpp)
target_link_libraries(testpinyin Fcitx5::Core Fcitx5::Module::TestFrontend Pthread::Pthread)
add_dependencies(testpinyin pinyin pinyinhelper copy-addon copy-im)
add_test(NAME testpinyin COMMAND testpinyin)
