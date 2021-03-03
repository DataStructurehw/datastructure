//first version of class creature (prototype
//2021/1/18

#ifndef CREATURE_H
#define CREATURE_H

#include <complex>

class Creature {
public:
        double getspeed();//every species has its own random speed
        virtual void energyloss(double) = 0;//how we define the energy loss, using speed or else?
        virtual bool ishungry() = 0;
        double getprobability();
        double getenergy();
        std::complex<double> getLoc();
        std::complex<double> getVel();
        void setLoc(std::complex<double>);
        void setLoc(double, double);
        void setVel(std::complex<double>);
        void setVel(double, double);

protected:
        double energy;
        bool hungry;
        std::complex<double> loc, vel; // location, velocity
        double probability;//probability of dying
       //double life_span() whether we build in class or realize it by calculating on energy
};
#endif // CREATURE_H
