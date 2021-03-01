//first version of class creature (prototype
//2021/1/18

#ifndef CREATURE_H
#define CREATURE_H

class Creature {
public:
        double getspeed();//every species has its own random speed
        virtual void energyloss(double) = 0;//how we define the energy loss, using speed or else?
        virtual bool ishungry() = 0;
        double getprobability();
        double getenergy();
        double displayx();
        double displayy();
        double displaytx();
        double displayty();
        void setcoordinate(double, double);
        void setdirection(double, double);
        void setspeed(double);

protected:
        double speed;
        double energy;
        double coordinatex;
        double coordinatey;
        bool hungry;
        double tx;
        double ty;
        double probability;//probability of dying
       //double life_span() whether we build in class or realize it by calculating on energy
};
#endif // CREATURE_H
