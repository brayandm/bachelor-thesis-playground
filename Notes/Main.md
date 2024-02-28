# Need to check
- In commit 16af07e150bdebce4efa84b400abef2a359676a7 if we set iterations to 1 and comment the following code then we got:

Total delivered: 120 / 150
Total delivered: 443 / 829
Total delivered: 184 / 184

```
if (TTIOccupation[t] == true)

continue;
```
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

# Machine Learning
- Because the funcion $f(x) = (x <= TBS[i])$ is not differentiable it will be difficult to make a gradient descent or Train a Neural Network  

## [[Formulas]]

## Algorithms

- [[Multiple iteration - single frame]]
- [[Multiple Iteration - sort frames by power consumption]]

## References

- [[HW ICPC Fall Challenge 2023 by gvastash.pdf]]
	- [[References/HW ICPC Fall Challenge 2023 by gvastash/Notes|Notes]]
- [[Deterministic scheduling of periodic datagrams for low latency in 5G and beyond.pdf]]
	- [[References/Deterministic scheduling of periodic datagrams for low latency in 5G and beyond/Notes|Notes]]
- [[Radio resource allocation in 5G wireless networks.pdf]]
	- [[References/Radio resource allocation in 5G wireless networks/Notes|Notes]]
