#pragma once

#include <cmath>
#include <vector>
#include <string>
#include "SDL.h"

// Note : 
// -rm for right member
// -i use rotation in degrees

namespace Struct {

	//Vector2 with lot of function and operators for easy use | Int version if needed for integral coordinates
	struct Vector2
	{
		float x;
		float y;

		static const Vector2 zero;
		static const Vector2 one;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 right;
		static const Vector2 left;

		Vector2() = default;
		inline Vector2(float x_, float y_) : x( x_ ), y( y_ ) {}
		inline Vector2(int x_, int y_) : x( (float)x_ ), y( (float)y_ ) {}

		//Addition
		inline Vector2 operator+(const Vector2& rm) const			{ return { x + rm.x, y + rm.y }; };
		inline Vector2& operator+=(const Vector2& rm)				{ x += rm.x; y += rm.y; return *this; };

		//Substraction
		inline Vector2 operator-(const Vector2& rm) const			{ return { x - rm.x, y - rm.y }; };
		inline Vector2& operator-=(const Vector2& rm)				{ x -= rm.x; y -= rm.y; return *this; };

		//Negation
		inline Vector2 operator-() const							{ return { -x, -y }; };

		//Scale Up
		inline Vector2 operator*(const float& rm) const				{ return { x * rm, y * rm }; };
		inline Vector2& operator*=(const float& rm)					{ x *= rm; y *= rm; return *this; };
		inline Vector2 operator*(const int& rm) const				{ return { x * rm, y * rm }; };
		inline Vector2& operator*=(const int& rm)					{ x *= rm; y *= rm; return *this; };

		//Scale Down
		inline Vector2 operator/(const float& rm) const				{ return { x / rm, y / rm }; };
		inline Vector2& operator/=(const float& rm)					{ x /= rm; y /= rm; return *this; };
		inline Vector2 operator/(const int& rm) const				{ return { x / rm, y / rm }; };
		inline Vector2& operator/=(const int& rm)					{ x /= rm; y /= rm; return *this; };

		//Multiplication
		inline Vector2 operator*(const Vector2& rm) const			{ return { x * rm.x, y * rm.y }; };
		inline Vector2& operator*=(const Vector2& rm)				{ x *= rm.x; y *= rm.y; return *this; };

		//Division
		inline Vector2 operator/(const Vector2& rm) const			{ return { x / rm.x, y / rm.y }; };
		inline Vector2& operator/=(const Vector2& rm)				{ x /= rm.x; y /= rm.y; return *this; };

		//Boolean
		bool operator==(const Vector2& rm) const;
		inline bool operator!=(const Vector2& rm) const				{ return !(*this == rm); };
		bool operator<(const Vector2& rm) const;
		inline bool operator>(const Vector2& rm) const				{ return (rm < *this); };

		//Dot Product
		inline float dot(const Vector2& other) const				{ return x * other.x + y * other.y; };

		//Rotation from Vect2F
		float getRot() const;

		//Perpendicular ClockWise or CounterClockWise 
		inline Vector2 PerpendicularCCW() const						{ return { -y, x }; };
		inline Vector2 PerpendicularCW() const						{ return { y, -x }; };

		//Squared Length and Length
		inline float sqrLength() const								{ return x * x + y * y; };
		float length() const;

		Vector2 normalized() const;
		void normalize();
		void clamp(float min, float max);

		inline std::string toString() const							{ return " x : " + std::to_string(x) + " | y : " + std::to_string(y); };
	};

	struct Transform2D
	{
		Vector2 position;
		Vector2 scale;
		float rotation;

		Transform2D(Vector2 pos = Vector2::zero, Vector2 pScale = Vector2::one, float rot = 0.0f) :
			position(pos), scale(pScale), rotation(rot)
		{
		};

		Vector2 Up() const;
		Vector2 Right() const;

		static const Transform2D one;
	};

	//Oriented Rectangle struct with Collision | origin is the center
	struct Rectangle
	{
		Vector2 center;
		Vector2 halfSize;
		float rotation;

		static const Rectangle Null;

		bool operator==(const Rectangle& rm) const { return center == rm.center && halfSize == rm.halfSize && rotation == rm.rotation; };
		bool operator!=(const Rectangle& rm) const { return !(*this == rm); };

		std::vector<Vector2> getCorners() const;

		//Collision
		Vector2 CheckAABB(const Rectangle& other) const;	// ignore rot
		Vector2 CheckOBB(const Rectangle& other) const;

		bool ContainPoint(const Vector2& point) const;	// ignore rot

		inline Rectangle toObjectSpace(const Transform2D& transform) const { return { transform.position + center, transform.scale * halfSize, transform.rotation + rotation }; };

		inline SDL_Rect toSdlRect() const { return { (int)(center.x - halfSize.x), (int)(center.y - halfSize.y), (int)halfSize.x * 2, (int)halfSize.y * 2 }; } // ignore rotation
	};

	struct Color
	{
		unsigned short r, g, b, a;

		static const Color WHITE;
		static const Color BLACK;
	};

	float OverlapOnAxis(const std::vector<Vector2>& a, const std::vector<Vector2>& b, Vector2 axis);

	inline Vector2 Vect2FLerp(Vector2 a, Vector2 b, float t);

	Vector2 Vector2FromRot(float rot);
}