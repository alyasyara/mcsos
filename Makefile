.PHONY: proof clean

proof:
	./tools/scripts/build_probe.sh

clean:
	rm -rf build/proof
