INCLUDES=FuncTraits.h gen_wrap.h RWrap.h Value.h

INST=/usr/include/RWrap

all:

install: $(INCLUDES)
	mkdir -p $(INST)
	cp -a $(INCLUDES) $(INST)
