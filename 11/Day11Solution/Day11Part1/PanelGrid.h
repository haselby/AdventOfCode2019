#pragma once
#include <vector>
#include <iostream>
#include <set>
using namespace std;

// y
// ^
// |
// |
// |--------> x
//

class PanelGrid
{
private:
    int x_robot{};
    int y_robot{};
    vector<vector<int>> matrix;
    enum class Direction { left, up, right, down };
    Direction robot_direction{ Direction::up };
    enum class CommandMode { paint, move };
    CommandMode robotCommandMode{ CommandMode::paint };
    


public:

 // TODO:  Create Set to capture X,Y coordinates of panels that were painted (Use set to prevent counting the same panel twice)

    PanelGrid(int x_max, int y_max, int default_color) {

        // Set robot location to approximate center of matrix
        x_robot = x_max / 2;
        y_robot = y_max / 2;



        // instantiate vector object of type std::vector<int> and
        // use push_back() function to resize it

        for (int i = 0; i < y_max; i++)
        {
            // construct a vector of ints with the given default value
            std::vector<int> v;
            for (int j = 0; j < x_max; j++) {
                v.push_back(default_color);
            }

            // push back above one-dimensional vector
            matrix.push_back(v);
        }

        // print the two-dimensional vector
    };


    int getColor() {
        return matrix[x_robot][y_robot];
    }

    void paintColor(int color) {
        matrix[x_robot][y_robot] = color;
        cout << "painted: " << x_robot << "," << y_robot << ": " << color << endl;
    }

    void changeDirection(int rotation){
        //turn 90 degrees Direction::left(ccw) = 0
        if (rotation == 0) {
            switch(robot_direction) {
            case Direction::left : robot_direction = Direction::down;
                break;
            case Direction::up : robot_direction = Direction::left;
                break;
            case Direction::right : robot_direction = Direction::up;
                break;
            case Direction::down : robot_direction = Direction::right;
            }           
        }
        //turn 90 degrees Direction::right (cw) = 1
        else if (rotation == 1) {
            switch (robot_direction) {
            case Direction::left : robot_direction = Direction::up;
                break;
            case Direction::up : robot_direction = Direction::right;
                break;
            case Direction::right : robot_direction = Direction::down;
                break;
            case Direction::down : robot_direction = Direction::left;
            }
        }
    }

    void takeStep() {
        switch (robot_direction) {
        case Direction::left : x_robot -= 1;
            break;
        case Direction::up : y_robot += 1;
            break;
        case Direction::right : x_robot += 1;
            break;
        case Direction::down : y_robot -= 1;
        }

    }

    void readCommand(int input) {
        if (robotCommandMode == CommandMode::paint) {
            paintColor(input);
            robotCommandMode = CommandMode::move;
        }
        else if(robotCommandMode == CommandMode::move) {
            changeDirection(input);
            takeStep();
            robotCommandMode = CommandMode::paint;
        }

    }

    

};

