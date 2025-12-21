#pragma once
#include <stdint.h>

typedef struct cmap_vertex_t {
	float x, y, z;
} cmap_vertex_t;

typedef struct cmap_plane_t {
	float normal[3];
	float dist;
} cmap_plane_t;

typedef struct cmap_face_t {
	uint32_t first_vertex;
	uint16_t vertex_count;
	uint16_t material_id;
	uint32_t plane_id;
	uint32_t flags;
} cmap_face_t;

typedef struct cmap_material_t {
	uint32_t name_offset;
	uint32_t flags;
	float roughness;
	float metallic;
	uint32_t albedo_tex;
	uint32_t normal_tex;
} cmap_material_t;