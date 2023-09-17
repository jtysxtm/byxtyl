--- fib.s	2023-09-13 17:23:38.000000000 +0800
+++ fibO1.s	2023-09-16 10:50:09.000000000 +0800
@@ -1,155 +1,118 @@
-	.file	"fib.cpp"
 	.text
-	.local	_ZStL8__ioinit
-	.comm	_ZStL8__ioinit,1,1
-	.globl	main
-	.type	main, @function
-main:
-.LFB1731:
+	.file	"fib.cpp"
+	.section	.text.startup,"ax",@progbits
+	.p2align	4, 0x90                         # -- Begin function __cxx_global_var_init
+	.type	__cxx_global_var_init,@function
+__cxx_global_var_init:                  # @__cxx_global_var_init
 	.cfi_startproc
-	endbr64
+# %bb.0:
 	pushq	%rbp
 	.cfi_def_cfa_offset 16
-	.cfi_offset 6, -16
+	.cfi_offset %rbp, -16
 	movq	%rsp, %rbp
-	.cfi_def_cfa_register 6
-	subq	$32, %rsp
-	movq	%fs:40, %rax
-	movq	%rax, -8(%rbp)
-	xorl	%eax, %eax
-	movl	$0, -24(%rbp)
-	movl	$1, -20(%rbp)
-	movl	$1, -16(%rbp)
-	leaq	-28(%rbp), %rax
-	movq	%rax, %rsi
-	leaq	_ZSt3cin(%rip), %rax
-	movq	%rax, %rdi
-	call	_ZNSirsERi@PLT
-	movl	-24(%rbp), %eax
-	movl	%eax, %esi
-	leaq	_ZSt4cout(%rip), %rax
-	movq	%rax, %rdi
-	call	_ZNSolsEi@PLT
-	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx
-	movq	%rdx, %rsi
-	movq	%rax, %rdi
-	call	_ZNSolsEPFRSoS_E@PLT
-	movl	-20(%rbp), %eax
-	movl	%eax, %esi
-	leaq	_ZSt4cout(%rip), %rax
-	movq	%rax, %rdi
-	call	_ZNSolsEi@PLT
-	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx
-	movq	%rdx, %rsi
-	movq	%rax, %rdi
-	call	_ZNSolsEPFRSoS_E@PLT
-	jmp	.L2
-.L3:
-	movl	-20(%rbp), %eax
-	movl	%eax, -12(%rbp)
-	movl	-24(%rbp), %eax
-	addl	%eax, -20(%rbp)
-	movl	-20(%rbp), %eax
-	movl	%eax, %esi
-	leaq	_ZSt4cout(%rip), %rax
-	movq	%rax, %rdi
-	call	_ZNSolsEi@PLT
-	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx
-	movq	%rdx, %rsi
-	movq	%rax, %rdi
-	call	_ZNSolsEPFRSoS_E@PLT
-	movl	-12(%rbp), %eax
-	movl	%eax, -24(%rbp)
-	addl	$1, -16(%rbp)
-.L2:
-	movl	-28(%rbp), %eax
-	cmpl	%eax, -16(%rbp)
-	jl	.L3
-	movl	$0, %eax
-	movq	-8(%rbp), %rdx
-	subq	%fs:40, %rdx
-	je	.L5
-	call	__stack_chk_fail@PLT
-.L5:
-	leave
-	.cfi_def_cfa 7, 8
-	ret
+	.cfi_def_cfa_register %rbp
+	movl	$_ZStL8__ioinit, %edi
+	callq	_ZNSt8ios_base4InitC1Ev@PLT
+	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
+	movl	$_ZStL8__ioinit, %esi
+	movl	$__dso_handle, %edx
+	callq	__cxa_atexit@PLT
+	popq	%rbp
+	.cfi_def_cfa %rsp, 8
+	retq
+.Lfunc_end0:
+	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
 	.cfi_endproc
-.LFE1731:
-	.size	main, .-main
-	.type	_Z41__static_initialization_and_destruction_0ii, @function
-_Z41__static_initialization_and_destruction_0ii:
-.LFB2231:
+                                        # -- End function
+	.text
+	.globl	main                            # -- Begin function main
+	.p2align	4, 0x90
+	.type	main,@function
+main:                                   # @main
 	.cfi_startproc
-	endbr64
+# %bb.0:
 	pushq	%rbp
 	.cfi_def_cfa_offset 16
-	.cfi_offset 6, -16
+	.cfi_offset %rbp, -16
 	movq	%rsp, %rbp
