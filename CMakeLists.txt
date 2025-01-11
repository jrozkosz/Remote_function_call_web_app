# Jakub Rozkosz

cmake_minimum_required(VERSION 3.0)
project(MyProject)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(SQLite3 REQUIRED)

set(CLIENT_SOURCE_FILES backend/TCPClient.cc backend/TCPClient.h backend/Client.cc
    backend/EvolutionaryClient.cc backend/EvolutionaryClient.h)
set(WEBAPP_SOURCE_FILES webapp/Webapp.cc webapp/AdminLogin.cc webapp/AdminLogin.h 
    webapp/AdminPanel.cc webapp/AdminPanel.h webapp/UserRegister.cc webapp/UserRegister.h
    webapp/WebappPage.h webapp/WebappPage.cc)

file(COPY backend/input_data webapp/demo_client.png webapp/webapp_style.css db/zpr_db.db DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(SERVER_SOURCE_FILES backend/TCPServer.cc backend/TCPServer.h backend/Server.cc
    backend/EvolutionaryServer.cc backend/EvolutionaryServer.h 
    backend/cec22_test_func.h backend/cec22_test_func.cc)
set(DB_SOURCE_FILES db/Database.cc db/Database.h)

add_executable(TCPClient ${CLIENT_SOURCE_FILES})

add_executable(TCPServer ${SERVER_SOURCE_FILES} ${DB_SOURCE_FILES})
target_link_libraries(TCPServer ${SQLite3_LIBRARIES})

add_executable(Webapp ${WEBAPP_SOURCE_FILES} ${DB_SOURCE_FILES})

target_include_directories(Webapp PUBLIC "${CMAKE_SOURCE_DIR}/install/wt_install/include")
get_filename_component(WT_LIB "${CMAKE_SOURCE_DIR}/install/wt_install/lib/" ABSOLUTE)
target_link_libraries(Webapp -L${WT_LIB} -lwthttp -lwt ${SQLite3_LIBRARIES})

add_executable(TCPClientTest tests/test_TCPClient.cc backend/TCPClient.cc backend/TCPClient.h)
target_include_directories(TCPClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TCPClientTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()
add_test(NAME TCPClientTest COMMAND TCPClientTest)

add_executable(TCPServerTest tests/test_TCPServer.cc backend/TCPServer.cc backend/TCPServer.h
                ${DB_SOURCE_FILES})
target_include_directories(TCPServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TCPServerTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SQLite3_LIBRARIES})

add_test(NAME TCPServerTest COMMAND TCPServerTest)

add_executable(DatabaseTest tests/test_Database.cc ${DB_SOURCE_FILES})
target_link_libraries(DatabaseTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SQLite3_LIBRARIES})

add_test(NAME DatabaseTest COMMAND DatabaseTest)

add_executable(UserRegisterTest tests/test_UserRegister.cc webapp/UserRegister.h webapp/UserRegister.cc
    webapp/WebappPage.h webapp/WebappPage.cc ${DB_SOURCE_FILES})
target_link_libraries(UserRegisterTest -L${WT_LIB} -lwthttp -lwt -lwttest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SQLite3_LIBRARIES})

add_test(NAME UserRegisterTest COMMAND UserRegisterTest)

add_executable(AdminPanelTest tests/test_AdminPanel.cc webapp/AdminPanel.h webapp/AdminPanel.cc
    webapp/WebappPage.h webapp/WebappPage.cc ${DB_SOURCE_FILES})
target_link_libraries(AdminPanelTest -L${WT_LIB} -lwthttp -lwt -lwttest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SQLite3_LIBRARIES})

add_test(NAME AdminPanelTest COMMAND AdminPanelTest)

add_executable(AdminLoginTest tests/test_AdminLogin.cc webapp/AdminLogin.h webapp/AdminLogin.cc
    webapp/WebappPage.h webapp/WebappPage.cc ${DB_SOURCE_FILES})
target_link_libraries(AdminLoginTest -L${WT_LIB} -lwthttp -lwt -lwttest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SQLite3_LIBRARIES})

add_test(NAME AdminLoginTest COMMAND AdminLoginTest)