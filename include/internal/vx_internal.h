/* Copyright Statement:
 *
 * Copyright (C) 2017 Tix Lo All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __VX_INTERNAL_H__
#define __VX_INTERNAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <VX/vx.h>
#include <VX/vx_compatibility.h>

/*
 * kernel argument flags
 */
#define OVX_KERNEL_MAX_ARGS             32
#define OVX_KERNEL_ARG_IN               0x01
#define OVX_KERNEL_ARG_OUT              0x02
#define OVX_KERNEL_ARG_OPTIONAL         0x04

/*
 * kernel configuration
 */
#define OVX_KERNEL_CONF_DEVICE_CPU      0x0001
#define OVX_KERNEL_CONF_DEVICE_GPU      0x0002

/*
 * extened more image format based on the VX_DF_IMAGE definition.
 */
enum vx_df_image_ext_e {
    /* grayscale format */
    VX_DF_IMAGE_GRAY = VX_DF_IMAGE('G', 'R', 'A', 'Y'),
};

/*
 * include platform independent header
 */
#include "vx_platform.h"

/*! \brief A magic value to look for and set in references.
 * \ingroup group_int_defines
 */
#define VX_MAGIC            (0xAAC0DEAA)

/*! \brief Defines the maximum number of characters in a target string.
 * \ingroup group_target
 */
#define VX_MAX_TARGET_NAME  (64)

/*! \brief Maximum number of nodes in a graph
 * \ingroup group_target
 */
#define VX_MAX_NODES        (128)

/*! \brief Maximum number of kernel in a context
 * \ingroup group_target
 */
#define VX_MAX_KERNELS      (256)

/*! \brief The maximum number of 2d planes an image may have.
 * \ingroup group_int_image
 */
#define VX_PLANE_MAX         (4)

#ifndef dimof
/*! \brief Get the dimensionality of the array.
 * \details If not defined by the platform, this allows client to retrieve the
 * dimensionality of an array of fixed sized units.
 * \ingroup group_int_macros
 */
#define dimof(x)    (sizeof(x)/sizeof(x[0]))
#endif

enum vx_target_priority_e {
    VX_TARGET_PRIORITY_BASE = -1,
#if defined(HAVE_C_MODEL)
    /*! \brief Defines the priority of the C model target */
    VX_TARGET_PRIORITY_C_MODEL,
#endif
#if defined(HAVE_OPENCL)
    /*! \brief Defines the priority of the OpenCL target */
    VX_TARGET_PRIORITY_OPENCL,
#endif
    /*! \brief Defines the maximum priority */
    VX_TARGET_PRIORITY_MAX,
};

/*! \brief An internal enum for notating which sort of reference type we need.
 * \ingroup group_int_type
 */
typedef enum _vx_reftype_e {
    VX_INTERNAL = 1,
    VX_EXTERNAL = 2,
    VX_BOTH = 3,
} vx_reftype_e;

/*! \brief The dimensions enumeration, also stride enumerations.
 * \ingroup group_int_image
 */
enum vx_dim_e {
    /*! \brief Channels dimension, stride */
    VX_DIM_C = 0,
    /*! \brief Width (dimension) or x stride */
    VX_DIM_X,
    /*! \brief Height (dimension) or y stride */
    VX_DIM_Y,
    /*! \brief [hidden] The maximum number of dimensions */
    VX_DIM_MAX,
};

/*! \brief Defines the number of targets in this implementation.
 * \ingroup group_int_target
 */
#define VX_INT_MAX_NUM_TARGETS  (VX_TARGET_PRIORITY_MAX)

/*! \brief Defines the number of image format in this implementation.
 * \ingroup group_int_target
 */
#define VX_INT_MAX_NUM_IMAGE_FORMAT (2)

/*! \brief Maximum number of references in the context
 */
#define VX_INT_MAX_REF              (128)

/*! A parameter checker for size
 * \ingroup group_int_macros
 */
#define VX_CHECK_SIZE_PARAM(size, type) (size == sizeof(type))


/*
 * Define structure variables
 */ 
typedef struct _vx_target vx_target_t;
typedef struct _vx_node vx_node_t;
typedef struct _vx_graph vx_graph_t;
typedef struct _vx_context vx_context_t;
typedef struct _vx_target_funcs_t vx_target_funcs_t; 
typedef struct _vx_reference vx_reference_t;
typedef struct _vx_kernel vx_kernel_t;
typedef struct _vx_image vx_image_t;
typedef struct _vx_matrix vx_matrix_t;
typedef struct _vx_memory vx_memory_t;
typedef struct _vx_image_fmt_desp vx_image_fmt_desp_t;
 
/*
 * include all neccessary private headers
 */