-	.cfi_def_cfa_register 6
-	subq	$16, %rsp
-	movl	%edi, -4(%rbp)
-	movl	%esi, -8(%rbp)
-	cmpl	$1, -4(%rbp)
-	jne	.L8
-	cmpl	$65535, -8(%rbp)
-	jne	.L8
-	leaq	_ZStL8__ioinit(%rip), %rax
-	movq	%rax, %rdi
-	call	_ZNSt8ios_base4InitC1Ev@PLT
-	leaq	__dso_handle(%rip), %rax
-	movq	%rax, %rdx
-	leaq	_ZStL8__ioinit(%rip), %rax
-	movq	%rax, %rsi
-	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
+	.cfi_def_cfa_register %rbp
+	subq	$32, %rsp
+	movl	$0, -24(%rbp)
+	movl	$0, -12(%rbp)
+	movl	$1, -4(%rbp)
+	movl	$1, -8(%rbp)
+	movq	_ZSt3cin@GOTPCREL(%rip), %rdi
+	leaq	-16(%rbp), %rsi
+	callq	_ZNSirsERi@PLT
+	movl	-12(%rbp), %esi
+	movq	_ZSt4cout@GOTPCREL(%rip), %rdi
+	callq	_ZNSolsEi@PLT
+	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rsi
+	movq	%rax, %rdi
+	callq	_ZNSolsEPFRSoS_E@PLT
+	movl	-4(%rbp), %esi
+	movq	_ZSt4cout@GOTPCREL(%rip), %rdi
+	callq	_ZNSolsEi@PLT
+	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rsi
+	movq	%rax, %rdi
+	callq	_ZNSolsEPFRSoS_E@PLT
+.LBB1_1:                                # =>This Inner Loop Header: Depth=1
+	movl	-8(%rbp), %eax
+	cmpl	-16(%rbp), %eax
+	jge	.LBB1_3
+# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
+	movl	-4(%rbp), %eax
+	movl	%eax, -20(%rbp)
+	movl	-12(%rbp), %eax
+	addl	-4(%rbp), %eax
+	movl	%eax, -4(%rbp)
+	movl	-4(%rbp), %esi
+	movq	_ZSt4cout@GOTPCREL(%rip), %rdi
+	callq	_ZNSolsEi@PLT
+	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rsi
 	movq	%rax, %rdi
-	call	__cxa_atexit@PLT
-.L8:
-	nop
-	leave
-	.cfi_def_cfa 7, 8
-	ret
+	callq	_ZNSolsEPFRSoS_E@PLT
+	movl	-20(%rbp), %eax
+	movl	%eax, -12(%rbp)
+	movl	-8(%rbp), %eax
+	addl	$1, %eax
+	movl	%eax, -8(%rbp)
+	jmp	.LBB1_1
+.LBB1_3:
+	xorl	%eax, %eax
+	addq	$32, %rsp
+	popq	%rbp
+	.cfi_def_cfa %rsp, 8
+	retq
+.Lfunc_end1:
+	.size	main, .Lfunc_end1-main
 	.cfi_endproc
-.LFE2231:
-	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
-	.type	_GLOBAL__sub_I_main, @function
-_GLOBAL__sub_I_main:
-.LFB2232:
+                                        # -- End function
+	.section	.text.startup,"ax",@progbits
+	.p2align	4, 0x90                         # -- Begin function _GLOBAL__sub_I_fib.cpp
+	.type	_GLOBAL__sub_I_fib.cpp,@function
+_GLOBAL__sub_I_fib.cpp:                 # @_GLOBAL__sub_I_fib.cpp
 	.cfi_startproc
-	endbr64
+# %bb.0:
 	pushq	%rbp
 	.cfi_def_cfa_offset 16
-	.cfi_offset 6, -16
+	.cfi_offset %rbp, -16
 	movq	%rsp, %rbp
-	.cfi_def_cfa_register 6
-	movl	$65535, %esi
-	movl	$1, %edi
-	call	_Z41__static_initialization_and_destruction_0ii
+	.cfi_def_cfa_register %rbp
+	callq	__cxx_global_var_init
 	popq	%rbp
-	.cfi_def_cfa 7, 8
-	ret
+	.cfi_def_cfa %rsp, 8
+	retq
+.Lfunc_end2:
+	.size	_GLOBAL__sub_I_fib.cpp, .Lfunc_end2-_GLOBAL__sub_I_fib.cpp
 	.cfi_endproc
-.LFE2232:
-	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
-	.section	.init_array,"aw"
-	.align 8
-	.quad	_GLOBAL__sub_I_main
+                                        # -- End function
+	.type	_ZStL8__ioinit,@object          # @_ZStL8__ioinit
+	.local	_ZStL8__ioinit
+	.comm	_ZStL8__ioinit,1,1
 	.hidden	__dso_handle
-	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
-	.section	.note.GNU-stack,"",@progbits
-	.section	.note.gnu.property,"a"
-	.align 8
-	.long	1f - 0f
-	.long	4f - 1f
-	.long	5
-0:
-	.string	"GNU"
-1:
-	.align 8
-	.long	0xc0000002
-	.long	3f - 2f
-2:
-	.long	0x3
-3:
-	.align 8
-4:
+	.section	.init_array,"aw",@init_array
+	.p2align	3
+	.quad	_GLOBAL__sub_I_fib.cpp
+	.ident	"Ubuntu clang version 14.0.0-1ubuntu1.1"
+	.section	".note.GNU-stack","",@progbits
