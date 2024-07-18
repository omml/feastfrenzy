//
//  FileNamesHolder.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#include "FileNamesHolder.h"

// Holds all sprite names to avoid errors as Play Buffer is picky with file names
const char FileNamesHolder::fileNames[][20] = {
    "girl1_cd_3","girl1_cl_3","girl1_cr_3","girl1_cu_3","girl1_pd_3","girl1_pl_3","girl1_pr_3","girl1_pu_3","girl1_wdh_8","girl1_wd_8","girl1_wlh_8","girl1_wl_8","girl1_wrh_8","girl1_wr_8","girl1_wuh_8","girl1_wu_8",
    "boy1_cd_3","boy1_cl_3","boy1_cr_3","boy1_cu_3","boy1_pd_3","boy1_pl_3","boy1_pr_3","boy1_pu_3","boy1_wdh_8","boy1_wd_8","boy1_wlh_8","boy1_wl_8","boy1_wrh_8","boy1_wr_8","boy1_wuh_8","boy1_wu_8",
    "gm1_cd_3","gm1_cl_3","gm1_cr_3","gm1_cu_3","gm1_pd_3","gm1_pl_3","gm1_pr_3","gm1_pu_3","gm1_wdh_8","gm1_wd_8","gm1_wlh_8","gm1_wl_8","gm1_wrh_8","gm1_wr_8","gm1_wuh_8","gm1_wu_8",
    "f_bk_n","f_dn_n","f_hb_n","f_me_n","f_ms_n","f_pk_n","f_pz_n","f_tm_n",
    "mou1_d","mou1_l","mou1_u","mou1_wd_4","mou1_wl_4","mou1_wr_4","mou1_wu_4",
    "exp26_b_16", "exp27_b_16", "exp28_b_16", "exp29_b_16", "exp30_b_16", "exp31_b_16", "exp32_b_16",
    "main_gui", "main_gui2", "main_gui3", "main_gui4",
    "healthbar_bg", "healthbar_guide", "healthbar_main",
    "table",
    "playercollider",
    "extrascenery",
    "smoke_appear_7"
};

const char FileNamesHolder::foodNames[][20] = {
    "cake","donut","burger","melon","milk shake","pumpkin","pizza","tomato",
};

