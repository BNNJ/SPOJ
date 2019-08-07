using System;

    public class Program
    {
        public static void Main()
        {
            int N = int.Parse(Console.ReadLine());
            string[] Edges;
            double dVolumeTet;
            double dRadiusShp;
            double S1, S2, S3, S4;
            
            for(int i= 0; i != N; i++)
            {     
                Edges = Console.ReadLine().Split(' ');
                dVolumeTet = Volumetet(double.Parse(Edges[0]), double.Parse(Edges[1]), double.Parse(Edges[2]), double.Parse(Edges[3]), double.Parse(Edges[4]), double.Parse(Edges[5]));

                S1 = Area(double.Parse(Edges[0]), double.Parse(Edges[1]), double.Parse(Edges[3]));
                S2 = Area(double.Parse(Edges[0]), double.Parse(Edges[2]), double.Parse(Edges[4]));
                S3 = Area(double.Parse(Edges[1]), double.Parse(Edges[5]), double.Parse(Edges[2]));
                S4 = Area(double.Parse(Edges[3]), double.Parse(Edges[4]), double.Parse(Edges[5]));

                dRadiusShp = Math.Round(RadiusSph(S1, S2, S3, S4, dVolumeTet),4);
                Console.WriteLine(dRadiusShp);
            }
        }

        public static double RadiusSph(double s1, double s2, double s3, double s4, double vol)
        {
            // radius of sphere = (3*vol)/SurfaceArea 
            double radius;
            radius = (3 * vol) / (s1 + s2 + s3 + s4);
            return radius;
        }
        public static double Volumetet(double a, double b, double c, double d, double e, double f)
        {
            double volume;

            a = Math.Pow(a, 2);
            b = Math.Pow(b, 2);
            c = Math.Pow(c, 2);
            d = Math.Pow(d, 2);
            e = Math.Pow(e, 2);
            f = Math.Pow(f, 2);

            volume = Math.Sqrt(4 * a * b * c - a * (b + c - f) - b * (a + c - e) - c * (a + b - d) + (b + c - f) * (c + a - e) * (a + b - d)) / 12;

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
