#include "../include/graph.h"
#include <stdio.h>

graph_t *
graph_create(uint32_t num_vertices, int directed) {

	graph_t *graph = malloc(sizeof(graph_t));
	if (NULL == graph)
		return NULL;
	graph->num_vertices = num_vertices;
	graph->directed = directed;
	graph->adj_list = NULL;
	graph->num_edges = 0;

	// Allocate vertices
	graph->vertices = calloc(num_vertices, sizeof(vertex_t));
	if (graph->vertices == NULL) {
		free(graph);
		return NULL;
	}
	for (int i = 0; i < num_vertices; i++) {
		graph->vertices[i] = calloc(1, sizeof(vertex_t));
	}
	graph->adj = malloc(num_vertices * sizeof(node_t *));

	for (int i = 0; i < num_vertices; i++) {
		graph->adj[i] = NULL; // empty neighbor list
	}
	graph->edge_capacity = 1024;
	graph->edges = malloc(graph->edge_capacity * sizeof(edg_t));
	return graph;
}
graph_mst_t *graph_create_mst(uint32_t num_vertices) {
	graph_mst_t *mst = malloc(sizeof(graph_mst_t));
	mst->num_vertices = num_vertices;
	mst->num_edges = 0;
	mst->adj_list = malloc(sizeof(mst_edge_t) * (num_vertices - 1));
	return mst;

	return mst;
};
inline void graph_add_edge_mst(
        graph_mst_t *mst,
        uint32_t from,
        uint32_t to,
        double weight) {
	mst->adj_list[mst->num_edges].from = from;
	mst->adj_list[mst->num_edges].to = to;
	mst->adj_list[mst->num_edges].weight = weight;
	mst->num_edges++;
}

static void adj_list_free(node_t **adj_list, int num_vertices) {
	node_t *tmp;
	for (uint32_t i = 0; i < num_vertices; i++) {
		tmp = adj_list[i];
		node_t *tmp_free;
		while (tmp != NULL) {
			tmp_free = tmp;
			tmp = tmp->next;
			free(tmp_free);
		}
	}
	free(adj_list);
}
void graph_free(graph_t *graph) {
	if (NULL == graph)
		return;
	for (uint32_t i = 0; i < graph->num_vertices; i++) {
		free(graph->vertices[i]);
	}
	free(graph->vertices);
	if (graph->adj_list != NULL) {
		while (*graph->adj_list != NULL) {

			edge_t *tmp = *graph->adj_list;
			*graph->adj_list = (*graph->adj_list)->next;
			free(tmp);
		}
	}

	adj_list_free(graph->adj, graph->num_vertices);
	free(graph->edges);

	free(graph);
	graph = NULL;
}

int graph_add_vertex(graph_t *graph, size_t id, void *data) {
	if (NULL == graph || graph->num_vertices <= id)
		return -1;
	if (NULL == graph->vertices[id]->data) {
		graph->vertices[id]->data = data;
		graph->vertices[id]->id = id;
	}
	graph->adj[id] = malloc(sizeof(node_t));
	graph->adj[id]->id = id;
	graph->adj[id]->weight = 0;
	graph->adj[id]->next = NULL;
	return 0;
}
int graph_add_edge_new(graph_t *graph, vertex_t *from, vertex_t *to, double weight) {
	if (NULL == graph)
		return -1;
	if (graph->num_edges >= graph->edge_capacity) {
		graph->edge_capacity *= 2;
		graph->edges = realloc(graph->edges, graph->edge_capacity * sizeof(edg_t));
	}
	graph->edges[graph->num_edges].from = from->id;
	graph->edges[graph->num_edges].to = to->id;
	graph->edges[graph->num_edges].weight = weight;

	node_t *tmpfrom = graph->adj[from->id];
	node_t *tmpto = graph->adj[to->id];
	while (tmpfrom->next != NULL) {
		tmpfrom = tmpfrom->next;
	}
	while (tmpto->next != NULL) {
		tmpto = tmpto->next;
	}

	tmpfrom->next = malloc(sizeof(node_t));
	tmpfrom = tmpfrom->next;
	tmpfrom->id = to->id;
	tmpfrom->weight = weight;
	tmpfrom->next = NULL;

	tmpto->next = malloc(sizeof(node_t));
	tmpto = tmpto->next;
	tmpto->id = from->id;
	tmpto->weight = weight;
	tmpto->next = NULL;
	graph->num_edges += 1;
	from->degree += 1;
	to->degree += 1;

	return 0;
}

int graph_add_edge(graph_t *graph, vertex_t *from, vertex_t *to, double weight) {
	if (NULL == graph)
		return -1;
	if (NULL == graph->adj_list) {
		graph->adj_list = malloc(sizeof(edge_t *)); //Alocate for double pointer
		if (NULL == graph->adj_list) {
			return -1;
		}
		*graph->adj_list = malloc(sizeof(edge_t));
		if (NULL == *graph->adj_list) {
			free(graph->adj_list);
			return -1;
		}
		(*graph->adj_list)->weight = weight;
		(*graph->adj_list)->from = from;
		(*graph->adj_list)->to = to;
		graph->num_edges += 1;
		(*graph->adj_list)->next = NULL;
	}

	else {
		edge_t *tmp = *graph->adj_list;

		while (NULL != tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = malloc(sizeof(edge_t));
		if (tmp->next == NULL) {
			return -1;
		}
		tmp->next->from = from;
		tmp->next->to = to;
		tmp->next->weight = weight;
		tmp->next->next = NULL;
	}

	node_t *tmpfrom = graph->adj[from->id];
	node_t *tmpto = graph->adj[to->id];
	while (tmpfrom->next != NULL) {
		tmpfrom = tmpfrom->next;
	}
	while (tmpto->next != NULL) {
		tmpto = tmpto->next;
	}

	tmpfrom->next = malloc(sizeof(node_t));
	tmpfrom = tmpfrom->next;
	tmpfrom->id = to->id;
	tmpfrom->weight = weight;
	tmpfrom->next = NULL;

	tmpto->next = malloc(sizeof(node_t));
	tmpto = tmpto->next;
	tmpto->id = from->id;
	tmpto->weight = weight;
	tmpto->next = NULL;
	graph->num_edges += 1;
	from->degree += 1;
	to->degree += 1;
	return 0;
}

graph_mst_t *graph_free_mst(graph_mst_t *g) {
	if (NULL == g)
		return NULL;
	if (g->adj_list != NULL) {
		free(g->adj_list);
	}
	free(g);
	g = NULL;
	return NULL;
}

void graph_random_fill(graph_t *g, uint32_t num_edges, double max_weight) {
	if (g == NULL) return;
	uint32_t edges_added = 0;
	while (edges_added < num_edges) {
		uint32_t from = rand() % g->num_vertices;
		uint32_t to = rand() % g->num_vertices;
		if (from != to) {
			double weight = ((double)rand() / RAND_MAX) * max_weight;
			graph_add_edge_new(g, g->vertices[from], g->vertices[to], weight);
			edges_added++;
		}
	}
}