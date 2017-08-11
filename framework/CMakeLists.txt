SET(VX_SRCS vx_context.c
            vx_error.c
            vx_image.c
            vx_kernel.c
            vx_graph.c
            vx_node.c
            vx_parameter.c
            vx_scalar.c
            vx_reference.c
            vx_delay.c
            vx_logging.c
            vx_distribution.c
            vx_threshold.c
            vx_matrix.c
            vx_convolution.c
            vx_pyramid.c
            vx_remap.c
            vx_array.c
            vx_object_array.c
            vx_meta_format.c
            vx_node_api.c
            vx_target.c
            vxu.c)

IF(BUILD_MEM_ANALYSIS)
SET(VX_SRCS ${VX_SRCS} vx_memory.c)
ENDIF(BUILD_MEM_ANALYSIS)

ADD_LIBRARY(openvx ${VX_SRCS}) 
