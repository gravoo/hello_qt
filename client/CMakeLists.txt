add_executable(client main.cpp mainwindow.cpp ping_client.cpp client.cpp mainwindow.ui)
target_link_libraries(client PRIVATE Qt6::Widgets)
