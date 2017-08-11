SET(C_MODEL_KERNEL_SRCS kernels/cmodel_color_convert.c)

ADD_LIBRARY(openvx-c_model vx_interface.c
                           vx_kernel_list.c
                           ${C_MODEL_KERNEL_SRCS})
