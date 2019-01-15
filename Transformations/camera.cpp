#include "camera.h"

// TODO
// devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = 3.14159265 / 180;
	fovX = fovX * DEG2RAD;
	double tangent = 0; // tangent of half fovX
	double width = 0; // half width of near plane
	double height = 0; // half height of near plane
	tangent = tanf(fovX / 2.0f);
	height = nearValue * tangent;
	width = height * aspectRatio;
	FRUSTUM ret;
	ret.left = -width;
	ret.right = width;
	ret.top = height;
	ret.bottom = -height;
	ret.nearValue = nearValue;
	ret.farValue = farValue;
	// TODO : rellenar valores de ret
	return ret;
}
MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector){
	MATRIX4 resultado;
	//Hay que normalizar los vectores.
	VECTOR3D forward = Substract(target,eyePosition);//Eje Z
	VECTOR3D side = CrossProduct(forward, upVector);//Eje X
	VECTOR3D up = CrossProduct(side, forward);//Eje Y
	forward = Normalize(forward);
	side = Normalize(side);
	up = Normalize(up);
	MATRIX3 rotacion;
	rotacion.column0.x = side.x;
	rotacion.column1.x = side.y;
	rotacion.column2.x = side.z;

	rotacion.column0.y = up.x;
	rotacion.column1.y = up.y;
	rotacion.column2.y = up.z;

	rotacion.column0.z = -forward.x;
	rotacion.column1.z = -forward.y;
	rotacion.column2.z = -forward.z;

	resultado=InverseOrthogonalMatrix(rotacion, eyePosition);
	
	

	return resultado;
}

//ejercicio 2
void updateEulerOrientation(EULER& euler) {

	VECTOR3D vec;
	vec.x = euler.orientation.i;
	vec.y = euler.orientation.j;
	vec.z = euler.orientation.k;

	//creamos 3 cuaterniones a partir de los angulos yaw pitch y roll junto con el cuaternion de 
	//orientacion del objeto euler
	QUATERNION a = QuaternionFromAngleAxis(euler.yaw, vec);
	QUATERNION b = QuaternionFromAngleAxis(euler.pitch, vec);
	QUATERNION c = QuaternionFromAngleAxis(euler.roll, vec);

	QUATERNION aux;
	//multiplicamos estos cuaterniones para obtener el cuaternion actualizado
	aux = Multiply(a, b);
	aux = Multiply(aux, c);

	euler.orientation = aux;
}

VECTOR3D getForward(EULER euler) {

	updateEulerOrientation(euler);

	VECTOR3D z;
	z.x = 0;
	z.y = 0;
	z.z = -1;

	VECTOR3D ret =  RotateWithQuaternion(z, euler.orientation);

	return ret;
}