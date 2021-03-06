cmake_minimum_required(VERSION 2.8.11)	# 2.8.11 required for target_include_directories

project(ProbeApiTools)
include(src/common/version.h)
message(STATUS "Probe API Tools v.${PRODUCT_VERSION}")

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

# =================================================

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE MinSizeRel CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

message("CMAKE_C_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_C_FLAGS_RELEASE is ${CMAKE_C_FLAGS_RELEASE}")
message("CMAKE_C_FLAGS_MINSIZEREL is ${CMAKE_C_FLAGS_MINSIZEREL}")
message("CMAKE_C_FLAGS_RELWITHDEBINFO is ${CMAKE_C_FLAGS_RELWITHDEBINFO}")

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

# =================================================

if(NOT WIN32 AND CYGWIN)
	message(STATUS "WARNING! CYGWIN without WIN32 was found!")
	set(WIN32 1)
endif()

# http://stackoverflow.com/questions/1618927/cmake-microsoft-visual-studio-and-monolithic-runtimes
if(MSVC)
	message(STATUS "MSVC compiler is used! Use static linking to CRT...")
#We statically link to reduce dependencies
foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
    if(${flag_var} MATCHES "/MDd")
        string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MDd")
endforeach(flag_var)
endif(MSVC)

if(MSVC)
	set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /O2 /Os /GL /Gy")
	set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} /O2 /Os /GL /Gy")
	set(CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL "${CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL} /LTCG")
	set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} /OPT:REF /OPT:ICF /LTCG")
endif(MSVC)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations")
endif()

if(MINGW AND CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# =================================================

FIND_PACKAGE(Boost)
if(Boost_FOUND)
	message(STATUS "Boost libraries found at: ${Boost_LIBRARIES}")
	message(STATUS "Boost includes found at: ${Boost_INCLUDE_DIRS}")
else()
	message(STATUS "Could not find Boost on your system")
endif(Boost_FOUND)

FIND_PACKAGE(CURL)
if(CURL_FOUND)
	message(STATUS "Curl libraries found at: ${CURL_LIBRARIES}")
	message(STATUS "Curl includes found at: ${CURL_INCLUDE_DIRS}")
else()
	message(STATUS "Could not find cURL on your system")
endif(CURL_FOUND)

# =================================================

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#set(MYBINDIR .)

# =================================================

if(WIN32)
	add_subdirectory(deps/build.projects/curl ${MYBINDIR})
	add_subdirectory(deps/build.projects/zlib ${MYBINDIR})
#	add_subdirectory(deps/build.projects/openssl ${MYBINDIR})
endif()

add_subdirectory(deps/build.projects/curlpp ${MYBINDIR})
add_subdirectory(deps/build.projects/jsoncpp ${MYBINDIR})

add_subdirectory(src/common ${MYBINDIR})

add_subdirectory(src/dping ${MYBINDIR})
add_subdirectory(src/dtraceroute ${MYBINDIR})

# =================================================

set(VERSION "${PRODUCT_VERSION}")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "probe-api-tools")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Sergey Kolomenkin")
set(CPACK_PACKAGE_VENDOR "Optimal Software s.r.o.")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)

# =================================================
