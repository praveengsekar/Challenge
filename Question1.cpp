#include<iostream>
#include <vector>

bool is_inside_polygon(std::vector<std::vector<float>> &polygon, std::vector<float> &point)
{
    int intersection = 0;

    int n = polygon.size(); 

    for(int j = 0; j < n; j++)
    {
        //checking if the edge of a polygon and the point make a left turn or right turn
        int det = ( (polygon[(j+1)%n][0] - polygon[j][0]) * (point[1] - polygon[j][1]) ) - ( (point[0] - polygon[j][0]) * (polygon[(j+1)%n][1] - polygon[j][1]) );
        // if det is zero, then it is along the edge or outside the polygon 
        if (det == 0)
            return false;
        
        // if the edge is horizontal line, the edge does not contribute to the intersection
        if ( point[1] == polygon[j][1] && point[1] == polygon[(j+1)%n][1] ) 
            ;
        
        // if the first point on the edge is the bottom one 
        // and the edge and point forms a right turn, 
        // it contributes to the intersection 
        else if ( point[1] >= polygon[j][1] && point[1] < polygon[(j+1)%n][1] ) 
        {                
            if (det < 0)
                ++intersection;              
        }
        // if the first point on the edge is the top one 
        // and the edge and point forms a left turn, 
        // it contributes to the intersection 
        else if ( point[1] >= polygon[(j+1)%n][1] && point[1] < polygon[j][1]  )
        {             
            if (det > 0)
                ++intersection;  
        }            
    }        

    //if the number of intersection is even, the point lies outside the polygon
    if (intersection%2 == 0)
        return false;
    //if the number of intersection is odd, the point lies outside the polygon
    else
        return true;

}

int main()
{
    std::vector<std::vector<float>> polygon {};
    std::vector<float> point(2,0);
    std::string s;

    int sides;
    std::cout << "Enter the number of vertices" << std::endl;
    std::cin >> sides;

    std::cout << "Enter the vertices" << std::endl;
    for(int i = 0; i < sides; i++) {
        std::cout << "Enter the point : " << i << std::endl;
        std::cin >> point[0] >> point[1];
        polygon.push_back(point);
    }

    std::cout << "Enter the point" << std::endl;
    std::cin >> point[0] >> point[1];
  
    std::cout << "is_inside_polygon = " << is_inside_polygon(polygon, point) << std::endl;
      

    return 0;

}