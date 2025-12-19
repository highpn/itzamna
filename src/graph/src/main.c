#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/hypergraph.h"
#include <linux/time.h>

int main() {
	srand((unsigned int)time(NULL));
	graph_t *g;
	g = graph_create(10, 0);

	//graph_free(g);

	int payloadA = 1, payloadB = 2;

	// Add 10 vertices
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)
			graph_add_vertex(g, i, &payloadA);
		else {
			graph_add_vertex(g, i, &payloadB);
			//printf("%d", graph_count_vertices(g->adj, g->num_vertices));
		}
	}
	printf("Vertices added: %d\n", g->num_vertices);
	//utils_graph_add_grid(g, 10, 2500);
	printf("Edges added: %d\n", g->num_edges);
	//exit(1);
	//print_hypergraph(hg);

	// --- Add Petersen graph edges (undirected, weight = 1.0) ---

	// Outer cycle

	graph_add_edge_new(g, g->vertices[0], g->vertices[1], 1.0);
	graph_add_edge_new(g, g->vertices[1], g->vertices[2], 0.5);
	graph_add_edge_new(g, g->vertices[2], g->vertices[3], 1.0);
	graph_add_edge_new(g, g->vertices[3], g->vertices[0], 1.0);

	graph_add_edge_new(g, g->vertices[4], g->vertices[0], 0.1);
	// Inner cycle (star polygon)
	graph_add_edge_new(g, g->vertices[5], g->vertices[4], 1.0);
	graph_add_edge_new(g, g->vertices[5], g->vertices[7], 1.0);
	graph_add_edge_new(g, g->vertices[7], g->vertices[1], 1.0);
	graph_add_edge_new(g, g->vertices[6], g->vertices[7], 1.0);
	graph_add_edge_new(g, g->vertices[6], g->vertices[8], 1.0);
	// Spokes
	//graph_add_edge(g, g->vertices[0], g->vertices[5], 1.0);
	//graph_add_edge(g, g->vertices[1], g->vertices[6], 1.0);
	//graph_add_edge(g, g->vertices[2], g->vertices[7], 1.0);
	graph_add_edge_new(g, g->vertices[9], g->vertices[8], 0.5);
	graph_add_edge_new(g, g->vertices[6], g->vertices[9], 1.0);

	//node_t **copy = graph_copy_adj_list(g->adj, g->num_vertices);

	//vertex_list_print(copy, g->num_vertices);
	struct timespec start,
	        end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	graph_mst_t *mst = graph_boruvka(g);
	clock_gettime(CLOCK_MONOTONIC, &end);
	double dif = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1e9;
	printf("Prim's algorithm took %.2f seconds\n", dif);
	if (visualize_graph_weights(mst) == 7.1) {
		printf("Visualization successful with correct total weight.\n");
	} else {
		printf("Visualization completed but total weight mismatch.\n");
	}
	printf("\n");
	//utils_mst_print_as_grid(mst, 10, 2500);
	exit(1);
	//exit(1);
	//graph_edge_print(g);
	// printf("%d",(*g->adj_list)->next->from.id);
	//swap_edge(g->adj_list, 4, 0);
	//isualize_mst(*g->adj_list, g->num_vertices);

	//printf("%d", graph_is_complete(g));

	//printf("\n %lf", graph_edge_get(*g->adj_list, 0));
	return 0;
}