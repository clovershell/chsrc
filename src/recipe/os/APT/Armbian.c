/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Shengwei Chen <414685209@qq.com>
 * Contributors  :  Aoran Zeng   <ccmywish@qq.com>
 *               |  Yangmoooo <yangmoooo@outlook.com>
 *               |
 * Created On    : <2024-06-14>
 * Last Modified : <2025-07-14>
 * ------------------------------------------------------------*/

/**
 * @update 2024-11-21
 */
static Source_t os_armbian_sources[] =
{
  {&UpstreamProvider, "http://apt.armbian.com", NULL},
  {&MirrorZ,          "https://mirrors.cernet.edu.cn/armbian",        DelegateToMirror},
  {&Tuna,             "https://mirrors.tuna.tsinghua.edu.cn/armbian", DelegateToMirror},
  {&Sjtug_Zhiyuan,    "https://mirror.sjtu.edu.cn/armbian",            DelegateToMirror},
  {&Bfsu,             "https://mirrors.bfsu.edu.cn/armbian",           DelegateToMirror},
  {&Sustech,          "https://mirrors.sustech.edu.cn/armbian",        DelegateToMirror},
  {&Ustc,             "https://mirrors.ustc.edu.cn/armbian",           DelegateToMirror},
  {&Nju,              "https://mirrors.nju.edu.cn/armbian",             DelegateToMirror},
  {&Ali,              "https://mirrors.aliyun.com/armbian",             DelegateToMirror},
};
def_sources_n(os_armbian);


void
os_armbian_getsrc (char *option)
{
  if (chsrc_check_file (OS_Armbian_SourceList))
    {
      chsrc_view_file (OS_Armbian_SourceList);
      return;
    }

  char *msg = ENGLISH ? "Source list config file missing! Path: " OS_Armbian_SourceList
                      : "缺少源配置文件！路径：" OS_Armbian_SourceList;
  chsrc_error2 (msg);
}


/**
 * @consult https://mirrors.tuna.tsinghua.edu.cn/help/armbian
 */
void
os_armbian_setsrc (char *option)
{
  chsrc_ensure_root ();

  chsrc_yield_source_and_confirm (os_armbian);

  chsrc_backup (OS_Armbian_SourceList);

  char *cmd = xy_strjoin (3, "sed -E -i 's@https?[^ ]*armbian/?[^ ]*@", source.url,
                             "@g' " OS_Armbian_SourceList);

  chsrc_run (cmd, RunOpt_Default);
  chsrc_run ("apt update", RunOpt_No_Last_New_Line);

  chsrc_determine_chgtype (ChgType_Auto);
  chsrc_conclude (&source);
}


void
os_armbian_resetsrc (char *option)
{
  os_armbian_setsrc (option);
}


Feature_t
os_armbian_feat (char *option)
{
  Feature_t f = {0};

  f.can_get = true;
  f.can_reset = true;

  f.cap_locally = CanNot;
  f.can_english = true;
  f.can_user_define = true;

  return f;
}

def_target_gsrf(os_armbian);
