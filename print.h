__asm__(\
".data\t\n"\
".myStr:\t\n"\
".string \"$%d:%8x\\n\"\t\n"\
);


#define printReg(); __asm__(\
".code\t\n"\
".alignw	1\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,0\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$0\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,1\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$1\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,2\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$2\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,3\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$3\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,4\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$4\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,5\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$5\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,6\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$6\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,7\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$7\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,8\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$8\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,9\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$9\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,10\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$10\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,11\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$11\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,12\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$12\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,13\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$13\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,14\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$14\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,15\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$15\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,16\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$16\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,17\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$17\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,18\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$18\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,19\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$19\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,20\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$20\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,21\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$21\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,22\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$22\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,23\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$23\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,24\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$24\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,25\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$25\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,26\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$26\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,27\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$27\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,28\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$28\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,29\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$29\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,30\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$30\t\n"\
"long_call _printf\t\n"\
"aqw_ld		vb,sp\t\n"\
"long_ld	wq,.myStr\t\n"\
"aqw_add	vb,sp,4\t\n"\
"ld			wq,31\t\n"\
"aqw_add	vb,sp,8\t\n"\
"ld			wq,$31\t\n"\
"long_call _printf\t\n"\
);
	