#include <iostream>
#include <vector>

class Vehicle
{
public:
    virtual void print(std::ostream& os = std::cout) const = 0;
    virtual ~Vehicle() = default;
};

std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
    v.print(os);
    return os;
}

class WaterVehicle : public Vehicle
{
public:
    float precipitation = 0.f;
    WaterVehicle(float precipitation) : precipitation(precipitation) {}
    
    void print(std::ostream& os = std::cout) const override {
        os << "Precipitation: " << precipitation << "\n";
    }
};

class RoadVehicle : public Vehicle
{
public:
    float ride_height = 0.f;
    RoadVehicle(float ride_height) : ride_height(ride_height) {}
    
    void print(std::ostream& os = std::cout) const override {
        os << "Ride Height: " << ride_height << "\n";
    }
};

class Wheel {
public:
    float diameter;
    Wheel() : diameter(0.0f) {}
    Wheel(float diameter) : diameter(diameter) {}
};

class Engine {
public:
    float power;
    Engine() : power(0.0f) {}
    Engine(float power) : power(power) {}
};

class Bicycle : public RoadVehicle
{
public:
    Wheel wheel1;
    Wheel wheel2;

    Bicycle(const Wheel& w1, const Wheel& w2, float rideHeight)
        : RoadVehicle(rideHeight), wheel1(w1), wheel2(w2) {}

    void print(std::ostream& os = std::cout) const override {
        os << "Bicycle: " << wheel1.diameter << " " << wheel2.diameter << " Ride height: " << ride_height << "\n";
    }
};

class Car : public RoadVehicle {
public:
    Engine engine;
    Wheel wheels[4];
    
    Car(const Engine& engine,
        const Wheel& w1, const Wheel& w2, const Wheel& w3, const Wheel& w4,
        float rideHeight)
        : RoadVehicle(rideHeight), engine(engine)
    {
        wheels[0] = w1;
        wheels[1] = w2;
        wheels[2] = w3;
        wheels[3] = w4;
    }
    
    void print(std::ostream& os = std::cout) const override {
        os << "Car Engine: " << engine.power << " Wheels: ";
        for (int i = 0; i < 4; ++i) {
            os << wheels[i].diameter << (i < 3 ? " " : "");
        }
        os << " Ride height: " << ride_height;
    }
};

class Point {
public:
    float x, y, z;
    Point(float x, float y, float z): x(x), y(y), z(z) {}
};

class Circle : public Vehicle {
public:
    Point center;
    float radius;

    Circle(const Point& center, float radius)
        : center(center), radius(radius) {}

    void print(std::ostream& os = std::cout) const override {
        os << "Circle Center: (" << center.x << ", " << center.y << ", " << center.z
           << ") Radius: " << radius;
    }
};

float getHighestPower(const std::vector<Vehicle*>& vehicles) {
    float highest = 0.0f;
    for (auto v : vehicles) {
        const Car* car = dynamic_cast<const Car*>(v);
        if (car && car->engine.power > highest) {
            highest = car->engine.power;
        }
    }
    return highest;
}

int main()
{
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    std::cout << c << '\n';

    Bicycle t(Wheel(20), Wheel(20), 300);
    std::cout << t << '\n';

    std::vector<Vehicle*> v;
    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000));

    for (auto vehicle : v) {
        std::cout << *vehicle << '\n';
    }

    std::cout << "The highest power is " << getHighestPower(v) << '\n';

    for (auto vehicle : v) {
        delete vehicle;
    }
    v.clear();

    return 0;
}
