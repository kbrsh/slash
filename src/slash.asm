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
    mov rcx, rdi ; current

    ; Initial condition
    cmp byte [rcx], 0
    je .return

    ; Main Loop
    .slashLoop:
      ; Perform carry-less multiplication of result and prime
      clm rax, prime

      ; XOR result with current
      xor rax, byte [rcx]

      ; Loop logic
      inc rcx
      cmp byte [rcx], 0
      jne .slashLoop

    ; Return
    .return:
      ret