#include "vx_osal.h"
#include "vx_khr_icd.h"
#include "vx_debug.h"
#include "vx_memory.h"

/*! \brief An abstract handle to a target.
 * \ingroup group_targetd
 */
typedef vx_target_t *vx_target;

/*! \brief The function which initializes the target
 * \param [in] target The pointer to the target context.
 * \note The target interface function must be exported as "vxTargetInit"
 * \ingroup group_int_target
 */
typedef vx_status (*vx_target_init_f)(vx_target target);

/*! \brief The function which deinitializes the target.
 * \param [in] target The pointer to the target context.
 * \note The target interface function must be exported as "vxTargetDeinit"
 * \ingroup group_int_target
 */
typedef vx_status (*vx_target_deinit_f)(vx_target target);

/*! \brief Allows OpenVX to query a target to see if it supports an additional
 * abstract target type like "khronos.automatic" or "khronos.low_power" on a
 * specific kernel.
 * \param [in] target The pointer to the target context.
 * \param [in] targetName The name of the abstract target.
 * \param [in] kernelName The name of the kernel.
 * \param [out] pIndex The pointer to the index of the kernel in the target's list
 * if the kernel is supported (the function will return VX_SUCCESS).
 * \note The target interface function must be exported as "vxTargetSupports"
 * \return A <tt>\ref vx_status_e</tt> enumeration
 * \retval VX_SUCCESS The kernel is supported and the pIndex has been set.
 * \retval VX_ERROR_NOT_SUPPORTED the kernel is not supported as stated.
 * \ingroup group_int_target
 */
typedef vx_status (*vx_target_supports_f)(vx_target target,
                                          vx_char targetName[VX_MAX_TARGET_NAME],
                                          vx_char kernelName[VX_MAX_TARGET_NAME],
                                          vx_uint32 *pIndex);

/*! \brief Processes the array of nodes supplied.
 * \param [in] target The pointer to the target context.
 * \param [in] nodes The array of nodes pointers.
 * \param [in] startIndex The beginning index to process
 * \param [in] numNodes The number of nodes to process from startIndex.
 * \note The target interface function must be exported as "vxTargetProcess"
 * \ingroup group_int_target
 */
typedef vx_action (*vx_target_process_f)(vx_target target, vx_node nodes[], vx_size startIndex, vx_size numNodes);

/*! \brief Verifies the array of nodes supplied for target specific information.
 * \param [in] target The pointer to the target context.
 * \param [in] node The node to verify.
 * \note The target interface function must be exported as "vxTargetVerify"
 * \ingroup group_int_target
 */
typedef vx_status (*vx_target_verify_f)(vx_target target, vx_node node);

/*! \brief Adds a kernel to a target.
 * \param [in] target The target object.
 * \param [in] name
 * \param [in] enumeration
 * \param [in] func_ptr
 * \param [in] numParams
 * \param [in] validate
 * \param [in] input
 * \param [in] output
 * \param [in] initialize
 * \param [in] deinitialize
 * \ingroup group_int_target
 */
typedef vx_kernel (*vx_target_addkernel_f)(vx_target target,
                                           const vx_char name[VX_MAX_KERNEL_NAME],
                                           vx_enum enumeration,
                                           vx_kernel_f func_ptr,
                                           vx_uint32 num_parameters,
                                           vx_kernel_validate_f validate,
                                           vx_kernel_input_validate_f input,
                                           vx_kernel_output_validate_f output,
                                           vx_kernel_initialize_f initialize,
                                           vx_kernel_deinitialize_f deinitialize);

/*! \brief The structure which holds all the target interface function pointers.
 * \ingroup group_int_target
 */
struct _vx_target_funcs_t {
    /*! \brief Target name */
    vx_char                 name[VX_MAX_REFERENCE_NAME];
    /*! \brief Target author */
    vx_char                 author[VX_MAX_REFERENCE_NAME];
    /*! \brief Target description */
    vx_char                 description[VX_MAX_REFERENCE_NAME];
    /*! \brief Target initialization function */
    vx_target_init_f        init;
    /*! \brief Target deinitialization function */
    vx_target_deinit_f      deinit;
    /*! \brief Target query function */
    vx_target_supports_f    supports;
    /*! \brief Target processing function */
    vx_target_process_f     process;
    /*! \brief Target verification function */
    vx_target_verify_f      verify;
    /*! \brief Target function to add a kernel */
    vx_target_addkernel_f   addkernel;
};

/*
 * used to destroy a node
 */
typedef void (*vx_destructor_f)(vx_reference ref);
/*
 * definition of destructor 
 */
typedef struct _vx_destructor_t {
    vx_enum                 type;
    vx_destructor_f         destructor;
}vx_destructor_t;

/*
 * The internal representation of a image format description
 */
