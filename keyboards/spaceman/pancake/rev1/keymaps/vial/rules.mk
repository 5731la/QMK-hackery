VIA_ENABLE = yes
VIAL_ENABLE = yes
MOUSEKEY_ENABLE = yes

# to save space
# from https://github.com/qmk/qmk_firmware/issues/3224k
EXTRAFLAGS += -flto
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MAGIC_ENABLE = no
BOOTMAGIC_ENABLE = no
KEY_OVERRIDE_ENABLE = no
