cmake_minimum_required(VERSION 3.24)
project(aerialTransportation)

set(CMAKE_CXX_STANDARD 17)

add_executable(aerialTransportation src/main.cpp src/model/Graph.h src/model/Graph.cpp src/model/Airline.h src/model/Airline.cpp src/Program.h src/Program.cpp src/Database.h src/Database.cpp src/model/Airport.cpp src/model/Airport.h src/menu/Menu.cpp src/menu/MenuItem.cpp src/menu/change/ChangeMenu.cpp src/menu/show/Show.h src/menu/show/Show.cpp src/menu/show/ShowAirports.h src/menu/show/ShowAirports.cpp src/menu/show/ShowAirlines.h src/menu/show/ShowAirlines.cpp src/model/Coordinate.cpp src/menu/search/DirectFlights.h src/menu/search/DirectFlights.cpp src/organizers/Organizer.h src/organizers/Organizer.cpp src/organizers/DirectFlightsOrganizer.h src/organizers/DirectFlightsOrganizer.cpp src/organizers/AirlineOrganizer.h src/organizers/AirlineOrganizer.cpp src/organizers/AirportOrganizer.h src/organizers/AirportOrganizer.cpp src/menu/search/Search.cpp src/menu/search/ReachableDestinations.h src/menu/search/ReachableDestinations.cpp src/menu/show/ShowArtPoints.h src/menu/show/ShowArtPoints.cpp src/menu/show/ShowAirport.h src/menu/show/ShowAirport.cpp src/menu/show/ShowAirline.h src/menu/show/ShowAirline.cpp src/menu/statistics/Statistics.cpp src/menu/statistics/Statistics.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
