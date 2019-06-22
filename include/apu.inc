.segment "CODE"

.struct APU
  channels .byte
.endstruct

; x = APU
; y = bits 0:7 of timer
pulse1_play:
  lda APU::channels, x
  ora #%00000001                                                                ; enable pulse channel 1
  sta APU::channels, x
  sta $4015                                                                     ; $4015 = APU: status
                                                                                ; [0:0] enable pulse channel 1
                                                                                ; [1:1] enable pulse channel 2
                                                                                ; [2:2] enable triangle channel
                                                                                ; [3:3] enable noise channel
                                                                                ; [4:4] enable delta modulation channel
                                                                                ; [5:7] reserved
  sty $4002                                                                     ; $4002 = APU: bits 0:7 of pulse 1 timer
  lda #$0                                                                       ; set high bits of timer
  sta $4003                                                                     ; $4003 = APU: length counter load and bits 8:10 of pulse 1 timer
                                                                                ; [0:2] bits 8:10 of timer
                                                                                ; [3:7] length counter load
  lda #%10111111                                                                ; set pulse options
  sta $4000                                                                     ; $4000 = APU: pulse 1 options
                                                                                ; [0:3] volume/envelope divider period
                                                                                ; [4:4] constant volume/envelope
                                                                                ; [5:5] length counter halt
                                                                                ; [6:7] duty cycle
  rts


; x = APU
; y = bits 0:7 of timer
pulse2_play:
  lda APU::channels, x
  ora #%00000010                                                                ; enable pulse channel 2
  sta APU::channels, x
  sta $4015
  sty $4006                                                                     ; $4002 = APU: bits 0:7 of pulse 2 timer
  lda #$0                                                                       ; set high bits of timer
  sta $4007                                                                     ; $4003 = APU: length counter load and bits 8:10 of pulse 2 timer
                                                                                ; [0:2] bits 8:10 of timer
                                                                                ; [3:7] length counter load
  lda #%10111111                                                                ; set pulse options
  sta $4004                                                                     ; $4000 = APU: pulse 2 options
                                                                                ; [0:3] volume/envelope divider period
                                                                                ; [4:4] constant volume/envelope
                                                                                ; [5:5] length counter halt
                                                                                ; [6:7] duty cycle
  rts