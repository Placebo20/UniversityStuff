#ifndef LABGENERALALGEBRA_POINTDEGREE_H
#define LABGENERALALGEBRA_POINTDEGREE_H
#include "../lab11/EllipticCurve.h"
#include <vector>
using std::vector;

class PointDegree {
public:
	static vector<int> expandNum(unsigned int degree);
	static vector<LongArithmetic::Number> expandNum(LongArithmetic::Number degree);
	static Point pointDegree(Point a, unsigned int degree, LongArithmetic::Number numA, LongArithmetic::Number numB, LongArithmetic::Number mod);
	static Point pointDegree(Point a, LongArithmetic::Number degree, LongArithmetic::Number numA, LongArithmetic::Number numB, LongArithmetic::Number mod);
	
};


#endif //LABGENERALALGEBRA_POINTDEGREE_H
