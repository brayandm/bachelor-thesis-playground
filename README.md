# Bachelor's Thesis Playground

This repository contains the code and data for my bachelor's thesis. The thesis focuses on scheduling the power of Resource Block Groups (RBGs) to serve data frames to users in a network.

## Problem Statement

-   [Codeforces](https://codeforces.com/contest/1885/problem/A)

## TODO

-   [ ] Add experiments snapshot (load, save and summary)
-   [ ] Add the test cases generator
-   [ ] Add total summary experiments to generate overall results, plots, tables and yaml files
-   [ ] Dockerize the project
-   [ ] Try to do something to not search code in old experiments, maybe some regular expresion
-   [ ] Create Script to Generate Algorithm's Template
-   [ ] Make a CMake generator to avoid updating CMake Manually
-   [x] Update joined and snapshots to include new folder Algorithms

## Commands

### Build the experiment

```bash
bash build.sh
```

### Run the experiment

```bash
bash run.sh
```

### Build and run the experiment

```bash
bash br.sh
```

### Test the experiment

```bash
bash test.sh
```

### Save the experiment

```bash
bash save.sh
```

### Amalgamate the experiment

```bash
bash join.sh
```

### Update CMakeLists.txt when adding new Classes or Algorithms

```bash
bash cmakegen.sh
```
