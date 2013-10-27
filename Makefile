MAKE=make

.PHONY: default
default:
	cd src; $(MAKE) install
	mv src/fd.img .

.PHONY: clean
clean:
	cd src; $(MAKE) clean
	rm -rf fd.img
