# copy src/py to inst/py
# link inst/py to inst/bin

CWD:=$(shell pwd)

PYSRC = $(wildcard src/py/*.py)
PYINST = $(subst src/,inst/,$(PYSRC))
PYBIN = $(subst /py/,/bin/,$(subst .py,,$(PYINST)) )

py-bin: py-inst $(PYBIN)
	@echo 'make py-bin'

py-inst: $(PYINST)
	@echo 'make py-inst'

# copy src py files to inst py
$(PYINST): $(PYSRC)
	cp $< $@

$(PYBIN): $(PYINST)
	if [ ! -f $@ ]; then ./symln $@ $(CWD)/$<; fi