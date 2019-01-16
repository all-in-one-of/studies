Makefile notes

	# take files create links in an inst directory to files in a src directory

	SRC = $(wildcard temp/src/*)
	INST = $(subst /src/,/inst/,$(SRC))

	all: $(INST)

	$(INST): $(SRC)
		./symln $@ $<

