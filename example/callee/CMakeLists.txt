set(SRC_LIST userservice.cc ../user.pb.cc)

# 添加protobuf库的查找和链接
find_package(Protobuf REQUIRED)

add_executable(provider ${SRC_LIST})
target_link_libraries(provider crpc ${PROTOBUF_LIBRARIES})