struct _vx_image_fmt_desp {
    /*! \brief The image format */
    vx_df_image             format;
    /*! \brief The detail information of image format */
    vx_size                 components;
    vx_size                 planes;
    vx_size                 pixel_size_in_bits;
};

/*! \brief The most basic type in the OpenVX system. Any type that inherits
 *  from vx_reference_t must have a vx_reference_t as its first memeber
 *  to allow casting to this type.
 * \ingroup group_int_refererence
 */
struct _vx_reference {
    /*! \brief Platform for ICD compatibility. */
    struct _vx_platform     *platform;
    /*! \brief used to validate references, must be set to VX_MAGIC */
    vx_uint32               magic;
    /*! \brief Set to an enum value in \ref vx_type_e. */
    vx_enum                 type;
    /*! \brief Pointer to the top level context.
     * If this reference is the context, this will be NULL.
     */
    vx_context              context;
    /*! \brief The pointer to the object's scope parent. When virtual objects
     * are scoped within a graph, this will point to that parent graph. This is
     * left generic to allow future scoping variations. By default scope should
     * be the same as context.
     */
    vx_reference            scope;
    /*! \brief The count of the number of users with this reference. When
     * greater than 0, this can not be freed. When zero, the value can be
     * considered inaccessible.
     */
    vx_uint32               external_count;
    /*! \brief The count of the number of framework references. When
     * greater than 0, this can not be freed.
     */
    vx_uint32               internal_count;
    /*! \brief The reference lock which is used to protect access to "in-fly" data. */
    vx_sem_t                lock;
    /*! \brief The reference name */
    vx_char                 name[VX_MAX_REFERENCE_NAME];
};

/*
 * The internal representation of an abstract kernel
 */
struct _vx_kernel {
    /*! \brief The base of reference object*/
    vx_reference_t          ref;
    /*! \brief The kernel name */
    vx_char                 name[VX_MAX_REFERENCE_NAME];
    /*! \brief The kernel id */
    vx_enum                 enumeration;  
    /*! \brief The Kernek execution function */
    vx_kernel_f             func;
};

/*
 * The internal representation of a node.
 */
struct _vx_node {
    /*! \brief The base of reference object*/
    vx_reference_t          ref;
    /*! \brief the pointer of kernel */
    vx_kernel               kernel; 
    /*! \brief the pointer of parent graph */
    vx_graph                graph;
};

/*
 * The internal representation of a node.
 */
struct _vx_graph {
    /*! \brief The base of reference object*/
    vx_reference_t          ref;
    /*! \brief the pointer of nodes list */
    vx_node                 nodes[VX_MAX_NODES]; 
    /*! \brief the number of nodes in this graph */
    vx_uint32               num_nodes;
};

/*
 * The internal representation of a image.
 */
struct _vx_image {
    /*! \brief The base of reference object*/
    vx_reference_t          ref;
};

/*
 * The internal representation of a memory.
 */
struct _vx_memory {
    /*! \brief The number of pointers in the array */
    vx_uint32               nptrs;
    /*! \brief The array of ROI offsets (one per plane for images) */
    vx_uint32               offset[VX_PLANE_MAX];
    /*! \brief The array of pointers (one per plane for images) */
    vx_uint8*               ptrs[VX_PLANE_MAX];
    /*! \brief The number of dimensions per ptr */
    vx_int32                ndims;
    /*! \brief The dimensional values per ptr */
    vx_int32                dims[VX_PLANE_MAX][VX_DIM_MAX];
    /*! \brief The per ptr stride values per dimension */
    vx_int32                strides[VX_PLANE_MAX][VX_DIM_MAX];
};

/*
 * The internal representation of a matrix.
 */
struct _vx_matrix {
    /*! \brief The base of reference object */
    vx_reference_t          ref;
    /*! \brief reference from vx_type_e */
    vx_enum                 data_type;
    /*! \brief number of columns */
    vx_size                 cols;
    /*! \brief number of rows */
    vx_size                 rows;
    /*! \brief origin */
    vx_coordinates2d_t      origin;
    /*! \brief reference from vx_pattern_e */
    vx_enum                 pattern;
    /*! \brief memory layout */
    vx_memory_t             memory;
};

/*
 * The internal representation of a target.
 */
struct _vx_target {
    /*! \brief The table of function pointer to each target */
    vx_target_funcs_t       funcs;
    /*! \brief The number of supported kernels on this target */
    vx_uint32               num_kernels;
    /*! \brief The supported kernels on this target */
    vx_kernel_t             kernels[VX_MAX_KERNELS];
};

/*
 * The top level context data for the entire OpenVX instance
 */
