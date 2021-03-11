//first version of class creature (prototype
//2021/1/18

#ifndef CREATURE_H
#define CREATURE_H

#include <complex>

class Creature {
public:
        virtual double getspeed() = 0;//every species has its own random speed
        virtual void energyloss(double) = 0;//how we define the energy loss, using speed or else?
        virtual bool ishungry() = 0;
        virtual ~Creature();
        std::complex<double> getLoc();
        std::complex<double> getVel();
        double getprobability();
        double getenergy();
        void setLoc(std::complex<double>);
        void setLoc(double, double);
        void setVel(std::complex<double>);
        void setVel(double, double);
        double energy;
        double coordinatex;
        double coordinatey;
        std::complex<double> loc, vel;
        double probability;
       //double life_span() whether we build in class or realize it by calculating on energy
};
#endif // CREATURE_H
