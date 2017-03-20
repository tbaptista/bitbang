//
//  Steering.h
//  AircraftEvacuation
//
//  Created by João Simões on 19/09/15.
//
//

#ifndef AircraftEvacuation_Steering_h
#define AircraftEvacuation_Steering_h

class Steering
{
public:
    Steering();
    ~Steering();
    
    void SetLinear(float pLinear) { linear = pLinear; };
    void SetAngular(float pAngular) { angular = pAngular; };
    float GetLinear() { return linear; };
    float GetAngular() { return angular; };
    
private:
    float linear;
    float angular;
};

#endif
