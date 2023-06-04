#include "cpu.h"

namespace emulator
{
void CPU::create_opcode_table()
{
    opcode_table = 
    { 
        &CPU::opcode_00, &CPU::opcode_01, &CPU::opcode_02, &CPU::opcode_03, &CPU::opcode_04, &CPU::opcode_05, &CPU::opcode_06, &CPU::opcode_07,
        &CPU::opcode_08, &CPU::opcode_09, &CPU::opcode_0a, &CPU::opcode_0b, &CPU::opcode_0c, &CPU::opcode_0d, &CPU::opcode_0e, &CPU::opcode_0f,
        &CPU::opcode_10, &CPU::opcode_11, &CPU::opcode_12, &CPU::opcode_13, &CPU::opcode_14, &CPU::opcode_15, &CPU::opcode_16, &CPU::opcode_17,
        &CPU::opcode_18, &CPU::opcode_19, &CPU::opcode_1a, &CPU::opcode_1b, &CPU::opcode_1c, &CPU::opcode_1d, &CPU::opcode_1e, &CPU::opcode_1f,
        &CPU::opcode_20, &CPU::opcode_21, &CPU::opcode_22, &CPU::opcode_23, &CPU::opcode_24, &CPU::opcode_25, &CPU::opcode_26, &CPU::opcode_27,
        &CPU::opcode_28, &CPU::opcode_29, &CPU::opcode_2a, &CPU::opcode_2b, &CPU::opcode_2c, &CPU::opcode_2d, &CPU::opcode_2e, &CPU::opcode_2f,
        &CPU::opcode_30, &CPU::opcode_31, &CPU::opcode_32, &CPU::opcode_33, &CPU::opcode_34, &CPU::opcode_35, &CPU::opcode_36, &CPU::opcode_37,
        &CPU::opcode_38, &CPU::opcode_39, &CPU::opcode_3a, &CPU::opcode_3b, &CPU::opcode_3c, &CPU::opcode_3d, &CPU::opcode_3e, &CPU::opcode_3f,
        &CPU::opcode_40, &CPU::opcode_41, &CPU::opcode_42, &CPU::opcode_43, &CPU::opcode_44, &CPU::opcode_45, &CPU::opcode_46, &CPU::opcode_47,
        &CPU::opcode_48, &CPU::opcode_49, &CPU::opcode_4a, &CPU::opcode_4b, &CPU::opcode_4c, &CPU::opcode_4d, &CPU::opcode_4e, &CPU::opcode_4f,
        &CPU::opcode_50, &CPU::opcode_51, &CPU::opcode_52, &CPU::opcode_53, &CPU::opcode_54, &CPU::opcode_55, &CPU::opcode_56, &CPU::opcode_57,
        &CPU::opcode_58, &CPU::opcode_59, &CPU::opcode_5a, &CPU::opcode_5b, &CPU::opcode_5c, &CPU::opcode_5d, &CPU::opcode_5e, &CPU::opcode_5f,
        &CPU::opcode_60, &CPU::opcode_61, &CPU::opcode_62, &CPU::opcode_63, &CPU::opcode_64, &CPU::opcode_65, &CPU::opcode_66, &CPU::opcode_67,
        &CPU::opcode_68, &CPU::opcode_69, &CPU::opcode_6a, &CPU::opcode_6b, &CPU::opcode_6c, &CPU::opcode_6d, &CPU::opcode_6e, &CPU::opcode_6f,
        &CPU::opcode_70, &CPU::opcode_71, &CPU::opcode_72, &CPU::opcode_73, &CPU::opcode_74, &CPU::opcode_75, &CPU::opcode_76, &CPU::opcode_77,
        &CPU::opcode_78, &CPU::opcode_79, &CPU::opcode_7a, &CPU::opcode_7b, &CPU::opcode_7c, &CPU::opcode_7d, &CPU::opcode_7e, &CPU::opcode_7f,
        &CPU::opcode_80, &CPU::opcode_81, &CPU::opcode_82, &CPU::opcode_83, &CPU::opcode_84, &CPU::opcode_85, &CPU::opcode_86, &CPU::opcode_87,
        &CPU::opcode_88, &CPU::opcode_89, &CPU::opcode_8a, &CPU::opcode_8b, &CPU::opcode_8c, &CPU::opcode_8d, &CPU::opcode_8e, &CPU::opcode_8f,
        &CPU::opcode_90, &CPU::opcode_91, &CPU::opcode_92, &CPU::opcode_93, &CPU::opcode_94, &CPU::opcode_95, &CPU::opcode_96, &CPU::opcode_97,
        &CPU::opcode_98, &CPU::opcode_99, &CPU::opcode_9a, &CPU::opcode_9b, &CPU::opcode_9c, &CPU::opcode_9d, &CPU::opcode_9e, &CPU::opcode_9f,
        &CPU::opcode_a0, &CPU::opcode_a1, &CPU::opcode_a2, &CPU::opcode_a3, &CPU::opcode_a4, &CPU::opcode_a5, &CPU::opcode_a6, &CPU::opcode_a7,
        &CPU::opcode_a8, &CPU::opcode_a9, &CPU::opcode_aa, &CPU::opcode_ab, &CPU::opcode_ac, &CPU::opcode_ad, &CPU::opcode_ae, &CPU::opcode_af,
        &CPU::opcode_b0, &CPU::opcode_b1, &CPU::opcode_b2, &CPU::opcode_b3, &CPU::opcode_b4, &CPU::opcode_b5, &CPU::opcode_b6, &CPU::opcode_b7,
        &CPU::opcode_b8, &CPU::opcode_b9, &CPU::opcode_ba, &CPU::opcode_bb, &CPU::opcode_bc, &CPU::opcode_bd, &CPU::opcode_be, &CPU::opcode_bf,
        &CPU::opcode_c0, &CPU::opcode_c1, &CPU::opcode_c2, &CPU::opcode_c3, &CPU::opcode_c4, &CPU::opcode_c5, &CPU::opcode_c6, &CPU::opcode_c7,
        &CPU::opcode_c8, &CPU::opcode_c9, &CPU::opcode_ca, &CPU::opcode_cb, &CPU::opcode_cc, &CPU::opcode_cd, &CPU::opcode_ce, &CPU::opcode_cf,
        &CPU::opcode_d0, &CPU::opcode_d1, &CPU::opcode_d2, &CPU::opcode_d3, &CPU::opcode_d4, &CPU::opcode_d5, &CPU::opcode_d6, &CPU::opcode_d7,
        &CPU::opcode_d8, &CPU::opcode_d9, &CPU::opcode_da, &CPU::opcode_db, &CPU::opcode_dc, &CPU::opcode_dd, &CPU::opcode_de, &CPU::opcode_df,
        &CPU::opcode_e0, &CPU::opcode_e1, &CPU::opcode_e2, &CPU::opcode_e3, &CPU::opcode_e4, &CPU::opcode_e5, &CPU::opcode_e6, &CPU::opcode_e7,
        &CPU::opcode_e8, &CPU::opcode_e9, &CPU::opcode_ea, &CPU::opcode_eb, &CPU::opcode_ec, &CPU::opcode_ed, &CPU::opcode_ee, &CPU::opcode_ef,
        &CPU::opcode_f0, &CPU::opcode_f1, &CPU::opcode_f2, &CPU::opcode_f3, &CPU::opcode_f4, &CPU::opcode_f5, &CPU::opcode_f6, &CPU::opcode_f7,
        &CPU::opcode_f8, &CPU::opcode_f9, &CPU::opcode_fa, &CPU::opcode_fb, &CPU::opcode_fc, &CPU::opcode_fd, &CPU::opcode_fe, &CPU::opcode_ff 
    };
}

void CPU::create_cb_opcode_table()
{
    cb_opcode_table = 
    { 
        &CPU::opcode_cb_00, &CPU::opcode_cb_01, &CPU::opcode_cb_02, &CPU::opcode_cb_03, &CPU::opcode_cb_04, &CPU::opcode_cb_05, &CPU::opcode_cb_06, &CPU::opcode_cb_07,
        &CPU::opcode_cb_08, &CPU::opcode_cb_09, &CPU::opcode_cb_0a, &CPU::opcode_cb_0b, &CPU::opcode_cb_0c, &CPU::opcode_cb_0d, &CPU::opcode_cb_0e, &CPU::opcode_cb_0f,
        &CPU::opcode_cb_10, &CPU::opcode_cb_11, &CPU::opcode_cb_12, &CPU::opcode_cb_13, &CPU::opcode_cb_14, &CPU::opcode_cb_15, &CPU::opcode_cb_16, &CPU::opcode_cb_17,
        &CPU::opcode_cb_18, &CPU::opcode_cb_19, &CPU::opcode_cb_1a, &CPU::opcode_cb_1b, &CPU::opcode_cb_1c, &CPU::opcode_cb_1d, &CPU::opcode_cb_1e, &CPU::opcode_cb_1f,
        &CPU::opcode_cb_20, &CPU::opcode_cb_21, &CPU::opcode_cb_22, &CPU::opcode_cb_23, &CPU::opcode_cb_24, &CPU::opcode_cb_25, &CPU::opcode_cb_26, &CPU::opcode_cb_27,
        &CPU::opcode_cb_28, &CPU::opcode_cb_29, &CPU::opcode_cb_2a, &CPU::opcode_cb_2b, &CPU::opcode_cb_2c, &CPU::opcode_cb_2d, &CPU::opcode_cb_2e, &CPU::opcode_cb_2f,
        &CPU::opcode_cb_30, &CPU::opcode_cb_31, &CPU::opcode_cb_32, &CPU::opcode_cb_33, &CPU::opcode_cb_34, &CPU::opcode_cb_35, &CPU::opcode_cb_36, &CPU::opcode_cb_37,
        &CPU::opcode_cb_38, &CPU::opcode_cb_39, &CPU::opcode_cb_3a, &CPU::opcode_cb_3b, &CPU::opcode_cb_3c, &CPU::opcode_cb_3d, &CPU::opcode_cb_3e, &CPU::opcode_cb_3f,
        &CPU::opcode_cb_40, &CPU::opcode_cb_41, &CPU::opcode_cb_42, &CPU::opcode_cb_43, &CPU::opcode_cb_44, &CPU::opcode_cb_45, &CPU::opcode_cb_46, &CPU::opcode_cb_47,
        &CPU::opcode_cb_48, &CPU::opcode_cb_49, &CPU::opcode_cb_4a, &CPU::opcode_cb_4b, &CPU::opcode_cb_4c, &CPU::opcode_cb_4d, &CPU::opcode_cb_4e, &CPU::opcode_cb_4f,
        &CPU::opcode_cb_50, &CPU::opcode_cb_51, &CPU::opcode_cb_52, &CPU::opcode_cb_53, &CPU::opcode_cb_54, &CPU::opcode_cb_55, &CPU::opcode_cb_56, &CPU::opcode_cb_57,
        &CPU::opcode_cb_58, &CPU::opcode_cb_59, &CPU::opcode_cb_5a, &CPU::opcode_cb_5b, &CPU::opcode_cb_5c, &CPU::opcode_cb_5d, &CPU::opcode_cb_5e, &CPU::opcode_cb_5f,
        &CPU::opcode_cb_60, &CPU::opcode_cb_61, &CPU::opcode_cb_62, &CPU::opcode_cb_63, &CPU::opcode_cb_64, &CPU::opcode_cb_65, &CPU::opcode_cb_66, &CPU::opcode_cb_67,
        &CPU::opcode_cb_68, &CPU::opcode_cb_69, &CPU::opcode_cb_6a, &CPU::opcode_cb_6b, &CPU::opcode_cb_6c, &CPU::opcode_cb_6d, &CPU::opcode_cb_6e, &CPU::opcode_cb_6f,
        &CPU::opcode_cb_70, &CPU::opcode_cb_71, &CPU::opcode_cb_72, &CPU::opcode_cb_73, &CPU::opcode_cb_74, &CPU::opcode_cb_75, &CPU::opcode_cb_76, &CPU::opcode_cb_77,
        &CPU::opcode_cb_78, &CPU::opcode_cb_79, &CPU::opcode_cb_7a, &CPU::opcode_cb_7b, &CPU::opcode_cb_7c, &CPU::opcode_cb_7d, &CPU::opcode_cb_7e, &CPU::opcode_cb_7f,
        &CPU::opcode_cb_80, &CPU::opcode_cb_81, &CPU::opcode_cb_82, &CPU::opcode_cb_83, &CPU::opcode_cb_84, &CPU::opcode_cb_85, &CPU::opcode_cb_86, &CPU::opcode_cb_87,
        &CPU::opcode_cb_88, &CPU::opcode_cb_89, &CPU::opcode_cb_8a, &CPU::opcode_cb_8b, &CPU::opcode_cb_8c, &CPU::opcode_cb_8d, &CPU::opcode_cb_8e, &CPU::opcode_cb_8f,
        &CPU::opcode_cb_90, &CPU::opcode_cb_91, &CPU::opcode_cb_92, &CPU::opcode_cb_93, &CPU::opcode_cb_94, &CPU::opcode_cb_95, &CPU::opcode_cb_96, &CPU::opcode_cb_97,
        &CPU::opcode_cb_98, &CPU::opcode_cb_99, &CPU::opcode_cb_9a, &CPU::opcode_cb_9b, &CPU::opcode_cb_9c, &CPU::opcode_cb_9d, &CPU::opcode_cb_9e, &CPU::opcode_cb_9f,
        &CPU::opcode_cb_a0, &CPU::opcode_cb_a1, &CPU::opcode_cb_a2, &CPU::opcode_cb_a3, &CPU::opcode_cb_a4, &CPU::opcode_cb_a5, &CPU::opcode_cb_a6, &CPU::opcode_cb_a7,
        &CPU::opcode_cb_a8, &CPU::opcode_cb_a9, &CPU::opcode_cb_aa, &CPU::opcode_cb_ab, &CPU::opcode_cb_ac, &CPU::opcode_cb_ad, &CPU::opcode_cb_ae, &CPU::opcode_cb_af,
        &CPU::opcode_cb_b0, &CPU::opcode_cb_b1, &CPU::opcode_cb_b2, &CPU::opcode_cb_b3, &CPU::opcode_cb_b4, &CPU::opcode_cb_b5, &CPU::opcode_cb_b6, &CPU::opcode_cb_b7,
        &CPU::opcode_cb_b8, &CPU::opcode_cb_b9, &CPU::opcode_cb_ba, &CPU::opcode_cb_bb, &CPU::opcode_cb_bc, &CPU::opcode_cb_bd, &CPU::opcode_cb_be, &CPU::opcode_cb_bf,
        &CPU::opcode_cb_c0, &CPU::opcode_cb_c1, &CPU::opcode_cb_c2, &CPU::opcode_cb_c3, &CPU::opcode_cb_c4, &CPU::opcode_cb_c5, &CPU::opcode_cb_c6, &CPU::opcode_cb_c7,
        &CPU::opcode_cb_c8, &CPU::opcode_cb_c9, &CPU::opcode_cb_ca, &CPU::opcode_cb_cb, &CPU::opcode_cb_cc, &CPU::opcode_cb_cd, &CPU::opcode_cb_ce, &CPU::opcode_cb_cf,
        &CPU::opcode_cb_d0, &CPU::opcode_cb_d1, &CPU::opcode_cb_d2, &CPU::opcode_cb_d3, &CPU::opcode_cb_d4, &CPU::opcode_cb_d5, &CPU::opcode_cb_d6, &CPU::opcode_cb_d7,
        &CPU::opcode_cb_d8, &CPU::opcode_cb_d9, &CPU::opcode_cb_da, &CPU::opcode_cb_db, &CPU::opcode_cb_dc, &CPU::opcode_cb_dd, &CPU::opcode_cb_de, &CPU::opcode_cb_df,
        &CPU::opcode_cb_e0, &CPU::opcode_cb_e1, &CPU::opcode_cb_e2, &CPU::opcode_cb_e3, &CPU::opcode_cb_e4, &CPU::opcode_cb_e5, &CPU::opcode_cb_e6, &CPU::opcode_cb_e7,
        &CPU::opcode_cb_e8, &CPU::opcode_cb_e9, &CPU::opcode_cb_ea, &CPU::opcode_cb_eb, &CPU::opcode_cb_ec, &CPU::opcode_cb_ed, &CPU::opcode_cb_ee, &CPU::opcode_cb_ef,
        &CPU::opcode_cb_f0, &CPU::opcode_cb_f1, &CPU::opcode_cb_f2, &CPU::opcode_cb_f3, &CPU::opcode_cb_f4, &CPU::opcode_cb_f5, &CPU::opcode_cb_f6, &CPU::opcode_cb_f7,
        &CPU::opcode_cb_f8, &CPU::opcode_cb_f9, &CPU::opcode_cb_fa, &CPU::opcode_cb_fb, &CPU::opcode_cb_fc, &CPU::opcode_cb_fd, &CPU::opcode_cb_fe, &CPU::opcode_cb_ff 
    };
}

void CPU::create_cycle_tables()
{
    cycle_table = 
    {
        1, 3, 2, 2, 1, 1, 2, 1,
        5, 2, 2, 2, 1, 1, 2, 1,
        1, 3, 2, 2, 1, 1, 2, 1,
        3, 2, 2, 2, 1, 1, 2, 1,
        2, 3, 2, 2, 1, 1, 2, 1,
        2, 2, 2, 2, 1, 1, 2, 1,
        2, 3, 2, 2, 3, 3, 3, 1,
        2, 2, 2, 2, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        2, 2, 2, 2, 2, 2, 1, 2,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        2, 3, 3, 4, 3, 4, 2, 4,
        2, 4, 3, 0, 3, 6, 2, 4,
        2, 3, 3, 0, 3, 4, 2, 4,
        2, 4, 3, 0, 3, 0, 2, 4,
        3, 3, 2, 0, 0, 4, 2, 4,
        4, 1, 4, 0, 0, 0, 2, 4,
        3, 3, 2, 1, 0, 4, 2, 4,
        3, 2, 4, 1, 0, 0, 2, 4 
    };
    
    cycle_branch_table = 
    {
        1, 3, 2, 2, 1, 1, 2, 1,
        5, 2, 2, 2, 1, 1, 2, 1,
        1, 3, 2, 2, 1, 1, 2, 1,
        3, 2, 2, 2, 1, 1, 2, 1,
        3, 3, 2, 2, 1, 1, 2, 1,
        3, 2, 2, 2, 1, 1, 2, 1,
        3, 3, 2, 2, 3, 3, 3, 1,
        3, 2, 2, 2, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        2, 2, 2, 2, 2, 2, 1, 2,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 2, 1,
        5, 3, 4, 4, 6, 4, 2, 4,
        5, 4, 4, 0, 6, 6, 2, 4,
        5, 3, 4, 0, 6, 4, 2, 4,
        5, 4, 4, 0, 6, 0, 2, 4,
        3, 3, 2, 0, 0, 4, 2, 4,
        4, 1, 4, 0, 0, 0, 2, 4,
        3, 3, 2, 1, 0, 4, 2, 4,
        3, 2, 4, 1, 0, 0, 2, 4
    };

    cycle_cb_table = 
    {
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2
    };
}
}