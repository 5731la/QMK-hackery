VIA_ENABLE = yes
VIAL_ENABLE = yes
#VIAL_INSECURE = yes


# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF

VPATH += keyboards/cannonkeys/lib/satisfaction75
SRC += satisfaction_encoder.c \
      satisfaction_oled.c \
      satisfaction_core.c



OS_DETECTION_ENABLE = yes

CONSOLE_ENABLE = yes
