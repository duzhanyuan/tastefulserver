
# Target
set(target tastefulserver)
message(STATUS "Lib ${target}")

#
# External libraries
#

find_package(Qt5Core 5.0 REQUIRED)

#
# Includes
#

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
)

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DTASTEFULSERVER_STATIC")
else()
    add_definitions("-DTASTEFULSERVER_EXPORTS")
endif()

#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(sources
	${source_path}/core/ThreadPool.cpp
	${source_path}/core/ThreadPool.h
	${source_path}/core/Task.cpp
	${source_path}/core/QVariantTree.h
	${source_path}/core/QVariantTree.hpp
	${source_path}/core/ByteArrayStream.cpp
	${source_path}/core/QVariantTree.cpp
	${source_path}/http/Cookie.cpp
	${source_path}/http/ContentType.cpp
	${source_path}/http/HttpVersion.cpp
	${source_path}/http/MultiPart.cpp
	${source_path}/http/RequestParameters.cpp
	${source_path}/http/HttpRequest.cpp
	${source_path}/http/HttpEntity.cpp
	${source_path}/http/HttpServer.cpp
	${source_path}/http/HttpMessage.cpp
	${source_path}/http/HttpHandler.cpp
	${source_path}/http/HttpResponse.cpp
	${source_path}/http/httpUtil.cpp
	${source_path}/http/UploadedFile.cpp
	${source_path}/http/HttpHeader.cpp
	${source_path}/http/HttpMethod.cpp
	${source_path}/http/HttpsServer.cpp
	${source_path}/server/SocketCreation.h
	${source_path}/server/ConnectionHandler.cpp
	${source_path}/server/TcpServer.cpp
	${source_path}/server/SocketCreation.cpp
)

set(api_includes
	${include_path}/ByteArrayStream
	${include_path}/ByteArrayStream.h
	${include_path}/ConnectionHandler
	${include_path}/ConnectionHandler.h
	${include_path}/ContentType
	${include_path}/ContentType.h
	${include_path}/Cookie
	${include_path}/Cookie.h
	${include_path}/http
	${include_path}/HttpEntity
	${include_path}/HttpEntity.h
	${include_path}/http.h
	${include_path}/HttpHandler
	${include_path}/HttpHandler.h
	${include_path}/HttpHeader
	${include_path}/HttpHeader.h
	${include_path}/HttpMessage
	${include_path}/HttpMessage.h
	${include_path}/HttpMethod
	${include_path}/HttpMethod.h
	${include_path}/HttpRequest
	${include_path}/HttpRequest.h
	${include_path}/HttpResponse
	${include_path}/HttpResponse.h
	${include_path}/HttpServer
	${include_path}/HttpServer.h
	${include_path}/HttpsServer
	${include_path}/HttpsServer.h
	${include_path}/httpStatusCodes
	${include_path}/httpStatusCodes.h
	${include_path}/httpUtil
	${include_path}/httpUtil.h
	${include_path}/HttpVersion
	${include_path}/HttpVersion.h
	${include_path}/MultiPart
	${include_path}/MultiPart.h
	${include_path}/RequestParameters
	${include_path}/RequestParameters.h
	${include_path}/Task
	${include_path}/Task.h
	${include_path}/TcpServer
	${include_path}/TcpServer.h
	${include_path}/UploadedFile
	${include_path}/UploadedFile.h
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})

#
# Build library
#

if(OPTION_BUILD_STATIC)
    add_library(${target} ${api_includes} ${sources})
else()
    add_library(${target} SHARED ${api_includes} ${sources})
endif()

target_link_libraries(${target} ${libs})
qt5_use_modules(${target} Core Network Xml)

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	            ${include_path})

#
# Deployment
#

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})