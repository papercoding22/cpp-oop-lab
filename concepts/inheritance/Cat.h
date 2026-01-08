/**
 * @file Cat.h
 * @brief Declaration of Cat class
 */

#ifndef CAT_H
#define CAT_H

#include "Animal.h"

using namespace std;

/**
 * @class Cat
 * @brief TODO: Add class description
 */
class Cat : public Animal
{
public:
    /**
     * @brief Constructor
     */
    Cat();

    Cat(const string &name, int age, bool isIndoor, int clawSharpness);

    /**
     * @brief Destructor
     */
    virtual ~Cat();

    bool getIsIndoor() const;
    void setIsIndoor(bool isIndoor);

    int getClawSharpness() const;
    void setClawSharpness(int sharpness);

    virtual void makeSound() const override;
    virtual void describe() const override;

    void scratch() const;

    void climb() const;

protected:
private:
    bool isIndoor;     ///< Indicates if the cat is an indoor cat
    int clawSharpness; ///< Sharpness level of the cat's claws
};

#endif // CAT_H
