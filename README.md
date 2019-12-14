# CS31106 Homework

## build

`cmake --build build --config Debug --target all -- -j 4`

## generate translation templates

`find . -iname "*.c" | xargs xgettext --from-code=UTF-8 -o CS31106.pot -k_`