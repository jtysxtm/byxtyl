--- factorial_O1.s	2023-09-16 10:55:19.000000000 +0800
+++ factorial_O2.s	2023-09-16 10:55:54.000000000 +0800
@@ -16,10 +16,9 @@
 	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
 	movl	$_ZStL8__ioinit, %esi
 	movl	$__dso_handle, %edx
-	callq	__cxa_atexit@PLT
 	popq	%rbp
 	.cfi_def_cfa %rsp, 8
-	retq
+	jmp	__cxa_atexit@PLT                # TAILCALL
 .Lfunc_end0:
 	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
 	.cfi_endproc
@@ -82,10 +81,9 @@
 	.cfi_offset %rbp, -16
 	movq	%rsp, %rbp
 	.cfi_def_cfa_register %rbp
-	callq	__cxx_global_var_init
 	popq	%rbp
 	.cfi_def_cfa %rsp, 8
-	retq
+	jmp	__cxx_global_var_init           # TAILCALL
 .Lfunc_end2:
 	.size	_GLOBAL__sub_I_factorial.cpp, .Lfunc_end2-_GLOBAL__sub_I_factorial.cpp
 	.cfi_endproc
