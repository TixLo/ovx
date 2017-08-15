SET(UT_SRCS seatest/seatest.c
            unittest.c
            ut_context.c
            ut_graph.c
            ut_image.c
            ut_matrix.c
            ut_logging.c
            ut_reference.c) 

IF(BUILD_MEM_ANALYSIS)
SET(UT_SRCS ${UT_SRCS} ut_memory.c)
ENDIF(BUILD_MEM_ANALYSIS)

ADD_EXECUTABLE(unittest ${UT_SRCS})
 
TARGET_LINK_LIBRARIES(unittest ${LINK_LIBS})
