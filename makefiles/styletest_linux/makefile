SOURCEDIR = ../../uCNC/src/modules/style
BUILDDIR = build
CFLAGS = -lx11 -I../../blackpill_f411ce/lvgl/src -I$(SDL_PATH)/include

OBJ = styletest.o \
			$($(wildcard $(SOURCEDIR)/*.c):.c=.o)

OBJ_PREF = $(addprefix $(BUILDDIR)/,$(OBJ))

$(BUILDDIR)/styletest.o: main.c
	gcc -o $@ -c $< $(CFLAGS)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

