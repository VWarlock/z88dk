
; size_t b_vector_read_block(void *dst, size_t n, b_vector_t *v, size_t idx)

XDEF b_vector_read_block_callee

b_vector_read_block_callee:

   pop af
   pop bc
   pop hl
   pop de
   exx
   pop de
   exx
   push af
   
   INCLUDE "../../z80/asm_b_vector_read_block.asm"
