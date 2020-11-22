//
//  main.cpp
//  Day6App_Part2
//
//  Created by Jeffrey Haselby on 11/21/20.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
using namespace std;

int solve_puzzle_piecewise(map<string,string> &map_of_orbits, string child_body){
    int orbits = 0;
        while (child_body != "COM"){
            orbits++;
            child_body = map_of_orbits[child_body];
        }
    
    return orbits;
}

string find_common_node(map<string,string> &map_of_orbits, set<string> &set_orbits_1, set<string> &set_orbits_2){
    string common;
    int max = 0;
    int max_comp = 0;
    for (const auto& body : set_orbits_1){
        if (set_orbits_2.count(body))
        {
            max_comp = solve_puzzle_piecewise(map_of_orbits, body);
            if (max_comp > max){
                max = max_comp;
                common = body;
            }
        }
    }
    return common;
}

int solve_puzzle_piecewise(map<string,string> &map_of_orbits, string child_body, set<string> &set_orbits){
    int orbits = 0;
        while (child_body != "COM"){
            orbits++;
            child_body = map_of_orbits[child_body];
            set_orbits.insert(child_body);
        }
    
    return orbits;
}

void print_orbits(map<string,string> &map_of_orbits){
    //https://stackoverflow.com/questions/2850312/use-of-for-each-on-map-elements
    for (const auto& [child,parent] : map_of_orbits){
        cout << child << " orbits " << parent << endl;
    }
    return;
}

void load_puzzle(map<string,string> &map_of_orbits){
    string input_file_location = "/Users/haselby/Development/C++/AdventOfCode2019/6/Day6App/puzzle_input.txt";
    ifstream input_file;
    input_file.open(input_file_location);
    string line_of_text;
    char delimiter = ')';
    
    //child orbits parent
    string child;
    string parent;
    
    while(input_file >> line_of_text){
        parent = line_of_text.substr(0,line_of_text.find(delimiter));
        child = line_of_text.substr(line_of_text.find(delimiter)+1);
        map_of_orbits[child] = parent;
    }
    input_file.close();
    return;
}

int main(int argc, const char * argv[]) {
    cout << "Starting Day 6 Application\n";
    map<string,string> map_of_orbits;
    load_puzzle(map_of_orbits);
    print_orbits(map_of_orbits);
    set<string> you_set;
    set<string> santa_set;
    int solution_a = solve_puzzle_piecewise(map_of_orbits, "YOU", you_set);
    int solution_b = solve_puzzle_piecewise(map_of_orbits, "SAN", santa_set);
    
    string common_node = find_common_node(map_of_orbits,you_set, santa_set);
    cout << "Common Node: " << common_node << endl;
    
    int solution_c = solve_puzzle_piecewise(map_of_orbits, common_node, santa_set);
    
    int solution = (solution_a - 1) + (solution_b - 1) - 2 * solution_c;
    cout << "Minimum number of orbit transfers: " << solution << endl;
    return 0;
}

