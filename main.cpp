#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define INF 10000

struct Point
{
    float x, y;
    Point(float x, float y) : x(x), y(y){};
    Point(){};
};

vector<Point> generateRandomPts(int numPoints, int minx, int miny, int maxx, int maxy)
{
    srand(time(NULL));
    vector<Point> points;
    for (int i = 0; i < numPoints; i++)
    {
        float xpt = floor(rand() % (maxx - minx + 1)) + minx;
        float ypt = floor(rand() % (maxy - miny + 1)) + miny;
        // cout << xpt << " " << ypt << endl;
        Point point = {xpt, ypt};
        points.push_back(point);
    }

    return points;
}

double findAngle(Point prev_o, Point o, Point p)
{
    double dAx = o.x - prev_o.x;
    double dAy = o.y - prev_o.y;
    double dBx = p.x - o.x;
    double dBy = p.y - o.y;
    // finding angle
    double angle = atan2(dAx * dBy - dAy * dBx, dAx * dBx + dAy * dBy);
    double degree_angle = angle * (180 / 3.1415);
    degree_angle = degree_angle + 180;
    return degree_angle;
}

Point findNextOrigin(Point prev_o, Point o, vector<Point> points)
{
    double max_angle = 360;
    Point next_o;
    for (int i = 0; i < points.size(); i++)
    {
        if ((points[i].x == o.x && points[i].y == o.y) || (points[i].x == prev_o.x && points[i].y == prev_o.y))
        {
            continue;
        }
        double angle = findAngle(prev_o, o, points[i]);
        if (angle < max_angle)
        {
            max_angle = angle;
            next_o = points[i];
        }

        else if (angle == max_angle)
        {
            double dist1 = sqrt(pow((prev_o.x - o.x), 2) + pow((prev_o.y - o.y), 2));
            double dist2 = sqrt(pow((prev_o.x - points[i].x), 2) + pow((prev_o.y - points[i].y), 2));
            if (dist2 > dist1)
            {
                next_o = points[i];
            }
        }
    }
    return next_o;
}

vector<Point> my_jarvis(vector<Point> points)
{
    vector<Point> hull;
    int n = points.size();
    Point origin;
    origin.x = 100000;
    origin.y = 100000;
    for (int i = 0; i < n; i++)
    {
        if (points[i].y < origin.y)
        {
            origin = points[i];
        }
    }

    Point prev_o;
    prev_o.x = origin.x + 0.01;
    prev_o.y = origin.y;
    hull.push_back(origin);
    // cout << origin.x << " " << origin.y << endl;
    while (true)
    {
        Point next_o = findNextOrigin(prev_o, origin, points);
        // cout << next_o.x << " " << next_o.y << endl;
        if (next_o.x == hull[0].x && next_o.y == hull[0].y)
        {
            break;
        }
        hull.push_back(next_o);
        prev_o = origin;
        origin = next_o;
    }

    return hull;
}

void findNonHullPoints(vector<pair<int, int>> &nonhull, vector<pair<int, int>> hull, vector<Point> pts)
{
    set<string> strhull;
    for (auto i : hull)
    {
        string str = to_string(i.first);
        str.push_back('.');
        str += to_string(i.second);
        strhull.insert(str);
    }
    for (auto i : pts)
    {
        string str = to_string(i.x);
        str.push_back('.');
        str += to_string(i.y);
        if (strhull.find(str) == strhull.end())
        {
            nonhull.push_back(make_pair(i.x, i.y));
        }
    }
}

float area(vector<pair<int, int>> tri)
{
    int x1 = tri[0].first;
    int y1 = tri[0].second;
    int x2 = tri[1].first;
    int y2 = tri[1].second;
    int x3 = tri[2].first;
    int y3 = tri[2].second;
    float ans = abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    // cout << ans << endl;
    return ans;
}

