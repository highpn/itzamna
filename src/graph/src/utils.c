#include "../include/graph.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// Map vertices to a simple struct with coordinates
typedef struct {
	vertex_t *v;
	uint32_t x, y;
} vertex_pos_t;

void draw_line(char grid[HEIGHT][WIDTH], uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void visualize_graph(edge_t *edges);
int graph_is_complete(graph_t *graph) {
	if (NULL == graph)
		return -1;
	if (graph->num_vertices == 0) //a graph with 0 vertices is a complete graph k0 null graph
		return 1;

	if (!graph_is_simple(graph))
		return 0;
	for (size_t i = 0; i < graph->num_vertices; i++) {
		if (graph->vertices[i]->degree != (int)graph->num_vertices - 1)
			return 0;
	}

	return 1;
}
vertex_t *graph_get_vertex(graph_t *g, size_t id) {
	if (g == NULL)
		return NULL;
	if (g->num_vertices <= id)
		return NULL;
	return g->vertices[id];
}
int graph_is_simple(graph_t *graph) {
	if (NULL == graph)
		return -1;
	if (graph->num_vertices == 0) //a graph with 0 vertices is a simple graph
		return 1;
	int count_paralell_edges[graph->num_vertices][graph->num_vertices];
	memset(count_paralell_edges, 0, sizeof(count_paralell_edges));
	edge_t *e = *graph->adj_list;
	while (e) {
		int u = e->from->id;
		int v = e->to->id;
		if (e->from == e->to) return 0; // loop found
		if (++count_paralell_edges[u][v] > 1) return 0; // parallel edge found
		if (++count_paralell_edges[v][u] > 1) return 0; // undirected
		e = e->next;
	}
	return 1; // no parallel edges  no loops
}

/*
edge_t *list_sort(edge_t *e, int num) {
	if (num <= 1) {
		return e;
	}
	edge_t *left = NULL;
	edge_t *right = NULL;
	size_t list_size;
	for (edge_t *tmp = e; int i = 0; tmp != NULL; tmp = tmp->next; i++) {
		if (i < num / 2)
			right->
	}
	//add quick sort later if num small mbe use function pointer
	list_sort(left, num / 2);
	list_sort(right, num - num / 2);
	return merge(left, right)
}

edge_t *merge(edge_t *left, edge_t *right) {
	edge_t *result = NULL;
	while (left != NULL && right != NULL) {
		if (left->weight <= right->weight) {
			result
		}
	}
}

int list_edge_add(edge_t **edge, edge_t other_edge) {
	if (NULL == edge) {
		edge = malloc(sizeof(edge_t *)); //Alocate for double pointer
		if (NULL == graph->adj_list) {
			return -1;
		}
		*graph->adj_list = malloc(sizeof(edge_t));
		if (NULL == *graph->adj_list) {
			free(graph->adj_list);
			return -1;
		}
		(*graph->adj_list)->weight = weight;
		(*graph->adj_list)->from.id = from;
		(*graph->adj_list)->to.id = to;

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
		tmp->next->from.id = from;
		tmp->next->to.id = to;
		tmp->next->weight = weight;
		tmp->next->next = NULL;
	}
	graph->vertices[from].degree += 1;
	graph->vertices[to].degree += 1;
	return 0;
}
    */

// Draw line with basic characters for clarity
void draw_line(char grid[HEIGHT][WIDTH], uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1) {
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT && grid[y0][x0] == ' ') {
			if (x0 == x1 || y0 == y1)
				grid[y0][x0] = '-'; // horizontal or vertical
			else if ((x1 - x0) * (y1 - y0) > 0)
				grid[y0][x0] = '/';
			else
				grid[y0][x0] = '\\'; // diagonal
		}
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) {
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void visualize_graph(edge_t *edges) {
	char grid[HEIGHT][WIDTH];
	memset(grid, ' ', sizeof(grid));

	// Collect unique vertices
	vertex_t *vertices[MAX_VERTICES];
	int vcount = 0;
	edge_t *e = edges;
	while (e) {
		int found_from = 0, found_to = 0;
		for (int i = 0; i < vcount; i++) {
			if (vertices[i] == e->from) found_from = 1;
			if (vertices[i] == e->to) found_to = 1;
		}
		if (!found_from && vcount < MAX_VERTICES) vertices[vcount++] = e->from;
		if (!found_to && vcount < MAX_VERTICES) vertices[vcount++] = e->to;
		e = e->next;
	}

	// Assign positions in a circle with bigger radius
	int cx = WIDTH / 2, cy = HEIGHT / 2;
	int r = (HEIGHT < WIDTH ? HEIGHT : WIDTH) / 3; // bigger radius for more space
	int pos_x[MAX_VERTICES], pos_y[MAX_VERTICES];
	for (int i = 0; i < vcount; i++) {
		double angle = 2 * M_PI * i / vcount - M_PI / 2;
		pos_x[i] = cx + (int)(r * cos(angle));
		pos_y[i] = cy + (int)(r * sin(angle));
		if (pos_x[i] < 0) pos_x[i] = 0;
		if (pos_x[i] >= WIDTH) pos_x[i] = WIDTH - 1;
		if (pos_y[i] < 0) pos_y[i] = 0;
		if (pos_y[i] >= HEIGHT) pos_y[i] = HEIGHT - 1;
	}

	// Draw edges
	e = edges;
	while (e) {
		int from_idx = -1, to_idx = -1;
		for (int i = 0; i < vcount; i++) {
			if (vertices[i] == e->from) from_idx = i;
			if (vertices[i] == e->to) to_idx = i;
		}
		if (from_idx != -1 && to_idx != -1) {
			draw_line(grid, pos_x[from_idx], pos_y[from_idx], pos_x[to_idx], pos_y[to_idx]);
		}
		e = e->next;
	}

	// Draw nodes
	for (int i = 0; i < vcount; i++) {
		int x = pos_x[i], y = pos_y[i];
		grid[y][x] = 'O';
		char label[6];
		snprintf(label, sizeof(label), "%u", vertices[i]->id);
		int lx = x + 1;
		for (int j = 0; j < (int)strlen(label) && lx + j < WIDTH; j++)
			grid[y][lx + j] = label[j];
	}

	// Print grid
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++)
			putchar(grid[y][x]);
		putchar('\n');
	}
}

