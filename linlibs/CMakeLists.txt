add_library(linlibs simplex.c twostage.c)
install(TARGETS linlibs DESTINATION lib)
install(FILES simplex.h twostage.h DESTINATION include)
