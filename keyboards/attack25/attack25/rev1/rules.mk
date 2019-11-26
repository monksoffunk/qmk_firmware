# Build Options
# If you need, add below.

ifeq ($(findstring matrix,$(ATTACK25)), matrix)
	SRC += rgb_matrix_layer.c
endif
