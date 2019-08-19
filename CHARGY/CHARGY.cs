using System;
using System.Collections;


public class Program
{

    public static void Main()
    {
        string[] TastCase;
        int N;
        Stack MyStack = new Stack();

        N = int.Parse(Console.ReadLine());
        TastCase = Console.ReadLine().Split(' ');


        foreach(string C in TastCase)
        {
            if(MyStack.Count == 0)
            {
                MyStack.Push(C);
            }
            else
            {
                switch (C)
                {

                    case "0":
                    MyStack.Push(C);
                    break;

                    case "1":

                    switch (MyStack.Peek().ToString())
                    {
                        case "0":
                        case "1":
                        MyStack.Push(C);
                        break;

                        case "-1":
                        MyStack.Pop();
                        break;
                    }

                    break;

                    case "-1":

                    switch (MyStack.Peek().ToString())
                    {
                        case "0":
                        case "-1":
                        MyStack.Push(C);
                        break;

                        case "1":
                        MyStack.Pop();
                        break;
                    }

                    break;
                }
            }            
        }

        Console.WriteLine(MyStack.Count);

    }

}
