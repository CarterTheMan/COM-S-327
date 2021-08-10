#include "candy.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/**
 * The default constructor of candy
 */
candy::candy() {
    name = "N/A";
}

/**
 * The constructor of candy that takes in an string and sets that as the name
 * @param n
 */
candy::candy(string n) {
    name = n;
}

/**
 * The copy constructor of candy. This only copies the name since that is the only thing to copy
 * @param original
 */
candy::candy(const candy& original) {
    name = original.name;
}

/**
 * This returns the name of the candy. It works for all classes, including derived classes
 */
string candy::getName() const {
    return name;
}

/**
 * This sets the name for the candy class
 * @param n
 */
void candy::setName(string n) {
    name = n;
}

//Functions for piece (constructor is in .h file)

/**
 * This is the copy constructor of the pieces class. It provides a deep copy
 */
piece::piece(const piece& original) {
    setName(original.getName());
    candyType = original.candyType;
    price = original.price;
    color = original.color;
    amount = original.amount;
    calories = original.calories;
}

/**
 * This is the operator= for the the pieces class. It sets all the variables equal to the right hand side
 * and returns it
 * @param rhs
 * @return *this
 */
const piece piece::operator=(const piece& rhs) {
    if (this != &rhs) {
        setName(rhs.getName());
        priceType = "piece";
        candyType = rhs.getCandyType();
        price = rhs.getPrice();
        color = rhs.getColor();
        amount = rhs.getAmount();
        calories = rhs.getCalories();
    }

    return *this;
}

/**
 * This combines two piece classes. It checks to make sure all but the amounts match and if that doesn't
 * happen it adds the amount together and returns a piece that has the new amount and all the
 * original properties
 * @param rhs
 * @return make
 */
piece piece::operator+(piece& rhs) {
    //For when any variable (except amount) doesn't match up it throws out a description of what the error is
    if (getName() != rhs.getName()) {
        cout << "The names " << getName() << " and " << rhs.getName() << " don't match up." << endl;
    } else if (getPrice() != rhs.getPrice()) {
        cout << "There are two " << getName() << "'s and their prices don't match." << endl;
    } else if (getColor() != rhs.getColor()) {
        cout << "There are two " << getName() << "'s and their colors don't match." << endl;
    } else if (getCandyType() != rhs.getCandyType()) {
        cout << "There are two " << getName() << "'s and their candy types don't match." << endl;
    } else if (getCalories() != rhs.getCalories()) {
        cout << "There are two " << getName() << "'s and their calories don't match." << endl;
    }

    //Adds the new amounts together, make a piece out of it and then returns that piece
    float newAmount = getAmount() + rhs.getAmount();
    piece make = piece(getName(), getCandyType(), getPrice(), getColor(), newAmount, getCalories());
    return make;
}

/**
 * This returns the total price for the piece class
 * @return amount * price
 */
float piece::totalPrice() const {
    return amount * price;
}

/**
 * This returns the candy type for the piece class
 * @return candytype
 */
string piece::getCandyType() const {
    return candyType;
}

/**
 * This returns the price for the piece class
 * @return price
 */
float piece::getPrice() const {
    return price;
}

/**
 * This returns the color for the piece class
 * @return color
 */
int piece::getColor() const {
    return color;
}

/**
 * This returns the amount for the piece class
 * @return amount
 */
float piece::getAmount() const {
    return amount;
}

/**
 * This returns the calories for the piece class
 * @return calories
 */
float piece::getCalories() const {
    return calories;
}

/**
 * This prints out the info for the piece class
 * It includes the name of the item, the amount of it in inventory and the total price of that item
 */
void piece::getInfo() const {
    if (totalPrice() < 1) {
        cout.precision(2);
    } else {
        cout.precision(3);
    }
    cout << "Name: " << getName() << " - Amount: " << amount << " pieces - Total Price: $" << totalPrice() << endl;
}

/**
 * This allows the user to set the amount for the pieces class
 * @param amo
 */
void piece::setAmount(float amo) {
    amount = amo;
}

//Functions for pound (constructor is in .h file)

/**
 * This is the copy constructor of the pounds class. It provides a deep copy
 */
pound::pound(const pound& original) {
    setName(original.getName());
    candyType = original.candyType;
    price = original.price;
    color = original.color;
    amount = original.amount;
    calories = original.calories;
}

/**
 * This is the operator= for the the pound class. It sets all the variables equal to the right hand side
 * and returns it
 * @param rhs
 * @return this*
 */
const pound pound::operator=(const pound& rhs) {
    if (this != &rhs) {
        setName(rhs.getName());
        priceType = "pound";
        candyType = rhs.getCandyType();
        price = rhs.getPrice();
        color = rhs.getColor();
        amount = rhs.getAmount();
        calories = rhs.getCalories();
    }

    return *this;
}

/**
 * This combines two pound classes and adds the amounts of each class together
 * @param rhs
 * @return make
 */
pound pound::operator+(pound& rhs) {
    //For when any variable (except amount) doesn't match up it throws out a description of what the error is
    if (getName() != rhs.getName()) {
        cout << "The names " << getName() << " and " << rhs.getName() << " don't match up." << endl;
    } else if (getPrice() != rhs.getPrice()) {
        cout << "There are two " << getName() << " and their prices don't match." << endl;
    } else if (getColor() != rhs.getColor()) {
        cout << "There are two " << getName() << " and their colors don't match." << endl;
    } else if (getCandyType() != rhs.getCandyType()) {
        cout << "There are two " << getName() << " and their candy types don't match." << endl;
    } else if (getCalories() != rhs.getCalories()) {
        cout << "There are two " << getName() << " and their calories don't match." << endl;
    }

    //Adds the new amounts together, make a pound out of it and then returns that pound
    float newAmount = getAmount() + rhs.getAmount();
    pound make = pound(getName(), getCandyType(), getPrice(), getColor(), newAmount, getCalories());
    return make;
}

/**
 * This returns the total price for the pound class
 * @return (amount/16) * price
 */
float pound::totalPrice() const {
    return (amount/16) * price;
}

/**
 * This returns the candy type for the pound class
 * @return candytype
 */
string pound::getCandyType() const {
    return candyType;
}

/**
 * This returns the price for the pound class
 * @return price
 */
float pound::getPrice() const {
    return price;
}

/**
 * This returns the color for the pound class
 * @return color
 */
int pound::getColor() const {
    return color;
}

/**
 * This returns the amount for the pound class
 * @return amount
 */
float pound::getAmount() const {
    return amount;
}

/**
 * This returns the calories for the pound class
 * @return calories
 */
float pound::getCalories() const {
    return calories;
}

/**
 * This prints out the info for the pound class
 * It includes the name of the item, the amount of it in inventory and the total price of that item
 */
void pound::getInfo() const {
    if (totalPrice() < 1) {
        cout.precision(2);
    } else {
        cout.precision(3);
    }
    cout << "Name: " << getName() << " - Amount: " << amount << " ounces - Total Price: $" << totalPrice() << endl;
}

/**
 * This allows the user to set the amount for the pieces class
 * @param amo
 */
void pound::setAmount(float amo) {
    amount = amo;
}
