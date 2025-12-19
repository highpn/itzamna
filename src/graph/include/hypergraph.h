#include <stdint.h>
#include <stdlib.h>
//data structures

typedef struct hypervertex_t {
	uint32_t id; /* vertex id */
	struct hypervertex_t *next; /* next vertex in hyperedge */
	uint64_t bitmask; /* bitmask representation hyperedge */
} hypervertex_t;
typedef struct hyperedge_t {
	hypervertex_t *vertices;
	struct hyperedge_t *next;
} hyperedge_t;

typedef struct hypergraph_t {
	hyperedge_t *incidency_list; /* list of hyperedges */
	hypervertex_t **edge_list; /* array of pointers to hypervertices */
	uint32_t num_hyperedges; /* number of hyperedges */
	uint32_t num_hypervertices; /* number of hypervertices */
	double hg_weights[64];
} hypergraph_t;
typedef uint64_t hg_bitmask_t; /* bitmask type for hyperedges */
int hg_bit_index(hg_bitmask_t bitmask, uint32_t index);
void hypergraph_create(hypergraph_t **hg, uint32_t num_hypervertices);
int hypergraph_add_hyperedge(hypergraph_t *hg, hg_bitmask_t *bitmask, uint32_t *vertex_ids, uint32_t num_vertices);
void hypergraph_free(hypergraph_t *hg);

void hypergraph_create(hypergraph_t **hg, uint32_t num_hypervertices) {
	*hg = malloc(sizeof(hypergraph_t));
	if (NULL == *hg) {
		return -1;
	}
	(*hg)->num_hyperedges = 0;
	(*hg)->num_hypervertices = num_hypervertices;
	(*hg)->incidency_list = NULL;
	(*hg)->edge_list = malloc(num_hypervertices * sizeof(hypervertex_t *));
	if (NULL == (*hg)->edge_list) {
		free(*hg);
		return -1;
	}
	for (uint32_t i = 0; i < num_hypervertices; i++) {
		(*hg)->edge_list[i] = NULL;
	}
	return 0;
}
int hypergraph_add_hyperedge(hypergraph_t *hg, hg_bitmask_t *bitmask, uint32_t *vertex_ids, uint32_t num_vertices) {
	if (NULL == hg || NULL == bitmask || NULL == vertex_ids || num_vertices == 0) {
		return -1;
	}

	hyperedge_t *new_edge = malloc(sizeof(hyperedge_t));
	if (NULL == new_edge) {
		return -1;
	}
	new_edge->vertices = NULL;
	new_edge->next = hg->incidency_list;
	hg->incidency_list = new_edge;

	hypervertex_t *prev_vertex = NULL;
	for (uint32_t i = 0; i < num_vertices; i++) {
		uint32_t vid = vertex_ids[i];
		if (vid >= hg->num_hypervertices) {
			return -1;
		}

		hypervertex_t *new_vertex = malloc(sizeof(hypervertex_t));
		if (NULL == new_vertex) {
			return -1;
		}
		new_vertex->id = vid;
		new_vertex->bitmask = *bitmask;
		new_vertex->next = NULL;

		if (prev_vertex == NULL) {
			new_edge->vertices = new_vertex;
		} else {
			prev_vertex->next = new_vertex;
		}
		prev_vertex = new_vertex;

		new_vertex->next = hg->edge_list[vid];
		hg->edge_list[vid] = new_vertex;
	}
	*bitmask <<= 1; //  shift bitmask for next hyperedge
	hg->num_hyperedges++;
	return 0;
}

void hypergraph_free(hypergraph_t *hg) {
	if (NULL == hg) {
		return;
	}

	hyperedge_t *current_edge = hg->incidency_list;
	while (current_edge != NULL) {
		hyperedge_t *tmp_edge = current_edge;
		current_edge = current_edge->next;

		hypervertex_t *current_vertex = tmp_edge->vertices;
		while (current_vertex != NULL) {
			hypervertex_t *tmp_vertex = current_vertex;
			current_vertex = current_vertex->next;
			free(tmp_vertex);
		}
		free(tmp_edge);
	}

	free(hg->edge_list);
	free(hg);
}
void print_hypergraph(hypergraph_t *hg) {
	if (hg == NULL) {
		return;
	}
	printf("Hypergraph with %u hypervertices and %u hyperedges:\n", hg->num_hypervertices, hg->num_hyperedges);
	hyperedge_t *current_edge = hg->incidency_list;
	uint32_t edge_index = 0;
	while (current_edge != NULL) {
		printf(" Hyperedge %u: ", edge_index++);
		hypervertex_t *current_vertex = current_edge->vertices;
		while (current_vertex != NULL) {
			printf("%u ", current_vertex->id);
			current_vertex = current_vertex->next;
		}
		printf("\n");
		current_edge = current_edge->next;
	}
}