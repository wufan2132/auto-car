#include "planning/common.h"
#include "planning/car_model.h"


class TrajectoryCost_conf{
public:
    double k_smooth;
};


class TrajectoryCost{
public:
    TrajectoryCost(YAML::Node yaml_conf);
    void reset();
    double evaluate();
    TrajectoryCost_conf* conf;
private:
    double smoothcost();    
};
