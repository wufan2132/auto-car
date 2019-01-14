#include "Elipsoid.h"

float A,B,C,D,E,F;
Vector newv;
u8 start = 0;
void Elipsoid_::Input(Vector NewValue)
{
	float Tmp[7];
	if(start == 0) 
	{
	Tmp[0] = NewValue.x * NewValue.x;
	Tmp[1] = NewValue.y * NewValue.y;
	Tmp[2] = NewValue.z * NewValue.z;
	Tmp[3] = NewValue.x;
	Tmp[4] = NewValue.y;
	Tmp[5] = NewValue.z;
	Tmp[6] = 1.0f;
	
	for(u8 i = 0;i < 7;i++)
	{
		for(u8 j = 0;j < 7;j++)
		{
			Matrix[j][i] += Tmp[i] * Tmp[j];
		}
	}
	
}
	newv.x = A * NewValue.x + D;
	newv.y = 1.22f * NewValue.y - 520.0f;
	newv.z = C * NewValue.z + F;

	User_Data.Data1 = newv.y;
}

// Matrix[0][0] * a + Matrix[0][1] * b + Matrix[0][2] * c + Matrix[0][3] * d + Matrix[0][4] * e + Matrix[0][5] * f + Matrix[0][6] * g = 0;
// Matrix[1][0] * a + Matrix[1][1] * b + Matrix[1][2] * c + Matrix[1][3] * d + Matrix[1][4] * e + Matrix[1][5] * f + Matrix[1][6] * g = 0;
// Matrix[2][0] * a + Matrix[2][1] * b + Matrix[2][2] * c + Matrix[2][3] * d + Matrix[2][4] * e + Matrix[2][5] * f + Matrix[2][6] * g = 0;
// Matrix[3][0] * a + Matrix[3][1] * b + Matrix[3][2] * c + Matrix[3][3] * d + Matrix[3][4] * e + Matrix[3][5] * f + Matrix[3][6] * g = 0;
// Matrix[4][0] * a + Matrix[4][1] * b + Matrix[4][2] * c + Matrix[4][3] * d + Matrix[4][4] * e + Matrix[4][5] * f + Matrix[4][6] * g = 0;
// Matrix[5][0] * a + Matrix[5][1] * b + Matrix[5][2] * c + Matrix[5][3] * d + Matrix[5][4] * e + Matrix[5][5] * f + Matrix[5][6] * g = 0;
// Matrix[6][0] * a + Matrix[6][1] * b + Matrix[6][2] * c + Matrix[6][3] * d + Matrix[6][4] * e + Matrix[6][5] * f + Matrix[6][6] * g = 0;

// a = -(Matrix[1][0] * b + Matrix[2][0] * c + Matrix[3][0] * d + Matrix[4][0] * e + Matrix[5][0] * f + Matrix[6][0] * g) / Matrix[0][0];
// b = -(Matrix[0][1] * a + Matrix[2][1] * c + Matrix[3][1] * d + Matrix[4][1] * e + Matrix[5][1] * f + Matrix[6][1] * g) / Matrix[1][1];
// c = -(Matrix[0][2] * a + Matrix[1][2] * b + Matrix[3][2] * d + Matrix[4][2] * e + Matrix[5][2] * f + Matrix[6][2] * g) / Matrix[2][2];
// d = -(Matrix[0][3] * a + Matrix[1][3] * b + Matrix[2][3] * c + Matrix[4][3] * e + Matrix[5][3] * f + Matrix[6][3] * g) / Matrix[3][3];
// e = -(Matrix[0][4] * a + Matrix[1][4] * b + Matrix[2][4] * c + Matrix[3][4] * d + Matrix[5][4] * f + Matrix[6][4] * g) / Matrix[4][4];
// f = -(Matrix[0][5] * a + Matrix[1][5] * b + Matrix[2][5] * c + Matrix[3][5] * d + Matrix[4][5] * e + Matrix[6][5] * g) / Matrix[5][5];
// g = -(Matrix[0][6] * a + Matrix[1][6] * b + Matrix[2][6] * c + Matrix[3][6] * d + Matrix[4][6] * e + Matrix[5][6] * f) / Matrix[6][6];

// [a,b,c,d,e,f,g]' = 


void Elipsoid_::Calulate(void)
{
	if(start == 0) return;
	a = -(                   Matrix[0][1] * b + Matrix[0][2] * c + Matrix[0][3] * d + Matrix[0][4] * e + Matrix[0][5] * f + Matrix[0][6] * g) / Matrix[0][0];
	b = -(Matrix[1][0] * a +                    Matrix[1][2] * c + Matrix[1][3] * d + Matrix[1][4] * e + Matrix[1][5] * f + Matrix[1][6] * g) / Matrix[1][1];
	c = -(Matrix[2][0] * a + Matrix[2][1] * b +                    Matrix[2][3] * d + Matrix[2][4] * e + Matrix[2][5] * f + Matrix[2][6] * g) / Matrix[2][2];
	d = -(Matrix[3][0] * a + Matrix[3][1] * b + Matrix[3][2] * c +                    Matrix[3][4] * e + Matrix[3][5] * f + Matrix[3][6] * g) / Matrix[3][3];
	e = -(Matrix[4][0] * a + Matrix[4][1] * b + Matrix[4][2] * c + Matrix[4][3] * d +                    Matrix[4][5] * f + Matrix[4][6] * g) / Matrix[4][4];
	f = -(Matrix[5][0] * a + Matrix[5][1] * b + Matrix[5][2] * c + Matrix[5][3] * d + Matrix[5][4] * e +                    Matrix[5][6] * g) / Matrix[5][5];
	g = -(Matrix[6][0] * a + Matrix[6][1] * b + Matrix[6][2] * c + Matrix[6][3] * d + Matrix[6][4] * e + Matrix[6][5] * f                   ) / Matrix[6][6];	

	
	arm_sqrt_f32(a,&A);
	arm_sqrt_f32(b,&B);
	arm_sqrt_f32(c,&C);
	
	D = d / A / 2.0f;
	E = e / B / 2.0f;
	F = f / C / 2.0f;
}

