dir_out := out

all: $(dir_out) hashGenerator stage1 stage2

$(dir_out):
	@mkdir -p $(dir_out)

.PHONY: hashGenerator
hashGenerator:
	@cc hashGenerator.c -o hashGenerator

.PHONY: stage1
stage1: $(dir_out) hashGenerator
	@$(MAKE) -C payload_stage1
	@./hashGenerator $(dir_out)/payload_stage1.bin

.PHONY: stage2
stage2: $(dir_out) hashGenerator
	@$(MAKE) -C payload_stage2
	@./hashGenerator $(dir_out)/payload_stage2.bin

clean:
	@$(MAKE) -C payload_stage1 clean
	@$(MAKE) -C payload_stage2 clean
	@rm -rf $(dir_out) hashGenerator hashGenerator.exe
