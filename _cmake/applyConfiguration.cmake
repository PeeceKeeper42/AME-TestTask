message("< Start of \"applyConfiguration.cmake\"")

# Aquiring github link to project
# GIT_REPOSITORY_URL
execute_process(
    COMMAND git config --get remote.origin.url
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REPOSITORY_URL
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Aquiring github link to user
# GIT_USER_URL
string(FIND ${GIT_REPOSITORY_URL} "/" INDEX_GIT_NAME REVERSE)
string(SUBSTRING ${GIT_REPOSITORY_URL} 0 ${INDEX_GIT_NAME} GIT_USER_URL)
message("GIT_USER_URL = ${GIT_USER_URL}")

# Aquiring git author's name
# GIT_PROJECT_CREATOR
string(REPLACE "https://github.com/" "" GIT_PROJECT_CREATOR ${GIT_USER_URL})

# Aquiring build date
# BUILD_DATE
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")

configure_file (
    "${INCLUDE_DIRECTORY}/config.hpp.in"
    "${PROJECT_BINARY_DIR}/config.h"
    @ONLY
)

# START OUTPUT BLOCK

message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message("GIT_PROJECT_CREATOR = ${GIT_PROJECT_CREATOR}")
message("GIT_USER_URL = ${GIT_USER_URL}")
message("GIT_REPOSITORY_URL = ${GIT_REPOSITORY_URL}")
message("BUILD_DATE = ${BUILD_DATE}")

# END OUTPUT BLOCK

message("< End of file \"applyConfiguration.cmake\"")
