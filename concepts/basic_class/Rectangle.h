/**
 * @file Rectangle.h
 * @brief Declaration of Rectangle class
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H


/**
 * @class Rectangle
 * @brief Represents a rectangle with width and height
 */
class Rectangle {
public:
    /**
     * @brief Default constructor
     */
    Rectangle();

    /**
     * @brief Parameterized constructor
     * @param w Width of the rectangle
     * @param h Height of the rectangle
     */
    Rectangle(double w, double h);

    /**
     * @brief Destructor
     */
    ~Rectangle();

    /**
     * @brief Set the width of the rectangle
     * @param w Width value
     */
    void setWidth(double w);

    /**
     * @brief Set the height of the rectangle
     * @param h Height value
     */
    void setHeight(double h);

    /**
     * @brief Get the width of the rectangle
     * @return Width value
     */
    double getWidth() const;

    /**
     * @brief Get the height of the rectangle
     * @return Height value
     */
    double getHeight() const;

    /**
     * @brief Calculate the area of the rectangle
     * @return Area (width * height)
     */
    double area() const;

    /**
     * @brief Calculate the perimeter of the rectangle
     * @return Perimeter (2 * (width + height))
     */
    double perimeter() const;

    /**
     * @brief Display rectangle information
     */
    void display() const;

protected:
    // No protected members in this example

private:
    double width;   ///< Width of the rectangle
    double height;  ///< Height of the rectangle
};

#endif // RECTANGLE_H
