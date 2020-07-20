#include<iostream>
#include <vector>
#include <bits/stdc++.h> 

// function to find out the intection between lines AB and CD
// input : A,B,C,D
//output : intersection point
std::vector<float> intersection(std::vector<float> A, std::vector<float> B, std::vector<float> C, std::vector<float> D) 
{

    // Line AB represented as ax + by = c
    double a = B[1] - A[1];
    double b = A[0] - B[0];
    double c = a*(A[0]) + b*(A[1]);
    // Line CD represented as a1x + b1y = c1
    double a1 = D[1] - C[1];
    double b1 = C[0] - D[0];
    double c1 = a1*(C[0])+ b1*(C[1]);
    
    //calculation of intersection point   
    double det = a*b1 - a1*b;
    double x = (b1*c - b*c1)/det;
    double y = (a*c1 - a1*c)/det;
    std::vector<float> intersection_point;
    intersection_point.push_back(x);
    intersection_point.push_back(y);
    return intersection_point;

}

// function to calculate distance between points (x1,y1) and (x2,y2)
// input : x1,y1,x2,y2
// output : distance
float distance(float x1, float y1, float x2, float y2) 
{
    return std::sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2)); 
}

// funtion to check if the given point is inside the given polygon
// input : polygon, point
// output : true if point lies inside the polygon and false if it lies on the border or outside
bool is_inside_polygon(std::vector<std::vector<float>> &polygon, std::vector<float> &point)
{
    int intersection_count = 0;

    int n = polygon.size(); 

    for(int j = 0; j < n; j++)
    {
        int det = ( (polygon[(j+1)%n][0] - polygon[j][0]) * (point[1] - polygon[j][1]) ) - ( (point[0] - polygon[j][0]) * (polygon[(j+1)%n][1] - polygon[j][1]) );

        if (det == 0)
            return false;
        
        if ( point[1] == polygon[j][1] && point[1] == polygon[(j+1)%n][1] ) ;

        else if ( point[1] >= polygon[j][1] && point[1] < polygon[(j+1)%n][1] ) 
        {                
            if (det < 0)
                ++intersection_count;              
        }
        else if ( point[1] >= polygon[(j+1)%n][1] && point[1] < polygon[j][1]  )
        {             
            if (det > 0)
                ++intersection_count;  
        }            
    }        

    if (intersection_count%2 == 0)
        return false;
    else
        return true;

}

// function to check if there are any points inside a triange connecting the source and a side of a building
// and modify the length exposed accordingly
// input : triangle co-ordinates and all building co-ordinates
// output : true if any building co-ordinate is found within the triangle and
//          false otherwise
bool is_inside_triangle(std::vector<std::vector<float>> &triangle, std::vector<std::vector<std::vector<float>>> &building, float &length )
{    
    bool is_inside = false;
    std::vector<std::vector<float>> points;
    std::vector<float> length_list;

    //boundbox for the triangle
    float min_y = triangle[0][1];
    float min_x = triangle[0][0];
    float max_x = triangle[0][0];
    float max_y = triangle[0][1];

    for (int i = 1; i < 3; i++)
    {
        if (min_y > triangle[i][1])
            min_y = triangle[i][1];

        if (min_x > triangle[i][0])
            min_x = triangle[i][0];
        
        if (max_y < triangle[i][1])
            max_y = triangle[i][1];

        if (max_x < triangle[i][0])
            max_x = triangle[i][0];        
    }

    // looping over all buidling co-ordinates
    for(int i = 0; i < building.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //checking if the building co-ordinates lie inside the boundbox
            if (building[i][j][0] >= min_x && building[i][j][0] <= max_x )
            {
                if ( building[i][j][1] >= min_y && building[i][j][1] <= max_y )
                {
                    //checking if building co-ordinates lie inside the triangle
                    if(is_inside_polygon(triangle, building[i][j]))
                    {
                        //checking if the points inside the triangle is exposed to the source
                        int det = ( (building[i][(j+1)%4][0] - building[i][j][0]) * (triangle[2][1] - building[i][j][1]) ) - ( (triangle[2][0] - building[i][j][0]) * (building[i][(j+1)%4][1] - building[i][j][1]) );
                        is_inside = true;
                        // if points inside the triangle is exposed then changing the exposed size of the building side accordingly
                        if  (det < 0) 
                        {
                            std::vector<float> ans = intersection(triangle[0], triangle[1], triangle[2], building[i][j] );
                            length_list.push_back(distance(triangle[0][0], triangle[0][1],  ans[0],  ans[1]));
                        }
                    }
                }
            }
        }
    }

    //updating the minimum length to the lenth exposed variable
    if (length_list.size())
    {
        float min_length = length_list[0];
        for (auto i = length_list.begin(); i != length_list.end(); ++i) 
        {
            if (min_length > *i)
                min_length = *i;
        }
        length += min_length;
    }
    
    return is_inside;
}

float length_exposed(std::vector<std::vector<std::vector<float>>> &building, std::vector<float> &source)
{
    int n = building.size();  // total number of buildings
    float length = 0; // length of the building exposed to sunlight

    //looping over the building coordinates
    for(int i = 0; i < building.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            // checking if the building sides and the source make a right turn
            // if it makes a left turn, it is not exposed
            float det = ( (building[i][(j+1)%4][0] - building[i][j][0]) * (source[1] - building[i][j][1]) ) - ( (source[0] - building[i][j][0]) * (building[i][(j+1)%4][1] - building[i][j][1]) );
            // if it makes a right turn, we need to check if the entire side is exposed or a only a part of it is exposed
            // for this we need to check if the triangle formed between the side and the souce contains any other building coordinate
            if (det < 0)
            {
                std::vector<std::vector<float>> triangle;
                triangle.push_back(building[i][j]);
                triangle.push_back(building[i][(j+1)%4]);
                triangle.push_back(source);
                bool is_inside = is_inside_triangle(triangle, building, length);
                // if it does not contain any building co-ordinate inside the triangle, then the entire lenght is exposed
                if (!is_inside)
                {
                    length += distance( building[i][(j+1)%4][0], building[i][(j+1)%4][1],  building[i][j][0],  building[i][j][1]);
                }
            }
        }
    }        

    return length;
}

int main()
{
    std::vector<std::vector<std::vector<float>>> buildings_list {};
    std::vector<float> p(2,0);
    std::string s;

    int sides;
    std::cout << "Enter the number of buildings" << std::endl;
    std::cin >> sides;

    std::cout << "Enter the building details" << std::endl;
    for(int i = 0; i < sides; i++) 
    {
        std::cout << "Enter the building : " << i << " details" << std::endl;
        std::vector<std::vector<float>> building;
        for (int j = 0; j < 4; j++ )
        {
            std::cin >> p[0] >> p[1];
            building.push_back(p);
        }
        buildings_list.push_back(building);
    }

    std::cout << "Enter the source co-ordinates" << std::endl;
    std::cin >> p[0] >> p[1];
  
    std::cout << "length = " << length_exposed(buildings_list, p) <<  std::endl;
      

    return 0;

}
