**Maximize P:**

$$ P : \max \sum_{j} f_{j} $$

  

<br><br>

**Data frame $j$ was delivered:**

  

$$

f_{j} = \begin{cases} 1, & g_{j} \geq TBS_{j} \\ 0, & g_{j} < TBS_{j} \end{cases}

$$

  

<br><br>

**Power assigned 0/1:**

$$ b_{rnt}^{(k)} \in \{0, 1\} $$

  

<br><br>

**Power assigned Exact amount :**

$$ p_{rnt}^{(k)} \geq 0, \quad \sum_{r} \sum_{n} p_{rnt}^{(k)} \leq R, \quad \sum_{n} p_{rnt}^{(k)} \leq 4 $$

  

<br><br>

**Actual transmitted bits for the frame:**

$$ g_{j} = W \times \sum_{i=t_{0,j}}^{t_{1,j}} \sum_{k} \sum_{r} b_{rnt}^{(k)} \times \log_{2} \left( 1 + s_{nt}^{(k)} \right) $$

  

<br><br>

**Expression of total SINR:**

$$ s_{nt}^{(k)} = \left( \prod_{r, b_{rnt}^{(k)}=1} s_{rnt}^{(k)} \right)^\frac{1}{\sum_r b_{rnt}^{(k)}}  $$

<br><br>

**Expression of SINR per cell:**
$$

s_{rnt}^{(k)} = \frac{s_{0,rnt}^{(k)}\times p_{rnt}^{(k)} \times \prod_{m\neq n}e^{d_{mrn}^{(k)}\times b_{rmt}^{(k)}}}{1 + \sum_{k' \neq k,n' \neq n} s_{0,rnt}^{(k')}\times p_{rn't}^{(k')}\times e^{-d_{n'rn}^{(k')}}}

$$