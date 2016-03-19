.PHONY : stage1 screen_init stage2

OUTDIR = out

all : $(OUTDIR) stage1 screen_init stage2

$(OUTDIR):
	@[ -d $(OUTDIR) ] || mkdir -p $(OUTDIR)

screen_init:
	@$(MAKE) -C screen_init

stage1:
	@$(MAKE) -C payload_stage1
	@mv payload_stage1/payload_stage1.bin $(OUTDIR)

stage2:
	@[ -d payload_stage2/data ] || mkdir -p payload_stage2/data
	@mv screen_init/screen_init.bin payload_stage2/data
	@$(MAKE) -C payload_stage2
	@mv payload_stage2/payload_stage2.bin $(OUTDIR)

clean:
	@$(MAKE) -C payload_stage1 clean
	@$(MAKE) -C screen_init clean
	@$(MAKE) -C payload_stage2 clean
	@rm -rf $(OUTDIR)