bool isInside(vector<pair<int, int>> tri, pair<int, int> point)
{
    vector<pair<int, int>> tri1 = tri;
    vector<pair<int, int>> tri2 = tri;
    vector<pair<int, int>> tri3 = tri;

    /* Calculate area of triangle ABC */
    float A = area(tri);

    auto it1 = tri1.begin();
    tri1.erase(it1);
    tri1.push_back(point);
    float A1 = area(tri1);

    auto it2 = tri2.begin() + 1;
    tri2.erase(it2);
    tri2.push_back(point);
    float A2 = area(tri2);

    auto it3 = tri3.end();
    tri3.erase(it3);
    tri3.push_back(point);

    float A3 = area(tri3);

    /* Check if sum of A1, A2 and A3 is same as A */
    return (A == A1 + A2 + A3);
}

int main()
{
    int numPoints = 3 + rand() % 48;
    vector<Point> points = generateRandomPts(numPoints, 0, 0, 100, 100);
    vector<Point> hull_points = my_jarvis(points);
    vector<pair<int, int>> hull;
    for (int i = 0; i < hull_points.size(); i++)
    {
        hull.push_back(make_pair(hull_points[i].x, hull_points[i].y));
    }
    vector<pair<int, int>> nonhull;
    findNonHullPoints(nonhull, hull, points);
    cout << "The points in the convex hull are: ";
    for (int i = 0; i < hull.size(); i++)
    {
        cout << "(" << hull[i].first << ", " << hull[i].second << ")" << endl;
    }

    // get a random number from 1 to nonhull.size()

    vector<vector<pair<int, int>>> triangle;
    pair<int, int> start;

    if (nonhull.size() == 0)
    {
        int x = 0;
        int y = 0;
        for (int i = 0; i < hull.size(); i++)
        {
            x += hull[i].first;
            y += hull[i].second;
        }
        x = x / hull.size();
        y = y / hull.size();
        start = {x, y};
    }

    else
    {
        start = nonhull[0];
    }

    int random = 1 + rand() % (3 * nonhull.size() / 4);
    vector<pair<int, int>> selected;
    for (int i = 1; i < random; i++)
    {
        selected.push_back(nonhull[i]);
    }

    for (int i = 0; i < hull.size(); i++)
    {
        vector<pair<int, int>> tri;
        tri.push_back(start);
        tri.push_back(hull[i]);
        tri.push_back(hull[(i + 1) % hull.size()]);
        triangle.push_back(tri);
    }

    for (int i = 1; i < selected.size(); i++)
    {
        for (int j = 0; j < triangle.size(); j++)
        {
            int f = 0;
            if (isInside(triangle[j], nonhull[i]))
            {
                vector<pair<int, int>> tri = triangle[j];
                vector<pair<int, int>> tri1 = tri;
                vector<pair<int, int>> tri2 = tri;
                vector<pair<int, int>> tri3 = tri;
                triangle.erase(triangle.begin() + j);

                pair<int, int> point = nonhull[i];
                auto it1 = tri1.begin();
                tri1.erase(it1);
                tri1.push_back(point);
                triangle.push_back(tri1);

                auto it2 = tri2.begin() + 1;
                tri2.erase(it2);
                tri2.push_back(point);
                triangle.push_back(tri2);

                auto it3 = tri3.end();
                tri3.erase(it3);
                tri3.push_back(point);
                triangle.push_back(tri3);

                f = 1;
            }

            if (f == 1)
                break;
        }
    }

    // write all point in triangle to output file
    ofstream outputFile("output.txt");
    for (int i = 0; i < triangle.size(); i++)
    {
        for (int j = 0; j < triangle[i].size(); j++)
        {
            outputFile << triangle[i][j].first << " " << triangle[i][j].second << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    // write all hull points to output file
    // ofstream outputFile1("output1.txt");
    // for (int i = 0; i < hull.size(); i++)
    // {
    //     outputFile1 << hull[i].first << " " << hull[i].second << endl;
    // }
    // outputFile1.close();

    // write a function which sorts the points in the hull in clockwise order
}
