#include "MyVector2.h"

// Michael Rapciak


/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(const sf::Vector2f t_vectorA)
{
	float sumOfSquares = (t_vectorA.x * t_vectorA.x ) + (t_vectorA.y * t_vectorA.y);
	const float length = std::sqrt(sumOfSquares);
	return length;
}

/// <summary>
/// get length of vector and square it
/// </summary>
/// <param name="t_vectorA">input vector</param>
/// <returns>length squared</returns>
float vectorLengthSquared(const sf::Vector2f t_vectorA)
{
	float sumOfSquares = (t_vectorA.x * t_vectorA.x) + (t_vectorA.y * t_vectorA.y);
	return sumOfSquares;
}

/// <summary>
/// get cross product of vectors
/// </summary>
/// <param name="t_vectorA">first input vector</param>
/// <param name="t_VectorB">second input vector</param>
/// <returns>the cross product</returns>
float vectorCrossProduct(const sf::Vector2f t_vectorA, const sf::Vector2f t_VectorB)
{
	float crossProduct = ((t_vectorA.x * t_VectorB.y) - (t_vectorA.y * t_VectorB.x));
	return crossProduct;
}

/// <summary>
/// get dot product of vectors
/// </summary>
/// <param name="t_vectorA">first input vector</param>
/// <param name="t_VectorB">second input vector</param>
/// <returns>the dot product</returns>
float vectorDotProduct(const sf::Vector2f t_vectorA, const sf::Vector2f t_VectorB)
{
	float dotProduct = ((t_vectorA.x * t_VectorB.x) + (t_vectorA.y * t_VectorB.y));
	return dotProduct;
}

/// <summary>
/// Get angle between two vectors
/// </summary>
/// <param name="t_vectorA">first input vector</param>
/// <param name="t_VectorB">seond input vector</param>
/// <returns>the angle between the two vectors in degrees</returns>
float vectorAngleBetween(const sf::Vector2f t_vectorA, const sf::Vector2f t_VectorB)
{
	float placeHolder = vectorDotProduct(t_vectorA, t_VectorB) / (vectorLength(t_vectorA) * (vectorLength(t_VectorB)));
	float angleBetween = acos(placeHolder);
	angleBetween = angleBetween * (180 / PI);
	return angleBetween;
}

/// <summary>
/// Rotate vector by angle
/// </summary>
/// <param name="t_vectorA">input vector</param>
/// <param name="t_angleRadians">input angle</param>
/// <returns>vector rotated</returns>
sf::Vector2f vectorRotateBy(const sf::Vector2f t_vectorA, const  float t_angleRadians)
{
	sf::Vector2f answer;
	answer.x = (t_vectorA.x * (cos(t_angleRadians))) - (t_vectorA.y * (sin(t_angleRadians)));
	answer.y = (t_vectorA.x * (sin(t_angleRadians))) + (t_vectorA.y * (cos(t_angleRadians)));
	return answer;
}

/// <summary>
/// project vector a on vector b
/// </summary>
/// <param name="t_vectorA">first input vector</param>
/// <param name="t_onto">second input vector</param>
/// <returns>vector projected onto vector b</returns>
sf::Vector2f vectorProjection(const sf::Vector2f t_vectorA, const  sf::Vector2f t_onto)
{	
	sf::Vector2f answer;
	answer = (vectorDotProduct(t_vectorA, t_onto) / vectorLengthSquared(t_onto)) * t_onto;
	return answer;
}

/// <summary>
/// vector rejection
/// </summary>
/// <param name="t_vectorA">first input vector</param>
/// <param name="t_onto">second input vector</param>
/// <returns>vector rejection</returns>
sf::Vector2f vectorRejection(const sf::Vector2f t_vectorA, const  sf::Vector2f t_onto)
{
	sf::Vector2f answer;
	answer = t_vectorA - ((vectorDotProduct(t_vectorA, t_onto) / vectorLength(t_onto)) * t_onto);
	return answer;
}

/// <summary>
/// Vector scalar projection
/// </summary>
/// <param name="t_vector">first input vector</param>
/// <param name="t_onto">second input vector</param>
/// <returns>vector projected onto vector b</returns>
float vectorScalarProjection(const sf::Vector2f t_vector, const  sf::Vector2f t_onto)
{
	float scalarProjection = vectorDotProduct(t_vector, t_onto) / vectorLength(t_onto);
	return scalarProjection;
}

/// <summary>
/// Unit vector of a vector
/// </summary>
/// <param name="t_vectorA">input vector</param>
/// <returns>unit vector of the vector</returns>
sf::Vector2f vectorUnitVector(const sf::Vector2f t_vectorA)
{
	sf::Vector2f answer;
	answer = (t_vectorA / vectorLength(t_vectorA));
	return answer;
}
