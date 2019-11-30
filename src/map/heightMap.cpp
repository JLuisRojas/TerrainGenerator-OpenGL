#include "heightMap.h"

HeightMap::HeightMap(float _frequency, int _depth, int _width, int _height, int _SEED) {
    frequency = _frequency;
    depth = _depth;
	width = _width;
	height = _height;
	SEED = _SEED;

    offsetX = 0;
}

int HeightMap::noise2(int x, int y)
{
    int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];
}

float HeightMap::lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float HeightMap::smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float HeightMap::noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float HeightMap::perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}

void HeightMap::Generate(int scale, int octaves, float persistance, float lacunarity) {
	map = (int*) malloc(sizeof(int)*height*width);
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			*(map + j*width + i) = perlin2d(i, j, frequency, depth) * 255;
		}
	}
}

void HeightMap::Offset() {
    offsetX ++;
	//for(int j = 0; j < height; j++) {
		//for(int i = 0; i < width; i++) {
	for(int j = height-1; j >= 0; j--) {
		for(int i = width-1; i >= 0; i--) {
            /*
            if(i == width - 1) {
                *(map + j*width + i) = perlin2d(i+offsetX, j, frequency, depth) * 255;
            } else {
			    *(map + j*width + i) = *(map + j*width + i+1);
            }
            */
            if(j == 0) {
                *(map + j*width + i) = perlin2d(i, j+offsetX, frequency, depth) * 255;
            } else {
			    *(map + j*width + i) = *(map + (j-1)*width + i);
            }
        }
    }
}

void HeightMap::ExportMap() {
	int i, j, value;
	BMP image(width, height, false);
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			value = *(map + j*width + i);
			image.putpixel(i, j, value);
		}
	}

	image.write("prueba.bmp");
}

// Method that gets the current height at certain point of the map
// Args:
// 		x: x coordinate in the map
// 		z: z coordinate in the map, or y in image
float HeightMap::GetValue(int x, int z) {
	if(x >= 0 && x < width) {
		if(z >= 0 && z < height) {
			int value = *(map + z*width + x);
			return (value / 255.0);
		}
	}
	return 0.0;
}
