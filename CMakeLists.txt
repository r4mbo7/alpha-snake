cmake_minimum_required(VERSION 3.0)

project(alpha-snake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

find_package(PkgConfig)
pkg_check_modules(CLUTTER REQUIRED clutter-1.0 glib-2.0 gobject-2.0)

add_executable(alpha-snake
        src/main.c
        src/affichage.c src/affichage.h src/list.c src/list.h
        src/struc.c src/struc.h src/bonus.c src/bonus.h src/ia.c src/ia.h src/partie.c src/partie.h src/collisions.c src/collisions.h
        src/widgets/alpha-button.c src/widgets/alpha-button.h
        src/widgets/alpha-field.c src/widgets/alpha-field.h src/application.c src/application.h
        src/score.c src/score.h src/widgets/utils.c src/widgets/utils.h
        src/config.c src/config.h src/widgets/alpha-check-box.c src/widgets/alpha-check-box.h)

add_executable(tests
        tests/tests.c
        src/struc.c src/struc.h
        src/list.c src/list.h
        src/ia.c src/ia.h
        src/affichage.c src/affichage.h
        src/bonus.c src/bonus.h
        src/score.c src/score.h
        src/config.c src/config.h)

target_link_libraries(alpha-snake ${CLUTTER_LIBRARIES} m)
include_directories(alpha-snake ${CLUTTER_INCLUDE_DIRS})

target_link_libraries(tests ${CLUTTER_LIBRARIES})
include_directories(tests ${CLUTTER_INCLUDE_DIRS})