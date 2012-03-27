#!/bin/bash

valgrind --tool=massif --time-unit=B --stacks=yes ./demo
valgrind --tool=massif --time-unit=B --pages-as-heap=yes ./demo
ms_print ./massif.out.8520 | less

# To samo dla container_test


