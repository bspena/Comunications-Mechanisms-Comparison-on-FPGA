# Performance Analysis
I have conducted a `full factorial desing` 10<sup>1</sup>5:
* `1 indipendent factor`: array_size
* `10 levels`: choosing 10 powers of 2, in a range from 2<sup>10</sup> (1 KB) to 2<sup>25</sup> (32 MB)
* `5 ripetitions`

resulting in a total of `50 experiments` for each sample. On the other hand, the response variables are `latency` and `throughtput`. 


As follows, there are the results:
<p align="center">
  <img src="img/latencies_throughputs_plot.png" width="900">
</p>