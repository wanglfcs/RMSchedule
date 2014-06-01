#define breakpoint(); __asm__ (\
"ld       wq, $1	\n\t" \
"ld       wq, $2  \n\t" \
"ld       wq, $3  \n\t" \
"ld       wq, $4  \n\t" \
"ld       wq, $5  \n\t" \
"ld       wq, $6  \n\t" \
"ld       wq, $7  \n\t" \
"ld       wq, $8  \n\t" \
"ld       wq, $9  \n\t" \
"ld       wq, $10 \n\t" \
"ld       wq, $11 \n\t" \
"ld       wq, $12 \n\t" \
"ld       wq, $13 \n\t" \
"ld       wq, $14 \n\t" \
"ld       wq, $15 \n\t" \
"ld       wq, $16 \n\t" \
"ld       wq, $17 \n\t" \
"ld       wq, $18 \n\t" \
"ld       wq, $19 \n\t" \
"ld       wq, $20 \n\t" \
"ld       wq, $21 \n\t" \
"ld       wq, $22 \n\t" \
"ld       wq, $23 \n\t" \
"ld       wq, $24 \n\t" \
"ld       wq, $25 \n\t" \
"ld       wq, $26 \n\t" \
"ld       wq, $27 \n\t" \
"ld       wq, $28 \n\t" \
"add      wq, zero, $29  \n\t" \
"ld       wq, link\n\t" \
"ld		  $1,30\n\t"\
"j7       1        \n\t" \
"sub  link, link, 4 \n\t" \
"aqw_add  link, link, 4 \n\t" \
"sub      $1, $1, 1 \n\t" \
"jnz      .-2 \n\t" \
"aqr_ld	  vb,122\n\t"\
"ld		  $2,rq\n\t"\
"ld		  wq,$2\n\t"\
"aqw_add  link,link,4\n\t"\
);

#define returnBreakpoint(); __asm__ (\
"j7  1\n\t" \
"sub      link, link, 4  \n\t" \
"ld       $1, 31      \n\t" \
"aqr_add  link, link, 4  \n\t" \
"sub      $1, $1, 1\n\t" \
"jnz      .-2            \n\t" \
"ld       $1, rq         \n\t" \
"ld       $2, rq         \n\t" \
"ld       $3, rq         \n\t" \
"ld       $4, rq         \n\t" \
"ld       $5, rq         \n\t" \
"ld       $6, rq         \n\t" \
"ld       $7, rq         \n\t" \
"ld       $8, rq         \n\t" \
"ld       $9, rq         \n\t" \
"ld       $10, rq        \n\t" \
"ld       $11, rq        \n\t" \
"ld       $12, rq        \n\t" \
"ld       $13, rq        \n\t" \
"ld       $14, rq        \n\t" \
"ld       $15, rq        \n\t" \
"ld       $16, rq        \n\t" \
"ld       $17, rq        \n\t" \
"ld       $18, rq        \n\t" \
"ld       $19, rq        \n\t" \
"ld       $20, rq        \n\t" \
"ld       $21, rq        \n\t" \
"ld       $22, rq        \n\t" \
"ld       $23, rq        \n\t" \
"ld       $24, rq        \n\t" \
"ld       $25, rq        \n\t" \
"ld       $26, rq        \n\t" \
"ld       $27, rq        \n\t" \
"ld       $28, rq        \n\t" \
"ld       $29, rq        \n\t" \
"ld       link, rq       \n\t" \
"j		  rq             \n\t"\
);
