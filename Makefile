ALGO = algorithm/

VISU = visualizer/

all:
	@make -C $(ALGO) all
	@mv $(ALGO)skunz.filler .
	@make -C $(VISU) all
	@mv $(VISU)visualizer skunz.visualizer

clean:
	@make -C $(ALGO) clean
	@make -C  $(VISU) clean

fclean: clean
	@/bin/rm skunz.filler
	@/bin/rm skunz.visualizer

re:
	@make -C $(ALGO) re
	@mv $(ALGO)skunz.filler .
	@make -C $(VISU) re
	@mv $(VISU)visualizer skunz.visualizer
