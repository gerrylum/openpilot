#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_6689287202068207421);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6652507941137758454);
void car_H_mod_fun(double *state, double *out_1241686598395299543);
void car_f_fun(double *state, double dt, double *out_1969896210282524456);
void car_F_fun(double *state, double dt, double *out_3055228452963269409);
void car_h_25(double *state, double *unused, double *out_3733191017237306096);
void car_H_25(double *state, double *unused, double *out_6036517441323168652);
void car_h_24(double *state, double *unused, double *out_4323419187172556926);
void car_H_24(double *state, double *unused, double *out_8209167040328668218);
void car_h_30(double *state, double *unused, double *out_2854636909238989067);
void car_H_30(double *state, double *unused, double *out_3518184482815920025);
void car_h_26(double *state, double *unused, double *out_1767549120217119247);
void car_H_26(double *state, double *unused, double *out_8668723313512326740);
void car_h_27(double *state, double *unused, double *out_8457728334513198266);
void car_H_27(double *state, double *unused, double *out_5692947794616344936);
void car_h_29(double *state, double *unused, double *out_2107743088442304165);
void car_H_29(double *state, double *unused, double *out_3007953138501527841);
void car_h_28(double *state, double *unused, double *out_4073384985462491014);
void car_H_28(double *state, double *unused, double *out_8090352155571058415);
void car_h_31(double *state, double *unused, double *out_4906686459481235788);
void car_H_31(double *state, double *unused, double *out_8042515211278975264);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}