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
#include "vx_internal.h"

VX_API_ENTRY vx_node VX_API_CALL vxCreateGenericNode(vx_graph graph, vx_kernel kernel)
{
    int i=0;
    vx_node node = NULL;

    if (!ownIsValidReference((vx_reference)graph) || !ownIsValidReference((vx_reference)kernel))
    {
        VX_PRINT(VX_DEBUG_WRN, "graph or kernel is a null pointer");
        return NULL;
    }

    ownSemWait(&((vx_reference)graph)->lock);

    // find a empty node slot
    for (i=0; i<VX_MAX_NODES ; i++)
    {
        if (graph->nodes[i] == NULL)
        {
            node = graph->nodes[i];
            break;
        }
    }

    // check 
    if (!node)
    {
        VX_PRINT(VX_DEBUG_WRN, "too many nodes in a graph");
        ownSemPost(&((vx_reference)graph)->lock);
        return NULL;
    }

    node->kernel = kernel;
    node->graph = graph;

    graph->num_nodes++;

    // increase reference count of current kernel and show that there are potentially
    // multiple nodes using this kernel
    ownIncrementReference(&kernel->ref, VX_INTERNAL);

    ownSemPost(&((vx_reference)graph)->lock);
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxQueryNode(vx_node node, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxSetNodeAttribute(vx_node node, vx_enum attribute, const void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseNode(vx_node *node)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxRemoveNode(vx_node *node)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxAssignNodeCallback(vx_node node, vx_nodecomplete_f callback)
{
    return 0;
}

VX_API_ENTRY vx_nodecomplete_f VX_API_CALL vxRetrieveNodeCallback(vx_node node)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxSetNodeTarget(vx_node node, vx_enum target_enum, const char* target_string)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxReplicateNode(vx_graph graph, vx_node first_node, vx_bool replicate[], vx_uint32 number_of_parameters)
{
    return 0;
}
