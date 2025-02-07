add_executable(client main.cpp mainwindow.cpp client.cpp connection.cpp)
target_link_libraries(client PRIVATE Qt6::Widgets)