struct _vx_context {
    /*! \brief The base of reference object*/
    vx_reference_t          ref;
    /*! \brief The list of implemented targets */
    vx_target_t             targets[VX_INT_MAX_NUM_TARGETS];
    /*! \brief The list of allowed image formats*/
    vx_image_fmt_desp_t     image_formats[VX_INT_MAX_NUM_IMAGE_FORMAT];
    /*! \brief log callback for errors*/
    vx_log_callback_f       log_cb;
    /*! \brief the log toggle */
    vx_bool                 log_enabled;
    /*! \brief if true, the log callback is reentrant and doesn't need to be locked */
    vx_bool                 log_reentrant;
    /*! \brief the log semaphore */
    vx_sem_t                log_lock;
    /*! \brief The reference table which contains all object handls */
    vx_reference            ref_table[VX_INT_MAX_REF];
    /*! \brief The number of reference in ref_table */
    vx_uint32               ref_num;
};

//////////////////////////////////////////////////////////////////////////////////
// The internal functions of vx_context
//////////////////////////////////////////////////////////////////////////////////
/*! \brief Used to validate vx_context object.
 * \param [in] context The context to validate.
 */
vx_bool ownIsValidContext(vx_context context);

/*! \brief Dump context object
 */
void ownPrintContext(vx_context context);

//////////////////////////////////////////////////////////////////////////////////
// The internal functions of vx_graph
//////////////////////////////////////////////////////////////////////////////////
/*! \brief Used to validate vx_context object.
 * \param [in] ref The graph will be destroyed
 */
void ownDestructGraph(vx_reference ref);

//////////////////////////////////////////////////////////////////////////////////
// The internal functions of vx_reference
//////////////////////////////////////////////////////////////////////////////////
/*! \brief Used to initialize any vx_reference.
 * \param [in] ref The pointer to the reference object.
 * \param [in] context The system context to put in the reference.
 * \param [in] type The type of the vx_<object>
 * \param [in] scope The scope under which the object is allocated.
 * \ingroup group_int_reference
 */
void ownInitReference(vx_reference ref, vx_context context, vx_enum type, vx_reference scope);

/*! \brief Used to destroy a reference.
 * \param [in] ref The reference to release.
 * \param [in] internal If true, the internal count is decremented, else the external
 * \ingroup group_int_reference
 */
vx_status ownReleaseReferenceInt(vx_reference *ref, vx_enum reftype);

/*! \brief Used to validate everything but vx_context, vx_image and vx_buffer.
 * \param [in] ref The reference to validate.
 * \ingroup group_implementation
 */
vx_bool ownIsValidReference(vx_reference ref);

/*! \brief Increments the ref count.
 * \param [in] ref The reference to print.
 * \ingroup group_int_reference
 */
vx_uint32 ownIncrementReference(vx_reference ref, vx_enum reftype);

/*! \brief Decrements the ref count.
 * \param [in] ref The reference to print.
 * \ingroup group_int_reference
 */
vx_uint32 ownDecrementReference(vx_reference ref, vx_enum reftype);

/*! \brief Returns the total reference count of the object.
 * \param [in] ref The reference to print.
 * \ingroup group_int_reference
 */
vx_uint32 ownTotalReferenceCount(vx_reference ref);

/*! \brief Used to create a reference.
 * \param [in] context the system context
 * \param [in] type object type
 * \param [in] reftype reference type. external, internal, or both
 * \param [in] scope
 * \ingroup group_int_reference
 */
vx_reference ownCreateRef(vx_context context, vx_enum type, vx_enum reftype, vx_reference scope);

//////////////////////////////////////////////////////////////////////////////////
// The internal functions of vx_target
//////////////////////////////////////////////////////////////////////////////////
/*! \brief This allows the implementation to load a target interface into OpenVX.
 * \param [in] context The overall context pointer.
 * \param [in] the function pointer of the target module.
 * \ingroup group_int_target
 */
vx_status ownLoadTarget(vx_context_t *context, vx_target_funcs_t *target_func);

//////////////////////////////////////////////////////////////////////////////////
// The internal functions of vx_image
//////////////////////////////////////////////////////////////////////////////////
/*! \brief Create all legal image format in OpenVX
 * \param [in] context The overall context pointer.
 * \ingroup group_int_target
 */
vx_status ownInitImageFormats(vx_context context);

/*! \brief Used to validate vx_context object.
 * \param [in] ref The image will be destroyed
 */
void ownDestructImage(vx_reference ref);

//////////////////////////////////////////////////////////////////////////////////
// The internal functions of vx_matrix
//////////////////////////////////////////////////////////////////////////////////
/*! \brief Used to validate vx_matrix object.
 * \param [in] ref The image will be destroyed
 */
void ownDestructMatrix(vx_reference ref);

#endif// __VX_INTERNAL_H__
