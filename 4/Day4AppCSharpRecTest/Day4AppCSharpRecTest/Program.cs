using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Day4AppCSharpRecTest
{
    class Program
    {
        static int pwd_solver(int current_guess, int upper_bound, int successful_match )
        {
            successful_match++;

            if (successful_match % 100.0 == 0)
            {
                Console.WriteLine(successful_match.ToString() + "\n");
            }

            if (current_guess < upper_bound)
            {
                current_guess++;
                successful_match = pwd_solver(current_guess, upper_bound, successful_match);
            }
            else
            {
                return successful_match;
            }
            return successful_match;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Starting Solver...\n");
            int puzzle_pwd_lb = 130254;
            int puzzle_pwd_ub = 678275;
            int meets_criteria = 0;
            meets_criteria = pwd_solver(puzzle_pwd_lb, puzzle_pwd_ub, meets_criteria);
            Console.WriteLine("Number of passwords that meet criteria: " + meets_criteria.ToString() + "/n");
        }
    }
}
