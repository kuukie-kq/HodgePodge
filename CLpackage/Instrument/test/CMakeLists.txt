cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(../net SOURCE)
aux_source_directory(../plugin SOURCE)
aux_source_directory(../sys SOURCE)

add_executable(tus test/t_udp_server.cpp ${SOURCE})
add_executable(tuc test/t_udp_client.cpp ${SOURCE})
add_executable(tks test/t_kcp_server.cpp ${SOURCE})
add_executable(tkc test/t_kcp_client.cpp ${SOURCE})
add_executable(ts test/t__server.cpp ${SOURCE})
add_executable(tc test/t__client.cpp ${SOURCE})

target_link_libraries(tus ws2_32.lib)
target_link_libraries(tuc ws2_32.lib)
target_link_libraries(tks ws2_32.lib)
target_link_libraries(tkc ws2_32.lib)
target_link_libraries(ts ws2_32.lib)
target_link_libraries(tc ws2_32.lib)
