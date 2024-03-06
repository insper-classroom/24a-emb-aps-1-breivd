add_executable(main main.c pico_flash.c pico_flash.h)

# pull in common dependencies
target_link_libraries(main pico_stdlib hardware_flash hardware_sync)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)
