/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Aoran Zeng <ccmywish@qq.com>
 * Contributors  :  Nil Null  <nil@null.org>
 * Created On    : <2023-09-15>
 * Last Modified : <2025-07-14>
 * ------------------------------------------------------------*/

/**
 * @update 2025-07-14
 */
static Source_t pl_ocaml_sources[] =
{
  {&UpstreamProvider, NULL, NULL},
  {&Sjtug_Zhiyuan,   "https://mirrors.sjtug.sjtu.edu.cn/git/opam-repository.git", NULL}
};
def_sources_n(pl_ocaml);


void
pl_ocaml_check_cmd ()
{
  chsrc_ensure_program ("opam");
}


void
pl_ocaml_getsrc (char *option)
{
  pl_ocaml_check_cmd ();
  chsrc_run ("opam repo get-url default", RunOpt_Default);
}


/**
 * @consult https://mirrors.sjtug.sjtu.edu.cn/docs/git/opam-repository.git
 */
void
pl_ocaml_setsrc (char *option)
{
  pl_ocaml_check_cmd ();

  chsrc_yield_source_and_confirm (pl_ocaml);

  char *cmd = xy_strjoin (3, "opam repo set-url default ",
                              source.url,
                             " --all --set-default");

  chsrc_run (cmd, RunOpt_Default);

  chsrc_alert2 ("如果是首次使用 opam ，请使用以下命令进行初始化");
  println (xy_2strjoin ("opam init default ", source.url));

  chsrc_determine_chgtype (ChgType_SemiAuto);
  chsrc_conclude (&source);
}


Feature_t
pl_ocaml_feat (char *option)
{
  Feature_t f = {0};

  f.can_get = true;
  f.can_reset = false;

  f.cap_locally = CanNot;
  f.cap_locally_explain = NA;
  f.can_english = false;
  f.can_user_define = true;

  f.note = NULL;
  return f;
}


def_target_gsf(pl_ocaml);
