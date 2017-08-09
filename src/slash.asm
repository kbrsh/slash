SECTION .data
  ; Prime constant
  prime dq 0xA171020315130201

SECTION .text
  DEFAULT REL

  ; Slash
  GLOBAL _slash
  _slash:
    ; Initialize variables
    mov rax, 1 ; result
    mov rcx, rdi ; current

    ; Initial condition
    cmp rcx, 0
    je .return

    ; Main Loop
    .slashLoop:
      ; Perform carry-less multiplication of result and prime
      clm rax, qword [prime]

      ; XOR result with current
      xor rax, rcx

      ; Rotate right by 7
      ror rax, 7

      ; Loop logic
      inc rcx
      cmp rcx, 0
      jne .slashLoop

    ; Return
    .return:
      ret
