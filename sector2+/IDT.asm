[extern _idt]
idtDescriptor:
  dw 4095
  dq _idt


%macro pushall 0
  	push rax
  	push rcx
  	push rdx
  	push r8
  	push r9
  	push r10
  	push r11
%endmacro

%macro popall 0
    pop r11
  	pop r10
  	pop r9
  	pop r8
  	pop rdx
  	pop rcx
  	pop rax
%endmacro

[extern isr1_handler]

isr1:
  pushall
  call isr1_handler
  popall
  iretq
global isr1

LoadIDT:
  lidt[idtDescriptor]
  sti
  ret
GLOBAL LoadIDT