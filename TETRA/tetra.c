#include <stdio.h>
#include <math.h>

static double	calc_tetra_vol(double u, double v, double w,
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

static double	calc_area(double a, double b, double c)
{
	double	p = (a + b + c) / 2;

	return (sqrt(p * (p - a) * (p - b) * (p - c)));
}

#define vol_sphere(x, y) (3 * x) / y

int		main(void)
{
	int		nb_case;
	double	U, V, W, u, v, w;
	double	tetra_vol, surface_area;

	scanf("%d", &nb_case);
	while (--nb_case >= 0)
	{
		scanf("%lf %lf %lf %lf %lf %lf", &u, &v, &W, &w, &V, &U);
		tetra_vol = calc_tetra_vol(u, v, w, U, V, W);
		surface_area = calc_area(u, v, w)
						+ calc_area(u, V, W)
						+ calc_area(v, W, U)
						+ calc_area(w, V, U);
		printf("%.4F\n", vol_sphere(tetra_vol, surface_area));
	}
	return (0);
}
