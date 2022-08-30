# Fast Minimum Degree

This repository contains an implementation of the minimum degree algorithm in
[A Fast Minimum Degree Algorithm and Matching Lower Bound](https://arxiv.org/abs/1907.12119).

## Summary
The minimum degree algorithm is one of the most widely-used heuristics for reducing the cost of solving large sparse systems of linear equations. It has been studied for nearly half a century and has a rich history of bridging techniques from data structures, graph algorithms, and scientific computing. In this repository, we provide an implementation of a simple but novel combinatorial algorithm for computing an exact minimum degree elimination ordering in $O(nm)$ time, which improves on the best known time complexity of $O(n^3)$ and offers practical improvements for sparse systems with small values of $m$.

## Citation

If you find this code useful in your research, please cite the following paper:

```
@inproceedings{cummings2021fast,
  title={A fast minimum degree algorithm and matching lower bound},
  author={Cummings, Robert and Fahrbach, Matthew and Fatehpuria, Animesh},
  booktitle={Proceedings of the 2021 ACM-SIAM Symposium on Discrete Algorithms (SODA)},
  pages={724--734},
  year={2021},
  organization={SIAM}
}
```
