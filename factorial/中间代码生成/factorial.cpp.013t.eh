
;; Function main (main, funcdef_no=1778, decl_uid=44906, cgraph_uid=512, symbol_order=542)

int main ()
{
  struct basic_ostream & D.49814;
  int f;
  int n;
  int i;
  int D.49812;

  std::basic_istream<char>::operator>> (&cin, &n);
  i = 2;
  f = 1;
  goto <D.44966>;
  <D.44967>:
  f = f * i;
  i = i + 1;
  <D.44966>:
  n.0_1 = n;
  if (i <= n.0_1) goto <D.44967>; else goto <D.44965>;
  <D.44965>:
  D.49814 = std::basic_ostream<char>::operator<< (&cout, f);
  _2 = D.49814;
  std::basic_ostream<char>::operator<< (_2, endl);
  D.49812 = 0;
  goto <D.49816>;
  <D.49816>:
  n = {CLOBBER};
  goto <D.49813>;
  D.49812 = 0;
  goto <D.49813>;
  <D.49813>:
  return D.49812;
  <D.49815>:
  n = {CLOBBER};
  resx 1
}



;; Function std::endl<char, std::char_traits<char> > (_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, funcdef_no=2039, decl_uid=42332, cgraph_uid=773, symbol_order=806)

struct basic_ostream & std::endl<char, std::char_traits<char> > (struct basic_ostream & __os)
{
  struct basic_ostream & D.49822;
  struct basic_ostream & D.49821;
  char D.49820;
  struct basic_ostream & D.49818;

  _1 = __os->_vptr.basic_ostream;
  _2 = _1 + 18446744073709551592;
  _3 = MEM[(long int *)_2];
  _4 = (sizetype) _3;
  _5 = __os + _4;
  D.49820 = std::basic_ios<char>::widen (_5, 10);
  _6 = D.49820;
  _7 = (int) _6;
  D.49821 = std::basic_ostream<char>::put (__os, _7);
  _8 = D.49821;
  D.49822 = std::flush<char, std::char_traits<char> > (_8);
  D.49818 = D.49822;
  goto <D.49819>;
  <D.49819>:
  return D.49818;
}



;; Function std::basic_ios<char>::widen (_ZNKSt9basic_iosIcSt11char_traitsIcEE5widenEc, funcdef_no=2118, decl_uid=41378, cgraph_uid=852, symbol_order=885)

char_type std::basic_ios<char>::widen (const struct basic_ios * const this, char __c)
{
  char_type D.49826;
  const struct ctype & D.49825;
  char_type D.49823;

  _1 = this->_M_ctype;
  D.49825 = std::__check_facet<std::ctype<char> > (_1);
  _2 = D.49825;
  _3 = (int) __c;
  D.49826 = std::ctype<char>::widen (_2, _3);
  D.49823 = D.49826;
  goto <D.49824>;
  <D.49824>:
  return D.49823;
}



;; Function std::__check_facet<std::ctype<char> > (_ZSt13__check_facetISt5ctypeIcEERKT_PS3_, funcdef_no=2154, decl_uid=48103, cgraph_uid=888, symbol_order=921)

const struct ctype & std::__check_facet<std::ctype<char> > (const struct ctype * __f)
{
  const struct ctype & D.49829;

  if (__f == 0B) goto <D.49827>; else goto <D.49828>;
  <D.49827>:
  std::__throw_bad_cast ();
  <D.49828>:
  D.49829 = __f;
  goto <D.49830>;
  <D.49830>:
  return D.49829;
}



;; Function std::ctype<char>::widen (_ZNKSt5ctypeIcE5widenEc, funcdef_no=1526, decl_uid=37816, cgraph_uid=497, symbol_order=526)

char_type std::ctype<char>::widen (const struct ctype * const this, char __c)
{
  char_type D.49835;
  char_type D.49833;

  _1 = this->_M_widen_ok;
  if (_1 != 0) goto <D.49831>; else goto <D.49832>;
  <D.49831>:
  __c.1_2 = (unsigned char) __c;
  _3 = (int) __c.1_2;
  D.49833 = this->_M_widen[_3];
  // predicted unlikely by early return (on trees) predictor.
  goto <D.49834>;
  <D.49832>:
  std::ctype<char>::_M_widen_init (this);
  _4 = this->D.37930._vptr.facet;
  _5 = _4 + 48;
  _6 = *_5;
  _7 = (int) __c;
  D.49835 = OBJ_TYPE_REF(_6;(const struct ctype)this->6) (this, _7);
  D.49833 = D.49835;
  goto <D.49834>;
  <D.49834>:
  return D.49833;
}



;; Function std::ctype<char>::do_widen (_ZNKSt5ctypeIcE8do_widenEc, funcdef_no=1531, decl_uid=37864, cgraph_uid=502, symbol_order=531)

char_type std::ctype<char>::do_widen (const struct ctype * const this, char __c)
{
  char_type D.49836;

  D.49836 = __c;
  goto <D.49837>;
  <D.49837>:
  return D.49836;
}



;; Function std::flush<char, std::char_traits<char> > (_ZSt5flushIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, funcdef_no=2119, decl_uid=42340, cgraph_uid=853, symbol_order=886)

struct basic_ostream & std::flush<char, std::char_traits<char> > (struct basic_ostream & __os)
{
  struct basic_ostream & D.49840;
  struct basic_ostream & D.49838;

  D.49840 = std::basic_ostream<char>::flush (__os);
  D.49838 = D.49840;
  goto <D.49839>;
  <D.49839>:
  return D.49838;
}



;; Function std::basic_ostream<char>::operator<< (_ZNSolsEPFRSoS_E, funcdef_no=2040, decl_uid=42120, cgraph_uid=774, symbol_order=807)

struct __ostream_type & std::basic_ostream<char>::operator<< (struct basic_ostream * const this, struct __ostream_type & (*<T65a7>) (struct __ostream_type &) __pf)
{
  struct __ostream_type & D.49843;
  struct __ostream_type & D.49841;

  __pf.2_1 = __pf;
  D.49843 = __pf.2_1 (this);
  D.49841 = D.49843;
  goto <D.49842>;
  <D.49842>:
  return D.49841;
}



;; Function _GLOBAL__sub_I_main (_GLOBAL__sub_I_main, funcdef_no=2279, decl_uid=49810, cgraph_uid=1013, symbol_order=1188)

void _GLOBAL__sub_I_main ()
{
  __static_initialization_and_destruction_0 (1, 65535);
  return;
}



;; Function __static_initialization_and_destruction_0 (_Z41__static_initialization_and_destruction_0ii, funcdef_no=2278, decl_uid=49804, cgraph_uid=1012, symbol_order=1069)

void __static_initialization_and_destruction_0 (int __initialize_p, int __priority)
{
  if (__initialize_p == 1) goto <D.49844>; else goto <D.49845>;
  <D.49844>:
  if (__priority == 65535) goto <D.49846>; else goto <D.49847>;
  <D.49846>:
  std::ios_base::Init::Init (&__ioinit);
  __cxxabiv1::__cxa_atexit (__dt_comp , &__ioinit, &__dso_handle);
  goto <D.49848>;
  <D.49847>:
  <D.49848>:
  goto <D.49849>;
  <D.49845>:
  <D.49849>:
  return;
}