double visualize_graph_weights(graph_mst_t *mst) {
	char grid[HEIGHT][WIDTH];
	memset(grid, ' ', sizeof(grid));

	// Collect unique vertices
	uint32_t vertices[MAX_VERTICES];
	int vcount = 0;
	mst_edge_t *e = mst->adj_list;

	for (uint32_t index = 0; index < mst->num_edges; index++) {
		int found_from = 0, found_to = 0;
		for (int i = 0; i < vcount; i++) {
			if (vertices[i] == e[index].from) found_from = 1;
			if (vertices[i] == e[index].to) found_to = 1;
		}
		if (!found_from && vcount < MAX_VERTICES) vertices[vcount++] = e[index].from;
		if (!found_to && vcount < MAX_VERTICES) vertices[vcount++] = e[index].to;
	}

	// Assign positions on circle
	int cx = WIDTH / 2, cy = HEIGHT / 2;
	int r = (HEIGHT < WIDTH ? HEIGHT : WIDTH) / 3;

	int pos_x[MAX_VERTICES], pos_y[MAX_VERTICES];

	for (int i = 0; i < vcount; i++) {
		double angle = 2 * M_PI * i / vcount - M_PI / 2;
		pos_x[i] = cx + (int)(r * cos(angle));
		pos_y[i] = cy + (int)(r * sin(angle));

		if (pos_x[i] < 0) pos_x[i] = 0;
		if (pos_x[i] >= WIDTH) pos_x[i] = WIDTH - 1;
		if (pos_y[i] < 0) pos_y[i] = 0;
		if (pos_y[i] >= HEIGHT) pos_y[i] = HEIGHT - 1;
	}

	// Draw edges + weight labels

	for (uint32_t index = 0; index < mst->num_edges; index++) {
		int from_idx = -1, to_idx = -1;

		for (int i = 0; i < vcount; i++) {
			if (vertices[i] == e[index].from) from_idx = i;
			if (vertices[i] == e[index].to) to_idx = i;
		}

		if (from_idx != -1 && to_idx != -1) {
			int x1 = pos_x[from_idx], y1 = pos_y[from_idx];
			int x2 = pos_x[to_idx], y2 = pos_y[to_idx];

			// Draw the edge
			draw_line(grid, x1, y1, x2, y2);

			// NEW: Compute mid-point for weight label
			int mx = (x1 + x2) / 2;
			int my = (y1 + y2) / 2;

			// Shift label slightly so it doesn't overwrite the line
			if (mx + 1 < WIDTH) mx += 1;
			if (my + 1 < HEIGHT) my += 1;

			// NEW: Render weight text
			char wbuf[16];
			snprintf(wbuf, sizeof(wbuf), "%.1f", e[index].weight);

			for (int k = 0; k < (int)strlen(wbuf); k++) {
				if (mx + k < WIDTH)
					grid[my][mx + k] = wbuf[k];
			}
		}
	}

	// Draw nodes
	for (int i = 0; i < vcount; i++) {
		int x = pos_x[i], y = pos_y[i];
		grid[y][x] = 'O';

		char label[6];
		snprintf(label, sizeof(label), "%u", vertices[i]);

		int lx = x + 1;
		for (int j = 0; j < (int)strlen(label) && lx + j < WIDTH; j++)
			grid[y][lx + j] = label[j];
	}

	// Output
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++)
			putchar(grid[y][x]);
		putchar('\n');
	}
	// 6. Print edge list and total weight
	printf("\nMST edges:\n");

	double sum = 0;
	for (uint32_t index = 0; index < mst->num_edges; index++) {

		printf("%d -- %d (%.1f)\n", e[index].from, e[index].to, e[index].weight);
		sum += e[index].weight;
	}
	printf("MST total weight: %.1f\n", sum);
	return sum;
}

