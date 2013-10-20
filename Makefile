MAKE=make

.PHONY: default
default:
	cd src; $(MAKE) tar
	mv src/fd.img .

.PHONY: clean
clean:
	cd src; $(MAKE) clean
	rm -rf fd.img
