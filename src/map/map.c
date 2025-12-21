#include "map_types.h"
#include <stdint.h>
#include <stddef.h>
struct cmap_map_t {
	uint32_t vertex_count;
	uint32_t face_count;
	uint32_t plane_count;
	uint32_t material_count;

	cmap_vertex_t *vertices;
	cmap_face_t *faces;
	cmap_plane_t *planes;
	cmap_material_t *materials;

	uint32_t *face_vertex_indices;

	char *string_table;

	// optionally store file buffer if mmap'ed
	void *file_buffer;
	size_t file_size;
};