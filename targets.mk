
# BOARD_TAG    = atmegang
# BOARD_SUB    = atmega168
# MONITOR_PORT = /dev/ttyACM0
# ARDUINO_DIR  = /usr/bin/arduino
# AVR_TOOLS_DIR = /usr
# BOARDS_TXT = ./platform/boards.txt 
# include platform/Arduino.mk

# --- SETUP ---
setup: cleanup
	sudo apt install arduino-mk python3-pip arduino
	pip3 install pyserial

cleanup:
	rm -rf build

# --- TEST TARGETS ---
offtest: test # off target test

ontest: test # on target test

.PHONY: cleanup