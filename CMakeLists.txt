cmake_minimum_required(VERSION 3.24)
project(aerialTransportation)

set(CMAKE_CXX_STANDARD 17)



add_executable(aerialTransportation src/main.cpp src/model/Graph.h src/model/Graph.cpp src/model/Airline.h src/model/Airline.cpp src/Program.h src/Program.cpp src/Database.h src/Database.cpp src/model/Airport.cpp src/model/Airport.h src/menu/Menu.cpp src/menu/MenuItem.cpp src/menu/change/ChangeMenu.cpp src/menu/show/Show.h src/menu/show/Show.cpp src/menu/show/ShowAirports.h src/menu/show/ShowAirports.cpp src/menu/show/ShowAirlines.h src/menu/show/ShowAirlines.cpp src/model/Coordinate.cpp src/menu/search/DirectFlights.h src/menu/search/DirectFlights.cpp src/organizers/Organizer.h src/organizers/Organizer.cpp src/organizers/DirectFlightsOrganizer.h src/organizers/DirectFlightsOrganizer.cpp src/organizers/AirlineOrganizer.h src/organizers/AirlineOrganizer.cpp src/organizers/AirportOrganizer.h src/organizers/AirportOrganizer.cpp src/menu/search/Search.cpp src/menu/search/ReachableDestinations.h src/menu/search/ReachableDestinations.cpp src/menu/show/ShowArtPoints.h src/menu/show/ShowArtPoints.cpp src/menu/show/ShowAirport.h src/menu/show/ShowAirport.cpp src/menu/show/ShowAirline.h src/menu/show/ShowAirline.cpp src/menu/statistics/Statistics.cpp src/menu/statistics/Statistics.h)


