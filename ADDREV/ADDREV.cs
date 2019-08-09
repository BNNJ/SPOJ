using System;

public class Program
    {
        public static void Main()
        {
            int N = int.Parse(Console.ReadLine());
            string[] Numbers;
            int Somme;

            for(int i = 0; i != N; i++)
            {
                Numbers = Console.ReadLine().Split(' ');

                Somme = int.Parse(ReverseString(Numbers[0])) + int.Parse(ReverseString(Numbers[1]));

                Console.WriteLine(int.Parse(ReverseString(Somme.ToString())));
            }

        }

        public static string ReverseString(string s)
        {
            char[] array = s.ToCharArray();
            Array.Reverse(array);
            return new string(array);
        }
    }
