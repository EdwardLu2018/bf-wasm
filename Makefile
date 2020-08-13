all: x86 wasm

x86:
	gcc -O3 bf.c bf_mem.c bf_stack.c bf_jmp_dict.c -o bf

wasm:
	emcc -O3 bf_wasm.c bf_mem.c bf_stack.c bf_jmp_dict.c \
	-s MODULARIZE=1 -s EXPORT_NAME='BFWASM' -s EXPORTED_FUNCTIONS='['_malloc', '_free']' \
	-s ASSERTIONS=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='['ccall', 'cwrap']' -s WASM=1 -o bf.js

serve:
	python3 -m http.server
