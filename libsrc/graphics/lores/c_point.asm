;
;       Z88 Graphics Functions - Small C+ stubs
;
;       Written around the Interlogic Standard Library
;
;       Stubs Written by D Morris - 30/9/98
;
;
;       $Id: point.asm,v 1.7 2016-04-13 21:09:09 dom Exp $
;


;Usage: point(struct *pixel)
;Result is true/false


		SECTION	  code_graphics
                PUBLIC    c_point
                PUBLIC    _c_point

                EXTERN     c_pointxy
                EXTERN     swapgfxbk
                EXTERN     swapgfxbk1


.c_point
._c_point
		push	ix
                ld      ix,2
                add     ix,sp
                ld      l,(ix+2)
                ld      h,(ix+4)
                call    swapgfxbk
                call    c_pointxy
                push    af
                call    swapgfxbk1
                pop     af
		pop	ix
                ld      hl,1
                ret     nz       ;pixel set
                dec     hl
                ret

