// Day10App_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <vector> 
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//  |-----------> x-dir
//  |
//  |
//  |
//  v
//  y-dir
//
// Traditionally grid[row #][column #]  = grid [y] [x]
// However for this puzzle, I'm looking for grid to display in (x,y) format aka grid[x][y] (Transposing x with y)

struct Asteroid {
    int loc_x;
    int loc_y;
    float angle;
    float distance;
};

std::string LoadPuzzle() {

    //Input Puzzle as C++ Raw string literal
    //usage: prefix(optional) R"delimiter(raw_characters)delimiter"
    std::string _puzzle = R"(
.#..#..##.#...###.#............#.
.....#..........##..#..#####.#..#
#....#...#..#.......#...........#
.#....#....#....#.#...#.#.#.#....
..#..#.....#.......###.#.#.##....
...#.##.###..#....#........#..#.#
..#.##..#.#.#...##..........#...#
..#..#.......................#..#
...#..#.#...##.#...#.#..#.#......
......#......#.....#.............
.###..#.#..#...#..#.#.......##..#
.#...#.................###......#
#.#.......#..####.#..##.###.....#
.#.#..#.#...##.#.#..#..##.#.#.#..
##...#....#...#....##....#.#....#
......#..#......#.#.....##..#.#..
##.###.....#.#.###.#..#..#..###..
#...........#.#..#..#..#....#....
..........#.#.#..#.###...#.....#.
...#.###........##..#..##........
.###.....#.#.###...##.........#..
#.#...##.....#.#.........#..#.###
..##..##........#........#......#
..####......#...#..........#.#...
......##...##.#........#...##.##.
.#..###...#.......#........#....#
...##...#..#...#..#..#.#.#...#...
....#......#.#............##.....
#......####...#.....#...#......#.
...#............#...#..#.#.#..#.#
.#...#....###.####....#.#........
#.#...##...#.##...#....#.#..##.#.
.#....#.###..#..##.#.##...#.#..##
)";

    return _puzzle;
}

