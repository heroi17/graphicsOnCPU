#ifndef _GMATH_H_
#define _GMATH_H_
#include <math.h>
#define PI 3.141592653589793
#define CUT_UP(number, maximum) ((number) > (maximum) ? (maximum) : (number))
namespace gMathLib
{



	template <typename TYPE>
	struct Rectangle
	{
		TYPE x_ = 0;
		TYPE y_ = 0;
		TYPE width_ = 0;
		TYPE height_ = 0;

		Rectangle(TYPE x, TYPE y, TYPE width, TYPE height) : x_(x), y_(y), width_(width), height_(height) {}

		Rectangle<TYPE> intersect(const Rectangle<TYPE>&);

		bool isIntersect(const Rectangle<TYPE>&);

		void print();
	};



	template <typename TYPE>
	struct Vector2D
	{
		TYPE x_ = 0;
		TYPE y_ = 0;


		Vector2D(TYPE x, TYPE y) : x_(x), y_(y) {};

		template <typename classCopy>
		Vector2D(const Vector2D<classCopy>&);

		Vector2D<TYPE> operator+(const Vector2D& other);

		Vector2D<TYPE> operator-(const Vector2D& other);

		template <typename TYPEKOEF>
		Vector2D<TYPE> operator*(const TYPEKOEF& koef) const;

		void normalize();

		double getLength();

		bool isNotZero();

		void print();

	};

	template<typename TYPE>
	inline Vector2D<TYPE> Vector2D<TYPE>::operator+(const Vector2D& other)
	{

		return Vector2D(this->x_ + other.x_, this->y_ + other.y_);
	}

	template<typename TYPE>
	inline Vector2D<TYPE> Vector2D<TYPE>::operator-(const Vector2D& other)
	{
		return Vector2D<TYPE>(this->x_ - other.x_, this->y_ - other.y_);
	}

	template<typename TYPE> template <typename TYPEKOEF>
	inline Vector2D<TYPE> Vector2D<TYPE>::operator*(const TYPEKOEF& koef) const
	{
		return Vector2D<TYPE>(this->x_*koef, this->y_*koef);
	}

	template<typename TYPE>
	inline void Vector2D<TYPE>::normalize()
	{
		double size = this->getLength();
		if (!this->isNotZero())
		{
			this->x_ = 1.;
			this->y_ = 0.;
			return;
		}
		this->x_ /= size;
		this->y_ /= size;
	}

	template<typename TYPE>
	inline double Vector2D<TYPE>::getLength()
	{
		return sqrt((x_ * x_) + (y_ * y_));
	}

	template<typename TYPE>
	inline bool Vector2D<TYPE>::isNotZero()
	{
		double size = this->getLength();
		return (size!=0);
	}

	template<typename TYPE>
	inline void Vector2D<TYPE>::print()
	{
		std::cout << "(" << this->x_ << ", " << this->y_ << ")";
	}

	template<typename TYPE>
	template<typename classCopy>
	inline Vector2D<TYPE>::Vector2D(const Vector2D<classCopy>& vectorCopy)
	{
		this->x_ = (TYPE)(vectorCopy.x_);
		this->y_ = (TYPE)(vectorCopy.y_);
	}



	template<typename TYPE>
	inline Rectangle<TYPE> Rectangle<TYPE>::intersect(const Rectangle<TYPE>& other)
	{
		TYPE x = other.x_ > this->x_ ? other.x_ : this->x_;
		TYPE y = other.y_ > this->y_ ? other.y_ : this->y_;
		TYPE x_end = other.x_ + other.width_ < this->x_ + this->width_ ? other.x_ + other.width_ : this->x_ + this->width_;
		TYPE y_end = other.y_ + other.height_ < this->y_ + this->height_ ? other.y_ + other.height_ : this->y_ + this->height_;
		if (x > x_end or y > y_end)
			return Rectangle<TYPE>(x, y, 0, 0);
		return Rectangle<TYPE>(x, y, x_end - x, y_end - y);
	}

	template<typename TYPE>
	inline bool Rectangle<TYPE>::isIntersect(const Rectangle<TYPE>& other)
	{
		TYPE x = other.x_ > this->x_ ? other.x_ : this->x_;
		TYPE y = other.y_ > this->y_ ? other.y_ : this->y_;
		TYPE x_end = other.x_ + other.width_ < this->x_ + this->width_ ? other.x_ + other.width_ : this->x_ + this->width_;
		TYPE y_end = other.y_ + other.height_ < this->y_ + this->height_ ? other.y_ + other.height_ : this->y_ + this->height_;
		if (x > x_end or y > y_end)
			return false;
		return true;
	}

	template<typename TYPE>
	inline void Rectangle<TYPE>::print()
	{
		std::cout << "(" << x_ << " " << y_ << ", " << width_ << " " << height_ << ")";
	}


	template <typename TYPE>
	inline Vector2D<TYPE> rotateLeft(const Vector2D<TYPE>& vec, double angleRadian)
	{
		Vector2D<double>	convertedVec = Vector2D<double>(0, 0);
		float cosA = cos(angleRadian);
		float sinA = sin(angleRadian);
		convertedVec.x_ = vec.x_ * cosA - vec.y_ * sinA;
		convertedVec.y_ = vec.x_ * sinA + vec.y_ * cosA;
		return convertedVec;
	}

	template <typename TYPE>
	float VectorAngle(const Vector2D<TYPE>& a, const Vector2D<TYPE>& b)
	{
		return atan2f(b.x_ - a.x_, b.y_ - a.y_);
	}


}


#endif // !_GMATH_H_
