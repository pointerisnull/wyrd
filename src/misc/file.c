#include "file.h"
#include "../core/primitives.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int read_legacy_file(char *path) {
    printf("Reading %s\n", path);
    FILE *fp = fopen(path, "rb");
    if(fp == NULL) {
        printf("File not found!\n");
        return 1;
    }
    /* find file size in bytes */
    fseek(fp, 0, SEEK_END);
    size_t length = ftell(fp);
    /* reset file cursor, and store all bytes in buffer */
    fseek(fp, 0, SEEK_SET);

    uint16_t data;
    fread(&data, sizeof(uint16_t), 1, fp);
    int vertex_count = data;
    printf("\nVertices: %d\n", data);

    fread(&data, sizeof(uint16_t), 1, fp);
    int line_count = data;
    printf("Lines: %d\n", data);

    fread(&data, sizeof(uint16_t), 1, fp);
    int sector_count = data;
    printf("Sectors: %d\n", data);

    fread(&data, sizeof(uint16_t), 1, fp);
    int portal_count = data;
    printf("Portals: %d\n", data);

    struct legacy_vertex {
        int16_t x, y;
    };
    struct legacy_vertex *vertices = malloc(sizeof(struct legacy_vertex)*vertex_count);
    fread(vertices, sizeof(struct legacy_vertex), vertex_count, fp);
    for (int i = 0; i < vertex_count; i++) {
        printf("Vertex %d -> x: %d y: %d\n", i, vertices[i].x, vertices[i].y);
    }

    struct legacy_line {
        uint16_t start_vertex;
        uint16_t end_vertex;
        uint16_t sector;
        uint16_t adj_sector;
        uint8_t is_portal;
        uint8_t type;
        uint8_t flags;
    };
    struct legacy_line *lines = malloc(sizeof(struct legacy_line)*line_count);
    fread(lines, sizeof(struct legacy_line), line_count, fp);
    for (int i = 0; i < line_count; i++) {
        printf("Line %d -> Start Vertex %d End Vertex: %d\n", i, lines[i].start_vertex, lines[i].end_vertex);
    }

   
    struct legacy_sector {
        uint16_t start_line;
        uint16_t line_count;
        uint16_t floor;
        uint16_t ceiling;
        uint8_t tags;
        uint8_t normal;
    };
    struct legacy_sector *sectors = malloc(sizeof(struct legacy_sector)*sector_count);
    fread(sectors, sizeof(struct legacy_sector), sector_count, fp);
    for (int i = 0; i < sector_count; i++) {
        printf("Sector %d -> Line count: %d\n", i, sectors[i].line_count);
    }

    free(vertices);
    free(lines);
    free(sectors);
    fclose(fp);

    printf("\nFile loaded into RAM, size: %ld bytes!\n\n", length);
    return 0;
}

#include "../../wyd/default.h"

void write_file(char *path) {
    FILE *fp = fopen(path, "wb");
    if(fp == NULL) {
        printf("could not save!\n");
    }
    for (int i = 0; i < default_cfworld_len; i++) {
        fwrite(&default_cfworld[i], sizeof(unsigned char), 1, fp);
    }
}
/* Legacy file format:
    FILE *fp = fopen(filePath, "wb");
    if(fp == NULL) {
        printf("could not save!\n");
    }

    fwrite(&map->vertexCount, sizeof(uint16_t), 1, fp);
    fwrite(&map->lineCount, sizeof(uint16_t), 1, fp);
    fwrite(&map->sectorCount, sizeof(uint16_t), 1, fp);
    fwrite(&map->portalCount, sizeof(uint16_t), 1, fp);

    if(fwrite(map->vertices, sizeof(Vertex), map->vertexCount, fp) != map->vertexCount) printf("\nERROR WRITING TO FILE!\n");
    fwrite(map->walls, sizeof(Wall), map->lineCount, fp);
    fwrite(map->sectors, sizeof(Sector), map->sectorCount, fp);
*/