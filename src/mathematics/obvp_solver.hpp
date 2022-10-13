#include <Eigen/Core>

using namespace std;

class OBVPSovler
{
public:
    OBVPSovler();
    ~OBVPSovler();
    void pontryagin();
private:
    Eigen::Vector3d state_init_;
    Eigen::Vector3d vector_constant_;
    void calConstant(Eigen::Vector3d state_init, Eigen::Vector3d state_final, double );
    Eigen::Vector3d getOptimalState(double time);
};

OBVPSovler::OBVPSovler() {};

OBVPSovler::~OBVPSovler() {};


void OBVPSovler::pontryagin(Eigen::Vector3d &state_init, Eigen::Vector3d &state_final) {
    calConstant(Eigen::Vector3d &state_init, Eigen::Vector3d &state_final);
}

void OBVPSovler::calConstant(Eigen::Vector3d &state_init, Eigen::Vector3d &state_final) {
    Eigen::Vector3d delta_state = state_init - state_final;
    Eigen::Matrix3d matrix_temp;
    matrix_temp << 720, -360*delta_time, 60*pow(delta_time, 2),
                -360*delta_time, 168*pow(delta_time, 2), -24*pow(delta_time, 3),
                60*pow(delta_time, 2), -24*pow(delta_time, 3), 3*pow(delta_time, 4);

    vector_constant_ = (1/pow(delta_time, 5)) * matrix_temp * delta_state;
}

Eigen::Vector3d getOptimalState(double time) {
    double p = vector_constant_[0]/120*pow(time,5) + vector_constant_[1]/24*pow(time,4) + vector_constant_[2]/6*pow(time,3) + state_init_[2]/2*pow(time,2) + state_init_[1]*time + state_init_[0];
    double v = vector_constant_[0]/24*pow(time,4) + vector_constant_[1]/6*pow(time,3) + vector_constant_[2]/2*time + state_init_[1];
    double a = vector_constant_[0]/6*pow(time,3) + vector_constant_[1]/2*pow(time,2) + vector_constant_[2]*time + state_init_[2];
    Eigen::Vector3d state_optimal;
    state_optimal << p, a, v;
    return state_optimal;
}