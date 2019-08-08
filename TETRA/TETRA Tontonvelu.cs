using System;
using System.Collections.Generic;


    public class Program
    {
        public static void Main()
        {
            int N = int.Parse(Console.ReadLine());
            string[] Edges;
            double dVolumeTet;
            double dRadiusShp;
            double S1, S2, S3, S4;

            for (int i = 0; i != N; i++)
            {
                Edges = Console.ReadLine().Split(' ');
                
            dVolumeTet = Volumetet(double.Parse(Edges[5]), double.Parse(Edges[4]), double.Parse(Edges[3]),
                                   double.Parse(Edges[0]), double.Parse(Edges[1]), double.Parse(Edges[2]));
                                  
                S1 = Area(double.Parse(Edges[0]), double.Parse(Edges[1]), double.Parse(Edges[3]));
                S2 = Area(double.Parse(Edges[0]), double.Parse(Edges[2]), double.Parse(Edges[4]));
                S3 = Area(double.Parse(Edges[1]), double.Parse(Edges[5]), double.Parse(Edges[2]));
                S4 = Area(double.Parse(Edges[3]), double.Parse(Edges[4]), double.Parse(Edges[5]));


                
                dRadiusShp = Math.Round(RadiusSph(S1, S2, S3, S4, dVolumeTet), 4);
                
                if (dRadiusShp == 0)
                {
                    Console.WriteLine("0.0000");
                }

                else
                {
                    Console.WriteLine(dRadiusShp);
                }
            }
        }

        public static double RadiusSph(double s1, double s2, double s3, double s4, double vol)
        {
            double radius;
            radius = (3 * vol) / (s1 + s2 + s3 + s4);
            return radius;
        }
        public static double Volumetet(double U, double V, double W, double u, double v, double w)
        {
            double volume;
            double a, b, c, d, X, x, Y, y, Z, z;

        X = (w - U + v) * (U + v + w);
        x = (U - v + w) * (v - w + U);
        Y = (u - V + w) * (V + w + u);
        y = (V - w + u) * (w - u + V);
        Z = (v - W + u) * (W + u + v);
        z = (W - u + v) * (u - v + W);

        a = Math.Sqrt(x * Y * Z);
        b = Math.Sqrt(y * Z * X);
        c = Math.Sqrt(z * X * Y);
        d = Math.Sqrt(x * y * z);

        volume = Math.Sqrt((-a + b + c + d) * (a - b + c + d) * (a + b - c + d) * 
            (a + b + c - d)) / (192 * u * v * w);            

            return volume;
        }


        public static double Area(double a, double b, double c)
        {
            double Area;
            double P;

            P = (a + b + c) / 2;
            Area = Math.Sqrt(P * (P - a) * (P - b) * (P - c));

            return Area;
        }
    }
      

