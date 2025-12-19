//BFS, DFS, Dijkstra, Kruskal, Prim etc
//
//
#include "../include/graph.h"
#include "../include/heap.h"
#include <stdlib.h>
#include <stdio.h>

static inline int utils_find(int *parent, int x) {
	if (parent[x] != x) {
		return parent[x] = utils_find(parent, parent[x]);
	}
	return parent[x];
}

static inline int utils_union(int *parent, int *rank, int a, int b) {
	if (parent == NULL || rank == NULL)
		return;
	a = utils_find(parent, a);
	b = utils_find(parent, b);
	if (a != b) {
		if (rank[a] < rank[b])
			parent[a] = b;
		else if (rank[a] > rank[b]) {
			parent[b] = a;

		} else {
			parent[b] = a;
			rank[a]++;
		}
	}
	return 1;
}
graph_mst_t *graph_kruskal(graph_t *g) {
	if (g == NULL || g->edges == NULL)
		return NULL;
	graph_mst_t *forest = graph_create_mst(g->num_vertices);
	if (forest == NULL)
		return NULL;
	if (g->num_edges == 0)
		return forest;
	merge_sort_edge(g->edges, g->num_edges);
	int *parent = malloc(g->num_vertices * sizeof(int));
	for (size_t i = 0; i < g->num_vertices; i++)
		parent[i] = i;
	int *rank = calloc(g->num_vertices, sizeof(int));
	for (uint32_t i = 0; i < g->num_edges; i++) {
		if (utils_find(parent, g->edges[i].from) != utils_find(parent, g->edges[i].to)) {
			utils_union(parent, rank, g->edges[i].from, g->edges[i].to);
			graph_add_edge_mst(forest, g->edges[i].from, g->edges[i].to, g->edges[i].weight);
		}
	}
	free(rank);
	free(parent);
	return forest;
}

graph_mst_t *graph_boruvka(graph_t *g) {
	int *parent = malloc(g->num_vertices * sizeof(int));
	for (size_t i = 0; i < g->num_vertices; i++)
		parent[i] = i;
	uint32_t num_components = g->num_vertices;
	edg_t **cheapest = malloc(g->num_vertices * sizeof(edg_t *));
	graph_mst_t *mst = graph_create_mst(g->num_vertices);
	int cu, cv;
	int *rank = calloc(g->num_vertices, sizeof(int));
	while (num_components > 1) {
		for (int i = 0; i < g->num_vertices; i++) {
			cheapest[i] = NULL;
		}
		for (int i = 0; i < g->num_edges; i++) {
			cu = utils_find(parent, g->edges[i].from);
			cv = utils_find(parent, g->edges[i].to);
			if (cu != cv) {
				if (cheapest[cu] == NULL || cheapest[cu]->weight > g->edges[i].weight) {
					cheapest[cu] = &g->edges[i];
				}
				if (cheapest[cv] == NULL || cheapest[cv]->weight > g->edges[i].weight) {
					cheapest[cv] = &g->edges[i];
				}
			}
		}
		for (int i = 0; i < g->num_vertices; i++) {
			if (parent[i] == i && cheapest[i] != NULL) {
				edg_t *edge = cheapest[i];
				cu = utils_find(parent, edge->from);
				cv = utils_find(parent, edge->to);
				if (cu != cv) {
					if (utils_union(parent, rank, cu, cv)) {
						graph_add_edge_mst(mst, edge->from, edge->to, edge->weight);
						num_components--;
					}
				}
			}
		}
	}

	free(cheapest);
	free(parent);
	free(rank);
	return mst;
}
int graph_count_vertices(node_t **adj_list, uint32_t size) {
	uint32_t count = 0;
	for (uint32_t i = 0; i < size; i++) {
		if (adj_list[i] != NULL)
			count++;
	}
	return count;
}

