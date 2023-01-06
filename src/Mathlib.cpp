#include <iostream>
#include "Mathlib.hpp"

void Angle::StayInRange(){
    if(radian > PI * 2) { radian -= PI * 2; }
    else if(radian < 0) { radian += PI * 2; }
    if(degree > 360) { degree -= 360; }
    else if(degree < 0) { degree += 360; }
}

Angle::Angle(){
    degree = 0;
    radian = 0;
}

Angle::Angle(float val, bool isRadian){
    if(isRadian){ SetRadian(val); }
    else{ SetDegree(val); }
}

void Angle::SetDegree(float val){
    degree = val;
    radian = val * PI / 180.f;
    if(in_range){ StayInRange(); }
}

void Angle::SetRadian(float val){
    radian = val;
    degree = val * 180.f / PI;
    if(in_range){ StayInRange(); }
}

float Angle::GetDegree(){ 
    return degree; 
}

float Angle::GetRadian(){ 
    return radian; 
}

Vec2::Vec2 () : x(0), y(0) {}                                     //Default: Set vector to (0,0)

Vec2::Vec2 (float x, float y) : x(x), y(y) {}                     //Create vector with given X & Y

Vec2::Vec2 (Angle *angle) 
: x(cos(angle->GetRadian())), y(sin(angle->GetRadian())) {} //Create unit vector with given angle

Vec2::Vec2 (Angle *angle, float length) 
: x(cos(angle->GetRadian())), y(sin(angle->GetRadian())) {  //Create unit vector with given angle and scale it
    x *= length;
    y *= length;
}

Vec2 Vec2::operator + (Vec2 const &vec){
    return Vec2(vec.x + x, vec.y + y);
}

Vec2 Vec2::operator - (Vec2 const &vec){
    return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator * (float value){
    return Vec2(x * value, y * value);
}

Vec2 Vec2::operator / (float value){
    return Vec2(x / value, y / value);
}

void Vec2::operator += (Vec2 const &vec){
    x += vec.x;
    y += vec.y;
}

void Vec2::operator -= (Vec2 const &vec){
    x -= vec.x;
    y -= vec.y;
}

void Vec2::operator *= (float value){
    x *= value;
    y *= value;
}

void Vec2::operator /= (float value){
    x /= value;
    y /= value;
}

float Vec2::dot(Vec2 const &vec){
    return (x * vec.x + y * vec.y);
}

float Vec2::length(){
    return sqrt(length2());
}

float Vec2::length2(){
    return x * x + y * y;
}

void Vec2::normalize(){
    float l = length();
    x /= l;
    y /= l;
}

sf::Vector2f Vec2::getVector2f(){
    return sf::Vector2f(x,y);
}

void Vec2::Print(){
    std::cout << "[Vec2] x: " << x << " y: " << y << std::endl;
}