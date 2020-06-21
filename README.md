# CCTech-June-2020-Software-Developer-Hiring-Challenge

## Question 1

### Algorithm
* From the point whose inclusion has to be checked, a horizontal ray is generated to the left.
* For all the non-horizontal edges of the polygon, we check whether the ray intersects the edge at a point other than its upper point.
* If the number of intersection is odd, the point lies inside the polygon. Otherwise it is outside the polygon.

## Question 2

### Algorithm

* For all sides of the buildings, check whether the side and the source make a right/left trun. If 2xArea(delABSO) is positive, then it is a left turn. If negative, then right turn. 
* If it is a left turn, the side of the building is not exposed.
* If it is a right turn, then we check if it is exposed or blocked by other buildings
  * we check if there are any other building corners inside the triangle formed by a building side and the source.
    * If yes, then we check if the side starting with this building corner makes a right turn with the source.
      * If yes, then we see where line joing this building corner and source intersects the building side. The building is exposed only till this intersection point.
      * If no, then this side of the building is not exposed.
    * If no, then the entire side is exposed.