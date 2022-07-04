cc = gcc
prom = main
deps = $(shell find ./include -name "*.h")
src = $(shell find ./src -name "*.c")
obj = $(src:%.c=%.o) 

$(prom): $(obj)
	$(cc) -lreadline -Wparentheses -o $(prom) $(obj)
 
%.o: %.c $(deps)
	$(cc) -c $< -o $@
 
clean:
	rm -rf $(obj) $(prom)