/*
 * Copyright (c) 2019, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once 

/** 
 * @Synopsis   Warp existing gdf columns representing an edge list in a gdf_graph. 
 *             cuGRAPH does not own the memory used to represent this graph. This function does not allocate memory. 
 * @Param[in] *source_indices        This gdf_column of size E (number of edges) contains the index of the source for each edge.
 *                                   Indices must be in the range [0, V-1]. 
 * @Param[in] *destination_indices   This gdf_column of size E (number of edges) contains the index of the destination for each edge. 
 *                                   Indices must be in the range [0, V-1].
 * @Param[in] *edge_data (optional)  This pointer can be null_ptr. If not, this gdf_column of size E (number of edges) contains the weiht for each edge. 
 *                                   The type expected to be floating point.
 * 
 * @Param[out] *graph                cuGRAPH graph descriptor containing the newly added edge list (edge_data is optional).
 * 
 * @Returns                          GDF_SUCCESS upon successful completion. 
 */
/* ----------------------------------------------------------------------------*/
gdf_error gdf_edge_list_view(gdf_graph *graph, 
                             const gdf_column *source_indices,
                             const gdf_column *destination_indices,
                             const gdf_column *edge_data);

gdf_error gdf_adj_list_view (gdf_graph *graph, 
                             const gdf_column *offsets,
                             const gdf_column *indices,
                             const gdf_column *edge_data);

gdf_error gdf_add_adj_list(gdf_graph *graph);
gdf_error gdf_add_transpose(gdf_graph *graph);
gdf_error gdf_add_edge_list(gdf_graph *graph);

gdf_error gdf_delete_adj_list(gdf_graph *graph);
gdf_error gdf_delete_edge_list(gdf_graph *graph);
gdf_error gdf_delete_transpose(gdf_graph *graph);

/** 
 * @Synopsis   Find the PageRank vertex values for a graph. cuGraph computes an approximation of the Pagerank eigenvector using the power method. 
 * The number of iterations depends on the properties of the network itself; it increases when the tolerance descreases and/or alpha increases toward the limiting value of 1.
 * The user is free to use default values or to provide inputs for the initial guess, tolerance and maximum number of iterations.
 * 
 * @Param[in] graph               cuGRAPH graph descriptor, should contain the connectivity information as an edge list (edge weights are not used for this algorithm). 
 *                                The transposed adjacency list will be computed if not already present.
 * @Param[in] alpha               The damping factor alpha represents the probability to follow an outgoing edge, standard value is 0.85. 
                                  Thus, 1.0-alpha is the probability to “teleport” to a random node. Alpha should be greater than 0.0 and strictly lower than 1.0.
 * @Param[in] has_guess           This parameter is used to notify cuGRAPH if it should use a user-provided initial guess. False means the user doesn't have a guess, in this case cuGRAPH will use a uniform vector set to 1/V. 
 *                                If the value is True, cuGRAPH will read the pagerank parameter and use this as an initial guess.
 *                                The initial guess must not be the vector of 0s. Any value other than 1 or 0 is treated as an invalid value.
 * @Param[in] pagerank (optional) Initial guess if has_guess=true
 * @Param[in] tolerance           Set the tolerance the approximation, this parameter should be a small magnitude value. 
 *                                The lower the tolerance the better the approximation. If this value is 0.0f, cuGRAPH will use the default value which is 1.0E-6. 
 *                                Setting too small a tolerance can lead to non-convergence due to numerical roundoff. Usually values between 0.01 and 0.00001 are acceptable.
 * @Param[in] max_iter            The maximum number of iterations before an answer is returned. This can be used to limit the execution time and do an early exit before the solver reaches the convergence tolerance. 
 *                                If this value is lower or equal to 0 cuGRAPH will use the default value, which is 500.
 * 
 * @Param[out] *pagerank          The PageRank : pagerank[i] is the PageRank of vertex i.
 * 
 * @Returns                       GDF_SUCCESS upon successful completion. 
 */
/* ----------------------------------------------------------------------------*/
gdf_error gdf_pagerank(gdf_graph *graph, gdf_column *pagerank, float alpha, float tolerance, int max_iter, bool has_guess);

gdf_error gdf_grmat_gen (const char* argv, size_t &vertices, size_t &edges, gdf_column* src, gdf_column* dest, gdf_column* val);

gdf_error gdf_bfs(gdf_graph *graph, gdf_column *distances, gdf_column *predecessors, int start_node, bool directed);
