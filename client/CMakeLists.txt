add_executable(client main.cpp mainwindow.cpp client.cpp connection.cpp connection_tab.cpp processes_tab.cpp)
add_executable(bp boost_process.cpp)
target_link_libraries(client PRIVATE Qt6::Widgets)
