using System;
using System.Linq;
using MPI;
using System.Diagnostics;

namespace ConsoleApplication1
{
    class Program
    {
        static int elem_numb;
        static int potok_numb;
        static int b = 12345;
            

        public static double calculate(int[] C)
        {
                int i, j;
                double var1 = 0;
                    
                for (i = 0; i < C.Length; i++)
                {

                    if (C[i] == b) var1++;
                        
               
                }

                return var1;
        }


        static void Main(string[] args)
            {
                    bool flag;

                    if (args.Count() == 0)
                    {
                            Console.Write("Введите количество элементов массива (от 100000 до 1000000): ");
                            do
                            {
                                    string numberStr = Console.ReadLine();

                                    flag = Int32.TryParse(numberStr, out elem_numb);
                                    if (!flag)
                                    {
                                        Console.WriteLine("Количество элементов массива указано некорректно. Попробуйте еще раз.");
                                    }
                                    else
                                    {
                                        if (elem_numb > 100000 & elem_numb < 1000000) { flag = true; } else { flag = false; }
                                        if (!flag) Console.WriteLine("Количество элементов массива быть > 100000 и < 1000000. Попробуйте еще раз.");
                                    }
                            } while (!flag);
                            Console.WriteLine("Количество элементов массива = " + elem_numb);
                                                
                            
                            
                            Console.Write("Введите количество потоков (не более 40): ", elem_numb);
                            do
                            {
                                    string numberStr = Console.ReadLine();

                                    flag = Int32.TryParse(numberStr, out potok_numb);
                                    if (!flag)
                                    {
                                            Console.WriteLine("Количество потоков указано некорректно. Попробуйте еще раз.");
                                    }
                                    else
                                    {
                                            if (potok_numb <= 40) { flag = true; } else { flag = false; }
                                            if (!flag) Console.WriteLine("Количество потоков должно быть меньше 40. Попробуйте еще раз.");
                                    }
                            }  while (!flag);
                            Console.WriteLine("Количество потоков = " + potok_numb);
                            
                            
                            Process.Start("CMD.exe", "/C cd "+ AppDomain.CurrentDomain.BaseDirectory + " && mpiexec -n " + potok_numb + " ConsoleApplication1.exe " + elem_numb);
                            Console.ReadLine();
                    }
                    else
                    {
                            Stopwatch sWatch = new Stopwatch();
                            sWatch.Start();

                            Random rnd1 = new Random();

                            elem_numb = Convert.ToInt32(args[0]);
                            int N = elem_numb;

                            int[] A = new int[N];
                            int[] C = new int[N];
                            int[,] Nabor = new int[2, elem_numb];
                            
                            for (int i = 0; i < N; i++)
                            {
                                    A[i] = rnd1.Next(100, 100000);
                                    C[i] = rnd1.Next(100, 100000);
                            }
                            for (int j = 0; j < 100; j++)
                            {
                                    Nabor[0, j] = rnd1.Next(100, 100000);
                                    Nabor[1, j] = rnd1.Next(100, 100000);
                            }
                            
                            
                            using (new MPI.Environment(ref args))
                            {
                                Intracommunicator comm = Communicator.world;
                                int rank = comm.Rank;                           
                                int size = comm.Size;                          
                                
                                int h = elem_numb / size;
                                int start;
                                int end;

                                if (rank == 0)
                                {
                                        for (int i = 1; i < size; i++)                          
                                        {
                                                start = h * i;
                                                end = start + h - 1;
                                                if (i == size - 1) end = elem_numb - 1;

                                                comm.Send(end - start + 1, i, 1);
                                        }
                                        for (int i = 1; i < size; i++)                         
                                        {
                                                start = h * i;
                                                end = start + h - 1;
                                                if (i == size - 1) end = elem_numb - 1;

                                                int[] array_part1 = new int[end - start + 1];
                                                int[] array_part2 = new int[end - start + 1];

                                                Array.Copy(A, start, array_part1, 0, end - start + 1);
                                                Array.Copy(C, start, array_part2, 0, end - start + 1);
                                                
                                                comm.Send(array_part1, i, 2);
                                                comm.Send(array_part2, i, 3);
                                        }
                                        
                                        int[] arr_part1 = new int[h];
                                        int[] arr_part2 = new int[h];
                                        Array.Copy(A, 0, arr_part1, 0, h);
                                        Array.Copy(C, 0, arr_part2, 0, h);
                                        

                                        
                                        double psum;
          
                                        sWatch.Start();
                                        double rez3 = calculate(C);
                                        sWatch.Stop();
                                        Console.WriteLine("В одном потоке. В массиве С число " + b + " встретилось " + rez3 + " раз. Время: " + sWatch.ElapsedMilliseconds.ToString() + " мс.");
                                        
                                        sWatch.Reset();
                                        sWatch.Start();
                                        rez3 = calculate(arr_part2);
                                        for (int i = 1; i < size; i++)
                                        {
                                            psum = 0;
                                            comm.Receive(i, 9, out psum);
                                            rez3 += psum;
                                        }
                                        sWatch.Stop();
                                        Console.WriteLine("N потоков. В массиве С число " + b + " встретилось " + rez3 + " раз. Время: " + sWatch.ElapsedMilliseconds.ToString() + " мс.\r\n\r\n");
                                         }
                                else
                                {
                                        int N1 = 0;
                                        comm.Receive(0, 1, out N1);             
                                        int[] array1 = new int[N1];
                                        comm.Receive(0, 2, ref array1);        
                                        int[] array2 = new int[N1];
                                        comm.Receive(0, 3, ref array2);

                                        double psum;

                                        psum = calculate(array2);
                                        comm.Send(psum, 0, 9);


                    }
                            }
                            Console.ReadLine();
                    }
        }
    }
}
