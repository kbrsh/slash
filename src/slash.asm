SECTION .data
  ; Prime constant
  prime dq 0xA1720315130235

SECTION .text
  DEFAULT REL

  ; Slash
  GLOBAL _slash
  _slash:
    ; Initialize variables
    mov rax, 1 ; result
    movsx rcx, byte [rdi] ; current

    ; Initial condition
    cmp byte [rcx], 0
    je .return

    ; Store result and prime in 128 bit registers
    movq xmm0, [prime]
    movq xmm1, rax

    ; Main Loop
    .slashLoop:
      ; Perform carry-less multiplication of result and prime
      vpclmulqdq xmm1, xmm0, xmm1, 64

      ; XOR result with current
      movq xmm3, [rcx]
      pxor xmm1, xmm3

      ; Loop logic
      inc rcx
      cmp byte [rcx], 0
      jne .slashLoop

    ; Prepare result for return
    movq rax, xmm1

    ; Return
    .return:
      ret
