#include <iostream>
#include <stdexcept>

class Fraction
{

public:
    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::runtime_error("The denominator cannot be equal to 0");
        }
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

        
private:
    int numerator;
    int denominator;
};

int main()
{
    
    try {
        int num, den;
        std::cout << "Enter the numerator and denominator:";
        if (!(std::cin >> num >> den)) {
            throw std::runtime_error("Data entry error");
        }
        
        Fraction frac(num, den);
        std::cout << "Fraction created: " << frac.getNumerator() << "/" << frac.getDenominator() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Incorrect data: " << e.what() << '\n';
    }
    
    return 0;
}
