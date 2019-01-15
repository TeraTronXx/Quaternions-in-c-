
#include "GLInclude.h"
#include "shapes.h"

void drawDot(VECTOR3D position, float sradius, COLOUR color)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);


	VECTOR3D p[4], n[4];
	int STEP = 30;
	for (int i = 0; i<360; i += STEP) {
		for (int j = -90; j<90; j += STEP) {

			p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
			p[0].y = sradius * sin(j*DTOR);
			p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
			n[0] = p[0];

			p[1].x = sradius * cos((j + STEP)*DTOR) * cos(i*DTOR);
			p[1].y = sradius * sin((j + STEP)*DTOR);
			p[1].z = sradius * cos((j + STEP)*DTOR) * sin(i*DTOR);
			n[1] = p[1];

			p[2].x = sradius * cos((j + STEP)*DTOR) * cos((i + STEP)*DTOR);
			p[2].y = sradius * sin((j + STEP)*DTOR);
			p[2].z = sradius * cos((j + STEP)*DTOR) * sin((i + STEP)*DTOR);
			n[2] = p[2];

			p[3].x = sradius * cos(j*DTOR) * cos((i + STEP)*DTOR);
			p[3].y = sradius * sin(j*DTOR);
			p[3].z = sradius * cos(j*DTOR) * sin((i + STEP)*DTOR);
			n[3] = p[3];

			glBegin(GL_POLYGON);
			if (i % (STEP * 4) == 0)
				glColor3f(color.r, color.g, color.b);
			else
				glColor3f(color.r*0.5, color.g*0.5, color.b*0.5);
			for (int k = 0; k<4; k++) {
				glNormal3f(n[k].x, n[k].y, n[k].z);
				glVertex3f(p[k].x, p[k].y, p[k].z);
			}
			glEnd();
		}
	}

	glPopMatrix();
}
void drawLine(LINE line, COLOUR color , bool doDrawDots) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_STRIP);
	//Por cada vector en linea(que contiene vectores) se van calculando los puntos
	for each(VECTOR3D vector in line.P) {
		glVertex3f(vector.x,vector.y,vector.z);
	}
	glEnd();
	

}
void drawAxis() {
	//Si necesito punto de inicio y PUNTO FINAL ME FALTA LA MITAD DE ANYADIR
	LINE ejex;
	LINE ejey;
	LINE ejez;
	VECTOR3D vectorX;
	VECTOR3D vectorInicial;

	vectorInicial.x = 0.0;
	vectorInicial.y = 0.0;
	vectorInicial.z = 0.0;
	vectorX.x = 10.0;
	vectorX.y = 0.0;
	vectorX.z = 0.0;
	ejex.P.push_back(vectorInicial);
	ejex.P.push_back(vectorX);
	COLOUR color1 = red;
	VECTOR3D vectorY;
	vectorY.x = 0.0;
	vectorY.y = 10.0;
	vectorY.z = 0.0;
	ejey.P.push_back(vectorInicial);
	ejey.P.push_back(vectorY);
	COLOUR color2 = green;
	VECTOR3D vectorZ;
	vectorZ.x = 0.0;
	vectorZ.y = 0.0;
	vectorZ.z = 10.0;
	COLOUR color3 = blue;
	ejez.P.push_back(vectorInicial);
	ejez.P.push_back(vectorZ);
	bool doDrawDots = false;
	drawLine(ejex, color1, doDrawDots);
	drawLine(ejey, color2, doDrawDots);
	drawLine(ejez,color3, doDrawDots);

}