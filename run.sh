#!/bin/sh
export DYLD_INSERT_LIBRARIES="lib/libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1 
$@
