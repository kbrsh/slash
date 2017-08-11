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

    ; current
    xor rcx, rcx
    mov cl, byte [rdi]

    ; Initial condition
    cmp cl, 0

    ; Main Loop
    .slashLoop:
      ; Multiply result and prime
      imul rax, qword [prime]

      ; XOR result with current byte
      xor rax, rcx

      ; Rotate right by 7
      ror rax, 7

      ; Loop logic
      add rdi, 1
      mov cl, byte [rdi]
      cmp cl, 0
      jne .slashLoop

    ; Return
    .return:
      ret
