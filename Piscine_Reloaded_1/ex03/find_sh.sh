find . -type f -name '*.sh' -exec sh -c 'for n; do basename "$n" .sh; done' sh {} +
