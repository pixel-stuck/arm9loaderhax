.arm.little

payload_addr equ 0x1FFF900

.create "reboot.bin", 0
.arm
    ; Interesting registers and locations to keep in mind, set before this code is ran:
    ; - sp + 0x3A8 - 0x70: FIRM path in exefs.
    ; - r7 (which is sp + 0x3A8 - 0x198): Reserved space for file handle
    ; - *(sp + 0x3A8 - 0x198) + 0x28: fread function.

    pxi_wait_recv:
        ldr r2, =0x44846
        ldr r0, =0x10008000
        readPxiLoop1:
            ldrh r1, [r0, #4]
            lsls r1, #0x17
            bmi readPxiLoop1
            ldr r0, [r0, #0xC]
        cmp r0, r2
        bne pxi_wait_recv

    ; Copy the last digits of the wanted firm to the 5th byte of the payload
    add r2, sp, #0x3A8 - 0x70
    ldr r0, [r2, #0x27]
    ldr r1, =payload_addr + 4
    str r0, [r1]
    ldr r0, [r2, #0x2B]
    str r0, [r1, #4]

    ; Set kernel state
    mov r0, #0
    mov r1, #0
    mov r2, #0
    mov r3, #0
    swi 0x7C

    goto_reboot:
        ; Jump to reboot code
        ldr r0, =(kernelcode_start - goto_reboot - 12)
        add r0, pc
        swi 0x7B

    die:
        b die

.pool

.align 4
    ; Flush cache
    kernelcode_start:
    mov r1, #0                          ; segment counter
    outer_loop:
        mov r0, #0                      ; line counter

        inner_loop:
            orr r2, r1, r0                  ; generate segment and line address
            mcr p15, 0, r2, c7, c14, 2      ; clean and flush the line
            add r0, #0x20                   ; increment to next line
            cmp r0, #0x400
            bne inner_loop

        add r1, #0x40000000
        cmp r1, #0
        bne outer_loop

    mcr p15, 0, r1, c7, c10, 4              ; drain write buffer

    ; Flush instruction cache
    mcr p15, 0, r1, c7, c5, 0

    ; Jump to payload
    ldr r0, =payload_addr
    bx r0

.pool
.close
