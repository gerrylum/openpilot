#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6689287202068207421) {
   out_6689287202068207421[0] = delta_x[0] + nom_x[0];
   out_6689287202068207421[1] = delta_x[1] + nom_x[1];
   out_6689287202068207421[2] = delta_x[2] + nom_x[2];
   out_6689287202068207421[3] = delta_x[3] + nom_x[3];
   out_6689287202068207421[4] = delta_x[4] + nom_x[4];
   out_6689287202068207421[5] = delta_x[5] + nom_x[5];
   out_6689287202068207421[6] = delta_x[6] + nom_x[6];
   out_6689287202068207421[7] = delta_x[7] + nom_x[7];
   out_6689287202068207421[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6652507941137758454) {
   out_6652507941137758454[0] = -nom_x[0] + true_x[0];
   out_6652507941137758454[1] = -nom_x[1] + true_x[1];
   out_6652507941137758454[2] = -nom_x[2] + true_x[2];
   out_6652507941137758454[3] = -nom_x[3] + true_x[3];
   out_6652507941137758454[4] = -nom_x[4] + true_x[4];
   out_6652507941137758454[5] = -nom_x[5] + true_x[5];
   out_6652507941137758454[6] = -nom_x[6] + true_x[6];
   out_6652507941137758454[7] = -nom_x[7] + true_x[7];
   out_6652507941137758454[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1241686598395299543) {
   out_1241686598395299543[0] = 1.0;
   out_1241686598395299543[1] = 0.0;
   out_1241686598395299543[2] = 0.0;
   out_1241686598395299543[3] = 0.0;
   out_1241686598395299543[4] = 0.0;
   out_1241686598395299543[5] = 0.0;
   out_1241686598395299543[6] = 0.0;
   out_1241686598395299543[7] = 0.0;
   out_1241686598395299543[8] = 0.0;
   out_1241686598395299543[9] = 0.0;
   out_1241686598395299543[10] = 1.0;
   out_1241686598395299543[11] = 0.0;
   out_1241686598395299543[12] = 0.0;
   out_1241686598395299543[13] = 0.0;
   out_1241686598395299543[14] = 0.0;
   out_1241686598395299543[15] = 0.0;
   out_1241686598395299543[16] = 0.0;
   out_1241686598395299543[17] = 0.0;
   out_1241686598395299543[18] = 0.0;
   out_1241686598395299543[19] = 0.0;
   out_1241686598395299543[20] = 1.0;
   out_1241686598395299543[21] = 0.0;
   out_1241686598395299543[22] = 0.0;
   out_1241686598395299543[23] = 0.0;
   out_1241686598395299543[24] = 0.0;
   out_1241686598395299543[25] = 0.0;
   out_1241686598395299543[26] = 0.0;
   out_1241686598395299543[27] = 0.0;
   out_1241686598395299543[28] = 0.0;
   out_1241686598395299543[29] = 0.0;
   out_1241686598395299543[30] = 1.0;
   out_1241686598395299543[31] = 0.0;
   out_1241686598395299543[32] = 0.0;
   out_1241686598395299543[33] = 0.0;
   out_1241686598395299543[34] = 0.0;
   out_1241686598395299543[35] = 0.0;
   out_1241686598395299543[36] = 0.0;
   out_1241686598395299543[37] = 0.0;
   out_1241686598395299543[38] = 0.0;
   out_1241686598395299543[39] = 0.0;
   out_1241686598395299543[40] = 1.0;
   out_1241686598395299543[41] = 0.0;
   out_1241686598395299543[42] = 0.0;
   out_1241686598395299543[43] = 0.0;
   out_1241686598395299543[44] = 0.0;
   out_1241686598395299543[45] = 0.0;
   out_1241686598395299543[46] = 0.0;
   out_1241686598395299543[47] = 0.0;
   out_1241686598395299543[48] = 0.0;
   out_1241686598395299543[49] = 0.0;
   out_1241686598395299543[50] = 1.0;
   out_1241686598395299543[51] = 0.0;
   out_1241686598395299543[52] = 0.0;
   out_1241686598395299543[53] = 0.0;
   out_1241686598395299543[54] = 0.0;
   out_1241686598395299543[55] = 0.0;
   out_1241686598395299543[56] = 0.0;
   out_1241686598395299543[57] = 0.0;
   out_1241686598395299543[58] = 0.0;
   out_1241686598395299543[59] = 0.0;
   out_1241686598395299543[60] = 1.0;
   out_1241686598395299543[61] = 0.0;
   out_1241686598395299543[62] = 0.0;
   out_1241686598395299543[63] = 0.0;
   out_1241686598395299543[64] = 0.0;
   out_1241686598395299543[65] = 0.0;
   out_1241686598395299543[66] = 0.0;
   out_1241686598395299543[67] = 0.0;
   out_1241686598395299543[68] = 0.0;
   out_1241686598395299543[69] = 0.0;
   out_1241686598395299543[70] = 1.0;
   out_1241686598395299543[71] = 0.0;
   out_1241686598395299543[72] = 0.0;
   out_1241686598395299543[73] = 0.0;
   out_1241686598395299543[74] = 0.0;
   out_1241686598395299543[75] = 0.0;
   out_1241686598395299543[76] = 0.0;
   out_1241686598395299543[77] = 0.0;
   out_1241686598395299543[78] = 0.0;
   out_1241686598395299543[79] = 0.0;
   out_1241686598395299543[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1969896210282524456) {
   out_1969896210282524456[0] = state[0];
   out_1969896210282524456[1] = state[1];
   out_1969896210282524456[2] = state[2];
   out_1969896210282524456[3] = state[3];
   out_1969896210282524456[4] = state[4];
   out_1969896210282524456[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1969896210282524456[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1969896210282524456[7] = state[7];
   out_1969896210282524456[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3055228452963269409) {
   out_3055228452963269409[0] = 1;
   out_3055228452963269409[1] = 0;
   out_3055228452963269409[2] = 0;
   out_3055228452963269409[3] = 0;
   out_3055228452963269409[4] = 0;
   out_3055228452963269409[5] = 0;
   out_3055228452963269409[6] = 0;
   out_3055228452963269409[7] = 0;
   out_3055228452963269409[8] = 0;
   out_3055228452963269409[9] = 0;
   out_3055228452963269409[10] = 1;
   out_3055228452963269409[11] = 0;
   out_3055228452963269409[12] = 0;
   out_3055228452963269409[13] = 0;
   out_3055228452963269409[14] = 0;
   out_3055228452963269409[15] = 0;
   out_3055228452963269409[16] = 0;
   out_3055228452963269409[17] = 0;
   out_3055228452963269409[18] = 0;
   out_3055228452963269409[19] = 0;
   out_3055228452963269409[20] = 1;
   out_3055228452963269409[21] = 0;
   out_3055228452963269409[22] = 0;
   out_3055228452963269409[23] = 0;
   out_3055228452963269409[24] = 0;
   out_3055228452963269409[25] = 0;
   out_3055228452963269409[26] = 0;
   out_3055228452963269409[27] = 0;
   out_3055228452963269409[28] = 0;
   out_3055228452963269409[29] = 0;
   out_3055228452963269409[30] = 1;
   out_3055228452963269409[31] = 0;
   out_3055228452963269409[32] = 0;
   out_3055228452963269409[33] = 0;
   out_3055228452963269409[34] = 0;
   out_3055228452963269409[35] = 0;
   out_3055228452963269409[36] = 0;
   out_3055228452963269409[37] = 0;
   out_3055228452963269409[38] = 0;
   out_3055228452963269409[39] = 0;
   out_3055228452963269409[40] = 1;
   out_3055228452963269409[41] = 0;
   out_3055228452963269409[42] = 0;
   out_3055228452963269409[43] = 0;
   out_3055228452963269409[44] = 0;
   out_3055228452963269409[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3055228452963269409[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3055228452963269409[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3055228452963269409[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3055228452963269409[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3055228452963269409[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3055228452963269409[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3055228452963269409[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3055228452963269409[53] = -9.8100000000000005*dt;
   out_3055228452963269409[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3055228452963269409[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3055228452963269409[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3055228452963269409[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3055228452963269409[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3055228452963269409[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3055228452963269409[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3055228452963269409[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3055228452963269409[62] = 0;
   out_3055228452963269409[63] = 0;
   out_3055228452963269409[64] = 0;
   out_3055228452963269409[65] = 0;
   out_3055228452963269409[66] = 0;
   out_3055228452963269409[67] = 0;
   out_3055228452963269409[68] = 0;
   out_3055228452963269409[69] = 0;
   out_3055228452963269409[70] = 1;
   out_3055228452963269409[71] = 0;
   out_3055228452963269409[72] = 0;
   out_3055228452963269409[73] = 0;
   out_3055228452963269409[74] = 0;
   out_3055228452963269409[75] = 0;
   out_3055228452963269409[76] = 0;
   out_3055228452963269409[77] = 0;
   out_3055228452963269409[78] = 0;
   out_3055228452963269409[79] = 0;
   out_3055228452963269409[80] = 1;
}
void h_25(double *state, double *unused, double *out_3733191017237306096) {
   out_3733191017237306096[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6036517441323168652) {
   out_6036517441323168652[0] = 0;
   out_6036517441323168652[1] = 0;
   out_6036517441323168652[2] = 0;
   out_6036517441323168652[3] = 0;
   out_6036517441323168652[4] = 0;
   out_6036517441323168652[5] = 0;
   out_6036517441323168652[6] = 1;
   out_6036517441323168652[7] = 0;
   out_6036517441323168652[8] = 0;
}
void h_24(double *state, double *unused, double *out_4323419187172556926) {
   out_4323419187172556926[0] = state[4];
   out_4323419187172556926[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8209167040328668218) {
   out_8209167040328668218[0] = 0;
   out_8209167040328668218[1] = 0;
   out_8209167040328668218[2] = 0;
   out_8209167040328668218[3] = 0;
   out_8209167040328668218[4] = 1;
   out_8209167040328668218[5] = 0;
   out_8209167040328668218[6] = 0;
   out_8209167040328668218[7] = 0;
   out_8209167040328668218[8] = 0;
   out_8209167040328668218[9] = 0;
   out_8209167040328668218[10] = 0;
   out_8209167040328668218[11] = 0;
   out_8209167040328668218[12] = 0;
   out_8209167040328668218[13] = 0;
   out_8209167040328668218[14] = 1;
   out_8209167040328668218[15] = 0;
   out_8209167040328668218[16] = 0;
   out_8209167040328668218[17] = 0;
}
void h_30(double *state, double *unused, double *out_2854636909238989067) {
   out_2854636909238989067[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3518184482815920025) {
   out_3518184482815920025[0] = 0;
   out_3518184482815920025[1] = 0;
   out_3518184482815920025[2] = 0;
   out_3518184482815920025[3] = 0;
   out_3518184482815920025[4] = 1;
   out_3518184482815920025[5] = 0;
   out_3518184482815920025[6] = 0;
   out_3518184482815920025[7] = 0;
   out_3518184482815920025[8] = 0;
}
void h_26(double *state, double *unused, double *out_1767549120217119247) {
   out_1767549120217119247[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8668723313512326740) {
   out_8668723313512326740[0] = 0;
   out_8668723313512326740[1] = 0;
   out_8668723313512326740[2] = 0;
   out_8668723313512326740[3] = 0;
   out_8668723313512326740[4] = 0;
   out_8668723313512326740[5] = 0;
   out_8668723313512326740[6] = 0;
   out_8668723313512326740[7] = 1;
   out_8668723313512326740[8] = 0;
}
void h_27(double *state, double *unused, double *out_8457728334513198266) {
   out_8457728334513198266[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5692947794616344936) {
   out_5692947794616344936[0] = 0;
   out_5692947794616344936[1] = 0;
   out_5692947794616344936[2] = 0;
   out_5692947794616344936[3] = 1;
   out_5692947794616344936[4] = 0;
   out_5692947794616344936[5] = 0;
   out_5692947794616344936[6] = 0;
   out_5692947794616344936[7] = 0;
   out_5692947794616344936[8] = 0;
}
void h_29(double *state, double *unused, double *out_2107743088442304165) {
   out_2107743088442304165[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3007953138501527841) {
   out_3007953138501527841[0] = 0;
   out_3007953138501527841[1] = 1;
   out_3007953138501527841[2] = 0;
   out_3007953138501527841[3] = 0;
   out_3007953138501527841[4] = 0;
   out_3007953138501527841[5] = 0;
   out_3007953138501527841[6] = 0;
   out_3007953138501527841[7] = 0;
   out_3007953138501527841[8] = 0;
}
void h_28(double *state, double *unused, double *out_4073384985462491014) {
   out_4073384985462491014[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8090352155571058415) {
   out_8090352155571058415[0] = 1;
   out_8090352155571058415[1] = 0;
   out_8090352155571058415[2] = 0;
   out_8090352155571058415[3] = 0;
   out_8090352155571058415[4] = 0;
   out_8090352155571058415[5] = 0;
   out_8090352155571058415[6] = 0;
   out_8090352155571058415[7] = 0;
   out_8090352155571058415[8] = 0;
}
void h_31(double *state, double *unused, double *out_4906686459481235788) {
   out_4906686459481235788[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8042515211278975264) {
   out_8042515211278975264[0] = 0;
   out_8042515211278975264[1] = 0;
   out_8042515211278975264[2] = 0;
   out_8042515211278975264[3] = 0;
   out_8042515211278975264[4] = 0;
   out_8042515211278975264[5] = 0;
   out_8042515211278975264[6] = 0;
   out_8042515211278975264[7] = 0;
   out_8042515211278975264[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_6689287202068207421) {
  err_fun(nom_x, delta_x, out_6689287202068207421);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6652507941137758454) {
  inv_err_fun(nom_x, true_x, out_6652507941137758454);
}
void car_H_mod_fun(double *state, double *out_1241686598395299543) {
  H_mod_fun(state, out_1241686598395299543);
}
void car_f_fun(double *state, double dt, double *out_1969896210282524456) {
  f_fun(state,  dt, out_1969896210282524456);
}
void car_F_fun(double *state, double dt, double *out_3055228452963269409) {
  F_fun(state,  dt, out_3055228452963269409);
}
void car_h_25(double *state, double *unused, double *out_3733191017237306096) {
  h_25(state, unused, out_3733191017237306096);
}
void car_H_25(double *state, double *unused, double *out_6036517441323168652) {
  H_25(state, unused, out_6036517441323168652);
}
void car_h_24(double *state, double *unused, double *out_4323419187172556926) {
  h_24(state, unused, out_4323419187172556926);
}
void car_H_24(double *state, double *unused, double *out_8209167040328668218) {
  H_24(state, unused, out_8209167040328668218);
}
void car_h_30(double *state, double *unused, double *out_2854636909238989067) {
  h_30(state, unused, out_2854636909238989067);
}
void car_H_30(double *state, double *unused, double *out_3518184482815920025) {
  H_30(state, unused, out_3518184482815920025);
}
void car_h_26(double *state, double *unused, double *out_1767549120217119247) {
  h_26(state, unused, out_1767549120217119247);
}
void car_H_26(double *state, double *unused, double *out_8668723313512326740) {
  H_26(state, unused, out_8668723313512326740);
}
void car_h_27(double *state, double *unused, double *out_8457728334513198266) {
  h_27(state, unused, out_8457728334513198266);
}
void car_H_27(double *state, double *unused, double *out_5692947794616344936) {
  H_27(state, unused, out_5692947794616344936);
}
void car_h_29(double *state, double *unused, double *out_2107743088442304165) {
  h_29(state, unused, out_2107743088442304165);
}
void car_H_29(double *state, double *unused, double *out_3007953138501527841) {
  H_29(state, unused, out_3007953138501527841);
}
void car_h_28(double *state, double *unused, double *out_4073384985462491014) {
  h_28(state, unused, out_4073384985462491014);
}
void car_H_28(double *state, double *unused, double *out_8090352155571058415) {
  H_28(state, unused, out_8090352155571058415);
}
void car_h_31(double *state, double *unused, double *out_4906686459481235788) {
  h_31(state, unused, out_4906686459481235788);
}
void car_H_31(double *state, double *unused, double *out_8042515211278975264) {
  H_31(state, unused, out_8042515211278975264);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
