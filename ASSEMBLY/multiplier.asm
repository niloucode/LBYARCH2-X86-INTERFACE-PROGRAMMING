section .text

	default rel
	bits 64
	global multiplier

	multiplier:	
		XOR rax, rax
		XORPD xmm0, xmm0 
		L1:
			MOVSD xmm4, qword [rdx]
			MULSD xmm4, qword [r8]
			ADDSD xmm0, xmm4
			ADD rdx, 8
			ADD r8, 8
			LOOP L1

	ret