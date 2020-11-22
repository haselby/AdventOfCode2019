//
//  main.cpp
//  Day6App
//
//  Created by Jeffrey Haselby on 11/21/20.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


int solve_puzzle(map<string,string> &map_of_orbits){
    int orbits = 0;
    string child_body;
    
    
    for (const auto& [child,parent] : map_of_orbits){
        child_body = child;
        while (child_body != "COM"){
            orbits++;
            child_body = map_of_orbits[child_body];
        }
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
    int solution = solve_puzzle(map_of_orbits);
    cout << "Total number of direct and indirect orbits: " << solution << endl;
    return 0;
}
