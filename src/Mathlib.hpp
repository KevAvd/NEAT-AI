#pragma once
#include <SFML/Graphics.hpp>

#define PI 3.14159265359f

class Angle{
private:
    float radian, degree;   //Store angle value in radian and degree
    void StayInRange();     //Make both radian and degree stay in range (0-2PI)(0-360)
public:
    bool in_range;          //Indicate if the angle must be in range
    Angle();
    Angle(float val, bool isRadian = false);
    void SetDegree(float val);
    void SetRadian(float val);
    float GetDegree();
    float GetRadian();
};

struct Vec2 
{ 
    float x, y;                         // X & Y components of the vector
    Vec2 ();                            //Default: Set vector to (0,0)
    Vec2 (float x, float y);            //Create vector with given X & Y
    Vec2 (Angle *angle);                //Create unit vector with given angle
    Vec2 (Angle *angle, float length);  //Create unit vector with given angle and scales it
    Vec2 operator + (Vec2 const &vec);  //Vector addition
    Vec2 operator - (Vec2 const &vec);  //Vector substraction
    Vec2 operator * (float value);      //Vector multiplication
    Vec2 operator / (float value);      //Vector division
    void operator += (Vec2 const &vec); //Vector addition
    void operator -= (Vec2 const &vec); //Vector substraction
    void operator *= (float value);     //Vector multiplication
    void operator /= (float value);     //Vector division
    float dot(Vec2 const &vec);         //Compute the dot product
    float length();                     //Compute the vector length
    float length2();                    //Compute the vector length squared
    void normalize();                   //Normalize the vector
    sf::Vector2f getVector2f();         //Get the SFML version of this vector
    void Print();                       //Print vector value to console
};
