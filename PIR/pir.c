#include <stdio.h>
#include <math.h>

/*
static double	calc_area(double a, double b, double c)
{
	double	area;


	return (area);
}

static double	calc_vol(double ab, double ac, double ad, double bc, double bd, double cd)
{
	double	vol;
	double	ABC, ABD, ACD, BCD;

	ABC = calc_area(ab, ac, bc);
	ABD = calc_area(ab, ad, bd);
	ACD = calc_area(ac, ad, cd);
	BCD = calc_area(bc, bd, cd);

	vol = ();
	return (vol);
}

#define pow(x) pow(x, 2)

static double	calc_vol(double ab, double ac, double ad, double bc, double bd, double cd)
{
	double	vol;
	double	abc, acd, abd;
	double	ab2 = pow(ab);		// u
	double	ac2 = pow(ac);		// v
	double	ad2 = pow(ad);		// w
	double	bc2 = pow(bc);		// W
	double	bd2 = pow(bd);		// U
	double	cd2 = pow(cd);		// V

	abc = ab2 + ac2 - bc2;		// w'
	acd = ac2 + ad2 - cd2;		// v'
	abd = ab2 + ad2 - bd2;		// u'
	vol = sqrt((4 * ab2 * ac2 * ad2)
				- (ab2 * pow(abd))
				- (ac2 * pow(acd))
				- (ad2 * pow(abc))V
				+ (abc * acd * abd))
				/ 12;
	return (vol);
}
*/

static double	calc_vol(double u, double v, double w,
						double U, double V, double W)
{
	double	vol;
	double	X = (W - u + V) * (u + V + W);
	double	x = (u - V + W) * (V - W + u);
	double	Y = (U - v + W) * (v + W + U);
	double	y = (v - W + U) * (W - U + v);
	double	Z = (V - w + U) * (w + U + V);
	double	z = (w - U + V) * (U - V + w);
	double	a = sqrt(x * Y * Z);
	double	b = sqrt(y * Z * X);
	double	c = sqrt(z * X * Y);
	double	d = sqrt(x * y * z);

	if (!u || !v || !w || !U || !V || !W)
		return (0.0);
	vol = 	sqrt((-a + b + c + d)
				* (a - b + c + d)
				* (a + b - c + d)
				* (a + b + c - d))
			/ (192 * U * V * W);
	return (vol);
}

int		main(void)
{
	int		nb_case;
	double	U, V, W, u, v, w;

	scanf("%d", &nb_case);
	while (--nb_case >= 0)
	{
		scanf("%lf %lf %lf %lf %lf %lf", &u, &v, &W, &w, &V, &U);
		printf("%.4F\n", calc_vol(u, v, w, U, V, W));
	}
	return (0);
}
