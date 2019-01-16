Makefile notes

	# create links in an inst directory to files in a src directory

	#search via wildcard for src files
	SRC = $(wildcard temp/src/*)

	# create path in inst dir for links
	INST = $(subst /src/,/inst/,$(SRC))

	# default make target
	all: $(INST)

	# target inst files which depend on src files
	$(INST): $(SRC)
		# create a symlink (using custom script at the time to handle windows symlinks)
		# $@ is the filename from $(INST)
		# $< is the filename from $(SRC)
		./symln $@ $<

