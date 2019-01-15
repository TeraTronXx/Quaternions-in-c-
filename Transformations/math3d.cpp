#include "math3d.h"
#include "math.h"

VECTOR3D Add(VECTOR3D a, VECTOR3D b) //Ya implementado como ejemplo.
{
	VECTOR3D ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}
VECTOR3D Substract(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}
VECTOR3D Scale(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return ret;
}
VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a) {
	VECTOR3D ret;
	ret.x = scalar * a.x;
	ret.y = scalar * a.y;
	ret.z = scalar * a.z;
	return ret;
}
double Magnitude(VECTOR3D a) {
	VECTOR3D ret;
	ret.x = a.x * a.x;
	ret.y = a.y * a.y;
	ret.z = a.z * a.z;
	double resultado = sqrt(ret.x + ret.y + ret.z);
	return resultado;
}

double MagnitudeQuat(QUATERNION a) {
	QUATERNION ret;
	ret.s = a.s * a.s;
	ret.i = a.i * a.i;
	ret.j = a.j * a.j;
	ret.k = a.k * a.k;
	double resultado = sqrt(ret.s + ret.i + ret.j + ret.k);
	return resultado;
}

VECTOR3D Normalize(VECTOR3D a) {
	VECTOR3D ret;
	ret.x=a.x/Magnitude(a);
	ret.y=a.y / Magnitude(a);
	ret.z=a.z / Magnitude(a);
	return ret;
}
VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.y*b.z - a.z*b.y;
	ret.y = -a.x*b.z + a.z*b.x;
	ret.z = a.x*b.y - a.y*b.x;
	return ret;
}
double DotProduct(VECTOR3D a, VECTOR3D b) {
	float dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	float dist2 = sqrt(pow(a.x - b.x, 2) + pow(a.z - b.z, 2));
	return acos(dist2 / dist) * 180 / 3.1415926;
}

double Mult(VECTOR3D a, VECTOR3D b) {
	double ret;
	double x = a.x * b.x;
	double y = a.y * b.y;
	double z = a.z * b.z;

	ret = x + y + z;
	return ret;
}

MATRIX3 Transpose(MATRIX3 m) {
	MATRIX3 ret;
	ret.column0.x = m.column0.x;
	ret.column0.y = m.column1.x;
	ret.column0.z = m.column2.x;
	ret.column1.x = m.column0.y;
	ret.column1.y = m.column1.y;
	ret.column1.z = m.column2.y;
	ret.column2.x = m.column0.z;
	ret.column2.y = m.column1.z;
	ret.column2.z = m.column2.z;
	return ret;
}
VECTOR3D Transform(MATRIX3 m, VECTOR3D a) {
	VECTOR3D ret;
	ret.x=m.column0.x*a.x+m.column0.y*a.y+m.column0.z*a.z;
	ret.y = m.column1.x*a.x + m.column1.y*a.y + m.column1.z*a.z;
	ret.z = m.column2.x*a.x + m.column2.y*a.y + m.column2.z*a.z;
	return ret;
}
MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t)
{
	MATRIX4 sol;
	VECTOR3D tr = MultiplyWithScalar(-1, Transform(A, t));
	MATRIX3 At = Transpose(A);

	sol.m[0] = At.column0.x;
	sol.m[1] = At.column0.y;
	sol.m[2] = At.column0.z;
	sol.m[3] = 0;

	sol.m[4] = At.column1.x;
	sol.m[5] = At.column1.y;
	sol.m[6] = At.column1.z;
	sol.m[7] = 0;

	sol.m[8] = At.column2.x;
	sol.m[9] = At.column2.y;
	sol.m[10] = At.column2.z;
	sol.m[11] = 0;

	sol.m[12] = tr.x;
	sol.m[13] = tr.y;
	sol.m[14] = tr.z;
	sol.m[15] = 1;

	return sol;
}

//practica 2

//ejercicio 1
QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis){

	QUATERNION ret;

	//normalizamos el vector que nos pasan
	axis = Normalize(axis);

	ret.s = cos(angle / 2);
	ret.i = sin(angle / 2) * axis.x;
	ret.j = sin(angle / 2) * axis.y;
	ret.k = sin(angle / 2) * axis.z;

	return ret;
}

