#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4578487927036483330);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8115981069590118044);
void pose_H_mod_fun(double *state, double *out_3440511784681479444);
void pose_f_fun(double *state, double dt, double *out_8130855907072971399);
void pose_F_fun(double *state, double dt, double *out_1049188004151045087);
void pose_h_4(double *state, double *unused, double *out_1483013049936175968);
void pose_H_4(double *state, double *unused, double *out_2686350782626766837);
void pose_h_10(double *state, double *unused, double *out_3864158886137510799);
void pose_H_10(double *state, double *unused, double *out_3269848050062638194);
void pose_h_13(double *state, double *unused, double *out_6569675589277854157);
void pose_H_13(double *state, double *unused, double *out_525923042705565964);
void pose_h_14(double *state, double *unused, double *out_8427245737982145415);
void pose_H_14(double *state, double *unused, double *out_1276890073712717692);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}