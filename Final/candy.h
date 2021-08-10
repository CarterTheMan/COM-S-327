#ifndef CANDYH
#define CANDYH
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;

class candy {
    public:
        candy();
        candy(string n);
        candy(const candy& original);

        //All virtual functions that the derived classes need
        virtual float totalPrice() const=0;
        virtual string getCandyType() const=0;
        virtual float getPrice() const=0;
        virtual int getColor() const=0;
        virtual float getAmount() const=0;
        virtual float getCalories() const=0;
        virtual void getInfo() const=0;
        virtual void setAmount(float amo)=0;

        //Get and set for the name
        string getName() const;
        void setName(string n);

    private:
        string name;
};

class piece : public candy {
    public:
        /**
         * This is a constructor for the piece class. It completely makes the candy piece by taking in all variables
         * @param n
         * @param tp
         * @param pri
         * @param col
         * @param amo
         * @param cal
         */
        piece(string n, string tp, float pri, int col, float amo, float cal) : candy(n) {
            priceType = "piece";
            candyType = tp;
            price = pri;
            color = col;
            amount = amo;
            calories = cal;
        }

        //This is the copy constructor, operator=, and operator+ for the piece class
        //Since this class doesn't need to allocate memory for anything, there is no need for a special
        //destructor. The default one will work so it doesn't need to be defined
        piece(const piece& original);
        const piece operator=(const piece& rhs);
        piece operator+(piece& rhs);

        //All get and set functions for the piece class
        float totalPrice() const;
        string getCandyType() const;
        float getPrice() const;
        int getColor() const;
        float getAmount() const;
        float getCalories() const;
        void getInfo() const;
        void setAmount(float amo);

    private:
        string candyType;
        string priceType;
        float price;
        int color;
        float amount;       //num of pieces
        float calories;     //calories per piece
};

class pound : public candy {
    public:
        /**
         * This is a constructor for the pound class. It completely makes the candy piece by taking in all variables
         * @param n
         * @param tp
         * @param pri
         * @param col
         * @param amo
         * @param cal
         */
        pound(string n, string tp, float pri, int col, float amo, float cal) : candy(n) {
            priceType = "pound";
            candyType = tp;
            price = pri;
            color = col;
            amount = amo;
            calories = cal;
        }

        //This is the copy constructor, operator=, and operator+ for the piece class
        //Since this class doesn't need to allocate memory for anything, there is no need for a special
        //destructor. The default one will work so it doesn't need to be defined
        pound(const pound& original);
        const pound operator=(const pound& rhs);
        pound operator+(pound& rhs);

        //All get and set functions for the piece class
        float totalPrice() const;
        string getCandyType() const;
        float getPrice() const;
        int getColor() const;
        float getAmount() const;
        float getCalories() const;
        void getInfo() const;
        void setAmount(float amo);

    private:
        string candyType;
        string priceType;
        float price;
        int color;
        float amount;       //how many ounces
        float calories;     //calories per pound (16 ounces per pound)
};


#endif
