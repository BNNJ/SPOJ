using System;
using System.Collections.Generic;


    class Program
    {
        static void Main()
        {

            System.Collections.Stack OperatorStack = new System.Collections.Stack();
            List<string> Output = new List<string>();
            string OutputStr;
            int loops;
            string Express = "";
            string Letter;

            loops = int.Parse(Console.ReadLine());

            for(int i = 0; i != loops - 1; i++)
            {
                Express = Console.ReadLine();

                foreach (char c in Express)
                {                    
                    Letter = c.ToString();

                    switch(Letter)
                    {
                        case "a":
                        case "b":
                        case "c":
                        case "d":
                        case "e":
                        case "f":
                        case "g":
                        case "h":
                        case "i":
                        case "j":
                        case "k":
                        case "l":
                        case "m":
                        case "n":
                        case "o":
                        case "p":
                        case "q":
                        case "r":
                        case "s":
                        case "t":
                        case "u":
                        case "v":
                        case "w":
                        case "x":
                        case "y":
                        case "z":

                            Output.Add(Letter);
                            break;

                        case "+":
                        case "-":
                        case "*":
                        case "/":
                        case "^":

                            while (OperatorStack.Peek().ToString() == "+" | OperatorStack.Peek().ToString() == "-"| OperatorStack.Peek().ToString() == "+" | OperatorStack.Peek().ToString() == "+")
                            {

                            }


                            OperatorStack.Push(Letter);
                            break;

                        case "(":

                            OperatorStack.Push(Letter);
                            break;

                        case ")":

                            while (OperatorStack.Peek().ToString() != "(")
                            {
                                Output.Add(OperatorStack.Pop().ToString());                                                         
                            }
                            OperatorStack.Pop();
                            break;
                    }
                }

                if(OperatorStack.Count != 0)
                    {
                        while  (OperatorStack.Peek() != null)
                        {
                         Output.Add(OperatorStack.Pop().ToString());
                        }
                    }

                OutputStr = string.Join("", Output.ToArray());
                Console.WriteLine(OutputStr);
                Output.Clear();
                OperatorStack.Clear();
            }

        }
    }
