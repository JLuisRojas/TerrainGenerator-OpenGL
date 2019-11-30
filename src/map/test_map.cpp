#include <stdio.h>
#include "heightMap.h"

int main(int argc, char **argv) {
	HeightMap map = HeightMap(100, 100, 100);

	map.Generate(1, 4, 0.5, 2.0);
	map.ExportMap();

	return 0;
}
