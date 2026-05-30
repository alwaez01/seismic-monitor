CC     = gcc
CFLAGS = -Wall --pedantic

BIN = bin

SIM_SRC = sim/src/sim_main.c sim/src/sim_parser.c sim/src/sim_generator.c
MON_SRC = mon/src/mon_main.c mon/src/mon_parser.c mon/src/mon_queue.c mon/src/mon_stats.c mon/src/mon_display.c

SIM_OBJ = $(patsubst sim/src/%.c, $(BIN)/%.o, $(SIM_SRC))
MON_OBJ = $(patsubst mon/src/%.c, $(BIN)/%.o, $(MON_SRC))

all: $(BIN) simulator monitor

simulator: $(SIM_OBJ)
	$(CC) $(CFLAGS) -o $(BIN)/simulator $(SIM_OBJ)

monitor: $(MON_OBJ)
	$(CC) $(CFLAGS) -o $(BIN)/monitor $(MON_OBJ) -lm

$(BIN)/%.o: sim/src/%.c
	$(CC) $(CFLAGS) -I sim/include -c $< -o $@

$(BIN)/%.o: mon/src/%.c
	$(CC) $(CFLAGS) -I mon/include -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)