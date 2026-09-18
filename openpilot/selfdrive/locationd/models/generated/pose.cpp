#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4578487927036483330) {
   out_4578487927036483330[0] = delta_x[0] + nom_x[0];
   out_4578487927036483330[1] = delta_x[1] + nom_x[1];
   out_4578487927036483330[2] = delta_x[2] + nom_x[2];
   out_4578487927036483330[3] = delta_x[3] + nom_x[3];
   out_4578487927036483330[4] = delta_x[4] + nom_x[4];
   out_4578487927036483330[5] = delta_x[5] + nom_x[5];
   out_4578487927036483330[6] = delta_x[6] + nom_x[6];
   out_4578487927036483330[7] = delta_x[7] + nom_x[7];
   out_4578487927036483330[8] = delta_x[8] + nom_x[8];
   out_4578487927036483330[9] = delta_x[9] + nom_x[9];
   out_4578487927036483330[10] = delta_x[10] + nom_x[10];
   out_4578487927036483330[11] = delta_x[11] + nom_x[11];
   out_4578487927036483330[12] = delta_x[12] + nom_x[12];
   out_4578487927036483330[13] = delta_x[13] + nom_x[13];
   out_4578487927036483330[14] = delta_x[14] + nom_x[14];
   out_4578487927036483330[15] = delta_x[15] + nom_x[15];
   out_4578487927036483330[16] = delta_x[16] + nom_x[16];
   out_4578487927036483330[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8115981069590118044) {
   out_8115981069590118044[0] = -nom_x[0] + true_x[0];
   out_8115981069590118044[1] = -nom_x[1] + true_x[1];
   out_8115981069590118044[2] = -nom_x[2] + true_x[2];
   out_8115981069590118044[3] = -nom_x[3] + true_x[3];
   out_8115981069590118044[4] = -nom_x[4] + true_x[4];
   out_8115981069590118044[5] = -nom_x[5] + true_x[5];
   out_8115981069590118044[6] = -nom_x[6] + true_x[6];
   out_8115981069590118044[7] = -nom_x[7] + true_x[7];
   out_8115981069590118044[8] = -nom_x[8] + true_x[8];
   out_8115981069590118044[9] = -nom_x[9] + true_x[9];
   out_8115981069590118044[10] = -nom_x[10] + true_x[10];
   out_8115981069590118044[11] = -nom_x[11] + true_x[11];
   out_8115981069590118044[12] = -nom_x[12] + true_x[12];
   out_8115981069590118044[13] = -nom_x[13] + true_x[13];
   out_8115981069590118044[14] = -nom_x[14] + true_x[14];
   out_8115981069590118044[15] = -nom_x[15] + true_x[15];
   out_8115981069590118044[16] = -nom_x[16] + true_x[16];
   out_8115981069590118044[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3440511784681479444) {
   out_3440511784681479444[0] = 1.0;
   out_3440511784681479444[1] = 0.0;
   out_3440511784681479444[2] = 0.0;
   out_3440511784681479444[3] = 0.0;
   out_3440511784681479444[4] = 0.0;
   out_3440511784681479444[5] = 0.0;
   out_3440511784681479444[6] = 0.0;
   out_3440511784681479444[7] = 0.0;
   out_3440511784681479444[8] = 0.0;
   out_3440511784681479444[9] = 0.0;
   out_3440511784681479444[10] = 0.0;
   out_3440511784681479444[11] = 0.0;
   out_3440511784681479444[12] = 0.0;
   out_3440511784681479444[13] = 0.0;
   out_3440511784681479444[14] = 0.0;
   out_3440511784681479444[15] = 0.0;
   out_3440511784681479444[16] = 0.0;
   out_3440511784681479444[17] = 0.0;
   out_3440511784681479444[18] = 0.0;
   out_3440511784681479444[19] = 1.0;
   out_3440511784681479444[20] = 0.0;
   out_3440511784681479444[21] = 0.0;
   out_3440511784681479444[22] = 0.0;
   out_3440511784681479444[23] = 0.0;
   out_3440511784681479444[24] = 0.0;
   out_3440511784681479444[25] = 0.0;
   out_3440511784681479444[26] = 0.0;
   out_3440511784681479444[27] = 0.0;
   out_3440511784681479444[28] = 0.0;
   out_3440511784681479444[29] = 0.0;
   out_3440511784681479444[30] = 0.0;
   out_3440511784681479444[31] = 0.0;
   out_3440511784681479444[32] = 0.0;
   out_3440511784681479444[33] = 0.0;
   out_3440511784681479444[34] = 0.0;
   out_3440511784681479444[35] = 0.0;
   out_3440511784681479444[36] = 0.0;
   out_3440511784681479444[37] = 0.0;
   out_3440511784681479444[38] = 1.0;
   out_3440511784681479444[39] = 0.0;
   out_3440511784681479444[40] = 0.0;
   out_3440511784681479444[41] = 0.0;
   out_3440511784681479444[42] = 0.0;
   out_3440511784681479444[43] = 0.0;
   out_3440511784681479444[44] = 0.0;
   out_3440511784681479444[45] = 0.0;
   out_3440511784681479444[46] = 0.0;
   out_3440511784681479444[47] = 0.0;
   out_3440511784681479444[48] = 0.0;
   out_3440511784681479444[49] = 0.0;
   out_3440511784681479444[50] = 0.0;
   out_3440511784681479444[51] = 0.0;
   out_3440511784681479444[52] = 0.0;
   out_3440511784681479444[53] = 0.0;
   out_3440511784681479444[54] = 0.0;
   out_3440511784681479444[55] = 0.0;
   out_3440511784681479444[56] = 0.0;
   out_3440511784681479444[57] = 1.0;
   out_3440511784681479444[58] = 0.0;
   out_3440511784681479444[59] = 0.0;
   out_3440511784681479444[60] = 0.0;
   out_3440511784681479444[61] = 0.0;
   out_3440511784681479444[62] = 0.0;
   out_3440511784681479444[63] = 0.0;
   out_3440511784681479444[64] = 0.0;
   out_3440511784681479444[65] = 0.0;
   out_3440511784681479444[66] = 0.0;
   out_3440511784681479444[67] = 0.0;
   out_3440511784681479444[68] = 0.0;
   out_3440511784681479444[69] = 0.0;
   out_3440511784681479444[70] = 0.0;
   out_3440511784681479444[71] = 0.0;
   out_3440511784681479444[72] = 0.0;
   out_3440511784681479444[73] = 0.0;
   out_3440511784681479444[74] = 0.0;
   out_3440511784681479444[75] = 0.0;
   out_3440511784681479444[76] = 1.0;
   out_3440511784681479444[77] = 0.0;
   out_3440511784681479444[78] = 0.0;
   out_3440511784681479444[79] = 0.0;
   out_3440511784681479444[80] = 0.0;
   out_3440511784681479444[81] = 0.0;
   out_3440511784681479444[82] = 0.0;
   out_3440511784681479444[83] = 0.0;
   out_3440511784681479444[84] = 0.0;
   out_3440511784681479444[85] = 0.0;
   out_3440511784681479444[86] = 0.0;
   out_3440511784681479444[87] = 0.0;
   out_3440511784681479444[88] = 0.0;
   out_3440511784681479444[89] = 0.0;
   out_3440511784681479444[90] = 0.0;
   out_3440511784681479444[91] = 0.0;
   out_3440511784681479444[92] = 0.0;
   out_3440511784681479444[93] = 0.0;
   out_3440511784681479444[94] = 0.0;
   out_3440511784681479444[95] = 1.0;
   out_3440511784681479444[96] = 0.0;
   out_3440511784681479444[97] = 0.0;
   out_3440511784681479444[98] = 0.0;
   out_3440511784681479444[99] = 0.0;
   out_3440511784681479444[100] = 0.0;
   out_3440511784681479444[101] = 0.0;
   out_3440511784681479444[102] = 0.0;
   out_3440511784681479444[103] = 0.0;
   out_3440511784681479444[104] = 0.0;
   out_3440511784681479444[105] = 0.0;
   out_3440511784681479444[106] = 0.0;
   out_3440511784681479444[107] = 0.0;
   out_3440511784681479444[108] = 0.0;
   out_3440511784681479444[109] = 0.0;
   out_3440511784681479444[110] = 0.0;
   out_3440511784681479444[111] = 0.0;
   out_3440511784681479444[112] = 0.0;
   out_3440511784681479444[113] = 0.0;
   out_3440511784681479444[114] = 1.0;
   out_3440511784681479444[115] = 0.0;
   out_3440511784681479444[116] = 0.0;
   out_3440511784681479444[117] = 0.0;
   out_3440511784681479444[118] = 0.0;
   out_3440511784681479444[119] = 0.0;
   out_3440511784681479444[120] = 0.0;
   out_3440511784681479444[121] = 0.0;
   out_3440511784681479444[122] = 0.0;
   out_3440511784681479444[123] = 0.0;
   out_3440511784681479444[124] = 0.0;
   out_3440511784681479444[125] = 0.0;
   out_3440511784681479444[126] = 0.0;
   out_3440511784681479444[127] = 0.0;
   out_3440511784681479444[128] = 0.0;
   out_3440511784681479444[129] = 0.0;
   out_3440511784681479444[130] = 0.0;
   out_3440511784681479444[131] = 0.0;
   out_3440511784681479444[132] = 0.0;
   out_3440511784681479444[133] = 1.0;
   out_3440511784681479444[134] = 0.0;
   out_3440511784681479444[135] = 0.0;
   out_3440511784681479444[136] = 0.0;
   out_3440511784681479444[137] = 0.0;
   out_3440511784681479444[138] = 0.0;
   out_3440511784681479444[139] = 0.0;
   out_3440511784681479444[140] = 0.0;
   out_3440511784681479444[141] = 0.0;
   out_3440511784681479444[142] = 0.0;
   out_3440511784681479444[143] = 0.0;
   out_3440511784681479444[144] = 0.0;
   out_3440511784681479444[145] = 0.0;
   out_3440511784681479444[146] = 0.0;
   out_3440511784681479444[147] = 0.0;
   out_3440511784681479444[148] = 0.0;
   out_3440511784681479444[149] = 0.0;
   out_3440511784681479444[150] = 0.0;
   out_3440511784681479444[151] = 0.0;
   out_3440511784681479444[152] = 1.0;
   out_3440511784681479444[153] = 0.0;
   out_3440511784681479444[154] = 0.0;
   out_3440511784681479444[155] = 0.0;
   out_3440511784681479444[156] = 0.0;
   out_3440511784681479444[157] = 0.0;
   out_3440511784681479444[158] = 0.0;
   out_3440511784681479444[159] = 0.0;
   out_3440511784681479444[160] = 0.0;
   out_3440511784681479444[161] = 0.0;
   out_3440511784681479444[162] = 0.0;
   out_3440511784681479444[163] = 0.0;
   out_3440511784681479444[164] = 0.0;
   out_3440511784681479444[165] = 0.0;
   out_3440511784681479444[166] = 0.0;
   out_3440511784681479444[167] = 0.0;
   out_3440511784681479444[168] = 0.0;
   out_3440511784681479444[169] = 0.0;
   out_3440511784681479444[170] = 0.0;
   out_3440511784681479444[171] = 1.0;
   out_3440511784681479444[172] = 0.0;
   out_3440511784681479444[173] = 0.0;
   out_3440511784681479444[174] = 0.0;
   out_3440511784681479444[175] = 0.0;
   out_3440511784681479444[176] = 0.0;
   out_3440511784681479444[177] = 0.0;
   out_3440511784681479444[178] = 0.0;
   out_3440511784681479444[179] = 0.0;
   out_3440511784681479444[180] = 0.0;
   out_3440511784681479444[181] = 0.0;
   out_3440511784681479444[182] = 0.0;
   out_3440511784681479444[183] = 0.0;
   out_3440511784681479444[184] = 0.0;
   out_3440511784681479444[185] = 0.0;
   out_3440511784681479444[186] = 0.0;
   out_3440511784681479444[187] = 0.0;
   out_3440511784681479444[188] = 0.0;
   out_3440511784681479444[189] = 0.0;
   out_3440511784681479444[190] = 1.0;
   out_3440511784681479444[191] = 0.0;
   out_3440511784681479444[192] = 0.0;
   out_3440511784681479444[193] = 0.0;
   out_3440511784681479444[194] = 0.0;
   out_3440511784681479444[195] = 0.0;
   out_3440511784681479444[196] = 0.0;
   out_3440511784681479444[197] = 0.0;
   out_3440511784681479444[198] = 0.0;
   out_3440511784681479444[199] = 0.0;
   out_3440511784681479444[200] = 0.0;
   out_3440511784681479444[201] = 0.0;
   out_3440511784681479444[202] = 0.0;
   out_3440511784681479444[203] = 0.0;
   out_3440511784681479444[204] = 0.0;
   out_3440511784681479444[205] = 0.0;
   out_3440511784681479444[206] = 0.0;
   out_3440511784681479444[207] = 0.0;
   out_3440511784681479444[208] = 0.0;
   out_3440511784681479444[209] = 1.0;
   out_3440511784681479444[210] = 0.0;
   out_3440511784681479444[211] = 0.0;
   out_3440511784681479444[212] = 0.0;
   out_3440511784681479444[213] = 0.0;
   out_3440511784681479444[214] = 0.0;
   out_3440511784681479444[215] = 0.0;
   out_3440511784681479444[216] = 0.0;
   out_3440511784681479444[217] = 0.0;
   out_3440511784681479444[218] = 0.0;
   out_3440511784681479444[219] = 0.0;
   out_3440511784681479444[220] = 0.0;
   out_3440511784681479444[221] = 0.0;
   out_3440511784681479444[222] = 0.0;
   out_3440511784681479444[223] = 0.0;
   out_3440511784681479444[224] = 0.0;
   out_3440511784681479444[225] = 0.0;
   out_3440511784681479444[226] = 0.0;
   out_3440511784681479444[227] = 0.0;
   out_3440511784681479444[228] = 1.0;
   out_3440511784681479444[229] = 0.0;
   out_3440511784681479444[230] = 0.0;
   out_3440511784681479444[231] = 0.0;
   out_3440511784681479444[232] = 0.0;
   out_3440511784681479444[233] = 0.0;
   out_3440511784681479444[234] = 0.0;
   out_3440511784681479444[235] = 0.0;
   out_3440511784681479444[236] = 0.0;
   out_3440511784681479444[237] = 0.0;
   out_3440511784681479444[238] = 0.0;
   out_3440511784681479444[239] = 0.0;
   out_3440511784681479444[240] = 0.0;
   out_3440511784681479444[241] = 0.0;
   out_3440511784681479444[242] = 0.0;
   out_3440511784681479444[243] = 0.0;
   out_3440511784681479444[244] = 0.0;
   out_3440511784681479444[245] = 0.0;
   out_3440511784681479444[246] = 0.0;
   out_3440511784681479444[247] = 1.0;
   out_3440511784681479444[248] = 0.0;
   out_3440511784681479444[249] = 0.0;
   out_3440511784681479444[250] = 0.0;
   out_3440511784681479444[251] = 0.0;
   out_3440511784681479444[252] = 0.0;
   out_3440511784681479444[253] = 0.0;
   out_3440511784681479444[254] = 0.0;
   out_3440511784681479444[255] = 0.0;
   out_3440511784681479444[256] = 0.0;
   out_3440511784681479444[257] = 0.0;
   out_3440511784681479444[258] = 0.0;
   out_3440511784681479444[259] = 0.0;
   out_3440511784681479444[260] = 0.0;
   out_3440511784681479444[261] = 0.0;
   out_3440511784681479444[262] = 0.0;
   out_3440511784681479444[263] = 0.0;
   out_3440511784681479444[264] = 0.0;
   out_3440511784681479444[265] = 0.0;
   out_3440511784681479444[266] = 1.0;
   out_3440511784681479444[267] = 0.0;
   out_3440511784681479444[268] = 0.0;
   out_3440511784681479444[269] = 0.0;
   out_3440511784681479444[270] = 0.0;
   out_3440511784681479444[271] = 0.0;
   out_3440511784681479444[272] = 0.0;
   out_3440511784681479444[273] = 0.0;
   out_3440511784681479444[274] = 0.0;
   out_3440511784681479444[275] = 0.0;
   out_3440511784681479444[276] = 0.0;
   out_3440511784681479444[277] = 0.0;
   out_3440511784681479444[278] = 0.0;
   out_3440511784681479444[279] = 0.0;
   out_3440511784681479444[280] = 0.0;
   out_3440511784681479444[281] = 0.0;
   out_3440511784681479444[282] = 0.0;
   out_3440511784681479444[283] = 0.0;
   out_3440511784681479444[284] = 0.0;
   out_3440511784681479444[285] = 1.0;
   out_3440511784681479444[286] = 0.0;
   out_3440511784681479444[287] = 0.0;
   out_3440511784681479444[288] = 0.0;
   out_3440511784681479444[289] = 0.0;
   out_3440511784681479444[290] = 0.0;
   out_3440511784681479444[291] = 0.0;
   out_3440511784681479444[292] = 0.0;
   out_3440511784681479444[293] = 0.0;
   out_3440511784681479444[294] = 0.0;
   out_3440511784681479444[295] = 0.0;
   out_3440511784681479444[296] = 0.0;
   out_3440511784681479444[297] = 0.0;
   out_3440511784681479444[298] = 0.0;
   out_3440511784681479444[299] = 0.0;
   out_3440511784681479444[300] = 0.0;
   out_3440511784681479444[301] = 0.0;
   out_3440511784681479444[302] = 0.0;
   out_3440511784681479444[303] = 0.0;
   out_3440511784681479444[304] = 1.0;
   out_3440511784681479444[305] = 0.0;
   out_3440511784681479444[306] = 0.0;
   out_3440511784681479444[307] = 0.0;
   out_3440511784681479444[308] = 0.0;
   out_3440511784681479444[309] = 0.0;
   out_3440511784681479444[310] = 0.0;
   out_3440511784681479444[311] = 0.0;
   out_3440511784681479444[312] = 0.0;
   out_3440511784681479444[313] = 0.0;
   out_3440511784681479444[314] = 0.0;
   out_3440511784681479444[315] = 0.0;
   out_3440511784681479444[316] = 0.0;
   out_3440511784681479444[317] = 0.0;
   out_3440511784681479444[318] = 0.0;
   out_3440511784681479444[319] = 0.0;
   out_3440511784681479444[320] = 0.0;
   out_3440511784681479444[321] = 0.0;
   out_3440511784681479444[322] = 0.0;
   out_3440511784681479444[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8130855907072971399) {
   out_8130855907072971399[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8130855907072971399[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8130855907072971399[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8130855907072971399[3] = dt*state[12] + state[3];
   out_8130855907072971399[4] = dt*state[13] + state[4];
   out_8130855907072971399[5] = dt*state[14] + state[5];
   out_8130855907072971399[6] = state[6];
   out_8130855907072971399[7] = state[7];
   out_8130855907072971399[8] = state[8];
   out_8130855907072971399[9] = state[9];
   out_8130855907072971399[10] = state[10];
   out_8130855907072971399[11] = state[11];
   out_8130855907072971399[12] = state[12];
   out_8130855907072971399[13] = state[13];
   out_8130855907072971399[14] = state[14];
   out_8130855907072971399[15] = state[15];
   out_8130855907072971399[16] = state[16];
   out_8130855907072971399[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1049188004151045087) {
   out_1049188004151045087[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1049188004151045087[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1049188004151045087[2] = 0;
   out_1049188004151045087[3] = 0;
   out_1049188004151045087[4] = 0;
   out_1049188004151045087[5] = 0;
   out_1049188004151045087[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1049188004151045087[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1049188004151045087[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1049188004151045087[9] = 0;
   out_1049188004151045087[10] = 0;
   out_1049188004151045087[11] = 0;
   out_1049188004151045087[12] = 0;
   out_1049188004151045087[13] = 0;
   out_1049188004151045087[14] = 0;
   out_1049188004151045087[15] = 0;
   out_1049188004151045087[16] = 0;
   out_1049188004151045087[17] = 0;
   out_1049188004151045087[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1049188004151045087[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1049188004151045087[20] = 0;
   out_1049188004151045087[21] = 0;
   out_1049188004151045087[22] = 0;
   out_1049188004151045087[23] = 0;
   out_1049188004151045087[24] = 0;
   out_1049188004151045087[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1049188004151045087[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1049188004151045087[27] = 0;
   out_1049188004151045087[28] = 0;
   out_1049188004151045087[29] = 0;
   out_1049188004151045087[30] = 0;
   out_1049188004151045087[31] = 0;
   out_1049188004151045087[32] = 0;
   out_1049188004151045087[33] = 0;
   out_1049188004151045087[34] = 0;
   out_1049188004151045087[35] = 0;
   out_1049188004151045087[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1049188004151045087[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1049188004151045087[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1049188004151045087[39] = 0;
   out_1049188004151045087[40] = 0;
   out_1049188004151045087[41] = 0;
   out_1049188004151045087[42] = 0;
   out_1049188004151045087[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1049188004151045087[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1049188004151045087[45] = 0;
   out_1049188004151045087[46] = 0;
   out_1049188004151045087[47] = 0;
   out_1049188004151045087[48] = 0;
   out_1049188004151045087[49] = 0;
   out_1049188004151045087[50] = 0;
   out_1049188004151045087[51] = 0;
   out_1049188004151045087[52] = 0;
   out_1049188004151045087[53] = 0;
   out_1049188004151045087[54] = 0;
   out_1049188004151045087[55] = 0;
   out_1049188004151045087[56] = 0;
   out_1049188004151045087[57] = 1;
   out_1049188004151045087[58] = 0;
   out_1049188004151045087[59] = 0;
   out_1049188004151045087[60] = 0;
   out_1049188004151045087[61] = 0;
   out_1049188004151045087[62] = 0;
   out_1049188004151045087[63] = 0;
   out_1049188004151045087[64] = 0;
   out_1049188004151045087[65] = 0;
   out_1049188004151045087[66] = dt;
   out_1049188004151045087[67] = 0;
   out_1049188004151045087[68] = 0;
   out_1049188004151045087[69] = 0;
   out_1049188004151045087[70] = 0;
   out_1049188004151045087[71] = 0;
   out_1049188004151045087[72] = 0;
   out_1049188004151045087[73] = 0;
   out_1049188004151045087[74] = 0;
   out_1049188004151045087[75] = 0;
   out_1049188004151045087[76] = 1;
   out_1049188004151045087[77] = 0;
   out_1049188004151045087[78] = 0;
   out_1049188004151045087[79] = 0;
   out_1049188004151045087[80] = 0;
   out_1049188004151045087[81] = 0;
   out_1049188004151045087[82] = 0;
   out_1049188004151045087[83] = 0;
   out_1049188004151045087[84] = 0;
   out_1049188004151045087[85] = dt;
   out_1049188004151045087[86] = 0;
   out_1049188004151045087[87] = 0;
   out_1049188004151045087[88] = 0;
   out_1049188004151045087[89] = 0;
   out_1049188004151045087[90] = 0;
   out_1049188004151045087[91] = 0;
   out_1049188004151045087[92] = 0;
   out_1049188004151045087[93] = 0;
   out_1049188004151045087[94] = 0;
   out_1049188004151045087[95] = 1;
   out_1049188004151045087[96] = 0;
   out_1049188004151045087[97] = 0;
   out_1049188004151045087[98] = 0;
   out_1049188004151045087[99] = 0;
   out_1049188004151045087[100] = 0;
   out_1049188004151045087[101] = 0;
   out_1049188004151045087[102] = 0;
   out_1049188004151045087[103] = 0;
   out_1049188004151045087[104] = dt;
   out_1049188004151045087[105] = 0;
   out_1049188004151045087[106] = 0;
   out_1049188004151045087[107] = 0;
   out_1049188004151045087[108] = 0;
   out_1049188004151045087[109] = 0;
   out_1049188004151045087[110] = 0;
   out_1049188004151045087[111] = 0;
   out_1049188004151045087[112] = 0;
   out_1049188004151045087[113] = 0;
   out_1049188004151045087[114] = 1;
   out_1049188004151045087[115] = 0;
   out_1049188004151045087[116] = 0;
   out_1049188004151045087[117] = 0;
   out_1049188004151045087[118] = 0;
   out_1049188004151045087[119] = 0;
   out_1049188004151045087[120] = 0;
   out_1049188004151045087[121] = 0;
   out_1049188004151045087[122] = 0;
   out_1049188004151045087[123] = 0;
   out_1049188004151045087[124] = 0;
   out_1049188004151045087[125] = 0;
   out_1049188004151045087[126] = 0;
   out_1049188004151045087[127] = 0;
   out_1049188004151045087[128] = 0;
   out_1049188004151045087[129] = 0;
   out_1049188004151045087[130] = 0;
   out_1049188004151045087[131] = 0;
   out_1049188004151045087[132] = 0;
   out_1049188004151045087[133] = 1;
   out_1049188004151045087[134] = 0;
   out_1049188004151045087[135] = 0;
   out_1049188004151045087[136] = 0;
   out_1049188004151045087[137] = 0;
   out_1049188004151045087[138] = 0;
   out_1049188004151045087[139] = 0;
   out_1049188004151045087[140] = 0;
   out_1049188004151045087[141] = 0;
   out_1049188004151045087[142] = 0;
   out_1049188004151045087[143] = 0;
   out_1049188004151045087[144] = 0;
   out_1049188004151045087[145] = 0;
   out_1049188004151045087[146] = 0;
   out_1049188004151045087[147] = 0;
   out_1049188004151045087[148] = 0;
   out_1049188004151045087[149] = 0;
   out_1049188004151045087[150] = 0;
   out_1049188004151045087[151] = 0;
   out_1049188004151045087[152] = 1;
   out_1049188004151045087[153] = 0;
   out_1049188004151045087[154] = 0;
   out_1049188004151045087[155] = 0;
   out_1049188004151045087[156] = 0;
   out_1049188004151045087[157] = 0;
   out_1049188004151045087[158] = 0;
   out_1049188004151045087[159] = 0;
   out_1049188004151045087[160] = 0;
   out_1049188004151045087[161] = 0;
   out_1049188004151045087[162] = 0;
   out_1049188004151045087[163] = 0;
   out_1049188004151045087[164] = 0;
   out_1049188004151045087[165] = 0;
   out_1049188004151045087[166] = 0;
   out_1049188004151045087[167] = 0;
   out_1049188004151045087[168] = 0;
   out_1049188004151045087[169] = 0;
   out_1049188004151045087[170] = 0;
   out_1049188004151045087[171] = 1;
   out_1049188004151045087[172] = 0;
   out_1049188004151045087[173] = 0;
   out_1049188004151045087[174] = 0;
   out_1049188004151045087[175] = 0;
   out_1049188004151045087[176] = 0;
   out_1049188004151045087[177] = 0;
   out_1049188004151045087[178] = 0;
   out_1049188004151045087[179] = 0;
   out_1049188004151045087[180] = 0;
   out_1049188004151045087[181] = 0;
   out_1049188004151045087[182] = 0;
   out_1049188004151045087[183] = 0;
   out_1049188004151045087[184] = 0;
   out_1049188004151045087[185] = 0;
   out_1049188004151045087[186] = 0;
   out_1049188004151045087[187] = 0;
   out_1049188004151045087[188] = 0;
   out_1049188004151045087[189] = 0;
   out_1049188004151045087[190] = 1;
   out_1049188004151045087[191] = 0;
   out_1049188004151045087[192] = 0;
   out_1049188004151045087[193] = 0;
   out_1049188004151045087[194] = 0;
   out_1049188004151045087[195] = 0;
   out_1049188004151045087[196] = 0;
   out_1049188004151045087[197] = 0;
   out_1049188004151045087[198] = 0;
   out_1049188004151045087[199] = 0;
   out_1049188004151045087[200] = 0;
   out_1049188004151045087[201] = 0;
   out_1049188004151045087[202] = 0;
   out_1049188004151045087[203] = 0;
   out_1049188004151045087[204] = 0;
   out_1049188004151045087[205] = 0;
   out_1049188004151045087[206] = 0;
   out_1049188004151045087[207] = 0;
   out_1049188004151045087[208] = 0;
   out_1049188004151045087[209] = 1;
   out_1049188004151045087[210] = 0;
   out_1049188004151045087[211] = 0;
   out_1049188004151045087[212] = 0;
   out_1049188004151045087[213] = 0;
   out_1049188004151045087[214] = 0;
   out_1049188004151045087[215] = 0;
   out_1049188004151045087[216] = 0;
   out_1049188004151045087[217] = 0;
   out_1049188004151045087[218] = 0;
   out_1049188004151045087[219] = 0;
   out_1049188004151045087[220] = 0;
   out_1049188004151045087[221] = 0;
   out_1049188004151045087[222] = 0;
   out_1049188004151045087[223] = 0;
   out_1049188004151045087[224] = 0;
   out_1049188004151045087[225] = 0;
   out_1049188004151045087[226] = 0;
   out_1049188004151045087[227] = 0;
   out_1049188004151045087[228] = 1;
   out_1049188004151045087[229] = 0;
   out_1049188004151045087[230] = 0;
   out_1049188004151045087[231] = 0;
   out_1049188004151045087[232] = 0;
   out_1049188004151045087[233] = 0;
   out_1049188004151045087[234] = 0;
   out_1049188004151045087[235] = 0;
   out_1049188004151045087[236] = 0;
   out_1049188004151045087[237] = 0;
   out_1049188004151045087[238] = 0;
   out_1049188004151045087[239] = 0;
   out_1049188004151045087[240] = 0;
   out_1049188004151045087[241] = 0;
   out_1049188004151045087[242] = 0;
   out_1049188004151045087[243] = 0;
   out_1049188004151045087[244] = 0;
   out_1049188004151045087[245] = 0;
   out_1049188004151045087[246] = 0;
   out_1049188004151045087[247] = 1;
   out_1049188004151045087[248] = 0;
   out_1049188004151045087[249] = 0;
   out_1049188004151045087[250] = 0;
   out_1049188004151045087[251] = 0;
   out_1049188004151045087[252] = 0;
   out_1049188004151045087[253] = 0;
   out_1049188004151045087[254] = 0;
   out_1049188004151045087[255] = 0;
   out_1049188004151045087[256] = 0;
   out_1049188004151045087[257] = 0;
   out_1049188004151045087[258] = 0;
   out_1049188004151045087[259] = 0;
   out_1049188004151045087[260] = 0;
   out_1049188004151045087[261] = 0;
   out_1049188004151045087[262] = 0;
   out_1049188004151045087[263] = 0;
   out_1049188004151045087[264] = 0;
   out_1049188004151045087[265] = 0;
   out_1049188004151045087[266] = 1;
   out_1049188004151045087[267] = 0;
   out_1049188004151045087[268] = 0;
   out_1049188004151045087[269] = 0;
   out_1049188004151045087[270] = 0;
   out_1049188004151045087[271] = 0;
   out_1049188004151045087[272] = 0;
   out_1049188004151045087[273] = 0;
   out_1049188004151045087[274] = 0;
   out_1049188004151045087[275] = 0;
   out_1049188004151045087[276] = 0;
   out_1049188004151045087[277] = 0;
   out_1049188004151045087[278] = 0;
   out_1049188004151045087[279] = 0;
   out_1049188004151045087[280] = 0;
   out_1049188004151045087[281] = 0;
   out_1049188004151045087[282] = 0;
   out_1049188004151045087[283] = 0;
   out_1049188004151045087[284] = 0;
   out_1049188004151045087[285] = 1;
   out_1049188004151045087[286] = 0;
   out_1049188004151045087[287] = 0;
   out_1049188004151045087[288] = 0;
   out_1049188004151045087[289] = 0;
   out_1049188004151045087[290] = 0;
   out_1049188004151045087[291] = 0;
   out_1049188004151045087[292] = 0;
   out_1049188004151045087[293] = 0;
   out_1049188004151045087[294] = 0;
   out_1049188004151045087[295] = 0;
   out_1049188004151045087[296] = 0;
   out_1049188004151045087[297] = 0;
   out_1049188004151045087[298] = 0;
   out_1049188004151045087[299] = 0;
   out_1049188004151045087[300] = 0;
   out_1049188004151045087[301] = 0;
   out_1049188004151045087[302] = 0;
   out_1049188004151045087[303] = 0;
   out_1049188004151045087[304] = 1;
   out_1049188004151045087[305] = 0;
   out_1049188004151045087[306] = 0;
   out_1049188004151045087[307] = 0;
   out_1049188004151045087[308] = 0;
   out_1049188004151045087[309] = 0;
   out_1049188004151045087[310] = 0;
   out_1049188004151045087[311] = 0;
   out_1049188004151045087[312] = 0;
   out_1049188004151045087[313] = 0;
   out_1049188004151045087[314] = 0;
   out_1049188004151045087[315] = 0;
   out_1049188004151045087[316] = 0;
   out_1049188004151045087[317] = 0;
   out_1049188004151045087[318] = 0;
   out_1049188004151045087[319] = 0;
   out_1049188004151045087[320] = 0;
   out_1049188004151045087[321] = 0;
   out_1049188004151045087[322] = 0;
   out_1049188004151045087[323] = 1;
}
void h_4(double *state, double *unused, double *out_1483013049936175968) {
   out_1483013049936175968[0] = state[6] + state[9];
   out_1483013049936175968[1] = state[7] + state[10];
   out_1483013049936175968[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2686350782626766837) {
   out_2686350782626766837[0] = 0;
   out_2686350782626766837[1] = 0;
   out_2686350782626766837[2] = 0;
   out_2686350782626766837[3] = 0;
   out_2686350782626766837[4] = 0;
   out_2686350782626766837[5] = 0;
   out_2686350782626766837[6] = 1;
   out_2686350782626766837[7] = 0;
   out_2686350782626766837[8] = 0;
   out_2686350782626766837[9] = 1;
   out_2686350782626766837[10] = 0;
   out_2686350782626766837[11] = 0;
   out_2686350782626766837[12] = 0;
   out_2686350782626766837[13] = 0;
   out_2686350782626766837[14] = 0;
   out_2686350782626766837[15] = 0;
   out_2686350782626766837[16] = 0;
   out_2686350782626766837[17] = 0;
   out_2686350782626766837[18] = 0;
   out_2686350782626766837[19] = 0;
   out_2686350782626766837[20] = 0;
   out_2686350782626766837[21] = 0;
   out_2686350782626766837[22] = 0;
   out_2686350782626766837[23] = 0;
   out_2686350782626766837[24] = 0;
   out_2686350782626766837[25] = 1;
   out_2686350782626766837[26] = 0;
   out_2686350782626766837[27] = 0;
   out_2686350782626766837[28] = 1;
   out_2686350782626766837[29] = 0;
   out_2686350782626766837[30] = 0;
   out_2686350782626766837[31] = 0;
   out_2686350782626766837[32] = 0;
   out_2686350782626766837[33] = 0;
   out_2686350782626766837[34] = 0;
   out_2686350782626766837[35] = 0;
   out_2686350782626766837[36] = 0;
   out_2686350782626766837[37] = 0;
   out_2686350782626766837[38] = 0;
   out_2686350782626766837[39] = 0;
   out_2686350782626766837[40] = 0;
   out_2686350782626766837[41] = 0;
   out_2686350782626766837[42] = 0;
   out_2686350782626766837[43] = 0;
   out_2686350782626766837[44] = 1;
   out_2686350782626766837[45] = 0;
   out_2686350782626766837[46] = 0;
   out_2686350782626766837[47] = 1;
   out_2686350782626766837[48] = 0;
   out_2686350782626766837[49] = 0;
   out_2686350782626766837[50] = 0;
   out_2686350782626766837[51] = 0;
   out_2686350782626766837[52] = 0;
   out_2686350782626766837[53] = 0;
}
void h_10(double *state, double *unused, double *out_3864158886137510799) {
   out_3864158886137510799[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3864158886137510799[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3864158886137510799[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3269848050062638194) {
   out_3269848050062638194[0] = 0;
   out_3269848050062638194[1] = 9.8100000000000005*cos(state[1]);
   out_3269848050062638194[2] = 0;
   out_3269848050062638194[3] = 0;
   out_3269848050062638194[4] = -state[8];
   out_3269848050062638194[5] = state[7];
   out_3269848050062638194[6] = 0;
   out_3269848050062638194[7] = state[5];
   out_3269848050062638194[8] = -state[4];
   out_3269848050062638194[9] = 0;
   out_3269848050062638194[10] = 0;
   out_3269848050062638194[11] = 0;
   out_3269848050062638194[12] = 1;
   out_3269848050062638194[13] = 0;
   out_3269848050062638194[14] = 0;
   out_3269848050062638194[15] = 1;
   out_3269848050062638194[16] = 0;
   out_3269848050062638194[17] = 0;
   out_3269848050062638194[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3269848050062638194[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3269848050062638194[20] = 0;
   out_3269848050062638194[21] = state[8];
   out_3269848050062638194[22] = 0;
   out_3269848050062638194[23] = -state[6];
   out_3269848050062638194[24] = -state[5];
   out_3269848050062638194[25] = 0;
   out_3269848050062638194[26] = state[3];
   out_3269848050062638194[27] = 0;
   out_3269848050062638194[28] = 0;
   out_3269848050062638194[29] = 0;
   out_3269848050062638194[30] = 0;
   out_3269848050062638194[31] = 1;
   out_3269848050062638194[32] = 0;
   out_3269848050062638194[33] = 0;
   out_3269848050062638194[34] = 1;
   out_3269848050062638194[35] = 0;
   out_3269848050062638194[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3269848050062638194[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3269848050062638194[38] = 0;
   out_3269848050062638194[39] = -state[7];
   out_3269848050062638194[40] = state[6];
   out_3269848050062638194[41] = 0;
   out_3269848050062638194[42] = state[4];
   out_3269848050062638194[43] = -state[3];
   out_3269848050062638194[44] = 0;
   out_3269848050062638194[45] = 0;
   out_3269848050062638194[46] = 0;
   out_3269848050062638194[47] = 0;
   out_3269848050062638194[48] = 0;
   out_3269848050062638194[49] = 0;
   out_3269848050062638194[50] = 1;
   out_3269848050062638194[51] = 0;
   out_3269848050062638194[52] = 0;
   out_3269848050062638194[53] = 1;
}
void h_13(double *state, double *unused, double *out_6569675589277854157) {
   out_6569675589277854157[0] = state[3];
   out_6569675589277854157[1] = state[4];
   out_6569675589277854157[2] = state[5];
}
void H_13(double *state, double *unused, double *out_525923042705565964) {
   out_525923042705565964[0] = 0;
   out_525923042705565964[1] = 0;
   out_525923042705565964[2] = 0;
   out_525923042705565964[3] = 1;
   out_525923042705565964[4] = 0;
   out_525923042705565964[5] = 0;
   out_525923042705565964[6] = 0;
   out_525923042705565964[7] = 0;
   out_525923042705565964[8] = 0;
   out_525923042705565964[9] = 0;
   out_525923042705565964[10] = 0;
   out_525923042705565964[11] = 0;
   out_525923042705565964[12] = 0;
   out_525923042705565964[13] = 0;
   out_525923042705565964[14] = 0;
   out_525923042705565964[15] = 0;
   out_525923042705565964[16] = 0;
   out_525923042705565964[17] = 0;
   out_525923042705565964[18] = 0;
   out_525923042705565964[19] = 0;
   out_525923042705565964[20] = 0;
   out_525923042705565964[21] = 0;
   out_525923042705565964[22] = 1;
   out_525923042705565964[23] = 0;
   out_525923042705565964[24] = 0;
   out_525923042705565964[25] = 0;
   out_525923042705565964[26] = 0;
   out_525923042705565964[27] = 0;
   out_525923042705565964[28] = 0;
   out_525923042705565964[29] = 0;
   out_525923042705565964[30] = 0;
   out_525923042705565964[31] = 0;
   out_525923042705565964[32] = 0;
   out_525923042705565964[33] = 0;
   out_525923042705565964[34] = 0;
   out_525923042705565964[35] = 0;
   out_525923042705565964[36] = 0;
   out_525923042705565964[37] = 0;
   out_525923042705565964[38] = 0;
   out_525923042705565964[39] = 0;
   out_525923042705565964[40] = 0;
   out_525923042705565964[41] = 1;
   out_525923042705565964[42] = 0;
   out_525923042705565964[43] = 0;
   out_525923042705565964[44] = 0;
   out_525923042705565964[45] = 0;
   out_525923042705565964[46] = 0;
   out_525923042705565964[47] = 0;
   out_525923042705565964[48] = 0;
   out_525923042705565964[49] = 0;
   out_525923042705565964[50] = 0;
   out_525923042705565964[51] = 0;
   out_525923042705565964[52] = 0;
   out_525923042705565964[53] = 0;
}
void h_14(double *state, double *unused, double *out_8427245737982145415) {
   out_8427245737982145415[0] = state[6];
   out_8427245737982145415[1] = state[7];
   out_8427245737982145415[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1276890073712717692) {
   out_1276890073712717692[0] = 0;
   out_1276890073712717692[1] = 0;
   out_1276890073712717692[2] = 0;
   out_1276890073712717692[3] = 0;
   out_1276890073712717692[4] = 0;
   out_1276890073712717692[5] = 0;
   out_1276890073712717692[6] = 1;
   out_1276890073712717692[7] = 0;
   out_1276890073712717692[8] = 0;
   out_1276890073712717692[9] = 0;
   out_1276890073712717692[10] = 0;
   out_1276890073712717692[11] = 0;
   out_1276890073712717692[12] = 0;
   out_1276890073712717692[13] = 0;
   out_1276890073712717692[14] = 0;
   out_1276890073712717692[15] = 0;
   out_1276890073712717692[16] = 0;
   out_1276890073712717692[17] = 0;
   out_1276890073712717692[18] = 0;
   out_1276890073712717692[19] = 0;
   out_1276890073712717692[20] = 0;
   out_1276890073712717692[21] = 0;
   out_1276890073712717692[22] = 0;
   out_1276890073712717692[23] = 0;
   out_1276890073712717692[24] = 0;
   out_1276890073712717692[25] = 1;
   out_1276890073712717692[26] = 0;
   out_1276890073712717692[27] = 0;
   out_1276890073712717692[28] = 0;
   out_1276890073712717692[29] = 0;
   out_1276890073712717692[30] = 0;
   out_1276890073712717692[31] = 0;
   out_1276890073712717692[32] = 0;
   out_1276890073712717692[33] = 0;
   out_1276890073712717692[34] = 0;
   out_1276890073712717692[35] = 0;
   out_1276890073712717692[36] = 0;
   out_1276890073712717692[37] = 0;
   out_1276890073712717692[38] = 0;
   out_1276890073712717692[39] = 0;
   out_1276890073712717692[40] = 0;
   out_1276890073712717692[41] = 0;
   out_1276890073712717692[42] = 0;
   out_1276890073712717692[43] = 0;
   out_1276890073712717692[44] = 1;
   out_1276890073712717692[45] = 0;
   out_1276890073712717692[46] = 0;
   out_1276890073712717692[47] = 0;
   out_1276890073712717692[48] = 0;
   out_1276890073712717692[49] = 0;
   out_1276890073712717692[50] = 0;
   out_1276890073712717692[51] = 0;
   out_1276890073712717692[52] = 0;
   out_1276890073712717692[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_4578487927036483330) {
  err_fun(nom_x, delta_x, out_4578487927036483330);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8115981069590118044) {
  inv_err_fun(nom_x, true_x, out_8115981069590118044);
}
void pose_H_mod_fun(double *state, double *out_3440511784681479444) {
  H_mod_fun(state, out_3440511784681479444);
}
void pose_f_fun(double *state, double dt, double *out_8130855907072971399) {
  f_fun(state,  dt, out_8130855907072971399);
}
void pose_F_fun(double *state, double dt, double *out_1049188004151045087) {
  F_fun(state,  dt, out_1049188004151045087);
}
void pose_h_4(double *state, double *unused, double *out_1483013049936175968) {
  h_4(state, unused, out_1483013049936175968);
}
void pose_H_4(double *state, double *unused, double *out_2686350782626766837) {
  H_4(state, unused, out_2686350782626766837);
}
void pose_h_10(double *state, double *unused, double *out_3864158886137510799) {
  h_10(state, unused, out_3864158886137510799);
}
void pose_H_10(double *state, double *unused, double *out_3269848050062638194) {
  H_10(state, unused, out_3269848050062638194);
}
void pose_h_13(double *state, double *unused, double *out_6569675589277854157) {
  h_13(state, unused, out_6569675589277854157);
}
void pose_H_13(double *state, double *unused, double *out_525923042705565964) {
  H_13(state, unused, out_525923042705565964);
}
void pose_h_14(double *state, double *unused, double *out_8427245737982145415) {
  h_14(state, unused, out_8427245737982145415);
}
void pose_H_14(double *state, double *unused, double *out_1276890073712717692) {
  H_14(state, unused, out_1276890073712717692);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
