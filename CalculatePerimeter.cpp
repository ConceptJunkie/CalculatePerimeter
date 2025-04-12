#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>

// class Shape - represents an arbitrary 2D polygonal shape

class Shape {
    public:
        virtual double CalcPerimeter() = 0;
};


// class Point - represents a 2D cartesian point

class Point {
    public:
        double x, y;

    public:
        Point() : x(0.0), y(0.0) {
        }

        Point(double x, double y) : x(x), y(y) {
        }

        Point &operator =( const Point &other )
        {
            x = other.x;
            y = other.y;

            return *this;
        }

        // expects two floating point values separated by a comma
        // x and y are set to the first two values parsed, otherwise they
        // remain 0.0.

        Point &Parse( const std::string &value )
        {
            const char *delimiters = ",";

            char *input = const_cast< char * >( value.c_str( ) ),
                 *token = std::strtok(input, delimiters);

            if (token)
            {
                x = std::atof( token );

                token = std::strtok(nullptr, delimiters);

                if ( token )
                {
                    y = std::atof( token );
                }
                else
                {
                    y = 0.0;
                }
            }
            else
            {
                x = 0.0;
                y = 0.0;
            }

            return *this;
        }

        // calculates the Euclidian distance between two points
        double GetDistance( const Point &other ) const
        {
            double dx = std::abs( other.x - x ),
                   dy = std::abs( other.y - y );

            return std::sqrt( dx * dx + dy * dy );
        }

        // stream formatter
        friend std::ostream &operator <<(std::ostream &os, Point const &point) {
            return os << "( " << point.x << ", " << point.y << " )";
        }
};


//  I'm following instructions in making the data members an array.  I would
//  otherwise never use an array this way.  It should be a vector.  However, if
//  the data members are private, I can at least control how they are accessed.
//
// "The three points of the triangle should be private floating variables."
//
//  This contradicts the instruction that says they should be Point instances,
//  so I'm ignoring it.

class Triangle : public Shape {
    private:
        Point points[ 3 ];

    public:
        Triangle(Point vertex1, Point vertex2, Point vertex3) {
            points[ 0 ] = vertex1;
            points[ 1 ] = vertex2;
            points[ 2 ] = vertex3;
        }

        double CalcPerimeter() override {
            return points[ 0 ].GetDistance( points[ 1 ] ) +
                   points[ 1 ].GetDistance( points[ 2 ] ) +
                   points[ 2 ].GetDistance( points[ 0 ] );
        }
};

int main( int argc, char *argv[ ] )
{
    std::cout << "Enter points as 2 coordinates separated by a comma." << std::endl << std::endl;

    std::string input;
    std::vector< Point > points( 3 );

    std::cout << "Enter point 1: ";
    std::cin >> input;

    points[ 0 ].Parse( input );

    std::cout << std::endl << "Enter point 2: ";
    std::cin >> input;

    points[ 1 ].Parse( input );

    std::cout << std::endl << "Enter point 3: ";
    std::cin >> input;

    points[ 2 ].Parse( input );

    Triangle triangle( points[ 0 ], points[ 1 ], points[ 2 ] );

    std::cout << std::endl << "Triangle: " << points[ 0 ] << " " << points[ 1 ] << " " << points[ 2 ] << std::endl;
    std::cout << "Perimeter: " << triangle.CalcPerimeter( ) << std::endl;

    return 0;
}