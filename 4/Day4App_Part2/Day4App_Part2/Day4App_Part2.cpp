// Day4App_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

struct puzzle {
	puzzle(int new_lower_bound, int new_upper_bound) {
		lower_bound = new_lower_bound;
		upper_bound = new_upper_bound;
		current_guess = lower_bound;

	}

	int lower_bound{};
	int upper_bound{};
	int current_guess{};
	std::string password;
	int successful_match{};
	bool valid_double_exist{ false };

	bool no_adjacent_digits(std::string string_to_check, char char_to_look_for) {
		int occurrences{};
		for (size_t i = 0; i < string_to_check.length(); i++) {
			if (string_to_check[i] == char_to_look_for) {
				occurrences++;
			}
		}
		return (occurrences == 2);
	}

	void pwd_solver() {
		for (size_t i = current_guess; i <= upper_bound; i++) {
			password = std::to_string(i);
			valid_double_exist = false;
			for (size_t i = 1; i < password.length(); i++) {
				if ((int)(password[i - 1]) <= (int)(password[i])) {
					if ((int)(password[i - 1]) == (int)(password[i])) {
						if (no_adjacent_digits(password, password[i])) {
							valid_double_exist = true;
						}
					}
					if ((i == password.length() - 1) && valid_double_exist) {
						successful_match++;
						std::cout << password << std::endl;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
};

int main()
{
	const int puzzle_pwd_lb{ 130254 };
	const int puzzle_pwd_ub{ 678275 };
	int meets_criteria{ 0 };
	puzzle* mySolution = new puzzle(puzzle_pwd_lb, puzzle_pwd_ub);
	mySolution->pwd_solver();
	meets_criteria = mySolution->successful_match;
	std::cout << "Number of different passwords that meet criteria: " << meets_criteria << "\n";
}