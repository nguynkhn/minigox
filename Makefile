CC      = gcc
CFLAGS  = -Wall -Wextra
CFLAGS += -O2 -std=c11
LDFLAGS =

PLATFORM ?= ???
OBJ       = minigox.o
OUT       = minigox_$(PLATFORM)

RM = rm -f

ifeq ($(PLATFORM),win32)
	CFLAGS += -DMINIGOX_WIN32
	RM      = del /Q
endif
ifeq ($(PLATFORM),linux)
	CFLAGS  += -DMINIGOX_LINUX
	LDFLAGS += -lxkbcommon
endif

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	$(RM) $(OUT) $(OBJ)
