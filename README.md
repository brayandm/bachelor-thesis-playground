# Bachelor's Thesis Playground

This repository contains the code and data for my bachelor's thesis. The thesis focuses on scheduling the power of Resource Block Groups (RBGs) to serve data frames to users in a network.

## Problem Statement

-   [Codeforces](https://codeforces.com/contest/1885/problem/A)

## TODO

-   [ ] Add experiments snapshot (load, save and summary)
-   [ ] Add the test cases generator
-   [x] Improve the joiner.py to allow classes include other classes
-   [ ] Add total summary experiments to generate overall results, plots, tables and yaml files
-   [ ] Dockerize the project
-   [ ] Dont use constants in the Schedule class, just resize the dimensions of the vectors dynamically

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
