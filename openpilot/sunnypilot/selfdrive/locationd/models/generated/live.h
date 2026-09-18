#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_8454771102794905975);
void live_err_fun(double *nom_x, double *delta_x, double *out_817167495916257534);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_5852930910562149927);
void live_H_mod_fun(double *state, double *out_2984345542167738561);
void live_f_fun(double *state, double dt, double *out_446816257654600525);
void live_F_fun(double *state, double dt, double *out_8974311989400744600);
void live_h_4(double *state, double *unused, double *out_4942201549190373731);
void live_H_4(double *state, double *unused, double *out_7407556911887843371);
void live_h_9(double *state, double *unused, double *out_2963432024719206820);
void live_H_9(double *state, double *unused, double *out_7166367265258252726);
void live_h_10(double *state, double *unused, double *out_6936135498915126166);
void live_H_10(double *state, double *unused, double *out_1897438559567031751);
void live_h_12(double *state, double *unused, double *out_4339869801229635408);
void live_H_12(double *state, double *unused, double *out_2388100503855881576);
void live_h_35(double *state, double *unused, double *out_89737225840413109);
void live_H_35(double *state, double *unused, double *out_357462528469132133);
void live_h_32(double *state, double *unused, double *out_947085137332597009);
void live_H_32(double *state, double *unused, double *out_3909730069574495526);
void live_h_13(double *state, double *unused, double *out_7382458822850692134);
void live_H_13(double *state, double *unused, double *out_1906848045411314590);
void live_h_14(double *state, double *unused, double *out_2963432024719206820);
void live_H_14(double *state, double *unused, double *out_7166367265258252726);
void live_h_33(double *state, double *unused, double *out_3569676355322749844);
void live_H_33(double *state, double *unused, double *out_890337849876378391);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}