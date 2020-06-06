all: macros

ROOT = ../../../..

%.hduped.hpp: %.hdup
	ruby $(ROOT)/tools/ppduper.rb $< $@ -I 0 -N 256

MACRO = $(wildcard ./*.hdup)
MACRO_DUPPED = $(MACRO:.hdup=.hduped.hpp)

MACRO_SEQ_FOR_EACH = $(foreach var,64 128 256 512 1024 2048 4096 8192,./seq_for_each/it_$(var).hduped.hpp)
$(MACRO_SEQ_FOR_EACH): ./seq_for_each/seq_for_each.hdup
	ruby $(ROOT)/tools/ppduper.rb $< $@ -I 1

TARGET = $(MACRO_DUPPED) $(MACRO_SEQ_FOR_EACH)

macros: $(TARGET)

clean:
	rm -f $(TARGET)