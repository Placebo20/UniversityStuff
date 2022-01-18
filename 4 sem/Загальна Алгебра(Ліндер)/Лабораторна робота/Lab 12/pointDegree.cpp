#include "pointDegree.h"

Point PointDegree::pointDegree (Point a, unsigned int degree, LongArithmetic::Number numA, LongArithmetic::Number numB, LongArithmetic::Number mod){
	EllipticCurve ellipticCurve(numA, numB, mod);
	vector <int> degrees = expandNum(degree);
	Point resultPoint;
	bool resultPointClear = 1;
	
	for (int i = 0; i < degrees.size(); i++) {
		Point temporaryResultPoint = a;
		int currentTempPointDegree = 1;
		while(currentTempPointDegree < degrees[i]){
			temporaryResultPoint = ellipticCurve.Sum(temporaryResultPoint, temporaryResultPoint);
			currentTempPointDegree *= 2;
		}
		if(resultPointClear){
			resultPoint = temporaryResultPoint;
			resultPointClear = 0;
		}
		else{
			resultPoint = ellipticCurve.Sum(resultPoint, temporaryResultPoint);
		}
	}
	return resultPoint;
}

vector <int> PointDegree::expandNum (unsigned int degree){
	vector <int> degrees;
	while ( degree > 0 ) {
		int n = 1;
		while ( n * 2 <= degree ) {
			n *= 2;
		}
		degrees.push_back(n);
		degree -= n;
	}
	return degrees;
}

vector <LongArithmetic::Number> PointDegree::expandNum (LongArithmetic::Number degree){
	vector <LongArithmetic::Number> degrees;
	while ( degree > LongArithmetic::Number("0") ) {
		LongArithmetic::Number n("1");
		while ( n * LongArithmetic::Number("2") <= degree ) {
			n = n * LongArithmetic::Number("2");
		}
		degrees.push_back(n);
		degree = degree - n;
	}
	return degrees;
}

Point PointDegree::pointDegree (Point a, LongArithmetic::Number degree, LongArithmetic::Number numA, LongArithmetic::Number numB, LongArithmetic::Number mod){
	
	
	EllipticCurve ellipticCurve(numA, numB, mod);
	if(degree<LongArithmetic::Number("0")){
		degree = degree * LongArithmetic::Number("-1");
	}
	a = ellipticCurve.Inverse(a);
			vector <LongArithmetic::Number> degrees = expandNum(degree);
	Point resultPoint;
	bool resultPointClear = 1;
	
	Point temporaryResultPoint = a;
	LongArithmetic::Number currentTempPointDegree = LongArithmetic::Number("1");
	
	for (int i = degrees.size()-1; i >= 0; i--) {
		while(currentTempPointDegree < degrees[i]){
			temporaryResultPoint = ellipticCurve.Sum(temporaryResultPoint, temporaryResultPoint);
			currentTempPointDegree = currentTempPointDegree * LongArithmetic::Number("2") ;
		}
		if(resultPointClear){
			resultPoint = temporaryResultPoint;
			resultPointClear = 0;
		}
		else{
			resultPoint = ellipticCurve.Sum(resultPoint, temporaryResultPoint);
		}
	}
	return resultPoint;
}
