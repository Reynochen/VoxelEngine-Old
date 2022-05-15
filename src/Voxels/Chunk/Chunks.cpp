#include "Chunks.hpp"
#include "Chunk.hpp"

#include "Voxels/Voxel.hpp"

#include <glm/glm.hpp>
#include <iostream>

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