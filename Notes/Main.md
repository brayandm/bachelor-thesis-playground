# General Notes

-   There are $R$ RBGs
-   Each RBG has $K$ cells
-   At any point of time if all users correspond only one RBG
    and vice versa the formula for $S_{nt}^{(k)} = S_{0,rnt}^{(k)} \times P_{rnt}^{(k)}$, so the amount of data
    transmitted is $g_j = W \times \sum_{t=t_{0,j}}^{t_{1,j}}\sum_{k}\sum_{r}b_{rnt}^{(k)}\times \log_{2}(1 + S_{0,rnt}^{(k)} \times P_{rnt}^{(k)})$
-   It doesn't make sense to assign two RBGs to the same user
    beacuse the signal received by many RBGs is averaged geometrically
-   It is guaranteed that each user has at most one frame at each TTI
-   The total amount of power for an specific cell at any time from the same RBG should be less than $4$
-   The total amount of power for an specific cell at any time from all RBGs should be less than $R$

## [[Formulas]]

## Algorithms

- [[Multiple iteration - single frame]]

## References

- [[hw icpc fall challenge 2023 by gvastash.pdf]]
- [[99357_GUIRAUD_2021_archivage.pdf]]
- [[73042_MAAZ_2017_archivage.pdf]]
