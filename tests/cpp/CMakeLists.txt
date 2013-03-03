add_executable(DataUrlStreamTest DataUrlStreamTest.cpp ../../DataUrlStream.cpp)
target_link_libraries(DataUrlStreamTest ${TagLibCpp_LIBRARIES} -lz)
