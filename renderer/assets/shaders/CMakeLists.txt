# List files in directory
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist"")

    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()

    SET(${result} ${dirlist})
ENDMACRO()

# Build VS and FS shaders for each plateform
# osx                   <=> glsl(OpenGL)
# osx with metal        <=> metal shader(Metal)
# ios                   <=> essl(OpenGL ES)
# windows with vs_3_0   <=> hlsl(dx9)
# windows with ps_5_0   <=> hlsl(dx11)
MACRO(SHADERC directory tool)
    file(GLOB FS_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${directory}" "${directory}/*.sc")
    file(GLOB VS_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${directory}" "${directory}/*.sc")

    list(FILTER FS_FILES INCLUDE REGEX "^fs.*.sc$")
    list(FILTER VS_FILES INCLUDE REGEX "^vs.*.sc$")

    if(FS_FILES)
        message("\nBuilding Shaders for repertory ${directory}...")

        # see https://github.com/bkaradzic/bgfx/blob/master/tools/shaderc/shaderc.cpp#L98
        set(PLATFORMS glsl metal essl dx9 dx11)
        set(ARGUMENTS osx os ios windows windows)
        set(PS_ARGUMENTS 150 metal 150 ps_3_0 ps_5_0)
        set(VS_ARGUMENTS 150 metal 150 vs_3_0 vs_5_0)

        foreach(file ${FS_FILES})
            get_filename_component(bare_file ${file} NAME_WLE)

            file(MAKE_DIRECTORY "${directory}/fs_shaders")

            foreach(idx RANGE 4)
                list(GET PLATFORMS ${idx} platform)
                list(GET ARGUMENTS ${idx} argument)
                list(GET PS_ARGUMENTS ${idx} ps_argument)

                message("${directory}/${file} => ${directory}/fs_shaders/${bare_file}_${platform}.bin.hpp")

                execute_process(
                    COMMAND ${tool}
                    -i "tools/include"
                    --type fragment
                    --platform ${argument}
                    --profile ${ps_argument}
                    -f "${directory}/${file}"
                    -o "${directory}/fs_shaders/${bare_file}_${platform}.bin.hpp"
                    --varyingdef "${directory}/varying.def.sc"
                    --bin2c "${bare_file}_${platform}"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    COMMAND_ERROR_IS_FATAL ANY
                )
            endforeach()
        endforeach()

        foreach(file ${VS_FILES})
            get_filename_component(bare_file ${file} NAME_WLE)

            file(MAKE_DIRECTORY "${directory}/vs_shaders")

            foreach(idx RANGE 4)
                list(GET PLATFORMS ${idx} platform)
                list(GET ARGUMENTS ${idx} argument)
                list(GET VS_ARGUMENTS ${idx} vs_argument)

                message("${directory}/${file} => ${directory}/vs_shaders/${bare_file}_${platform}.bin.hpp")

                execute_process(
                    COMMAND ${tool}
                    -i "tools/include"
                    --type vertex
                    --platform ${argument}
                    --profile ${vs_argument}
                    -f "${directory}/${file}"
                    -o "${directory}/vs_shaders/${bare_file}_${platform}.bin.hpp"
                    --varyingdef "${directory}/varying.def.sc"
                    --bin2c "${bare_file}_${platform}"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    COMMAND_ERROR_IS_FATAL ANY
                )
            endforeach()
        endforeach()
    endif()
ENDMACRO()

set(SHADER_BUILD_NAME Shaders)
project(${SHADER_BUILD_NAME})

if(WIN32)
    SET(tool "tools/shaderc_win.exe")
elseif(APPLE)
    SET(tool "tools/shaderc_osx")
elseif(UNIX)
    SET(tool "tools/shaderc_lin")
endif()

message("\nBuilding ${SHADER_BUILD_NAME}...")
SUBDIRLIST(DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

foreach(directory ${DIRECTORIES})
    SHADERC(${directory} ${tool})
endforeach()

add_custom_target(${SHADER_BUILD_NAME}_BUILDS ALL DEPENDS ${BUILDED_SHADERS}) # add_dependencies(${SHADER_BUILD_NAME} ${SHADER_BUILD_NAME}_BUILDS)
message("\n${SHADER_BUILD_NAME} have been succefully builded.\n")