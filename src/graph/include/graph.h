#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#define WIDTH 100
#define HEIGHT 50
#define MAX_VERTICES 100
//data structures
typedef enum {
	DIR_OUT = 1,
	DIR_IN = -1,
	DIR_UNDIRECTED = 0
} edge_dir_t;

typedef struct
{
	uint32_t id;
	uint32_t degree;
	void *data; /* data */ //it is freed in graph free
} vertex_t;

typedef struct edge_t {
	vertex_t *from;
	vertex_t *to;

	double weight;
	struct edge_t *next;

} edge_t;
typedef struct edg_t {
	uint32_t from;
	uint32_t to;

	double weight;

} edg_t;

typedef struct node_t {
	uint32_t id;
	double weight;
	edge_dir_t direction;
	struct node_t *next;
} node_t;

typedef struct graph_t { // graph
	uint32_t num_vertices;
	uint32_t num_edges;
	uint32_t edge_capacity;
	int directed;
	vertex_t **vertices;
	node_t **adj; //vertex list primary structure Prim, BFS / DFS, Dijkstra, Connectivity, Topological sort
	edge_t **adj_list; //edge list, Kruskal (needs sorted list of edges), Easy file I/O (just write each edge), Debugging, Some flow algorithms
	edg_t *edges;
} graph_t;
typedef struct mst_edge {
	uint32_t from, to;
	double weight;
} mst_edge_t;

typedef struct graph_mst_t { //graph for minimum spanning trees returned by mst algorithms
	uint32_t num_vertices;
	uint32_t num_edges;
	mst_edge_t *adj_list; //edge list, Kruskal (needs sorted list of edges), Easy file I/O (just write each edge), Debugging, Some flow algorithms
} graph_mst_t;

// Graph management
graph_t *graph_create(uint32_t num_vertices, int directed);
int graph_has_vertex(graph_t *g, uint32_t index);
void graph_free(graph_t *g);
int graph_add_vertex(graph_t *g, size_t id, void *data);
int graph_add_edge(graph_t *g, vertex_t *from, vertex_t *to, double weight);
int graph_count_vertices(node_t **, uint32_t);
void graph_random_fill(graph_t *g, uint32_t num_edges, double max_weight);
// Traversal
void graph_bfs(graph_t *g, int start_id, void (*visit)(int vertex_id));
void graph_dfs(graph_t *g, int start_id, void (*visit)(int vertex_id));
// Shortest paths
double *graph_dijkstra(graph_t *g, int start_id);
double **graph_floyd_warshall(graph_t *g);
// MST
graph_mst_t *graph_kruskal(graph_t *g);
graph_mst_t *graph_prim(graph_t *g);
graph_mst_t *graph_boruvka(graph_t *g);
graph_mst_t *graph_create_mst(uint32_t num_vertices);
void graph_add_edge_mst(graph_mst_t *, uint32_t from, uint32_t to, double weight);

graph_mst_t *graph_free_mst(graph_mst_t *g);
// Utilities
int graph_is_complete(graph_t *graph);
int graph_degree(graph_t *g, int vertex_id);
int graph_connected_components(graph_t *g);
int graph_has_cycle(graph_t *g);
int graph_is_simple(graph_t *graph);
vertex_t *graph_get_vertex(graph_t *g, size_t id);

void merge_sort_edge(edg_t *, uint32_t);

// Visualization
void draw_line(char grid[HEIGHT][WIDTH], uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void visualize_graph(edge_t *edges);
double visualize_graph_weights(graph_mst_t *);
void graph_vertex_list_print(graph_t *g);
node_t **graph_copy_adj_list(node_t **adj_list, uint32_t num_vertices);
void vertex_list_print(node_t **n, int num_vertices);
void graph_edge_print(graph_t *g);
void utils_graph_add_grid(graph_t *g, uint32_t rows, uint32_t cols);
void utils_mst_print_as_grid(graph_mst_t *mst, uint32_t rows, uint32_t cols);
int graph_add_edge_new(graph_t *graph, vertex_t *from, vertex_t *to, double weight);
