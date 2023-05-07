add_library(iolibs ioctrl.c)
install(TARGETS iolibs DESTINATION lib)
install(FILES ioctrl.h DESTINATION include)
