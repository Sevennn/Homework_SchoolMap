#Homework about guidance in SYSU.

## Build

### Dependencies

+ build-essential
+ node
+ react-navtive (code not here)

### How to

Just
```
make
```

## Run

### Before Run

```
mkfifo -m 0666 /tmp/SCHOOLMAP_N2C
mkfifo -m 0666 /tmp/SCHOOLMAP_C2N
```

### Run
```
cd bin/
./main < /tmp/SCHOOLMAP_N2C > /tmp/SCHOOLMAP_C2N
```

In other console

```
node node_pipe.js
```
