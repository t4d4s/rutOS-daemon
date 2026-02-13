SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o)
TARGET_EXEC := tuyad

CFLAGS := -Wall
CPPFLAGS := -I$(CURDIR)/../argp-standalone-1.3
LDFLAGS := -l:liblink_core.so -l:libmiddleware_implementation.so \
           -l:libplatform_port.so -l:libutils_modules.so \
           -largp -lblobmsg_json -lubox -lubus

.PHONY: default_target
default_target: all

.PHONY: all
all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

./%.o: ./%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET_EXEC) $(OBJS)
