
; size_t b_vector_write_block(void *src, size_t n, b_vector_t *v, size_t idx)

XLIB b_vector_write_block

LIB asm_b_vector_write_block

b_vector_write_block:

   pop af
   pop bc
   pop hl
   pop de
   exx
   pop hl
   
   push hl
   exx
   push de
   push hl
   push bc
   push af
   
   jp asm_b_vector_write_block