QUATERNION QuaternionFromToVectors(VECTOR3D from, VECTOR3D to) {

	double angle = DotProduct(from, to);
	VECTOR3D ambos = CrossProduct(from, to);

	QUATERNION ret = QuaternionFromAngleAxis(angle, ambos);

	return ret;
}

QUATERNION Multiply(QUATERNION a, QUATERNION b) {

	QUATERNION ret;

	VECTOR3D v1;
	VECTOR3D v2;
	double primera;
	VECTOR3D segunda;

	VECTOR3D ba;//vector para s1 * v2
	VECTOR3D bb;//vector para s2 * v1
	VECTOR3D bc;//vector para v1 x v2

	v1.x = a.i;
	v1.y = a.j;
	v1.z = a.k;

	v2.x = b.i;
	v2.y = b.j;
	v2.z = b.k;

	//la primera parte de la ecuación
	primera = ((a.s + b.s) - (Mult(v1,v2)));
	
	//s1 * v2
	ba = MultiplyWithScalar(a.s, v2);

	//s2 * v1
	bb = MultiplyWithScalar(b.s, v1);

	//v1 x v2
	bc = CrossProduct(v1, v2);

	segunda = Add(Add(ba, bb), bc);

	ret.s = primera;
	ret.i = segunda.x;
	ret.j = segunda.y;
	ret.k = segunda.z;

	return ret;
}

QUATERNION Conjugate(QUATERNION a) {

	QUATERNION ret;

	ret.s = a.s;
	ret.i = -a.i;
	ret.j = -a.j;
	ret.k = -a.k;

	return ret;
}

VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q) {

	//1. Asociamos a un punto del espacio P = (x, y, z) el cuaternión p = [0, P]=0+ xi + yj + zk.

	QUATERNION p1;
	p1.s = 0;
	p1.i = a.x;
	p1.j = a.y;
	p1.k = a.z;

	//2. Asociamos al vector de dirección unitario u el cuaternión u = [0, u]=0+ uxi + uyj + uzk.

	VECTOR3D aux;
	aux.x = q.i;
	aux.y = q.j;
	aux.z = q.k;

	VECTOR3D u = Normalize(aux);
	VECTOR3D iUnitario = Scale(u, a); //parte imaginaria del vector unitario

	//ya no se normaliza el vector, se normaliza mas abajo el cuaternion
	//VECTOR3D iUnitario = Scale(aux, a);
	//VECTOR3D u = Normalize(aux);

	//normalizar el rotor-------------------------------------------------------------------------------------------

	QUATERNION unitario;
	unitario.s = 0;
	unitario.i = iUnitario.x;
	unitario.j = iUnitario.y;
	unitario.k = iUnitario.z;

	//3. Definimos el cuaternión de rotación o rotor q = [cos(a/2),sin(a/2)u].

	double angle = 2 * acos(unitario.s);
	//parte real del quaternion q
	QUATERNION qu;
	qu.s = cos(angle / 2);
	
	//parte imaginaria del quaternion q
	VECTOR3D qp2;
	qp2 = MultiplyWithScalar(sin(angle / 2), iUnitario);

	qu.i = qp2.x;
	qu.j = qp2.y;
	qu.k = qp2.z;

	//4. Calculamos el inverso q1 = [cos(a/2), sin(a/2)u].

	QUATERNION qu1;
	QUATERNION conj = Conjugate(qu);
	double moduloqu = MagnitudeQuat(qu);
	qu1.s = conj.s / moduloqu;
	qu1.i = conj.i / moduloqu;
	qu1.j = conj.j / moduloqu;
	qu1.k = conj.k / moduloqu;

	//5. La imagen P0 del punto P viene dada por la multiplicación de cuaterniones.  
	//(Regla del santdwitch)  p' = qpq^-1

	QUATERNION pPrima = Multiply(Multiply(qu, p1), qu1);

	//6. Finalmente, obtenemos el punto P' como las componentes i, j y k del cuaternión p' .

	VECTOR3D ret;
	ret.x = pPrima.i;
	ret.y = pPrima.j;
	ret.z = pPrima.k;

	return ret;
}