node_t **
graph_copy_adj_list(node_t **adj_list, uint32_t num_vertices) {
	node_t **adj_list_copy = malloc(num_vertices * sizeof(node_t *));
	node_t *tmp;
	node_t *tmp_set;
	for (uint32_t i = 0; i < num_vertices; i++) {
		tmp = adj_list[i];

		adj_list_copy[i] = malloc(sizeof(node_t));
		tmp_set = adj_list_copy[i];
		tmp_set->next = NULL;
		tmp_set->id = tmp->id;
		tmp_set->weight = tmp->weight;
		tmp = tmp->next;
		while (tmp != NULL) {

			tmp_set->next = malloc(sizeof(node_t));
			tmp_set = tmp_set->next;
			tmp_set->id = tmp->id;
			tmp_set->weight = tmp->weight;
			tmp_set->next = NULL;
			tmp = tmp->next;
		}
	}
	for (uint32_t i = 0; i < num_vertices; i++) {
		node_t *tmp = adj_list_copy[i];
		while (tmp != NULL) {
			printf("{%d}, %lf ", tmp->id, tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
	return adj_list_copy;
}

//void graph_bfs(graph_t *g, int start_id, void (*visit)(int vertex_id))
/*
void graph_dfs(graph_t *g, int start_id, void (*visit)(int vertex_id)) {
	graph_t tmp = *g->adj_list;
	unsigned int memory[g->num_vertices];
	while (tmp != NULL) {

		tmp = tmp->next;
	}
}*/
//Union-find algorithm for Kruskal with path compression
//Find with path compression
//Union by rank
//Find the root of the set containing x

int graph_has_vertex(graph_t *g, uint32_t index) {
	return g->adj[index] != NULL;
}
static inline int in_visited(uint32_t *visited, uint32_t index) {
	return visited[index] == 1;
}
static inline void mark_visited(uint32_t *visited, uint32_t index) {
	visited[index] = 1;
}
graph_mst_t *graph_prim(graph_t *g) {
	if (g == NULL)
		return NULL;
	uint32_t *visited = calloc(g->num_vertices, sizeof(uint32_t));

	uint32_t *parent = calloc(g->num_vertices, sizeof(uint32_t));
	double *key = calloc(g->num_vertices, sizeof(double));
	for (uint32_t i = 0; i < g->num_vertices; i++) {
		key[i] = __DBL_MAX__;
		parent[i] = 0;
	}
	uint32_t u;
	key[0] = 0;
	uint32_t visited_count = 0;
	heap_t *heap = heap_create(g->num_vertices);
	heap_push(heap, 0, 0.0);
	while (visited_count < g->num_vertices) {
		double min = __DBL_MAX__;
		if (heap_empty(heap))
			break;
		u = heap_pop(heap, &min);

		if (in_visited(visited, u))
			continue;
		mark_visited(visited, u);
		visited_count++;
		node_t *head = g->adj[u] ? g->adj[u]->next : NULL;

		while (head != NULL) {
			if (!in_visited(visited, head->id) && (head->weight < key[head->id])) {
				//printf(" id :%d , weight %d ", head->id, head->weight);

				key[head->id] = head->weight;
				parent[head->id] = u;
				heap_push(heap, head->id, key[head->id]);
			}
			head = head->next;
		}
	}
	free(visited);
	heap_free(heap);
	if (visited_count != g->num_vertices) {
		fprintf(stderr, "Warning: Graph is disconnected; MST will be incomplete.\n");
	}
	graph_mst_t *mst_set = graph_create_mst(g->num_vertices);
	for (uint32_t i = 0; i < g->num_vertices; i++) {
		if (i == 0) continue; //skip root
		graph_add_edge_mst(mst_set, i, parent[i], key[i]);
	}
	free(parent);
	free(key);
	return mst_set;
}

int partition(edg_t *array, int low, int high) {
	double pivot = array[high].weight;
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (array[j].weight <= pivot) {
			i += 1;
			edg_t tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}

	edg_t tmp = array[i + 1];
	array[i + 1] = array[high];
	array[high] = tmp;
	return i + 1;
}

int swap_edge(edge_t **head, int a, int b) {
	if (!head || !*head)
		return -1;
	if (a == b)
		return 0;

	// Ensure a < b
	if (a > b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	edge_t *prevA = NULL, *nodeA = *head;
	edge_t *prevB = NULL, *nodeB = *head;

	// Find nodeA
	for (int i = 0; i < a && nodeA; i++) {
		prevA = nodeA;
		nodeA = nodeA->next;
	}

	// Find nodeB
	for (int i = 0; i < b && nodeB; i++) {
		prevB = nodeB;
		nodeB = nodeB->next;
	}

	// If either index is out of bounds
	if (!nodeA || !nodeB)
		return -1;

	// If A has a previous node, link it to B
	if (prevA)
		prevA->next = nodeB;
	else
		*head = nodeB;

	// Same for B
	if (prevB)
		prevB->next = nodeA;
	else
		*head = nodeA;

	// Swap next pointers
	edge_t *tmp = nodeA->next;
	nodeA->next = nodeB->next;
	nodeB->next = tmp;

	return 0;
}

void graph_edge_print(graph_t *g) {
	edge_t *el = *g->adj_list;
	while (el != NULL) {
		printf("%lf from: %d to:%d \n", el->weight, el->from->id, el->to->id);
		el = el->next;
	}
}

int graph_edge_set(edge_t *edge, int index, double value) {
	for (int i = 0; i < index && edge->next != NULL; i++) {
		edge = edge->next;
	}
	edge->weight = value;
	return 0;
}
double graph_edge_get(edge_t *edge, int index) {
	for (int i = 0; i < index && edge->next != NULL; i++) {
		edge = edge->next;
	}
	return edge->weight;
}

/// Split a list into two halves
static void split_list(edg_t *source, edg_t **front, edg_t **back) {
}

static void merge(edg_t arr[], edg_t tmp[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {
		if (arr[i].weight <= arr[j].weight)
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}

	while (i <= mid)
		tmp[k++] = arr[i++];

	while (j <= right)
		tmp[k++] = arr[j++];

	for (i = left; i <= right; i++)
		arr[i] = tmp[i];
}

static void mergesort_rec(edg_t arr[], edg_t tmp[], int left, int right) {
	if (left >= right)
		return;

	int mid = (left + right) / 2;

	mergesort_rec(arr, tmp, left, mid);
	mergesort_rec(arr, tmp, mid + 1, right);
	merge(arr, tmp, left, mid, right);
}

void merge_sort_edge(edg_t *arr, uint32_t n) {
	edg_t *tmp = malloc(sizeof(edg_t) * n);
	if (!tmp) return; // handle alloc failure gracefully
	mergesort_rec(arr, tmp, 0, n - 1);
	free(tmp);
}