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
	int cX = pos.x / CHUNK_W;
	int cY = pos.y / CHUNK_H;
	int cZ = pos.z / CHUNK_L;

	if (pos.x < 0) cX--;
	if (pos.y < 0) cY--;
	if (pos.z < 0) cZ--;
	if (cX < 0 || cY < 0 || cZ < 0 || cX >= w || cY >= h || cZ >= l) return nullptr;

	Chunk* chunk = chunks[(cY * l + cZ) * w + cX];
	if (chunk == nullptr) return nullptr;
    
	int vX = pos.x - cX * CHUNK_W;
	int vY = pos.y - cY * CHUNK_H;
	int vZ = pos.z - cZ * CHUNK_L;
	return &chunk->voxels[(vY * CHUNK_L + vZ) * CHUNK_W + vX];
}

Chunk* Chunks::getChunk(const glm::vec3 pos) { 
	int cX = pos.x / CHUNK_W;
	int cY = pos.y / CHUNK_H;
	int cZ = pos.z / CHUNK_L;

	if (pos.x < 0) cX--;
	if (pos.y < 0) cY--;
	if (pos.z < 0) cZ--;
	if (cX < 0 || cY < 0 || cZ < 0 || cX >= w || cY >= h || cZ >= l) return nullptr;

	return chunks[(cY * l + cZ) * w + cX];
}

void Chunks::setVoxel(glm::vec3 pos, int id) {
    getVoxel(pos)->id = id;
}

Voxel* Chunks::rayCast(Chunks* chunks, glm::vec3 pos, glm::vec3 dir, glm::vec3* lastVoxel, glm::vec3* voxelPos, int radius) {
    glm::vec3 startPos(pos.x, pos.y, pos.z);

    glm::vec3 rayPos(startPos);

    glm::vec3 step(dir.x>0 ? 1:-1, dir.y>0 ? 1:-1, dir.z>0 ? 1:-1);
    glm::vec3 cellBoundary((int)rayPos.x + (step.x>0 ? 1:0), (int)rayPos.y + (step.y>0 ? 1:0), (int)rayPos.z + (step.z>0 ? 1:0));

    glm::vec3 tMax((cellBoundary.x - rayPos.x) / dir.x, (cellBoundary.y - rayPos.y) / dir.y, (cellBoundary.z - rayPos.z) / dir.z);
    glm::vec3 tDelta(abs(1/dir.x), abs(1/dir.y), abs(1/dir.z));

    if(lastVoxel != nullptr) *lastVoxel = rayPos;
    float radiusNow = 0.0f;
    while(radiusNow < radius) {
        if(chunks->getVoxel(rayPos) == nullptr) return nullptr;
        if(chunks->getVoxel(rayPos)->id != 0) {
			if(voxelPos != nullptr) *voxelPos = rayPos;
			return getVoxel(rayPos);
		}

        if(lastVoxel != nullptr) *lastVoxel = rayPos;

        if(tMax.x < tMax.y) {
            if(tMax.x < tMax.z) {
                rayPos.x += step.x;
                radiusNow = tMax.x;
                tMax.x += tDelta.x;
            }
            else {
                rayPos.z += step.z;
                radiusNow = tMax.z;
                tMax.z += tDelta.z;
            }
        }
        else {
            if(tMax.y < tMax.z) {
                rayPos.y += step.y;
                radiusNow = tMax.y;
                tMax.y += tDelta.y;
            }
            else {
                rayPos.z += step.z;
                radiusNow = tMax.z;
                tMax.z += tDelta.z;
            }
        }
    }
    
	return nullptr;
}