void PrintGrid(vector<vector<char>> grid) {

    for (int j = 0; j < grid.size(); j++)
    {
        for (int i = 0; i < grid[j].size(); i++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

vector<vector<char>> LoadToGrid(string puzzle) {
    //Creates grid[x][y]  grid[<row number>][<columns number>]
    vector<vector<char>> grid;
    vector<char> column;
    int x{};
    int y{};

    for (int i = 0; i < puzzle.length(); i++) {
        if (puzzle.at(i) == '\n') {
            //Increments x, y appropriately, new row begins after '\n'
            //This statement also handles puzzle input that starts with '\n' 
            if (x > 0) {
                x = 0;
                y++;
            }
        }
        else if (y == 0) {
            // create new column, adding one elment to column
            column.push_back(puzzle.at(i));
            grid.push_back(column);
            column.clear();
            x++;
        }
        else {
            // add element to bottom of column
            grid[x].push_back(puzzle.at(i));
            x++;
        }
    }

    return grid;
}

float CalculateHeading(int x_in, int y_in) {
    float x(x_in); // Narrowing conversion
    float y(y_in); // Narrowing conversion
    if ((x > 0) && (y >= 0)) return atan(y / x);
    if ((x == 0) && (y > 0)) return M_PI / 2;
    if ((x < 0) && (y >= 0)) return M_PI - atan(y / abs(x));
    if ((x <= 0) && (y < 0)) return (3.0f / 2.0f) * M_PI - atan(abs(x) / abs(y));
    if ((x > 0) && (y < 0)) return (3.0f / 2.0f) * M_PI + atan(x / abs(y));
    if ((x == 0) && (y == 0)) return 0;
}

int CalculateUniqueLines(vector<vector<char>> grid, int x_coord, int y_coord) {
    std::set<float> unique_lines_of_site;

    for (int j = 0; j < grid.size(); j++)
    {
        for (int i = 0; i < grid[j].size(); i++)
        {
            if (grid[i][j] == '#') {
                if (!((i == x_coord) && (j == y_coord))) {
                    //Calculate slope (rise over run)
                    unique_lines_of_site.insert(CalculateHeading((i - x_coord), (j - y_coord)));
                }
            }
        }
    }
    return unique_lines_of_site.size();
}

std::tuple<int, int> FindBestLocation(vector<vector<char>> grid) {
    int line_of_sight_max{};
    int line_of_sight_count{};
    int x_pos_ideal{};
    int y_pos_ideal{};

    for (int j = 0; j < grid.size(); j++)
    {
        for (int i = 0; i < grid[j].size(); i++)
        {
            if (grid[i][j] == '#') {
                line_of_sight_count = CalculateUniqueLines(grid, i, j);
                if (line_of_sight_count > line_of_sight_max) {
                    line_of_sight_max = line_of_sight_count;
                    x_pos_ideal = i;
                    y_pos_ideal = j;
                }
            }
        }
    }
    std::cout << "Ideal Position: (" << x_pos_ideal << "," << y_pos_ideal << ")" << std::endl;
    std::cout << "Unique lines of sight: " << line_of_sight_max << std::endl;

    return { x_pos_ideal , y_pos_ideal };
}


float nextDirection(vector<Asteroid> asteroidField, float lastDirection) {
    float min_angle_delta{2.0f*M_PI};
    float next_angle{};
    bool found_viable_angle{ false };
    
    do {
        for (Asteroid asteroid : asteroidField) {
            if (asteroid.angle > lastDirection) {
                float angle_delta = asteroid.angle - lastDirection;
                if (angle_delta < min_angle_delta) {
                    next_angle = asteroid.angle;
                    min_angle_delta = angle_delta;
                    found_viable_angle = true;
                }
            }
        }
        if (found_viable_angle == false) {
            lastDirection = -0.1f; // Angle wraps around; Set to neg value so it would catch angle of zero.
        }
    } while (found_viable_angle == false);
    //printf("Next Angle: %4.6f \n", next_angle);
    return next_angle;
}

std::tuple<int, int> FireOnTargets(vector<Asteroid> asteroidField) {
    int target_x{};
    int target_y{};
    float min_distance{};
    vector<Asteroid>::iterator asteroid_to_destroy{};
    int asteroids_destroyed{};
    
    //Starting angle - Pointing Up (high noon)
    float current_angle = (3.0f / 2.0f) * M_PI;
    
    //Finds closest asteroid at a given angle
    do {
        for (auto asteroid_target = asteroidField.begin(); asteroid_target != asteroidField.end(); ++asteroid_target) {
            if (asteroid_target->angle == current_angle) {
                if ((min_distance == 0) || (asteroid_target->distance < min_distance)) {
                    target_x = asteroid_target->loc_x;
                    target_y = asteroid_target->loc_y;
                    min_distance = asteroid_target->distance;
                    std::cerr << "angle: " << asteroid_target->angle << ", distance: " << asteroid_target->distance << std::endl;
                    asteroid_to_destroy = asteroid_target;
                }
            }
        }
        // Destroys asteroid, by removing it from vector;
        asteroidField.erase(asteroid_to_destroy);
        asteroids_destroyed++;
        std::cerr << "Asteroid Destroyed: " << target_x << "," << target_y << std::endl;

        //reset values for next iteration
        if (asteroidField.size() > 0) {
            current_angle = nextDirection(asteroidField, current_angle);
            min_distance = 0;
        }
        else {
            std::cout << "All Asteroids Destroyed..." << std::endl;
            break;
        }
    } 
    while (asteroids_destroyed < 200);

    //Returns location of last asteroid destroyed
    return { target_x, target_y }; 
}

void AcquireTargets(vector<vector<char>> grid, int x_coord, int y_coord) {
    vector<Asteroid> asteroidField;

    for (int j = 0; j < grid.size(); j++)
    {
        for (int i = 0; i < grid[j].size(); i++)
        {
            if (grid[i][j] == '#') {
                if (!((i == x_coord) && (j == y_coord))) {
                    float angle = CalculateHeading((i - x_coord), (j - y_coord));
                    float distance = sqrt(static_cast<float>(pow((i - x_coord), 2) + pow((j - y_coord) , 2)));
                    Asteroid asteroid{ i, j, angle, distance };
                    asteroidField.push_back(asteroid);
                }
            }
        }
    }
    std::cout << "NumberOfTargets: " << asteroidField.size() << std::endl;

    auto [x, y] = FireOnTargets(asteroidField);

    std::cout << "Location of two hundredth asteroid destroyed: " << x << "," << y << std::endl;

    return;
}

int main()
{
    std::cout << "Day 10 Proto: Starting ..." << std::endl;;

    std::string puzzle = LoadPuzzle();

    vector<vector<char>> asteroid_grid = LoadToGrid(puzzle);

    PrintGrid(asteroid_grid);

    std::cout << std::endl;

    //Returns optimal location for asteroid base
    auto [base_x, base_y] = FindBestLocation(asteroid_grid);

    AcquireTargets(asteroid_grid, base_x, base_y);

    system("pause");
}