void graph_vertex_list_print(graph_t *g) {
	for (uint32_t i = 0; i < g->num_vertices; i++) {
		node_t *tmp = g->adj[i];
		while (tmp != NULL) {
			printf("{%d}, %lf ", tmp->id, tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
}
void vertex_list_print(node_t **n, int num_vertices) {
	for (uint32_t i = 0; i < num_vertices; i++) {
		node_t *tmp = n[i];
		while (tmp != NULL) {
			printf("{%d}, %lf ", tmp->id, tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

void utils_graph_add_grid(graph_t *g, uint32_t rows, uint32_t cols) {
	if (!g) return;

	for (uint32_t r = 0; r < rows; r++) {
		for (uint32_t c = 0; c < cols; c++) {
			uint32_t id = r * cols + c;

			// connect to right neighbor
			if (c + 1 < cols) {
				graph_add_edge_new(
				        g,
				        g->vertices[id],
				        g->vertices[id + 1],
				        rand() % 100 / 100.0);
			}

			// connect to down neighbor
			if (r + 1 < rows) {
				graph_add_edge_new(
				        g,
				        g->vertices[id],
				        g->vertices[id + cols],
				        rand() % 100 / 100.0);
			}
		}
	}
}
void utils_graph_print_grid(graph_t *g, uint32_t rows, uint32_t cols) {
	if (!g) return;
	for (uint32_t r = 0; r < g->edges; r++) {
		printf("%d -- %d (%.1f)\n", g->edges[r].from, g->edges[r].to, g->edges[r].weight);

		printf("\n");
	}
}
// Print MST as ASCII grid (works with single NULL-terminated list)
void utils_mst_print_as_grid(graph_mst_t *mst, uint32_t rows, uint32_t cols) {
	if (!mst || !mst->adj_list || rows * cols != mst->num_vertices) {
		fprintf(stderr, "Grid size mismatch or empty MST!\n");
		return;
	}

	uint32_t H = rows * 2 - 1;
	uint32_t W = cols * 2 - 1;

	// Allocate ASCII grid
	char **grid = malloc(H * sizeof(char *));
	for (uint32_t r = 0; r < H; r++) {
		grid[r] = malloc(W * sizeof(char));
		memset(grid[r], ' ', W * sizeof(char));
	}

	// Place nodes
	for (uint32_t r = 0; r < rows; r++)
		for (uint32_t c = 0; c < cols; c++)
			grid[r * 2][c * 2] = "+"[0];

	// Iterate over all edges in the NULL-terminated list
	mst_edge_t *e = (mst->adj_list);
	for (uint32_t index = 0; index < mst->num_edges; index++) {
		uint32_t u = e[index].from;
		uint32_t v = e[index].to;

		if (u >= mst->num_vertices || v >= mst->num_vertices) {
			index++;
			continue;
		}

		uint32_t ur = u / cols, uc = u % cols;
		uint32_t vr = v / cols, vc = v % cols;

		if (ur == vr) {
			// Horizontal edge
			uint32_t minc = (uc < vc) ? uc : vc;
			grid[ur * 2][minc * 2 + 1] = "-"[0];
		} else if (uc == vc) {
			// Vertical edge
			uint32_t minr = (ur < vr) ? ur : vr;
			grid[minr * 2 + 1][uc * 2] = "I"[0];
		}
	}

	// Print grid
	for (uint32_t r = 0; r < H; r++) {
		for (uint32_t c = 0; c < W; c++)
			putchar(grid[r][c]);
		putchar('\n');
	}

	// Free
	for (uint32_t r = 0; r < H; r++) free(grid[r]);
	free(grid);
}