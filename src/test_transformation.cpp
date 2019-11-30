#include <stdlib.h>
#include "utils/transformations.h"
#include <vector>

int main(int argc, char **argv) {
	TTranslate translate(5.0, 2.5, 1.0);
	TTranslate translate2(3.0, 2.5, 0.5);
	TTranslate translate3(1.0, 1.0, 1.0);

	/*
	float coord[4] = {0.0, 0.0, 0.0, 1.0};
	float *res;

	res = translate.Compute(coord);

	for(int i = 0; i < 4; i++)
		printf("%f\n", res[i]);

	//*/

	std::vector<Transformation> trans;
	trans.push_back(translate);
	trans.push_back(translate2);
	trans.push_back(translate3);

	Transformation* resT = Transformation::Concat(trans);

	resT->PrintMtrx();

	return 0;
}
