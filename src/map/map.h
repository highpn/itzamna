#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct cmap_map_t cmap_map_t;

/* Load / unload */
cmap_map_t *map_load(const char *path);
void map_unload(cmap_map_t *map);

/* Counts */
uint32_t map_vertex_count(const cmap_map_t *map);
uint32_t map_face_count(const cmap_map_t *map);
uint32_t map_plane_count(const cmap_map_t *map);
uint32_t map_material_count(const cmap_map_t *map);

/* Raw access (read-only) */
const struct cmap_vertex_t *map_vertices(const cmap_map_t *map);
const struct cmap_face_t *map_faces(const cmap_map_t *map);
const struct cmap_plane_t *map_planes(const cmap_map_t *map);
const struct cmap_material_t *map_materials(const cmap_map_t *map);

/* Face helpers */
const uint32_t *map_face_indices(const cmap_map_t *map,
                                 const struct cmap_face_t *face);

/* Validation */
int map_validate(const cmap_map_t *map);