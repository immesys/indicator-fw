APPLICATION = indicator
RIOTBASE = $(CURDIR)/../RIOT-OS
BOARD = hamilton
USEMODULE += rtt_stdio
CFLAGS += -DRTT_STDIO_DISABLE_STDIN
CFLAGS += -DSOCK_HAS_IPV6
# Radio
USEMODULE += at86rf233

# Sensors
USEMODULE += at30ts74 # temperature sensor

USEMODULE += mma7660 # accelerometer

USEMODULE += xtimer

# networking
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules for IPv6 and UDP
USEMODULE += gnrc_ipv6
USEMODULE += gnrc_udp
# Add also the shell, some shell commands
USEMODULE += netstats_l2
USEMODULE += netstats_ipv6

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
# CFLAGS += -DDEVELHELP

DEFAULT_CHANNEL = 24
CFLAGS += -DDEFAULT_CHANNEL=$(DEFAULT_CHANNEL)

QUIET ?= 1

FEATURES_REQUIRED += periph_timer

include $(RIOTBASE)/Makefile.include
