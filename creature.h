//first version of class creature (prototype
//2021/1/18

#ifndef CREATURE_H
#define CREATURE_H

class Creature {
public:
        virtual double getspeed() = 0;//every species has its own random speed
        virtual void energyloss(double) = 0;//how we define the energy loss, using speed or else?
        virtual bool ishungry() = 0;
        double getenergy();
        double displayx();
        double displayy();
protected:
        double speed;
        double energy;
        double coordinatex;
        double coordinatey;
        bool hungry;
       //double life_span() whether we build in class or realize it by calculating on energy
};
#endif // CREATURE_H
