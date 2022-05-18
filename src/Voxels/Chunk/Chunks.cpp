#include "Chunks.hpp"
#include "Chunk.hpp"

#include "Voxels/Voxel.hpp"

#include <glm/glm.hpp>

Chunks::Chunks(int w, int h, int l) : w(w), h(h), l(l){
    volume = w * h * l;
    chunks = new Chunk*[volume];

    int index = 0;
    for (int y = 0; y < h; y++)
        for (int z = 0; z < l; z++)
            for (int x = 0; x < w; x++, index++) {
	            chunks[index] = new Chunk(x, y, z);
            }
}

Chunks::~Chunks() {
    for (int i = 0; i < volume; i++)
        delete chunks[i];
    
    delete[] chunks;
}

Voxel* Chunks::getVoxel(glm::vec3 pos) {
    pos += glm::vec3(0.5f, 0.5f, 0.5f);
	int cX = pos.x / CHUNK_W;
	int cY = pos.y / CHUNK_H;
	int cZ = pos.z / CHUNK_L;

	if (pos.x < 0) cX--;
	if (pos.y < 0) cY--;
	if (pos.z < 0) cZ--;
	if (cX < 0 || cY < 0 || cZ < 0 || cX >= w || cY >= h || cZ >= l)
		return nullptr;

	Chunk* chunk = chunks[(cY * l + cZ) * w + cX];
	if (chunk == nullptr)
		return nullptr;
    
	int vX = pos.x - cX * CHUNK_W;
	int vY = pos.y - cY * CHUNK_H;
	int vZ = pos.z - cZ * CHUNK_L;
	return &chunk->voxels[(vY * CHUNK_L + vZ) * CHUNK_W + vX];
}

void Chunks::setVoxel(glm::vec3 pos, int id) {
    getVoxel(pos)->id = id;
}